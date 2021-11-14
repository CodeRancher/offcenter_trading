/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the );
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
 * @file   TradingDB.cpp
 * @author Scott Brauer
 * @date   03-19-2021
 */

#include <iomanip>
#include <string>
#include <cassert>

#include "easylogging++.h"
#include "date/date.h"

#include "offcenter/trading/common/Exceptions.hpp"
#include "offcenter/trading/db/TradingDB.hpp"

#include "../../data_types/include/offcenter/trading/datatypes/common/ForexDateTime.hpp"
#include "offcenter/trading/datatypes/InstrumentSoci.hpp"
#include "offcenter/trading/datatypes/CandlestickDataSeriesSoci.hpp"
#include "offcenter/trading/datatypes/CandlestickDataSoci.hpp"
#include "offcenter/trading/datatypes/LookupTableDataSoci.hpp"
#include "offcenter/soci/Transaction.hpp"

namespace offcenter {
namespace trading {
namespace db {

/**
 *
 */
TradingDB::TradingDB():
		m_sessionPoolManager(g_sessionPoolSize)
{
	// TODO Auto-generated constructor stub

}

/**
 *
 */
TradingDB::~TradingDB()
{
	// TODO Auto-generated destructor stub
}

/**
 * Initialize and open the database
 *
 * @param options connection options to the MySQL database
 */
void TradingDB::initialize(const offcenter::soci::MySQLOptions &options)
{
	m_sessionPoolManager.open(options);
}

/**
 * Create an instrument record in the database
 *
 * @param instrument Instrument record to add to the database
 */
void TradingDB::instrumentCreate(const offcenter::trading::datatypes::Instrument &instrument)
{
	const std::string sql = R"###(
		INSERT INTO instrument
		(
			name,
			display_name
		)
		VALUES(
			:name,
			:display_name
		);
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(instrument));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session);
}

/**
 *	Read an instrument based on name
 *
 *	@param[out] instrument Instrument record for read
 *	@param name Name of instrument to read
 */
void TradingDB::instrumentRead(
        offcenter::trading::datatypes::Instrument &instrument,
        const std::string& name)
{
	const std::string read = R"###(
		SELECT * FROM instrument WHERE name = :name;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << read, ::soci::into(instrument), ::soci::use(name));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction);
}

/**
 * Read an instrument based on instrument id
 *
 *	@param instrument Instrument record for read
 *	@param instrument_id Instrument id of instrument to read
 */
void TradingDB::instrumentRead(
        offcenter::trading::datatypes::Instrument &instrument,
        unsigned instrument_id)
{
	const std::string read = R"###(
		SELECT * FROM instrument WHERE instrument_id = :instrument_id;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << read, ::soci::into(instrument), ::soci::use(instrument_id));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction);
}

/**
 * Update and instrument based on instrument id
 *
 *	@param instrument Instrument record to update
 */
void TradingDB::instrumentUpdate(
        const offcenter::trading::datatypes::Instrument &instrument)
{
	const std::string sql = R"###(
		UPDATE instrument
		SET
			name = :name,
			display_name = :display_name
		WHERE
			instrument_id = :instrument_id;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(instrument));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session);
}

/**
 * Delete an instrument based on name
 *
 * @param name Name of instrument to delete
 */
void TradingDB::instrumentDelete(const std::string& name)
{
	const std::string sql = R"###(
		DELETE FROM instrument WHERE name = :name;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(name));
	executeStatement(st, SOCIDataExchange::WithoutDataExchange, SOCITransaction::WithTransaction, &session);
}

/**
 * Delete an instrument based on instrument id
 *
 * @param instrument_id Instrument ID of instrument to delete
 */
void TradingDB::instrumentDelete(unsigned instrument_id)
{
	const std::string sql = R"###(
		DELETE FROM instrument WHERE instrument_id = :instrument_id;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(instrument_id));
	executeStatement(st, SOCIDataExchange::WithoutDataExchange, SOCITransaction::WithTransaction, &session);
}

/**
 * Count number of instruments
 *
 * @return Number of instruments
 */
