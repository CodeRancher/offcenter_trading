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
 * @file   OandaManagerProgramOptions.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */
#ifndef OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGERPROGRAMOPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGERPROGRAMOPTIONS_HPP_

#include <functional>
#include <vector>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

#include "offcenter/trading/oandamanager/OandaManagerOptions.hpp"

namespace offcenter {
namespace trading {
namespace oandamanager {

class OandaManagerProgramOptions:
		public program_options::ProgramOptionsGroup<OandaManagerOptions>
{
public:
	OandaManagerProgramOptions():
		ProgramOptionsGroup("Oanda Manager")
	{
		optionsDescription().add_options()
				("OandaManager.server", po::value<std::string>(&optionConfig().m_oandaServer)->default_value("fxpractice"), "Oanda Server [fxpractice|fxtrade]")
				("OandaManager.token", po::value<std::string>(&optionConfig().m_bearerToken), "Oanda Bearer Token")
				("OandaManager.account", po::value<std::string>(&optionConfig().m_accountID), "Oanda Account ID")
				("OandaManager.instrument", po::value<std::vector<std::string>>(&optionConfig().m_instruments)->multitoken()->composing(), "Oanda Instruments")

				("AMQP.tcpHost", po::value<std::string>(&optionConfig().m_tcpHost)->default_value("localhost"), "Active MQ Server")
				("AMQP.connectionSendTimeout", po::value<int>(&optionConfig().m_connectionSendTimeout)->default_value(100), "connection.sendTimeout")
				("AMQP.failoverTransportTimeout", po::value<int>(&optionConfig().m_failoverTransportTimeout)->default_value(100), "failoverTransport.timeout")
				;
	}
	// Bearer Token
	// AccountID
	virtual ~OandaManagerProgramOptions() = default;
};

} /* namespace oandamanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGERPROGRAMOPTIONS_HPP_ */
