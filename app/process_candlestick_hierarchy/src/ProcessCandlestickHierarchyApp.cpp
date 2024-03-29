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
 * @file   ProcessCandlestickHierarchyApp.cpp
 * @author Scott Brauer
 * @date   11-01-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
//
#include "offcenter/common/amqp/Listener.hpp"
#include "offcenter/common/amqp/URLSchemeHost.hpp"
#include "offcenter/common/amqp/ProducerMessageProducer.hpp"

//using namespace offcenter;

#include "offcenter/trading/processcandlestickhierarchy/ProcessCandlestickHierarchyApp.hpp"

#include "offcenter/trading/amqp/Topics.hpp"

namespace offcenter {
namespace trading {
namespace processcandlestickhierarchy {

ProcessCandlestickHierarchyApp::ProcessCandlestickHierarchyApp():
		IAmqpManagedServerApp()
{

}

ProcessCandlestickHierarchyApp::~ProcessCandlestickHierarchyApp() {
	// TODO Auto-generated destructor stub
}

void ProcessCandlestickHierarchyApp::onInitProgramOptions(
        offcenter::common::program_options::ProgramOptionsManager &optionsManager)
{
	m_amqpServerOptions = optionsManager.add<offcenter::common::amqpserver::AmqpConnectionProgramOptions>();
	m_options = optionsManager.add<offcenter::trading::processcandlestickhierarchy::ProcessCandlestickHierarchyProgramOptions>();
	//m_persistenceManagerConfig = optionsManager.add<offcenter::trading::oandapersistenceclient::PersistenceManagerProgramOptions>();
}

void ProcessCandlestickHierarchyApp::onInitAMQP(offcenter::common::amqp::ConnectionURIOptions& options)
{
	options = *m_amqpServerOptions;
}

void ProcessCandlestickHierarchyApp::onInitAMQPSessions(offcenter::common::amqp::ConnectionPtr connection)
{
	// Create a Session
	m_session = offcenter::common::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));
}


void ProcessCandlestickHierarchyApp::onSetUp()
{
//	LOG(INFO) << "\nPersistence Manager Options"
//				<< "\n\tScheme: " << m_persistenceManagerConfig->getScheme()
//				<< "\n\tUser Info: " << m_persistenceManagerConfig-> getUserInfo()
//				<< "\n\tHost: " << m_persistenceManagerConfig->getHost()
//				<< "\n\tPort: " << m_persistenceManagerConfig->getPort()
//				<< "\n\tPath: " << m_persistenceManagerConfig->getPath()
//				<< "\n\tQuery: " << m_persistenceManagerConfig->getQuery()
//				<< "\n\tFragment: " << m_persistenceManagerConfig->getFragment()
//				<< "\n\tTimeout: " << m_persistenceManagerConfig->getTimeout().count() << "ms"
//				<< "\n\tChunksize: " << m_persistenceManagerConfig->getChunksize()
//				<< "\n\tURI: " << m_persistenceManagerConfig->getURI().to_string();

	// Initialize Program Manager Options
//	m_persistenceEndpoints.setProgramManagerOptions(m_persistenceManagerConfig);
}

void ProcessCandlestickHierarchyApp::onExecute()
{
	for (const std::string& instrument : m_options->instruments()) {
		//const std::string signalCandleRangeTopic = offcenter::trading::amqp::topic::signalCandleRange(m_options->broker(), m_options->brokerServer(), instrument, m_options->granularity());
		//LOG(INFO) << "Output destination: " << signalCandleRangeTopic;

		m_threads.add(std::make_unique<offcenter::trading::amqp::BuildHigherTimeframeCandle>(m_session, m_options->broker(), m_options->brokerServer(), instrument, m_options->granularity()));
	}
	LOG(INFO) << "Start threads";
	m_threads.run();

	std::cout << "Waiting ..." << std::endl;
	offcenter::common::interrupthandler::waitForUserInterrupt();
	std::cout << std::endl << "Shutting down" << std::endl;

	LOG(INFO) << "Stopping threads";
	m_threads.stop();

	LOG(INFO) << "Waiting for threads to stop";
	m_threads.join();

	LOG(INFO) << "Waiting for threads to clear";
	m_threads.clear();

	LOG(INFO) << "Threads stopped";
}

void ProcessCandlestickHierarchyApp::onTearDown()
{
	LOG(DEBUG) << "Close session";
	m_session->close();
	m_session.reset();
}

void ProcessCandlestickHierarchyApp::onHelp(const std::string &help)
{
}

void ProcessCandlestickHierarchyApp::onVersion()
{
}

void ProcessCandlestickHierarchyApp::onStart()
{
}

void ProcessCandlestickHierarchyApp::onStop()
{
}

void ProcessCandlestickHierarchyApp::onPause()
{
}

void ProcessCandlestickHierarchyApp::onResume()
{
}

} /* namespace processcandlestickhierarchy */
} /* namespace trading */
} /* namespace offcenter */