unsigned int TradingDB::instrumentsCount()
{
	const std::string sql = R"###(
		SELECT COUNT(*)
		FROM instrument
	)###";

	int count = 0;
	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::into(count));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction);
	return count;
}

/**
 * Create a candlestick data series
 *
 * If the candlestick data series exists and updateOnDuplicate is true, then the saved series will be updated.
 *
 * @param candlestick_data_series The candlestick data series to create
 * @param updateOnDuplicate Update the candlestick data series if it already exists
 */
void TradingDB::candlestickDataSeriesCreate(
        const offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series,
        bool updateOnDuplicate)
{
	const std::string insert = R"###(
		INSERT INTO candlestick_data_series (instrument_id, broker_data_source_id, candlestick_granularity_id)
		VALUES(
			(SELECT instrument_id FROM instrument i WHERE i.name = :instrument_name),
			(SELECT broker_data_source_id FROM v_broker_source bs WHERE bs.broker_name = 'oanda' AND bs.source_name = :broker_data_source_name),
			(SELECT candlestick_granularity_id FROM candlestick_granularity cg WHERE cg.name = :candlestick_granularity_name)
		);
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << insert, ::soci::use(candlestick_data_series));
	try {
		executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session);
	} catch (offcenter::trading::common::DuplicateRecord const& e) {
		LOG(WARNING) << "Duplicate record found. Updating record." << e.what();
		candlestickDataSeriesUpdate(candlestick_data_series);
	}
}

/**
 * Read a candlestick data series based on broker data source name, broker name,
 *   instrument name, and candlestick granularity name.
 *
 * @param[out] candlestick_data_series		Candlestick data series information
 * @param      broker_data_source_name		Data source name
 * @param      broker_name					Broker name
 * @param      instrument_name				Instrument name
 * @param      candlestick_granularity_name	Candlestick granularity name
 */
void TradingDB::candlestickDataSeriesIDRead(
        offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series,
        const std::string& broker_data_source_name,
        const std::string& broker_name,
        const std::string& instrument_name,
        const std::string& candlestick_granularity_name)
{
	const std::string sql = R"###(
		SELECT candlestick_data_series_id
		FROM candlestick_data_series cds
		LEFT JOIN (instrument i, v_broker_source bs, candlestick_granularity cg)
		ON
		(
			cds.instrument_id = i.instrument_id 
			AND cds.broker_data_source_id = bs.broker_data_source_id 
			AND cds.candlestick_granularity_id = cg.candlestick_granularity_id
		)
		WHERE 
			i.name = :instrument_name
			AND bs.broker_name = :broker_name
			AND bs.source_name = :broker_data_source_name
			AND cg.name = :candlestick_granularity_name
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql,
			::soci::into(candlestick_data_series.candlestick_data_series_id),
			::soci::use(instrument_name, "instrument_name"),
			::soci::use(broker_name, "broker_name"),
			::soci::use(broker_data_source_name, "broker_data_source_name"),
			::soci::use(candlestick_granularity_name, "candlestick_granularity_name"));

	if (!executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session)) {
		// If empty recordset
		LOG(ERROR) << "candlestickDataSeriesIDRead returned an empty recordset: "
				<< broker_name << ", " << broker_data_source_name << ", "
				<< instrument_name << ", " << candlestick_granularity_name;
		throw offcenter::trading::common::EmptyRecordset("candlestick_data_series",
				broker_name + ", " + broker_data_source_name + ", "
				+ instrument_name + ", " + candlestick_granularity_name);
	} else {
		candlestick_data_series.broker_data_source_name = broker_data_source_name;
		candlestick_data_series.broker_name = broker_name;
		candlestick_data_series.instrument_name = instrument_name;
		candlestick_data_series.candlestick_granularity_name = candlestick_granularity_name;
	}
}

/**
 * Read all candlestick data series
 *
 * @param[out] candlestick_data_series Vector of candlestick data series
 */
