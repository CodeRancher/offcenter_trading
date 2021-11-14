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
 * @file   OandaManagerApp.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */

#ifndef OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGERAPP_HPP_
#define OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGERAPP_HPP_

#include "oanda/v20/endpoint/OandaEndpoints.hpp"

#include "offcenter/common/amqpserver/IAmqpServerApp.hpp"
using namespace offcenter::common;

#include "offcenter/amqp/ProducerMessageProducer.hpp"

#include "offcenter/trading/oandamanager/OandaManagerProgramOptions.hpp"

namespace offcenter {
namespace trading {
namespace oandamanager {

/**
 *
 */
class OandaManagerApp: public amqpserver::IAmqpServerApp {
public:
	explicit OandaManagerApp();
	virtual ~OandaManagerApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitAMQP(offcenter::amqp::ConnectionURIOptions& options) override;
	void onInitAMQPSessions(offcenter::amqp::ConnectionPtr connection) override;
	//void onInitMethodHandlers(restserver::AutoMethodHandler& methodHandler) override;
	//void onInitEndpoint(web::uri& uri) override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	void processBroker();
	void processBrokerServer();
	void processInstruments();
	void processInstrument(const std::string& instrument);

private:
	OandaManagerProgramOptions::ConfigPtr m_oandaOption;

	::oanda::v20::endpoint::OandaEndpoints::Ptr m_oandaEndpoints;
	amqp::ConnectionPtr m_connection;

	//offcenter::amqp::SessionPtr m_session;
	//offcenter::amqp::DestinationPtr m_destination;


	//offcenter::amqp::MessageProducerPtr m_producer;
	//offcenter::amqp::ProducerMessageHandler m_producer;
};

} /* namespace oandamanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAMANAGER_OANDAMANAGERAPP_HPP_ */
