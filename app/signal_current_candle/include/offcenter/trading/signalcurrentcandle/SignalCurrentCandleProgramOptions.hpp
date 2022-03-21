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
 * @file   SignalCurrentCandleProgramOptions.hpp
 * @author Scott Brauer
 * @date   10-12-2021
 */

#ifndef OFFCENTER_TRADING_SIGNALCURRENTCANDLE_SIGNALCURRENTCANDLEPROGRAMOPTIONS_H_
#define OFFCENTER_TRADING_SIGNALCURRENTCANDLE_SIGNALCURRENTCANDLEPROGRAMOPTIONS_H_

#include <functional>
#include <iostream>
#include <sstream>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/signalcurrentcandle/SignalCurrentCandleOptions.hpp"

namespace offcenter {
namespace trading {
namespace signalcurrentcandle {

class SignalCurrentCandleProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<offcenter::trading::signalcurrentcandle::SignalCurrentCandleOptions>
{
public:
	SignalCurrentCandleProgramOptions():
		ProgramOptionsGroup("Signal Current Candle Options")
	{
		optionsDescription().add_options()
				("broker,b", po::value<std::string>(&optionConfig().m_broker)->default_value("oanda"), "Broker")
				("fxtrade", po::bool_switch(&optionConfig().m_fxtrade)->default_value(false), "Connect to Oanda's trade server")
				("instruments,i", po::value<std::string>()->default_value("")
						->notifier(boost::bind(&SignalCurrentCandleProgramOptions::setInstruments, this, boost::placeholders::_1)), "Comma separated list of instruments")
				("granularity", po::value<std::string>(&optionConfig().m_granularity)->default_value("S5"), "Granularity")
				;
	}

	virtual ~SignalCurrentCandleProgramOptions() = default;

	virtual void validateOptions(po::variables_map& vm) {

	}

private:
	/*
	 * Separate the list of instruments
	 */
	void setInstruments(const std::string& value) {
		std::istringstream ss(value);
		std::string token;

		while(std::getline(ss, token, ',')) {
			optionConfig().m_instruments.push_back(token);
		}
	}
};

} /* namespace signalcurrentcandle */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_SIGNALCURRENTCANDLE_SIGNALCURRENTCANDLEPROGRAMOPTIONS_H_ */
