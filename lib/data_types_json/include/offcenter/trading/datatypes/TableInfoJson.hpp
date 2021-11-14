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
 * @file   TableInfo.hpp
 * @author Scott Brauer
 * @date   07-16-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_TABLEINFOJSON_HPP_
#define OFFCENTER_TRADING_DATATYPES_TABLEINFOJSON_HPP_

#include <nlohmann/json.hpp>

#include "offcenter/trading/datatypes/TableInfo.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace tableinfo {

namespace candlestickdata {

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		FirstLastRecord,
		candlestick_data_series_id,
		first_record_time,
		first_record_id,
		last_record_time,
		last_record_id,
		last_record_bid_close,
		last_record_ask_close
)

} /* namespace candlestickdata */

} /* namespace tableinfo */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_TABLEINFOJSON_HPP_ */
