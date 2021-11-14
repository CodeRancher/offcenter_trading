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
 * @file   PersistOandaCandleDataProgramOptions.hpp
 * @author Scott Brauer
 * @date   04-06-2021
 */
#ifndef OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAPROGRAMOPTIONS_H_
#define OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAPROGRAMOPTIONS_H_

#include <functional>
#include <iostream>
#include <sstream>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/persistoandacandledata/PersistOandaCandleDataOptions.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace trading {
namespace persistoandacandledata {

class PersistOandaCandleDataProgramOptions:
		public program_options::ProgramOptionsGroup<offcenter::trading::persistoandacandledata::PersistOandaCandleDataOptions>
{
public:
	PersistOandaCandleDataProgramOptions():
		ProgramOptionsGroup("Create Trading DB Options")
	{
		optionsDescription().add_options()
				("token,t", po::value<std::string>(&optionConfig().m_accessToken)->default_value(""), "Oanda access token")
				("account,a", po::value<std::string>(&optionConfig().m_userAccount)->default_value(""), "Oanda user account")
				("instruments,i", po::value<std::string>()->default_value("")
						->notifier(boost::bind(&PersistOandaCandleDataProgramOptions::setInstruments, this, boost::placeholders::_1)), "Comma separated list of instruments")
				("update,u", po::bool_switch(&optionConfig().m_updateInstruments)->default_value(false), "Force update of instruments list")
				("fxtrade", po::bool_switch(&optionConfig().m_updateInstruments)->default_value(false), "Connect to Oanda's trade server")
				("S5", po::bool_switch(&optionConfig().m_s5)->default_value(true), "Retrieve 5 second candles")
				("oandarecords", po::value<int>(&optionConfig().m_oandaRecords)->default_value(500), "Oanda candlestick download count")
				;
	}

	virtual ~PersistOandaCandleDataProgramOptions() = default;

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

} /* namespace persistoandacandledata */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAPROGRAMOPTIONS_H_ */
