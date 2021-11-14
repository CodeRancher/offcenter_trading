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
 * @file   PersistOandaForexDataToCSVOptions.hpp
 * @author Scott Brauer
 * @date   04-15-2021
 */
#ifndef AMQPEXAMPLEOPTIONS_HPP_
#define AMQPEXAMPLEOPTIONS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace persistoandaforexdatatocsv {

class PersistOandaForexDataToCSVOptions
{
public:
	explicit PersistOandaForexDataToCSVOptions():
		m_tcpHost(),
		m_connectionSendTimeout(),
		m_failoverTransportTimeout()
	{}

	virtual ~PersistOandaForexDataToCSVOptions() {}

	const std::string tcpHost() const { return m_tcpHost; }
	int connectionSendTimeout() const { return m_connectionSendTimeout; }
	int failoverTransportTimeout() const { return m_failoverTransportTimeout; }

	friend class AmqpExampleProgramOptions;

private:
	std::string m_tcpHost;
	int m_connectionSendTimeout;
	int m_failoverTransportTimeout;
};

} /* namespace persistoandaforexdatatocsv */
} /* namespace trading */
} /* namespace offcenter */

#endif /* AMQPEXAMPLEOPTIONS_HPP_ */
