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
 * @file   DateTime.cpp
 * @author Scott Brauer
 * @date   06-12-2021
 */

#include <chrono>
#include <iostream>
#include <sstream>
#include <ctime>

#include "date/date.h"
#include "date/tz.h"

#include "easylogging++.h"

#include "offcenter/trading/datatypes/common/ForexDateTime.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

namespace offcenter {
namespace common {

/**
 * Make a custom time_point based on a timestamp as a string.
 *
 * @tparam DateTime UTCCustomDateTime based type
 * @param dtAsString Timestamp defined as a string
 * @return A DateTime time_point based on the string
 */
template<>
const offcenter::trading::datatypes::ForexDateTime_W make_CustomDateTimeFromTimestamp<offcenter::trading::datatypes::ForexDateTime_W>(const std::string& dtAsString) {
	UTCDateTime dt = make_UTCDateTimeFromTimestamp(dtAsString);
	LOG(INFO) << "Input: " << dtAsString;
	LOG(INFO) << "Start DT: " << offcenter::common::UTCDateTimeToISO8601(dt);
	LOG(INFO) << "Floor DT: " << offcenter::common::UTCDateTimeToISO8601(date::floor<date::days>(dt));

	date::sys_days now_in_days { std::chrono::time_point_cast<date::days>(dt) };
	date::weekday weekday {now_in_days};

	LOG(INFO) << "Weekday: " << weekday;
//	std::cout << weekday << '\n';
//	LOG(INFO) << auto dp = floor<days>(tp);

	return std::chrono::time_point_cast<offcenter::trading::datatypes::ForexDateTime_W::duration>(dt);
}

//template<>
//const std::string UTCCustomDateTimeToISO8601<UTCDateTime_W>(const UTCDateTime_W& dt) {
//	return date::format("%FT%TZ", dt);
//}

} /* namespace common */
} /* namespace offcenter */
