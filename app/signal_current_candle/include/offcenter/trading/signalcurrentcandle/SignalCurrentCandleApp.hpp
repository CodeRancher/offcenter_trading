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
 * @file   SignalCurrentCandleApp.hpp
 * @author Scott Brauer
 * @date   10-12-2021
 */

#ifndef OFFCENTER_TRADING_SIGNALCURRENTCANDLE_SIGNALCURRENTCANDLEAPP_H_
#define OFFCENTER_TRADING_SIGNALCURRENTCANDLE_SIGNALCURRENTCANDLEAPP_H_

#include "offcenter/trading/amqp/ProcessCurrentCandleRange.hpp"
#include "offcenter/common/amqpserver/IAmqpManagedServerApp.hpp"
#include "offcenter/common/amqpserver/AmqpConnectionProgramOptions.hpp"
#include "offcenter/common/threading/RunningThreadArray.hpp"

#include "offcenter/trading/signalcurrentcandle/SignalCurrentCandleProgramOptions.hpp"
#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"
#include "offcenter/trading/oandapersistenceclient/PersistenceManagerProgramOptions.hpp"

namespace offcenter {
namespace trading {
namespace signalcurrentcandle {

/**
 *
 */
class SignalCurrentCandleApp
		: public offcenter::common::amqpserver::IAmqpManagedServerApp {
public:
	explicit SignalCurrentCandleApp();
	virtual ~SignalCurrentCandleApp();

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitAMQP(offcenter::common::amqp::ConnectionURIOptions& options) override;
	void onInitAMQPSessions(offcenter::common::amqp::ConnectionPtr connection) override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

	void onStart() override;
	void onStop() override;
	void onPause() override;
	void onResume() override;

private:
	offcenter::common::amqpserver::AmqpConnectionProgramOptions::ConfigPtr m_amqpServerOptions;
	offcenter::trading::signalcurrentcandle::SignalCurrentCandleProgramOptions::ConfigPtr m_options;
	offcenter::trading::oandapersistenceclient::PersistenceManagerProgramOptions::ConfigPtr m_persistenceManagerConfig;

	offcenter::common::amqp::SessionPtr m_session;
	offcenter::common::threading::RunningThreadArray<offcenter::trading::amqp::ProcessCurrentCandleRange> m_threads;
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints m_persistenceEndpoints;

};

} /* namespace signalcurrentcandle */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_SIGNALCURRENTCANDLE_SIGNALCURRENTCANDLEAPP_H_ */
