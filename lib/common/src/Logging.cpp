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
 * @file   Logging.cpp
 * @author Scott Brauer
 * @date   09-23-2021
 */
#include "offcenter/trading/common/Logging.hpp"

namespace offcenter {
namespace trading {
namespace common {
namespace logging {

/**
 * Calculates the logger ID for broker, brokerSource, instrument, and granularity.
 *
 * @param broker Broker
 * @param brokerSource Broker data source
 * @param instrument Instrument
 * @param granularity Granularity
 *
 * @return Combined string of all elements
 */
const std::string loggerID(
		const std::string& broker,
		const std::string& brokerSource,
		const std::string& instrument,
		const std::string& granularity)
{
	return broker + "." + brokerSource + "." + instrument + "." + granularity;
}


} /* namespace logging */
} /* namespace common */
} /* namespace trading */
} /* namespace offcenter */