void TradingDB::candlestickDataSeriesRead(
        std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete> &candlestick_data_series)
{
	const std::string sql = R"###(
		SELECT * FROM v_candlestick_data_series;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::CandlestickDataSeriesComplete> rs = (session().prepare << sql);
		for (::soci::rowset<offcenter::trading::datatypes::CandlestickDataSeriesComplete>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			candlestick_data_series.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read a candlestick data series
 *
 * @param[out] candlestick_data_series Return candlestick data series
 * @param candlestick_data_series_id ID of candlestick data series to return
 */
void TradingDB::candlestickDataSeriesRead(
        offcenter::trading::datatypes::CandlestickDataSeriesComplete &candlestick_data_series,
        unsigned candlestick_data_series_id)
{
	const std::string sql = R"###(
		SELECT * FROM v_candlestick_data_series WHERE candlestick_data_series_id = :candlestick_data_series_id;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::into(candlestick_data_series), ::soci::use(candlestick_data_series_id));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction);
}

/**
 * Read a candlestick data series id based on name
 *
 * @param[out] candlestick_data_series_id ID of candlestick data series
 * @param candlestick_data_series_by_name Name search data of candlestick data series to return
 */
void TradingDB::candlestickDataSeriesRead(
		unsigned& candlestick_data_series_id,
        const offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series_by_name)
{
	const std::string sql = R"###(
		SELECT candlestick_data_series_id
		FROM v_candlestick_data_series
		WHERE instrument_name = :instrument_name
		  AND broker_name = :broker_name
		  AND broker_data_source_name = :broker_data_source_name
		  AND candlestick_granularity_name = candlestick_granularity_name;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::into(candlestick_data_series_id), ::soci::use(candlestick_data_series_by_name));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction);
}

/**
 * Update a candlestick data series
 *
 * Currently not implemented
 *
 * @param candlestick_data_series Candlestick data series to update
 */
void TradingDB::candlestickDataSeriesUpdate(
        const offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series)
{
	LOG(ERROR) << "Called undefined method: candlestickDataSeriesUpdate";
}

/**
 * Delete a candlestick data series
 *
 * @param candlestick_data_series_id ID of candlestick data series to delete
 */
void TradingDB::candlestickDataSeriesDelete(unsigned candlestick_data_series_id)
{
	const std::string sql = R"###(
		DELETE FROM candlestick_data_series WHERE candlestick_data_series_id = :candlestick_data_series_id;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(candlestick_data_series_id));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session);
}

/**
 * Create candlestick data
 *
 * @param candlestick_data_create Candlestick data
 */
