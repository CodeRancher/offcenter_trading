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
 * @file   FinancingDayOfWeekJson.hpp
 * @author Scott Brauer
 * @date   05-26-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_OANDA_FINANCINGDAYOFWEEKJSON_HPP_
#define OFFCENTER_TRADING_DATATYPES_OANDA_FINANCINGDAYOFWEEKJSON_HPP_

#include <nlohmann/json.hpp>

#include "offcenter/trading/datatypes/oanda/FinancingDayOfWeek.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace oanda {

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		FinancingDayOfWeek,
		financing_day_of_week_id,
		instrument_id,
		day_of_week_id,
		days_charged
)

} /* namespace oanda */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_OANDA_FINANCINGDAYOFWEEKJSON_HPP_ */
