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
 * @file   PersistOandaForexDataToCSV.hpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#ifndef OFFCENTER_TRADING_PERSISTOANDAFOREXDATATOCSV_H_
#define OFFCENTER_TRADING_PERSISTOANDAFOREXDATATOCSV_H_

#include "offcenter/common/amqpserver/IAmqpServerApp.hpp"
using namespace offcenter::common;

#include "offcenter/trading/persistoandaforexdatatocsv/PersistOandaForexDataToCSVProgramOptions.hpp"
#include "AmqpDataElement.hpp"

namespace offcenter {
namespace trading {
namespace persistoandaforexdatatocsv {

/**
 *
 */
class PersistOandaForexDataToCSV: public amqpserver::IAmqpServerApp {
public:
	explicit PersistOandaForexDataToCSV();
	virtual ~PersistOandaForexDataToCSV();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitAMQP(amqp::ConnectionURIOptions& options) override;
	void onInitAMQPSessions(amqp::ConnectionPtr connection) override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	AmqpExampleProgramOptions::ConfigPtr m_amqpOption;

	offcenter::amqp::SessionPtr m_session;
	offcenter::amqp::DestinationPtr m_destination;

};

} /* namespace persistoandaforexdatatocsv */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_PERSISTOANDAFOREXDATATOCSV_H_ */
