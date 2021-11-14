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
 * @file   ProcessCurrentCandleRange.cpp
 * @author Scott Brauer
 * @date   10-13-2021
 */

#include "offcenter/trading/amqp/ProcessCurrentCandleRange.hpp"

#include "easylogging++.h"

#include "offcenter/trading/amqp/Topics.hpp"
#include "offcenter/common/DateTime.hpp"
#include "offcenter/trading/datatypes/CandlestickDataAmqp.hpp"

namespace offcenter {
namespace trading {
namespace amqp {

ProcessCurrentCandleRange::ProcessCurrentCandleRange(
		offcenter::amqp::SessionPtr session,
		offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints& persistenceEndpoints,
		const std::string& broker,
		const std::string& server,
		const std::string& instrument,
		const std::string& granularity
	):
		ProcessAmqpMessageThread(session, offcenter::trading::amqp::topic::signalCandleRange(broker, server, instrument, granularity)),
		m_inputTopic(offcenter::trading::amqp::topic::signalCandleRange(broker, server, instrument, granularity)),
		m_processInstrumentGranularityTopic(offcenter::trading::amqp::topic::processInstrumentGranularity(broker, server, instrument, granularity)),
		m_processInstrumentGranularityDestination(offcenter::amqp::helper::destinationFactory(session->createQueue(m_processInstrumentGranularityTopic))),
		m_processInstrumentGranularityProducer(session, m_processInstrumentGranularityDestination),
		m_persistenceEndpoints(persistenceEndpoints)
{
	LOG(INFO) << "ProcessCurrentCandleRange::ProcessCurrentCandleRange: " << m_inputTopic;
	m_processInstrumentGranularityProducer()->setDeliveryMode(cms::DeliveryMode::PERSISTENT);
	m_currentTime = offcenter::common::make_UTCDateTimeSmallest();

}

ProcessCurrentCandleRange::~ProcessCurrentCandleRange()
{
	LOG(INFO) << "ProcessCurrentCandleRange::~ProcessCurrentCandleRange: " << m_inputTopic;
}

void ProcessCurrentCandleRange::onNewData()
{
	LOG(INFO) << "onNewData: "
				<< data().broker_name << "."
				<< data().broker_data_source_name << "."
				<< data().instrument_name << "."
				<< data().candlestick_granularity_name << " "
				<< offcenter::common::UTCDateTimeToISO8601(data().range_begin) << " "
				<< offcenter::common::UTCDateTimeToISO8601(data().range_end);

	using namespace std::chrono_literals;
	// If current time is less than the first record in the range
	if (m_currentTime < data().range_begin) { m_currentTime = data().range_begin - 5s; }

	// If there are records left past the current time
	if (m_currentTime < data().range_end) {
		// A new max has been received so unblock and count
		unblock();
	}
}

void ProcessCurrentCandleRange::task()
{
	// Get next time
	offcenter::trading::datatypes::CandlestickDataAfterDate search;
	search.broker = data().broker_name;
	search.broker_source = data().broker_data_source_name;
	search.instrument = data().instrument_name;
	search.granularity = data().candlestick_granularity_name;
	search.search_time = m_currentTime;

	offcenter::trading::datatypes::CandlestickDataAmqp candlestickData;
	try {
		candlestickData = m_persistenceEndpoints.nextCandlestickDataRead("fxpractice", search);
	} catch(const std::exception& e) {
		LOG(ERROR) << e.what();
		throw;
	}
	m_currentTime = candlestickData.start_time;

	if (m_currentTime > data().range_end) {
		block();
		m_currentTime = data().range_end;
	} else {
		std::cout << "Process record: " << offcenter::common::UTCDateTimeToISO8601(m_currentTime) << std::endl;
		LOG(INFO) << "Current Time: " << offcenter::common::UTCDateTimeToISO8601(m_currentTime);
		m_processInstrumentGranularityProducer.send(candlestickData);
	}
}

void ProcessCurrentCandleRange::stopped()
{
}

void ProcessCurrentCandleRange::processNextCandle()
{
}

} /* namespace amqp */
} /* namespace trading */
} /* namespace offcenter */
