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
 * @file   SignalCurrentCandleTriggerOptions.hpp
 * @author Scott Brauer
 * @date   10-24-2021
 */
#ifndef OFFCENTER_TRADING_SIGNALCURRENTCANDLETRIGGER_SIGNALCURRENTCANDLETRIGGEROPTIONS__H_
#define OFFCENTER_TRADING_SIGNALCURRENTCANDLETRIGGER_SIGNALCURRENTCANDLETRIGGEROPTIONS__H_

#include <string>
#include <vector>

#include "../../../../../../lib/data_types/include/offcenter/trading/datatypes/common/ForexDateTime.hpp"

namespace offcenter {
namespace trading {
namespace signalcurrentcandletrigger {

class SignalCurrentCandleTriggerOptions
{
public:
	explicit SignalCurrentCandleTriggerOptions():
		m_accessToken(""),
		m_userAccount(""),
		m_fxtrade(false),
		m_instrument(),
		m_granularity(),
		m_startTime(),
		m_endTime()
	{}

	virtual ~SignalCurrentCandleTriggerOptions() {}

	const std::string accessToken() const { return m_accessToken; }
	const std::string userAccount() const { return m_userAccount; }
	bool fxtrade() const { return m_fxtrade; }
	const std::string instrument() const { return m_instrument; }
	const std::string granularity() const { return m_granularity; }
	offcenter::common::UTCDateTime startTime() const { return m_startTime; }
	const std::string startTimeAsString() const { return offcenter::common::UTCDateTimeToISO8601(m_startTime); }
	offcenter::common::UTCDateTime endTime() const { return m_endTime; }
	const std::string endTimeAsString() const { return offcenter::common::UTCDateTimeToISO8601(m_endTime); }

	const std::string broker() const { return "oanda"; }
	const std::string brokerServer() const { return m_fxtrade ? "fxtrade" : "fxpractice"; }

	void setStart(const std::string value) {
		m_startTime = offcenter::common::make_UTCDateTimeFromISO8601(value);
	}

	void setEnd(const std::string value) {
		m_endTime = offcenter::common::make_UTCDateTimeFromISO8601(value);
	}

	friend class SignalCurrentCandleTriggerProgramOptions;

private:
	std::string m_accessToken;
	std::string m_userAccount;
	bool m_fxtrade;
	std::string m_instrument;
	std::string m_granularity;
	offcenter::common::UTCDateTime m_startTime;
	offcenter::common::UTCDateTime m_endTime;
};

} /* namespace signalcurrentcandletrigger */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_SIGNALCURRENTCANDLETRIGGER_SIGNALCURRENTCANDLETRIGGEROPTIONS__H_ */
