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
 * @file   LookupTableDataSoci.hpp
 * @author Scott Brauer
 * @date   06-22-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_LOOKUPTABLEDATASOCI_HPP_
#define OFFCENTER_TRADING_DATATYPES_LOOKUPTABLEDATASOCI_HPP_

#include "soci/soci.h"

#include "offcenter/trading/datatypes/LookupTables.hpp"

namespace soci {

/**
 * BrokerDB
 */
template<>
struct type_conversion<offcenter::trading::datatypes::BrokerDB>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::BrokerDB & p)
	{
		p.broker_id = v.get<int>("broker_id");
		p.name = v.get<std::string>("name");
		p.display_name = v.get<std::string>("display_name");
		p.description = v.get<std::string>("description");
	}

	static void to_base(offcenter::trading::datatypes::BrokerDB const & p, values & v, indicator & ind)
	{
		v.set("broker_id", p.broker_id);
		v.set("name", p.name);
		v.set("display_name", p.display_name);
		v.set("description", p.description);
		ind = i_ok;
	}
};

/**
 * BrokerDataSource
 */
template<>
struct type_conversion<offcenter::trading::datatypes::BrokerDataSource>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::BrokerDataSource & p)
	{
		p.broker_data_source_id = v.get<int>("broker_data_source_id");
		p.name = v.get<std::string>("name");
		p.display_name = v.get<std::string>("display_name");
		p.description = v.get<std::string>("description");
		p.broker_id = v.get<int>("broker_id");
	}

	static void to_base(offcenter::trading::datatypes::BrokerDataSource const & p, values & v, indicator & ind)
	{
		v.set("broker_data_source_id", p.broker_data_source_id);
		v.set("name", p.name);
		v.set("display_name", p.display_name);
		v.set("description", p.description);
		v.set("broker_id", p.broker_id);
		ind = i_ok;
	}
};

/**
 * InstrumentType
 */
template<>
struct type_conversion<offcenter::trading::datatypes::InstrumentType>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::InstrumentType & p)
	{
		p.instrument_type_id = v.get<int>("instrument_type_id");
		p.name = v.get<std::string>("name");
		p.description = v.get<std::string>("description");
	}

	static void to_base(offcenter::trading::datatypes::InstrumentType const & p, values & v, indicator & ind)
	{
		v.set("instrument_type_id", p.instrument_type_id);
		v.set("name", p.name);
		v.set("description", p.description);
		ind = i_ok;
	}
};

/**
 * GuaranteedStopLossOrderModeForInstrument
 */
template<>
struct type_conversion<offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument & p)
	{
		p.guaranteed_stop_loss_order_mode_for_instrument_id = v.get<int>("guaranteed_stop_loss_order_mode_for_instrument_id");
		p.name = v.get<std::string>("name");
		p.description = v.get<std::string>("description");
	}

	static void to_base(offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrument const & p, values & v, indicator & ind)
	{
		v.set("guaranteed_stop_loss_order_mode_for_instrument_id", p.guaranteed_stop_loss_order_mode_for_instrument_id);
		v.set("name", p.name);
		v.set("description", p.description);
		ind = i_ok;
	}
};

/**
 * DayOfWeek
 */
template<>
struct type_conversion<offcenter::trading::datatypes::DayOfWeek>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::DayOfWeek & p)
	{
		p.day_of_week_id = v.get<int>("day_of_week_id");
		p.name = v.get<std::string>("name");
		p.description = v.get<std::string>("description");
	}

	static void to_base(offcenter::trading::datatypes::DayOfWeek const & p, values & v, indicator & ind)
	{
		v.set("day_of_week_id", p.day_of_week_id);
		v.set("name", p.name);
		v.set("description", p.description);
		ind = i_ok;
	}
};

/**
 * CandlestickGranularity
 */
template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickGranularity>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickGranularity & p)
	{
		p.candlestick_granularity_id = v.get<int>("candlestick_granularity_id");
		p.name = v.get<std::string>("name");
		p.description = v.get<std::string>("description");
		p.alignment = v.get<std::string>("alignment");
		p.duration_in_seconds = v.get<unsigned>("duration_in_seconds");
	}

	static void to_base(offcenter::trading::datatypes::CandlestickGranularity const & p, values & v, indicator & ind)
	{
		v.set("candlestick_granularity_id", p.candlestick_granularity_id);
		v.set("name", p.name);
		v.set("description", p.description);
		v.set("alignment", p.alignment);
		v.set("duration_in_seconds", p.duration_in_seconds);
		ind = i_ok;
	}
};

/**
 * Currency
 */
template<>
struct type_conversion<offcenter::trading::datatypes::Currency>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::Currency & p)
	{
		p.currency_id = v.get<unsigned>("currency_id");
		p.name = v.get<std::string>("name");
		p.currency = v.get<std::string>("currency");
		p.numeric_code = v.get<int>("numeric_code");
	}

	static void to_base(offcenter::trading::datatypes::Currency const & p, values & v, indicator & ind)
	{
		v.set("currency_id", p.currency_id);
		v.set("name", p.name);
		v.set("currency", p.currency);
		v.set("numeric_code", p.numeric_code);
		ind = i_ok;
	}
};


} /* namespace soci */

#endif /* OFFCENTER_TRADING_DATATYPES_LOOKUPTABLEDATASOCI_HPP_ */
