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
 * @file   SignalCurrentCandleTriggerApp.cpp
 * @author Scott Brauer
 * @date   10-24-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
//using namespace offcenter::common;

#include "offcenter/common/amqp/Listener.hpp"
#include "offcenter/common/amqp/URLSchemeHost.hpp"
#include "offcenter/common/amqp/ProducerMessageProducer.hpp"

//using namespace offcenter;

#include "offcenter/trading/signalcurrentcandletrigger/SignalCurrentCandleTriggerApp.hpp"

#include "offcenter/trading/amqp/Topics.hpp"
#include "offcenter/trading/datatypes/CandlestickTimeRangeAmqp.hpp"

namespace offcenter {
namespace trading {
namespace signalcurrentcandletrigger {

SignalCurrentCandleTriggerApp::SignalCurrentCandleTriggerApp():
		IAmqpManagedServerApp()
{

}

SignalCurrentCandleTriggerApp::~SignalCurrentCandleTriggerApp() {
	// TODO Auto-generated destructor stub
}

void SignalCurrentCandleTriggerApp::onInitProgramOptions(
        program_options::ProgramOptionsManager &optionsManager)
{
	m_amqpServerOptions = optionsManager.add<offcenter::common::amqpserver::AmqpConnectionProgramOptions>();
	m_options = optionsManager.add<offcenter::trading::signalcurrentcandletrigger::SignalCurrentCandleTriggerProgramOptions>();
}

void SignalCurrentCandleTriggerApp::onInitAMQP(offcenter::amqp::ConnectionURIOptions& options)
{
	options = *m_amqpServerOptions;
}

void SignalCurrentCandleTriggerApp::onInitAMQPSessions(offcenter::amqp::ConnectionPtr connection)
{
	// Create a Session
	m_session = offcenter::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));
}


void SignalCurrentCandleTriggerApp::onSetUp()
{
}

void SignalCurrentCandleTriggerApp::onExecute()
{
	std::cout
		<< "Broker:\t\t" << m_options->broker() << std::endl
		<< "Server:\t\t" << m_options->brokerServer() << std::endl
		<< "Account:\t" << m_options->userAccount() << std::endl
		<< "Instrument:\t" << m_options->instrument() << std::endl
		<< "Granularity:\t" << m_options->granularity() << std::endl
		<< "Start:\t\t" << m_options->startTimeAsString() << std::endl
		<< "End:\t\t" << m_options->endTimeAsString() << std::endl;

	{
		const std::string signalCandleRangeTopic = offcenter::trading::amqp::topic::signalCandleRange(m_options->broker(), m_options->brokerServer(), m_options->instrument(), m_options->granularity());
		LOG(INFO) << "Output destination: " << signalCandleRangeTopic;
		offcenter::amqp::DestinationPtr outputDestination = offcenter::amqp::helper::destinationFactory(m_session->createQueue(signalCandleRangeTopic));

		offcenter::amqp::ProducerMessageHandler producer(m_session, outputDestination);
		producer()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

		offcenter::trading::datatypes::CandlestickTimeRangeAmqp timeRange;
		timeRange.broker_name = m_options->broker();
		timeRange.broker_data_source_name = m_options->brokerServer();
		timeRange.instrument_name = m_options->instrument();
		timeRange.candlestick_granularity_name = m_options->granularity();
		timeRange.range_begin = m_options->startTime();
		timeRange.range_end = m_options->endTime();
		producer.send(timeRange);
	}

	return;

	// Create the destination (Topic or Queue)
	offcenter::amqp::DestinationPtr inputDestination = offcenter::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.input"));
	offcenter::amqp::DestinationPtr outputDestination = offcenter::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.output"));

	offcenter::amqp::MessageConsumerPtr consumer1 = offcenter::amqp::helper::messageConsumerFactory(m_session->createConsumer(inputDestination.get()));
	offcenter::amqp::ProducerMessageHandler producer1(m_session, outputDestination);
	producer1()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

	offcenter::amqp::MessageConsumerPtr consumer2 = offcenter::amqp::helper::messageConsumerFactory(m_session->createConsumer(inputDestination.get()));
	offcenter::amqp::ProducerMessageHandler producer2(m_session, outputDestination);
	producer2()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

	/*
	offcenter::amqp::Listener<AmqpDataElementInner, AmqpDataElementInner::MessageType> listener1(
			consumer1,
			[&producer1](const cms::Message *cmsMessage, const AmqpDataElementInner& amqpInner) {
				std::cout << "Receive message 1 (AmqpDataElement): "
						<< amqpInner.name << " : "
						<< amqpInner.description << " : "
						<< amqpInner.date << " : "
						<< amqpInner.value
						<< std::endl;

				AmqpDataElementOuter amqpOuter;
				amqpOuter = amqpInner;
				producer1.send(amqpOuter);
	});

	offcenter::amqp::Listener<AmqpDataElementInner, AmqpDataElementInner::MessageType> listener2(
			consumer2,
			[&producer2](const cms::Message *cmsMessage, const AmqpDataElementInner& amqpInner) {
				std::cout << "Receive message 2 (AmqpDataElement): "
						<< amqpInner.name << " : "
						<< amqpInner.description << " : "
						<< amqpInner.date << " : "
						<< amqpInner.value
						<< std::endl;

				AmqpDataElementOuter amqpOuter;
				amqpOuter = amqpInner;
				producer2.send(amqpOuter);
	});
	*/

	offcenter::common::interrupthandler::waitForUserInterrupt();

	LOG(DEBUG) << "Close consumers";
	consumer2->close();
	consumer2.reset();
	consumer1->close();
	consumer1.reset();
	LOG(DEBUG) << "Close destinations";
	inputDestination.reset();
	outputDestination.reset();
}

void SignalCurrentCandleTriggerApp::onTearDown()
{
	LOG(DEBUG) << "Close session";
	m_session->close();
	m_session.reset();
}

void SignalCurrentCandleTriggerApp::onHelp(const std::string &help)
{
}

void SignalCurrentCandleTriggerApp::onVersion()
{
}

void SignalCurrentCandleTriggerApp::onStart()
{
}

void SignalCurrentCandleTriggerApp::onStop()
{
}

void SignalCurrentCandleTriggerApp::onPause()
{
}

void SignalCurrentCandleTriggerApp::onResume()
{
}

} /* namespace signalcurrentcandletrigger */
} /* namespace trading */
} /* namespace offcenter */
