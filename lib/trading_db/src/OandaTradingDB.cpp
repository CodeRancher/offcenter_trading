/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   OandaTradingDB.cpp
 * @author Scott Brauer
 * @date   04-06-2021
 */

#include "easylogging++.h"

#include "offcenter/trading/db/oanda/OandaTradingDB.hpp"
#include "offcenter/trading/db/oanda/oanda_data_tables.hpp"
#include "offcenter/trading/datatypes/oanda/InstrumentSoci.hpp"
#include "offcenter/trading/datatypes/oanda/FinancingDayOfWeekSoci.hpp"

namespace offcenter {
namespace trading {
namespace db {
namespace oanda {

OandaTradingDB::OandaTradingDB():
		m_sessionPoolManager(g_sessionPoolSize)
{
	// TODO Auto-generated constructor stub

}

OandaTradingDB::~OandaTradingDB()
{
	// TODO Auto-generated destructor stub
}

void OandaTradingDB::initialize(const offcenter::common::soci::MySQLOptions &options)
{
	m_sessionPoolManager.open(options);
}

void OandaTradingDB::instrumentCreate(const offcenter::trading::datatypes::oanda::InstrumentWithIDs &instrument)
{
	const std::string insert = R"###(
	INSERT INTO oanda_instrument
	(
		name,
		instrument_type_id,
		display_name,
		pip_location,
		display_precision,
		trade_units_precision,
		minimum_trade_size,
		maximum_trailing_stop_distance,
		minimum_guaranteed_stop_loss_distance,
		minimum_trailing_stop_distance,
		maximum_position_size,
		maximum_order_units,
		margin_rate,
		commission_commission,
		commission_units_traded,
		commission_minimum_commission,
		guaranteed_stop_loss_order_mode,
		guaranteed_stop_loss_order_execution_premium,
		guaranteed_stop_loss_order_level_restriction_volume,
		guaranteed_stop_loss_order_level_restriction_priceRange,
		financing_longRate,
		financing_shortRate
	)
	VALUES(
		:name,
		:instrument_type_id,
		:display_name,
		:pip_location,
		:display_precision,
		:trade_units_precision,
		:minimum_trade_size,
		:maximum_trailing_stop_distance,
		:minimum_guaranteed_stop_loss_distance,
		:minimum_trailing_stop_distance,
		:maximum_position_size,
		:maximum_order_units,
		:margin_rate,
		:commission_commission,
		:commission_units_traded,
		:commission_minimum_commission,
		:guaranteed_stop_loss_order_mode,
		:guaranteed_stop_loss_order_execution_premium,
		:guaranteed_stop_loss_order_level_restriction_volume,
		:guaranteed_stop_loss_order_level_restriction_priceRange,
		:financing_longRate,
		:financing_shortRate
	);
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::transaction transInstrument(session());
	::soci::statement st = (session().prepare << insert, ::soci::use(instrument));
	st.execute(true);
	transInstrument.commit();

	::soci::transaction transFinancingDayOfWeekSave(session());
	offcenter::trading::datatypes::oanda::Instrument savedInstrument;
	instrumentRead(savedInstrument, instrument.name);
	financingDayOfWeekCreate(instrument.financingDaysOfWeek, savedInstrument.instrument_id);
	transFinancingDayOfWeekSave.commit();

}

void OandaTradingDB::instrumentRead(
        offcenter::trading::datatypes::oanda::Instrument &instrument,
        const std::string name)
{
	const std::string read = R"###(
		SELECT * FROM v_oanda_instrument WHERE name = :name;
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << read, ::soci::into(instrument), ::soci::use(name));
	st.execute(true);
	//st.fetch();
}

void OandaTradingDB::instrumentRead(
        offcenter::trading::datatypes::oanda::Instrument &instrument,
        unsigned instrument_id)
{
	const std::string read = R"###(
		SELECT * FROM v_oanda_instrument WHERE instrument_id = :instrument_id;
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << read, ::soci::into(instrument), ::soci::use(instrument_id));
	st.execute(true);
	//st.fetch();
}

void OandaTradingDB::instrumentUpdate(
        const offcenter::trading::datatypes::oanda::Instrument &instrument)
{
	const std::string sql = R"###(
	UPDATE oanda_instrument
	SET
		name = :name,
		instrument_type_id = :instrument_type_id,
		display_name = :display_name,
		pip_location = :pip_location,
		display_precision = :display_precision,
		trade_units_precision = :trade_units_precision,
		minimum_trade_size = :minimum_trade_size,
		maximum_trailing_stop_distance = :maximum_trailing_stop_distance,
		minimum_guaranteed_stop_loss_distance = :minimum_guaranteed_stop_loss_distance,
		minimum_trailing_stop_distance = :minimum_trailing_stop_distance,
		maximum_position_size = :maximum_position_size,
		maximum_order_units = :maximum_order_units,
		margin_rate = :margin_rate,
		commission_commission = :commission_commission,
		commission_units_traded = :commission_units_traded,
		commission_minimum_commission = :commission_minimum_commission,
		guaranteed_stop_loss_order_mode = :guaranteed_stop_loss_order_mode,
		guaranteed_stop_loss_order_execution_premium = :guaranteed_stop_loss_order_execution_premium,
		guaranteed_stop_loss_order_level_restriction_volume = :guaranteed_stop_loss_order_level_restriction_volume,
		guaranteed_stop_loss_order_level_restriction_priceRange = :guaranteed_stop_loss_order_level_restriction_priceRange,
		financing_longRate = :financing_longRate,
		financing_shortRate = :financing_shortRate
	WHERE
		instrument_id = :instrument_id;
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::transaction transInstrument(session());
	::soci::statement st = (session().prepare << sql, ::soci::use(instrument));
	st.execute(true);

	::soci::transaction transFinancingDayOfWeekSave(session());
	financingDayOfWeekUpdate(instrument.financingDaysOfWeek, instrument.instrument_id);
	transInstrument.commit();
}

/**
 *
 */
void OandaTradingDB::instrumentDelete(const std::string name)
{
	const std::string sql = R"###(
		DELETE FROM oanda_instrument WHERE name = :name;
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(name));
	st.execute();
}

/**
 *
 */
void OandaTradingDB::instrumentDelete(unsigned instrument_id)
{
	const std::string sql = R"###(
		DELETE FROM oanda_instrument WHERE instrument_id = :instrument_id;
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(instrument_id));
	st.execute();
}

