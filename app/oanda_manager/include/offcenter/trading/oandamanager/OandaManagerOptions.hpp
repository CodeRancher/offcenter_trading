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
 * @file   OandaManagerOptions.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */
#ifndef OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGEROPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGEROPTIONS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace oandamanager {

class OandaManagerOptions
{
public:
	explicit OandaManagerOptions():
		m_oandaServer(),
		m_bearerToken(),
		m_accountID(),
		m_instruments(),
		m_tcpHost(),
		m_connectionSendTimeout(),
		m_failoverTransportTimeout()
	{}

	virtual ~OandaManagerOptions() {}

	const std::string& oandaServer() const { return m_oandaServer; }
	const std::string& bearerToken() const { return m_bearerToken; }
	const std::string& accountID() const { return m_accountID; }
	const std::vector<std::string>& instruments() const { return m_instruments; }

	const std::string tcpHost() const { return m_tcpHost; }
	int connectionSendTimeout() const { return m_connectionSendTimeout; }
	int failoverTransportTimeout() const { return m_failoverTransportTimeout; }

	friend class OandaManagerProgramOptions;

private:
	std::string m_oandaServer;
	std::string m_bearerToken;
	std::string m_accountID;
	std::vector<std::string> m_instruments;

	std::string m_tcpHost;
	int m_connectionSendTimeout;
	int m_failoverTransportTimeout;
};

} /* namespace oandamanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGEROPTIONS_HPP_ */
