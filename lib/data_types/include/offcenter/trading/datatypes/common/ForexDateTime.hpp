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
 * @file   DateTime.hpp
 * @author Scott Brauer
 * @date   06-12-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_COMMON_DATETIME_HPP_
#define OFFCENTER_TRADING_DATATYPES_COMMON_DATETIME_HPP_

//#include <time.h>
#include <ios>
#include <chrono>
#include <utility>
#include <regex>

#include "date/date.h"
#include "offcenter/common/DateTime.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

using ForexDuration_Rep = long long;
using ForexDuration_Second = std::ratio_multiply<std::ratio<1>, std::chrono::seconds::period>;
using ForexDuration_Minute = std::ratio_multiply<std::ratio<1>, std::chrono::minutes::period>;
using ForexDuration_Hour   = std::ratio_multiply<std::ratio<1>, std::chrono::hours::period>;

using ForexDateTime_S5  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Second>; ///< 5 second UTCDateTime
using ForexDateTime_S10 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Second>; ///< 10 second UTCDateTime
using ForexDateTime_S15 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Second>; ///< 15 second UTCDateTime
using ForexDateTime_S30 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Second>; ///< 30 second UTCDateTime
using ForexDateTime_M1  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 1 minute UTCDateTime
using ForexDateTime_M2  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 2 minute UTCDateTime
using ForexDateTime_M4  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 4 minute UTCDateTime
using ForexDateTime_M5  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 5 minute UTCDateTime
using ForexDateTime_M10 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 10 minute UTCDateTime
using ForexDateTime_M15 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 15 minute UTCDateTime
using ForexDateTime_M30 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Minute>; ///< 30 minute UTCDateTime
using ForexDateTime_H1  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 1 hour UTCDateTime
using ForexDateTime_H2  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 2 hour UTCDateTime
using ForexDateTime_H3  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 3 hour UTCDateTime
using ForexDateTime_H4  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 4 hour UTCDateTime
using ForexDateTime_H6  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 6 hour UTCDateTime
using ForexDateTime_H8  = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 8 hour UTCDateTime
using ForexDateTime_H12 = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 12 hour UTCDateTime
using ForexDateTime_D   = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 1 day UTCDateTime
using ForexDateTime_W   = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 1 week UTCDateTime
using ForexDateTime_M   = offcenter::common::CustomDateTime<ForexDuration_Rep, ForexDuration_Hour>; ///< 1 month UTCDateTime




} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

namespace offcenter {
namespace common {

template<>
const offcenter::trading::datatypes::ForexDateTime_W make_CustomDateTimeFromTimestamp<offcenter::trading::datatypes::ForexDateTime_W>(const std::string& dtAsString);

} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_COMMON_DATETIME_HPP_ */
