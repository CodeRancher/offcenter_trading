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
 * @file   ProcessCurrentCandleRange.hpp
 * @author Scott Brauer
 * @date   10-13-2021
 */

#ifndef OFFCENTER_TRADING_AMQP_PROCESSCURRENTCANDLERANGE_HPP_
#define OFFCENTER_TRADING_AMQP_PROCESSCURRENTCANDLERANGE_HPP_

#include "offcenter/amqp/threading/ProcessAmqpMessageThread.hpp"
#include "offcenter/common/DateTime.hpp"
#include "offcenter/trading/datatypes/CandlestickTimeRangeAmqp.hpp"

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"

#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/ProducerMessageProducer.hpp"
#include "offcenter/amqp/ActiveMQCPP.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

/**
 * Process the Current Candle Range
 */
class ProcessCurrentCandleRange:
		public offcenter::amqp::threading::ProcessAmqpMessageThread<
			offcenter::trading::datatypes::CandlestickTimeRangeAmqp,
			offcenter::trading::datatypes::CandlestickTimeRangeAmqp::MessageType>
{
public:
	ProcessCurrentCandleRange() = delete;
	explicit ProcessCurrentCandleRange(
			offcenter::amqp::SessionPtr session,
			offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints& persistenceEndpoints,
			const std::string& broker,
			const std::string& server,
			const std::string& instrument,
			const std::string& granularity);
	virtual ~ProcessCurrentCandleRange();

	void setCandleRange();

protected:
	void onNewData() override;
	void task() override;
	void stopped() override;

private:
	void processNextCandle();

private:
	std::string m_inputTopic;
	std::string m_processInstrumentGranularityTopic;
	offcenter::common::UTCDateTime m_currentTime;
	offcenter::amqp::DestinationPtr m_processInstrumentGranularityDestination;
	offcenter::amqp::ProducerMessageHandler m_processInstrumentGranularityProducer;
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints& m_persistenceEndpoints;

};

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_AMQP_PROCESSCURRENTCANDLERANGE_HPP_ */
