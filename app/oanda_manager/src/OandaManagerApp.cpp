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
 * @file   OandaManagerApp.cpp
 * @author Scott Brauer
 * @date   05-10-2021
 */

#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <thread>

#include "easylogging++.h"

#include "offcenter/common/amqp/URLSchemeHost.hpp"
using namespace offcenter;

#include "offcenter/trading/oandamanager/Constants.hpp"
#include "offcenter/trading/oandamanager/OandaManagerApp.hpp"
//#include "AmqpDataElement.hpp"

#include "offcenter/trading/datatypes/Broker.hpp"
#include "offcenter/trading/amqp/BrokerAMQP.hpp"
using namespace offcenter::trading;

namespace offcenter {
namespace trading {
namespace oandamanager {

OandaManagerApp::OandaManagerApp():
	IAmqpServerApp(),
	m_oandaOption()
{

}

OandaManagerApp::~OandaManagerApp()
{
	// TODO Auto-generated destructor stub
}

void OandaManagerApp::onInitProgramOptions(program_options::ProgramOptionsManager &optionsManager)
{
	m_oandaOption = optionsManager.add<OandaManagerProgramOptions>();
}

void OandaManagerApp::onInitAMQP(offcenter::amqp::ConnectionURIOptions& options)
{
	offcenter::amqp::URLSchemeHost tcpHost(offcenter::amqp::URLSchemeHost::URLScheme::tcp, m_oandaOption->tcpHost());
	options.protocol.setTCPProtocol(tcpHost);
	options.connection.sendTimeout = m_oandaOption->connectionSendTimeout();
	options.failoverTransport.timeout = m_oandaOption->failoverTransportTimeout();
	LOG(INFO) << "AMQP URI: " << options.uri();
}

void OandaManagerApp::onInitAMQPSessions(offcenter::amqp::ConnectionPtr connection)
{
	m_connection = connection;

	// Create a Session
	//m_session = offcenter::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));

	// Create the destination (Topic or Queue)
	//m_destination = offcenter::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.input"));
}


void OandaManagerApp::onSetUp()
{
	// Connect to the Oanda server
	::oanda::v20::endpoint::OandaServerByName server(m_oandaOption->oandaServer());
	::oanda::v20::endpoint::OandaAuthorization authorization(m_oandaOption->bearerToken());
	m_oandaEndpoints = ::oanda::v20::endpoint::OandaEndpoints::instance(server, authorization);
}

void OandaManagerApp::onExecute()
{
	processBroker();
	processBrokerServer();
	processInstruments();

	std::vector<std::thread> threads;
	for (std::string instrument : m_oandaOption->instruments()) {
		threads.push_back(std::thread(
				[](const std::string instrument){
					LOG(INFO) << "Process Instrument: " << instrument;
				},
				instrument)
		);
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

void OandaManagerApp::onTearDown()
{
	LOG(DEBUG) << "Close Oanda";
	m_oandaEndpoints.reset();

//	LOG(DEBUG) << "Close consumer";
//	LOG(DEBUG) << "Close destination";
//	m_destination.reset();
//	LOG(DEBUG) << "Close session";
//	m_session->close();
//	m_session.reset();
}

void OandaManagerApp::onHelp(const std::string &help)
{
}

void OandaManagerApp::onVersion()
{
}

void OandaManagerApp::processBroker()
{
	LOG(INFO) << "Process Broker";

	datatypes::Broker broker(
			offcenter::trading::oandamanager::oanda::id,
			offcenter::trading::oandamanager::oanda::name,
			offcenter::trading::oandamanager::oanda::description);
	amqp::BrokerProducer brokerProducer(m_connection);

	brokerProducer.send(broker);
}

void OandaManagerApp::processBrokerServer()
{
	LOG(INFO) << "Process Broker Server";

}

void OandaManagerApp::processInstruments()
{
	LOG(INFO) << "Process Instruments";

}

void OandaManagerApp::processInstrument(const std::string& instrument)
{
	LOG(INFO) << "Process Instrument" << instrument;

}

} /* namespace oandamanager */
} /* namespace trading */
} /* namespace offcenter */
