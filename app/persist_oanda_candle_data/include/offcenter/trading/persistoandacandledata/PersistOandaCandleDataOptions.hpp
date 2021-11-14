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
 * @file   PersistOandaCandleDataOptions.hpp
 * @author Scott Brauer
 * @date   04-06-2021
 */
#ifndef OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAOPTIONS_H_
#define OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAOPTIONS_H_

#include <string>
#include <vector>

namespace offcenter {
namespace trading {
namespace persistoandacandledata {

class PersistOandaCandleDataOptions
{
public:
	explicit PersistOandaCandleDataOptions():
		m_accessToken(""),
		m_userAccount(""),
		m_instruments(),
		m_updateInstruments(false),
		m_fxtrade(false),
		m_s5(true),
		m_oandaRecords(500)
	{}

	virtual ~PersistOandaCandleDataOptions() {}

	const std::string accessToken() { return m_accessToken; }
	const std::string userAccount() { return m_userAccount; }
	const std::vector<std::string>& instruments() { return m_instruments; }
	bool updateInstruments() { return m_updateInstruments; }
	bool fxtrade() { return m_fxtrade; }
	bool s5() { return m_s5; }
	int oandaRecords() { return m_oandaRecords; }

	const std::string broker() { return "oanda"; }
	const std::string brokerServer() { return m_fxtrade ? "fxtrade" : "fxpractice"; }
	const std::string granularity() { return "S5"; }

	friend class PersistOandaCandleDataProgramOptions;

private:
	std::string m_accessToken;
	std::string m_userAccount;
	std::vector<std::string> m_instruments;
	bool m_updateInstruments;
	bool m_fxtrade;
	bool m_s5;
	int m_oandaRecords;
};

} /* namespace persistoandacandledata */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAOPTIONS_H_ */