void TradingDB::candlestickDataCreate(
        const offcenter::trading::datatypes::CandlestickDataCreate& candlestick_data_create)
{
	// If there are no records to save
	if (candlestick_data_create.candlestick_data.size() == 0) {
		LOG(INFO) << "Saved candlestick records: "
				<< "instrument(" << candlestick_data_create.instrument << ") "
				<< "broker(" << candlestick_data_create.broker << ") "
				<< "broker_source(" << candlestick_data_create.broker_source << ") "
				<< "granularity(" << candlestick_data_create.granularity << ") "
				<< "Empty dataset. No records saved.";
		return;
	}

	const std::string sql = R"###(
		INSERT INTO candlestick_data
		(
			candlestick_data_series_id,
			start_time,
			bid_open,
			bid_high,
			bid_low,
			bid_close,
			bid_gap_open,
			ask_open,
			ask_high,
			ask_low,
			ask_close,
			ask_gap_open,
			volume
		)
		VALUES(
			:candlestick_data_series_id,
			:start_time,
			:bid_open,
			:bid_high,
			:bid_low,
			:bid_close,
			:bid_gap_open,
			:ask_open,
			:ask_high,
			:ask_low,
			:ask_close,
			:ask_gap_open,
			:volume
		);
	)###";

	try {
		offcenter::trading::datatypes::CandlestickDataSeriesByName candlestick_data_series_by_name = {
				{
					candlestick_data_create.instrument,
					candlestick_data_create.broker,
					candlestick_data_create.broker_source,
					candlestick_data_create.granularity
				},
				0
		};

		// Read the candlestick data series id
		unsigned candlestick_data_series_id;
		candlestickDataSeriesRead(candlestick_data_series_id, candlestick_data_series_by_name);

		offcenter::common::UTCDateTime firstRecordSavedTime;
		offcenter::common::UTCDateTime lastRecordSavedTime;

		bool atLeastOneRecordSaved = false;
		offcenter::trading::datatypes::CandlestickData candlestick_data;
		{
			offcenter::soci::Session session(m_sessionPoolManager);
			::soci::statement st = (session().prepare << sql, ::soci::use(candlestick_data));
			offcenter::soci::Transaction transaction(session);
			for (offcenter::trading::datatypes::CandlestickData element : candlestick_data_create.candlestick_data) {
				candlestick_data = element;
				candlestick_data.candlestick_data_series_id = candlestick_data_series_id;

				// If record is successfully saved
				if (executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction)) {
					if (!atLeastOneRecordSaved) {
						// Save the start time for the first record saved
						firstRecordSavedTime = candlestick_data.start_time;
					}
					// Update last record saved
					lastRecordSavedTime = candlestick_data.start_time;
					atLeastOneRecordSaved = true;
				}
			}
		}
		LOG(INFO) << "Saved candlestick records: "
				<< "instrument(" << candlestick_data_create.instrument << ") "
				<< "broker(" << candlestick_data_create.broker << ") "
				<< "broker_source(" << candlestick_data_create.broker_source << ") "
				<< "granularity(" << candlestick_data_create.granularity << ") "
				<< "record count(" << candlestick_data_create.candlestick_data.size() << ") "
				<< "first record saved(" << (atLeastOneRecordSaved ? offcenter::common::UTCDateTimeToISO8601(firstRecordSavedTime) : "N/A") << ") "
				<< "last record saved(" << (atLeastOneRecordSaved ? offcenter::common::UTCDateTimeToISO8601(lastRecordSavedTime) : "N/A") << ") ";
	} catch(std::exception& e) {
		LOG(ERROR) << "Unable to Save Candlestick Data: "
				<< "instrument(" << candlestick_data_create.instrument << ") "
				<< "broker(" << candlestick_data_create.broker << ") "
				<< "broker_source(" << candlestick_data_create.broker_source << ") "
				<< "granularity(" << candlestick_data_create.granularity << ") "
				<< ")" << e.what();
		throw;
	}
}

/**
 * Read candlestick data
 *
 * @param candlestick_range Candlestick data read
 * @param[out] candlestick_search Definition of candlestick data to read
 */
void TradingDB::candlestickDataRead(
		offcenter::trading::datatypes::CandlestickDataRange &candlestick_range,
        const offcenter::trading::datatypes::CandlestickDataSearch &candlestick_search)
{
	const std::string read_include_start = R"###(
		SELECT * FROM candlestick_data
		WHERE start_time >= :start_time
		  AND start_time <= :end_time;
	)###";
	const std::string read_exclude_start = R"###(
		SELECT * FROM candlestick_data
		WHERE start_time > :start_time
		  AND start_time <= :end_time;
	)###";

	candlestick_range.broker = candlestick_search.broker;
	candlestick_range.broker_source = candlestick_search.broker_source;
	candlestick_range.instrument = candlestick_search.instrument;
	candlestick_range.granularity = candlestick_search.granularity;
	candlestick_range.start_time = candlestick_search.start_time;
	candlestick_range.end_time = candlestick_search.end_time;

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		if (candlestick_search.include_start_time) {
			::soci::rowset<offcenter::trading::datatypes::CandlestickData> rs = (session().prepare << read_include_start, ::soci::use(candlestick_search));
			for (::soci::rowset<offcenter::trading::datatypes::CandlestickData>::const_iterator it = rs.begin(); it != rs.end(); ++it)
			{
					LOG(DEBUG) << "cdi: " << it->candlestick_data_id;
					candlestick_range.candlestick_data.push_back(*it);
			}
		} else {
			::soci::rowset<offcenter::trading::datatypes::CandlestickData> rs = (session().prepare << read_exclude_start, ::soci::use(candlestick_search));
			for (::soci::rowset<offcenter::trading::datatypes::CandlestickData>::const_iterator it = rs.begin(); it != rs.end(); ++it)
			{
					LOG(DEBUG) << "cdi: " << it->candlestick_data_id;
					candlestick_range.candlestick_data.push_back(*it);
			}
		}
	} catch(std::exception& e) {
		LOG(ERROR) << "Unable to Read Candlestick Data: " << e.what();
		throw;
	}

}

