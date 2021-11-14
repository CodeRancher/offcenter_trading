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
 * @file   SignalCurrentCandleTriggerProgramOptions.hpp
 * @author Scott Brauer
 * @date   10-12-2021
 */
#ifndef OFFCENTER_TRADING_SIGNALCURRENTCANDLETRIGGER_SIGNALCURRENTCANDLETRIGGERPROGRAMOPTIONS_H_
#define OFFCENTER_TRADING_SIGNALCURRENTCANDLETRIGGER_SIGNALCURRENTCANDLETRIGGERPROGRAMOPTIONS_H_

#include <functional>
#include <iostream>
#include <sstream>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/signalcurrentcandletrigger/SignalCurrentCandleTriggerOptions.hpp"

namespace offcenter {
namespace trading {
namespace signalcurrentcandletrigger {

class SignalCurrentCandleTriggerProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<offcenter::trading::signalcurrentcandletrigger::SignalCurrentCandleTriggerOptions>
{
public:
	SignalCurrentCandleTriggerProgramOptions():
		ProgramOptionsGroup("Create Trading DB Options")
	{
		optionsDescription().add_options()
				("token,t", po::value<std::string>(&optionConfig().m_accessToken)->default_value(""), "Oanda access token")
				("account,a", po::value<std::string>(&optionConfig().m_userAccount)->default_value(""), "Oanda user account")
				("fxtrade", po::bool_switch(&optionConfig().m_fxtrade)->default_value(false), "Connect to Oanda's trade server")
				("instrument,i", po::value<std::string>(&optionConfig().m_instrument), "Instrument")
				("granularity", po::value<std::string>(&optionConfig().m_granularity)->default_value("S5"), "Granularity")
				("start,s", po::value<std::string>()->notifier(boost::bind(&SignalCurrentCandleTriggerOptions::setStart, &optionConfig(), boost::placeholders::_1)), "Start time (2004-06-09T20:59:55.000000000Z)")
				("end,e", po::value<std::string>()->notifier(boost::bind(&SignalCurrentCandleTriggerOptions::setEnd, &optionConfig(), boost::placeholders::_1)), "End time (2004-08-09T20:59:55.000000000Z)")
				;
	}

	virtual ~SignalCurrentCandleTriggerProgramOptions() = default;

	virtual void validateOptions(po::variables_map& vm) {

	}
};

} /* namespace signalcurrentcandletrigger */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_SIGNALCURRENTCANDLETRIGGER_SIGNALCURRENTCANDLETRIGGERPROGRAMOPTIONS_H_ */
