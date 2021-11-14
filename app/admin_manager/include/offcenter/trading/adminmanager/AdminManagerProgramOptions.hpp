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
 * @file   AdminManagerProgramOptions.hpp
 * @author Scott Brauer
 * @date   04-26-2021
 */
#ifndef OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGERPROGRAMOPTIONS_HPP_
#define OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGERPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

#include "offcenter/trading/adminmanager/AdminManagerOptions.hpp"

namespace offcenter {
namespace trading {
namespace adminmanager {


class AdminManagerProgramOptions:
		public program_options::ProgramOptionsGroup<AdminManagerOptions>
{
public:
	AdminManagerProgramOptions():
		ProgramOptionsGroup("AdminManager")
	{
		optionsDescription().add_options()
				("AMQP.tcpHost", po::value<std::string>(&optionConfig().m_tcpHost)->default_value("localhost"), "Active MQ Server")
				("AMQP.connectionSendTimeout", po::value<int>(&optionConfig().m_connectionSendTimeout)->default_value(100), "connection.sendTimeout")
				("AMQP.failoverTransportTimeout", po::value<int>(&optionConfig().m_failoverTransportTimeout)->default_value(100), "failoverTransport.timeout")
				;
	}

	virtual ~AdminManagerProgramOptions() = default;
};

} /* namespace adminmanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGERPROGRAMOPTIONS_HPP_ */