/**
 * Update candlestick data
 *
 * @param[out] candlestick_data Candlestick data to update
 */
void TradingDB::candlestickDataUpdate(
        const offcenter::trading::datatypes::CandlestickData &candlestick_data)
{
}

/**
 * Delete candlestick data
 *
 * @param candlestick_data_id ID of candlestick data record to delete
 */
void TradingDB::candlestickDataDelete(unsigned candlestick_data_id)
{
	const std::string sql = R"###(
		DELETE FROM candlestick_data WHERE candlestick_data_id = :candlestick_data_id;
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::use(candlestick_data_id));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session);
}

void TradingDB::candlestickDataAfterDate(
       offcenter::trading::datatypes::CandlestickData& candlestick_data,
       const offcenter::trading::datatypes::CandlestickDataAfterDate& candlestick_search)
{
	const std::string sql = R"###(
		SELECT *
		FROM candlestick_data cd
		WHERE cd.start_time > :search_time
		  AND cd.candlestick_data_series_id = (SELECT candlestick_data_series_id
				FROM candlestick_data_series cds
				LEFT JOIN (instrument i, v_broker_source bs, candlestick_granularity cg)
				ON
				(
					cds.instrument_id = i.instrument_id 
					AND cds.broker_data_source_id = bs.broker_data_source_id 
					AND cds.candlestick_granularity_id = cg.candlestick_granularity_id
				)
				WHERE 
					i.name = :instrument
					AND bs.broker_name = :broker
					AND bs.source_name = :broker_source
					AND cg.name = :granularity)
		ORDER BY cd.start_time
		LIMIT 1
	)###";

	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql,
			::soci::into(candlestick_data),
			::soci::use(candlestick_search));

	if (!executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction, &session)) {
		// If empty recordset
		LOG(ERROR) << "candlestickDataAfterDate returned an empty recordset: "
				<< candlestick_search.broker << ", " << candlestick_search.broker_source << ", "
				<< candlestick_search.instrument << ", " << candlestick_search.granularity << ", "
				<< offcenter::common::UTCDateTimeToISO8601(candlestick_search.search_time);
		throw offcenter::trading::common::EmptyRecordset("candlestick_data",
				candlestick_search.broker + ", " + candlestick_search.broker_source + ", "
				+ candlestick_search.instrument + ", " + candlestick_search.granularity + ", "
				+ offcenter::common::UTCDateTimeToISO8601(candlestick_search.search_time));
	}
}

/**
 * Count number of currency pairs
 *
 * @return Number of currency pairs in database
 */
unsigned int TradingDB::currencyPairCount()
{
	unsigned int recordCount = 0;
	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << "SELECT COUNT(currency_pair_id) FROM currency_pair", ::soci::into(recordCount));
	executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithoutTransaction);
	return recordCount;
}

/**
 * Read all brokers from database
 *
 * @param[out] records Brokers read from database
 */
