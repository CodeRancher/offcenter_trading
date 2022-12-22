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
 * @file   AdmainManager.hpp
 * @author Scott Brauer
 * @date   04-26-2021
 */

#ifndef OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGER_HPP_
#define OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGER_HPP_

#include "offcenter/common/amqpserver/IAmqpServerApp.hpp"

#include "offcenter/trading/adminmanager/AdminManagerProgramOptions.hpp"

namespace offcenter {
namespace trading {
namespace adminmanager {

/**
 *
 */
class AdminManager: public offcenter::common::amqpserver::IAmqpServerApp {
public:
	explicit AdminManager();
	virtual ~AdminManager();

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitAMQP(offcenter::common::amqp::ConnectionURIOptions& options) override;
	void onInitAMQPSessions(offcenter::common::amqp::ConnectionPtr connection) override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	AdminManagerProgramOptions::ConfigPtr m_amqpOption;

	offcenter::common::amqp::SessionPtr m_session;
};

} /* namespace adminmanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_ADMINMANAGER_ADMINMANAGER_HPP_ */
