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
 * @file   OandaPersistenceManagerProgramOptions.hpp
 * @author Scott Brauer
 * @date   05-18-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGERPROGRAMOPTIONS_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGERPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/oandapersistencemanager/OandaPersistenceManagerOptions.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistencemanager {

class OandaPersistenceManagerProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<offcenter::trading::oandapersistencemanager::OandaPersistenceManagerOptions>
{
public:
	OandaPersistenceManagerProgramOptions():
		ProgramOptionsGroup("Oanda Persistence Manager Options")
	{
		optionsDescription().add_options()
				("Persist.urlBase", po::value<std::string>(&optionConfig().m_urlBase)->default_value("/offcenter/trade/"), "URL Base [/offcenter/trade/]")
				("Persist.broker", po::value<std::string>(&optionConfig().m_broker)->default_value("oanda"), "Broker [oanda]")
				;
	}

	virtual ~OandaPersistenceManagerProgramOptions() = default;
};

} /* namespace oandapersistencemanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCEMANAGER_OANDAPERSISTENCEMANAGERPROGRAMOPTIONS_HPP_ */