void TradingDB::brokersRead(
		offcenter::trading::datatypes::AllBroker &records)
{
	const std::string read = R"###(
		SELECT * FROM broker;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::BrokerDB> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::BrokerDB>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read all broker data sources
 *
 * @param[out] records All broker data sources
 */
void TradingDB::brokerDataSourceRead(
        offcenter::trading::datatypes::AllBrokerDataSource &records)
{
	const std::string read = R"###(
		SELECT * FROM broker_data_source;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::BrokerDataSource> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::BrokerDataSource>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read all intrument types
 *
 * @param[out] records All instrument types
 */
void TradingDB::instrumentTypeRead(
        offcenter::trading::datatypes::AllInstrumentType &records)
{
	const std::string read = R"###(
		SELECT * FROM instrument_type;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::InstrumentType> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::InstrumentType>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read all guaranteed stop loss order mode for instrument
 *
 * @param[out] records All guaranteed stop loss order mode for instrument records
 */
void TradingDB::guaranteedStopLossOrderModeForInstrumentRead(
        offcenter::trading::datatypes::AllGuaranteedStopLossOrderModeForInstrument &records)
{
	const std::string read = R"###(
		SELECT * FROM guaranteed_stop_loss_order_mode_for_instrument;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read all day of week
 *
 * @param[out] records All days of week
 */
void TradingDB::dayOfWeek(offcenter::trading::datatypes::AllDayOfWeek &records)
{
	const std::string read = R"###(
		SELECT * FROM day_of_week;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::DayOfWeek> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::DayOfWeek>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read all candlestick granularity
 *
 * @param[out] records All candlestick granularity records
 */
void TradingDB::candlestickGranularity(
        offcenter::trading::datatypes::AllCandlestickGranularity &records)
{
	const std::string read = R"###(
		SELECT * FROM candlestick_granularity;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::CandlestickGranularity> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::CandlestickGranularity>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read all currencies
 *
 * @param[out] records All currencies
 */
void TradingDB::currency(offcenter::trading::datatypes::AllCurrency &records)
{
	const std::string read = R"###(
		SELECT * FROM currency;
	)###";

	try {
		offcenter::soci::Session session(m_sessionPoolManager);
		::soci::rowset<offcenter::trading::datatypes::Currency> rs = (session().prepare << read);
		for (::soci::rowset<offcenter::trading::datatypes::Currency>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
			records.records.push_back(*it);
		}
	} catch(::soci::mysql_soci_error const& e) {
		throw offcenter::trading::common::TradingRuntimeException(e);
	}
}

/**
 * Read first candlestick data record of candlestick data series
 *
 * @param candlestick_data_series_id ID of candlestick data series
 * @param[out] record_time Record time of first record
 * @param[out] record_id Record ID of first record
 */
void TradingDB::candlestickDataFirstRecord(
		unsigned candlestick_data_series_id,
		offcenter::common::UTCDateTime& record_time,
		unsigned long long& record_id)
{
	using namespace date;
	using namespace std::chrono;
	const std::string sql = R"###(
		SELECT 
			candlestick_data_id, start_time
		FROM
			candlestick_data
		WHERE start_time = (SELECT MIN(start_time) FROM candlestick_data WHERE candlestick_data_series_id = :candlestick_data_series_id)
		  AND candlestick_data_series_id = :candlestick_data_series_id;
	)###";

	unsigned long long tmpRecordTime;
	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (session().prepare << sql, ::soci::into(record_id), ::soci::into(tmpRecordTime), ::soci::use(candlestick_data_series_id, "candlestick_data_series_id"));
	if (executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session)) {
		//LOG(DEBUG) << "After Execute (First): " << record_id << ", " << tmpRecordTime << ", " << candlestick_data_series_id;
		record_time = offcenter::common::make_UTCDateTimeFromTimestamp(tmpRecordTime);
		//LOG(DEBUG) << "candlestickDataFirstRecord: id(" << record_id << ") time(" << offcenter::common::UTCDateTimeToISO8601(record_time) << ")";
	} else {
		LOG(ERROR) << "candlestickDataFirstRecord returned an empty recordset: "
				<< candlestick_data_series_id;
		throw offcenter::trading::common::EmptyRecordset("candlestick_data_series",
				"First candlestick_data_series_id(" + std::to_string(candlestick_data_series_id) + ")");
	}
}

/**
 * Read last candlestick data record of candlestick data series
 *
 * @param candlestick_data_series_id ID of candlestick data series
 * @param[out] record_time Record time of last record
 * @param[out] record_id Record ID of last record
 */
void TradingDB::candlestickDataLastRecord(
		unsigned candlestick_data_series_id,
		offcenter::common::UTCDateTime& record_time,
		unsigned long long& record_id,
		std::string& last_record_bid_close,
		std::string& last_record_ask_close)
{
	const std::string sql = R"###(
		SELECT 
			candlestick_data_id, start_time, bid_close, ask_close
		FROM
			candlestick_data
		WHERE start_time = (SELECT MAX(start_time) FROM candlestick_data WHERE candlestick_data_series_id = :candlestick_data_series_id)
		  AND candlestick_data_series_id = :candlestick_data_series_id;
	)###";

	unsigned long long tmpRecordTime;
	offcenter::soci::Session session(m_sessionPoolManager);
	::soci::statement st = (
			session().prepare << sql,
			::soci::into(record_id),
			::soci::into(tmpRecordTime),
			::soci::into(last_record_bid_close),
			::soci::into(last_record_ask_close),
			::soci::use(candlestick_data_series_id, "candlestick_data_series_id"));
	if (executeStatement(st, SOCIDataExchange::WithDataExchange, SOCITransaction::WithTransaction, &session)) {
		//LOG(DEBUG) << "After Execute (Last): " << record_id << ", " << tmpRecordTime << ", " << candlestick_data_series_id;
		record_time = offcenter::common::make_UTCDateTimeFromTimestamp(tmpRecordTime);
		//LOG(DEBUG) << "candlestickDataLastRecord: id(" << record_id << ") time(" << offcenter::common::UTCDateTimeToISO8601(record_time) << ")";
	} else {
		LOG(ERROR) << "candlestickDataLastRecord returned an empty recordset: "
				<< candlestick_data_series_id;
		throw offcenter::trading::common::EmptyRecordset("candlestick_data_series",
				"Last candlestick_data_series_id(" + std::to_string(candlestick_data_series_id) + ")");
	}
}

/**
 * Read first and last candlestick data record of candlestick data series
 *
 * @param candlestick_data_series_id ID of candlestick data series
 * @param[out] record First and last candlestick data records
 */
void TradingDB::candlestickDataFirstLastRecord(
		unsigned candlestick_data_series_id,
        offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord &record)
{
	record.candlestick_data_series_id = candlestick_data_series_id;

	try {
		candlestickDataFirstRecord(
				candlestick_data_series_id,
				record.first_record_time,
				record.first_record_id);

		candlestickDataLastRecord(
				candlestick_data_series_id,
				record.last_record_time,
				record.last_record_id,
				record.last_record_bid_close,
				record.last_record_ask_close);
	} catch(const offcenter::trading::common::EmptyRecordset& e) {
		record.candlestick_data_series_id = candlestick_data_series_id;
		record.first_record_id = 0;
		record.first_record_time = offcenter::common::make_UTCDateTimeFromTimestamp(0);
		record.last_record_id = 0;
		record.last_record_time = offcenter::common::make_UTCDateTimeFromTimestamp(0);
		record.last_record_bid_close = "0.0";
		record.last_record_ask_close = "0.0";
	}
}

/**
 * Execute a statement and handle SOCI errors
 *
 * @param st SOCI statement to execute
 * @param withDataExchange Data will be exchanged with execution of the statement
 * @param withTransaction Statement will be executed within a transaction
 * @param session Session pointer for creating a transaction
 */
bool TradingDB::executeStatement(
		::soci::statement& st,
		SOCIDataExchange withDataExchange,
		SOCITransaction withTransaction,
		offcenter::soci::Session* session)
{
	try {
		if (withTransaction == SOCITransaction::WithTransaction) {
			assert(session != nullptr);
			offcenter::soci::Transaction transaction(*session);
			return st.execute(withDataExchange == SOCIDataExchange::WithDataExchange);
		} else {
			return st.execute(withDataExchange == SOCIDataExchange::WithDataExchange);
		}
	} catch (::soci::mysql_soci_error const& e) {
		LOG(ERROR) << e.err_num_ << ":" << e.what();
		switch (e.err_num_) {
			case 1062: throw offcenter::trading::common::DuplicateRecord(e);
			default: throw;
		}
	}
}

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */
