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
 * @file   CandlestickDataSeriesJson.hpp
 * @author Scott Brauer
 * @date   06-01-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIESJSON_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIESJSON_HPP_

#include <nlohmann/json.hpp>

#include "offcenter/trading/datatypes/CandlestickDataSeries.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataSeries,
		candlestick_data_series_id,
		instrument_id,
		broker_data_source_id,
		candlestick_granularity_id
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataSeriesByName,
		candlestick_data_series_id,
		instrument_name,
		broker_name,
		broker_data_source_name,
		candlestick_granularity_name
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickDataSeriesComplete,
		candlestick_data_series_id,
		instrument_id,
		instrument_name,
		broker_id,
		broker_name,
		broker_display_name,
		broker_data_source_id,
		broker_data_source_name,
		broker_data_source_display_name,
		candlestick_granularity_id,
		candlestick_granularity_name
)

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIESJSON_HPP_ */
