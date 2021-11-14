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
 * @file   CandlestickDataJson.hpp
 * @author Scott Brauer
 * @date   06-10-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATAJSON_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATAJSON_HPP_

#include <nlohmann/json.hpp>

#include "offcenter/trading/datatypes/CandlestickData.hpp"
#include "offcenter/trading/datatypes/common/DateTimeJson.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickData,
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

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataRange,
		broker,
		broker_source,
		instrument,
		granularity,
		start_time,
		end_time,
		candlestick_data
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataAfterDate,
		broker,
		broker_source,
		instrument,
		granularity,
		search_time
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataSearch,
		broker,
		broker_source,
		instrument,
		granularity,
		start_time,
		end_time,
		include_start_time
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataCreate,
		broker,
		broker_source,
		instrument,
		granularity,
		candlestick_data
)

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATAJSON_HPP_ */
