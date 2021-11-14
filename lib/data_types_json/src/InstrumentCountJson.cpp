/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the );
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
 * @file   InstrumentCountJson.cpp
 * @author Scott Brauer
 * @date   05-23-2021
 */
#include "offcenter/trading/datatypes/InstrumentCountJson.hpp"
#include "offcenter/trading/common/JsonConversion.hpp"
#include "offcenter/trading/common/JsonExceptions.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

void to_json(nlohmann::json& j, const InstrumentCountResponse& p) {
	j = nlohmann::json {
		{"broker", p.broker},
		{"brokerSource", p.brokerSource},
		{"instrumentCount", p.instrumentCount}
	};
}
std::string broker;
std::string brokerSource;
unsigned int instrumentCount;

void from_json(const nlohmann::json& j, InstrumentCountResponse& p) {
	try {
		offcenter::trading::common::convertJson(j, "broker", p.broker);
		offcenter::trading::common::convertJson(j, "brokerSource", p.brokerSource);
		offcenter::trading::common::convertJson(j, "instrumentCount", p.instrumentCount);

	} catch(nlohmann::json::exception& e) {
		throw offcenter::trading::common::TradingJsonException(e);
	}
}

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */
