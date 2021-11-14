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
 * @file   CandlestickData.hpp
 * @author Scott Brauer
 * @date   06-10-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATA_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATA_HPP_

#include <ctime>
#include <string>
#include <vector>

#include "common/ForexDateTime.hpp"
#include "offcenter/common/DateTime.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
struct CandlestickDataFull
{
	std::string broker;
	std::string broker_source;
	std::string instrument;
	std::string granularity;

	offcenter::common::UTCDateTime start_time;
	std::string bid_open;
	std::string bid_high;
	std::string bid_low;
	std::string bid_close;
	std::string bid_gap_open;
	std::string ask_open;
	std::string ask_high;
	std::string ask_low;
	std::string ask_close;
	std::string ask_gap_open;
	unsigned volume;
};

/**
 *
 */
struct CandlestickData
{
	unsigned long long candlestick_data_id;
	unsigned candlestick_data_series_id;
	offcenter::common::UTCDateTime start_time;
	std::string bid_open;
	std::string bid_high;
	std::string bid_low;
	std::string bid_close;
	std::string bid_gap_open;
	std::string ask_open;
	std::string ask_high;
	std::string ask_low;
	std::string ask_close;
	std::string ask_gap_open;
	unsigned volume;
};

/**
 *
 */
struct CandlestickDataRange
{
	std::string broker;
	std::string broker_source;
	std::string instrument;
	std::string granularity;
	offcenter::common::UTCDateTime start_time;
	offcenter::common::UTCDateTime end_time;
	std::vector<CandlestickData> candlestick_data;
};

/**
 *
 */
struct CandlestickDataAfterDate
{
	std::string broker;
	std::string broker_source;
	std::string instrument;
	std::string granularity;
	offcenter::common::UTCDateTime search_time;
};

/**
 *
 */
struct CandlestickDataSearch
{
	std::string broker;
	std::string broker_source;
	std::string instrument;
	std::string granularity;
	offcenter::common::UTCDateTime start_time;
	offcenter::common::UTCDateTime end_time;
	bool include_start_time;
};

/**
 *
 */
struct CandlestickDataCreate
{
	std::string broker;
	std::string broker_source;
	std::string instrument;
	std::string granularity;
	std::vector<CandlestickData> candlestick_data;
};

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATA_HPP_ */
