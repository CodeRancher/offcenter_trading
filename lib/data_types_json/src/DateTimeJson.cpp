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
 * @file   DateTimeJson.cpp
 * @author Scott Brauer
 * @date   06-12-2021
 */
#include "offcenter/trading/datatypes/common/DateTimeJson.hpp"
#include "offcenter/trading/common/JsonConversion.hpp"
#include "offcenter/trading/common/JsonExceptions.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

void to_json(nlohmann::json& j, const offcenter::common::UTCDateTime& p) {
	j = offcenter::common::UTCDateTimeToISO8601(p);
}

void from_json(const nlohmann::json& j, offcenter::common::UTCDateTime& p) {
	try {
		std::string dt = j.get<std::string>();
		p = offcenter::common::make_UTCDateTimeFromISO8601(dt);

	} catch(nlohmann::json::exception& e) {
		throw offcenter::trading::common::TradingJsonException(e);
	}
}

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

namespace std {
namespace chrono {

//void to_json(nlohmann::json& j, const system_clock::time_point& p) {
//	j = offcenter::trading::datatypes::UTCDateTimeToISO8601(p);
//}

//void from_json(const nlohmann::json& j, system_clock::time_point& p) {
//	try {
//		std::string dt = j.get<std::string>();
//		p = offcenter::trading::datatypes::make_UTCDateTimeFromISO8601(dt);
//
//	} catch(nlohmann::json::exception& e) {
//		throw offcenter::trading::common::TradingJsonException(e);
//	}
//}

} /* namespace chrono */
} /* namespace std */