/**
 *
 */
unsigned int OandaTradingDB::instrumentCount()
{
	return 0;
}

/**
 *
 */
void OandaTradingDB::financingDayOfWeekCreate(
		const offcenter::trading::datatypes::oanda::FinancingDayOfWeek &financingDayOfWeek,
		unsigned int instrument_id)
{
	const std::string insert = R"###(
	INSERT INTO oanda_financing_day_of_week
	(
		instrument_id,
		day_of_week_id,
		days_charged
	)
	VALUES(
		:instrument_id,
		:day_of_week_id,
		:days_charged
	);
	)###";

	offcenter::trading::datatypes::oanda::FinancingDayOfWeek tmpFinancingDayOfWeek = financingDayOfWeek;
	if (instrument_id > 0) {
		tmpFinancingDayOfWeek.instrument_id = instrument_id;
	}
	offcenter::common::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << insert, ::soci::use(tmpFinancingDayOfWeek));
	st.execute(true);
}

/**
 *
 */
void OandaTradingDB::financingDayOfWeekCreate(
		const std::vector<offcenter::trading::datatypes::oanda::FinancingDayOfWeek> &financingDaysOfWeek,
		unsigned int instrument_id)
{
	for (offcenter::trading::datatypes::oanda::FinancingDayOfWeek financingDayOfWeek : financingDaysOfWeek) {
		financingDayOfWeekCreate(financingDayOfWeek, instrument_id);
	}
}

void OandaTradingDB::financingDayOfWeekUpdate(
        const offcenter::trading::datatypes::oanda::FinancingDayOfWeek &financingDayOfWeek)
{
}

void OandaTradingDB::financingDayOfWeekUpdate(
        const std::vector<offcenter::trading::datatypes::oanda::FinancingDayOfWeek> &financingDayOfWeek,
        unsigned int instrument_id)
{
	const std::string sql = R"###(
		SELECT financing_day_of_week_id
		FROM oanda_financing_day_of_week
		WHERE instrument_id = :instrument_id;
	)###";

	offcenter::common::soci::Session session(m_sessionPoolManager);
	std::vector<unsigned> financingDayOfWeekIDs;
	::soci::statement st = (session().prepare << sql, ::soci::into(financingDayOfWeekIDs), ::soci::use(instrument_id));
	st.execute(true);

	for (unsigned int financingDayOfWeekID : financingDayOfWeekIDs) {

	}
}

} /* namespace oanda */
} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

