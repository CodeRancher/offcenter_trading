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
 * @file   CandlestickDataSeriesSoci.hpp
 * @author Scott Brauer
 * @date   06-01-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIESSOCI_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIESSOCI_HPP_

#include "soci/soci.h"

#include "offcenter/trading/datatypes/CandlestickDataSeries.hpp"

namespace soci {

template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickDataSeries>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickDataSeries & p)
	{
		p.candlestick_data_series_id = v.get<unsigned>("candlestick_data_series_id");
		p.instrument_id = v.get<unsigned>("instrument_id");
		p.broker_data_source_id = v.get<int>("broker_data_source_id");
		p.candlestick_granularity_id = v.get<int>("candlestick_granularity_id");
	}

	static void to_base(offcenter::trading::datatypes::CandlestickDataSeries const & p, values & v, indicator & ind)
	{
		v.set("candlestick_data_series_id", p.candlestick_data_series_id);
		v.set("instrument_id", p.instrument_id);
		v.set("broker_data_source_id", p.broker_data_source_id);
		v.set("candlestick_granularity_id", p.candlestick_granularity_id);
		ind = i_ok;
	}
};

template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickDataSeriesByName>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickDataSeriesByName & p)
	{
		p.candlestick_data_series_id = v.get<unsigned>("candlestick_data_series_id");
		p.instrument_name = v.get<std::string>("instrument_name");
		p.broker_name = v.get<std::string>("broker_name");
		p.broker_data_source_name = v.get<std::string>("broker_data_source_name");
		p.candlestick_granularity_name = v.get<std::string>("candlestick_granularity_name");
	}

	static void to_base(offcenter::trading::datatypes::CandlestickDataSeriesByName const & p, values & v, indicator & ind)
	{
		v.set("candlestick_data_series_id", p.candlestick_data_series_id);
		v.set("instrument_name", p.instrument_name);
		v.set("broker_name", p.broker_name);
		v.set("broker_data_source_name", p.broker_data_source_name);
		v.set("candlestick_granularity_name", p.candlestick_granularity_name);
		ind = i_ok;
	}
};

template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickDataSeriesComplete>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickDataSeriesComplete & p)
	{
		p.candlestick_data_series_id = v.get<unsigned>("candlestick_data_series_id");
		p.instrument_id = v.get<unsigned>("instrument_id");
		p.instrument_name = v.get<std::string>("instrument_name");
		p.broker_id = v.get<int>("broker_id");
		p.broker_name = v.get<std::string>("broker_name");
		p.broker_display_name = v.get<std::string>("broker_display_name");
		p.broker_data_source_id = v.get<int>("broker_data_source_id");
		p.broker_data_source_name = v.get<std::string>("broker_data_source_name");
		p.broker_data_source_display_name = v.get<std::string>("broker_data_source_display_name");
		p.candlestick_granularity_id = v.get<int>("candlestick_granularity_id");
		p.candlestick_granularity_name = v.get<std::string>("candlestick_granularity_name");
	}

	static void to_base(offcenter::trading::datatypes::CandlestickDataSeriesComplete const & p, values & v, indicator & ind)
	{
		v.set("candlestick_data_series_id", p.candlestick_data_series_id);
		v.set("instrument_id", p.instrument_id);
		v.set("instrument_name", p.instrument_name);
		v.set("broker_id", p.broker_id);
		v.set("broker_name", p.broker_name);
		v.set("broker_display_name", p.broker_display_name);
		v.set("broker_data_source_id", p.broker_data_source_id);
		v.set("broker_data_source_name", p.broker_data_source_name);
		v.set("broker_data_source_display_name", p.broker_data_source_display_name);
		v.set("candlestick_granularity_id", p.candlestick_granularity_id);
		v.set("candlestick_granularity_name", p.candlestick_granularity_name);
		ind = i_ok;
	}
};

} /* namespace soci */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIESSOCI_HPP_ */
