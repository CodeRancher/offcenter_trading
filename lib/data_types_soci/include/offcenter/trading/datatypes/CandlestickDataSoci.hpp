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
 * @file   CandlestickDataSoci.hpp
 * @author Scott Brauer
 * @date   06-10-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASOCI_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASOCI_HPP_

#include "soci/soci.h"

#include "easylogging++.h"

#include "offcenter/trading/datatypes/CandlestickData.hpp"
#include "offcenter/common/DateTime.hpp"

namespace soci {

/**
 *
 */
template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickData>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickData& p)
	{
		try {
			try {
			p.candlestick_data_id = v.get<unsigned long long>("candlestick_data_id");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "candlestick_data_id: " << e.what();
				throw;
			}
			try {
			p.candlestick_data_series_id = v.get<unsigned>("candlestick_data_series_id", 0);
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "candlestick_data_series_id: " << e.what();
				throw;
			}

			try {
				unsigned long long sTime = v.get<unsigned long long>("start_time");
				p.start_time = offcenter::common::make_UTCDateTimeFromTimestamp(sTime);
			} catch(std::exception & e) {
				LOG(ERROR) << "from_base: " << e.what();
				throw;
			}

			try {
			p.bid_open = v.get<std::string>("bid_open");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "bid_open: " << e.what();
				throw;
			}
			try {
			p.bid_high = v.get<std::string>("bid_high");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "bid_high: " << e.what();
				throw;
			}
			try {
			p.bid_low = v.get<std::string>("bid_low");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "bid_low: " << e.what();
				throw;
			}
			try {
			p.bid_close = v.get<std::string>("bid_close");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "bid_close: " << e.what();
				throw;
			}
			try {
			p.bid_gap_open = v.get<std::string>("bid_gap_open");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "bid_gap_open: " << e.what();
				throw;
			}
			try {
			p.ask_open = v.get<std::string>("ask_open");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "ask_open: " << e.what();
				throw;
			}
			try {
			p.ask_high = v.get<std::string>("ask_high");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "ask_high: " << e.what();
				throw;
			}
			try {
			p.ask_low = v.get<std::string>("ask_low");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "ask_low: " << e.what();
				throw;
			}
			try {
			p.ask_close = v.get<std::string>("ask_close");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "ask_close: " << e.what();
				throw;
			}
			try {
			p.ask_gap_open = v.get<std::string>("ask_gap_open");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "ask_gap_open: " << e.what();
				throw;
			}
			try {
			p.volume = v.get<unsigned>("volume");
			} catch (std::bad_cast& e) {
				LOG(ERROR) << "volume: " << e.what();
				throw;
			}
		} catch(std::exception& e) {
			LOG(ERROR) << "Unable to convert CandlestickData from SOCI: " << e.what();
			throw;
		}
	}

	static void to_base(offcenter::trading::datatypes::CandlestickData const & p, values & v, indicator & ind)
	{
		v.set("candlestick_data_id", p.candlestick_data_id);
		v.set("candlestick_data_series_id", p.candlestick_data_series_id);
		v.set("start_time", offcenter::common::UTCDateTimeSecondsFromEpoch(p.start_time));
		v.set("bid_open", p.bid_open);
		v.set("bid_high", p.bid_high);
		v.set("bid_low", p.bid_low);
		v.set("bid_close", p.bid_close);
		v.set("bid_gap_open", p.bid_gap_open);
		v.set("ask_open", p.ask_open);
		v.set("ask_high", p.ask_high);
		v.set("ask_low", p.ask_low);
		v.set("ask_close", p.ask_close);
		v.set("ask_gap_open", p.ask_gap_open);
		v.set("volume", p.volume);
		ind = i_ok;
	}
};

/**
 *
 */
template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickDataSearch>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickDataSearch& p)
	{
		try {
			//p.broker = v.get<std::string>("broker");
			//p.broker_source = v.get<std::string>("broker_source");
			//p.instrument = v.get<std::string>("instrument");
			//p.granularity = v.get<std::string>("granularity");

			unsigned long long sTime = v.get<unsigned long long>("start_time");
			p.start_time = offcenter::common::make_UTCDateTimeFromTimestamp(sTime);

			unsigned long long eTime = v.get<unsigned long long>("end_time");
			p.end_time = offcenter::common::make_UTCDateTimeFromTimestamp(eTime);

			//p.include_start_time = v.get<bool>("include_start_time");
		} catch(std::exception& e) {
			LOG(ERROR) << "Unable to convert CandlestickDataSearch from SOCI: " << e.what();
			throw;
		}
	}

	static void to_base(offcenter::trading::datatypes::CandlestickDataSearch const & p, values & v, indicator & ind)
	{
		//v.set("broker", p.broker);
		//v.set("broker_source", p.broker_source);
		//v.set("instrument", p.instrument);
		//v.set("granularity", p.granularity);
		v.set("start_time", offcenter::common::UTCDateTimeSecondsFromEpoch(p.start_time));
		v.set("end_time", offcenter::common::UTCDateTimeSecondsFromEpoch(p.end_time));
		//v.set("include_start_time", p.include_start_time);
		ind = i_ok;
	}
};

/**
 *
 */
template<>
struct type_conversion<offcenter::trading::datatypes::CandlestickDataAfterDate>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::CandlestickDataAfterDate& p)
	{
		try {
			p.broker = v.get<std::string>("broker");
			p.broker_source = v.get<std::string>("broker_source");
			p.instrument = v.get<std::string>("instrument");
			p.granularity = v.get<std::string>("granularity");

			unsigned long long sTime = v.get<unsigned long long>("search_time");
			p.search_time = offcenter::common::make_UTCDateTimeFromTimestamp(sTime);
		} catch(std::exception& e) {
			LOG(ERROR) << "Unable to convert CandlestickDataAfterDate from SOCI: " << e.what();
			throw;
		}
	}

	static void to_base(offcenter::trading::datatypes::CandlestickDataAfterDate const & p, values & v, indicator & ind)
	{
		v.set("broker", p.broker);
		v.set("broker_source", p.broker_source);
		v.set("instrument", p.instrument);
		v.set("granularity", p.granularity);
		v.set("search_time", offcenter::common::UTCDateTimeSecondsFromEpoch(p.search_time));
		ind = i_ok;
	}
};

} /* namespace soci */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASOCI_HPP_ */
