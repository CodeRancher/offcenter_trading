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
 * @file   AdminManagerOptions.hpp
 * @author Scott Brauer
 * @date   04-26-2021
 */

#ifndef OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGEROPTIONS_HPP_
#define OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGEROPTIONS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace adminmanager {


class AdminManagerOptions
{
public:
	explicit AdminManagerOptions():
		m_tcpHost(),
		m_connectionSendTimeout(),
		m_failoverTransportTimeout()
	{}

	virtual ~AdminManagerOptions() {}

	const std::string tcpHost() const { return m_tcpHost; }
	int connectionSendTimeout() const { return m_connectionSendTimeout; }
	int failoverTransportTimeout() const { return m_failoverTransportTimeout; }

	friend class AdminManagerProgramOptions;

private:
	std::string m_tcpHost;
	int m_connectionSendTimeout;
	int m_failoverTransportTimeout;
};

} /* namespace adminmanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGEROPTIONS_HPP_ */
