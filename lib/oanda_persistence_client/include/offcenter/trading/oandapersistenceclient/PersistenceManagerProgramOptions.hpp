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
 * @file   PersistenceManagerProgramOptions.hpp
 * @author Scott Brauer
 * @date   09-10-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PERSISTENCEMANAGERPROGRAMOPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PERSISTENCEMANAGERPROGRAMOPTIONS_HPP_

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/oandapersistenceclient/PersistenceManagerOptions.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

/**
 *
 */
class PersistenceManagerProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<offcenter::trading::oandapersistenceclient::PersistenceManagerOptions>
{
public:
	PersistenceManagerProgramOptions():
		ProgramOptionsGroup("Persistence Manager Options")
	{
		optionsDescription().add_options()
				("pm.scheme", po::value<std::string>(&optionConfig().m_scheme)->default_value("http"), "Persistence Manager Scheme [http]")
				("pm.userinfo", po::value<std::string>(&optionConfig().m_userInfo), "Persistence Manager User Info")
				("pm.host", po::value<std ::string>(&optionConfig().m_host)->default_value("127.0.1.1"), "Persistence Manager Host [127.0.1.1]")
				("pm.port", po::value<int>(&optionConfig().m_port)->default_value(6503), "Persistence Manager Port [6503]")
				("pm.path", po::value<std::string>(&optionConfig().m_path), "Persistence Manager Path")
				("pm.query", po::value<std::string>(&optionConfig().m_query), "Persistence Manager Query")
				("pm.fragment", po::value<std::string>(&optionConfig().m_fragment), "Persistence Manager Fragment")
				("pm.timeout", po::value<int>(&optionConfig().m_timeout), "Persistence Manager Timeout in milliseconds")
				("pm.chunksize", po::value<int>(&optionConfig().m_chunksize), "Persistence Manager Chunksize")
				;
	}

	virtual ~PersistenceManagerProgramOptions() = default;
};

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PERSISTENCEMANAGERPROGRAMOPTIONS_HPP_ */
