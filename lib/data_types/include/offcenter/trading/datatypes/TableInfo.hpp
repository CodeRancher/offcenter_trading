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
 * @date   07-15-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_TABLEINFO_HPP_
#define OFFCENTER_TRADING_DATATYPES_TABLEINFO_HPP_

#include <string>

#include "offcenter/common/DateTime.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace tableinfo {

namespace candlestickdata {

/**
 *
 */
struct FirstLastRecord
{
	unsigned candlestick_data_series_id;
	offcenter::common::UTCDateTime first_record_time;
	unsigned long long first_record_id;
	offcenter::common::UTCDateTime last_record_time;
	unsigned long long last_record_id;
	std::string last_record_bid_close;
	std::string last_record_ask_close;
};

} /* namespace candlestickdata */

} /* namespace tableinfo */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_TABLEINFO_HPP_ */
