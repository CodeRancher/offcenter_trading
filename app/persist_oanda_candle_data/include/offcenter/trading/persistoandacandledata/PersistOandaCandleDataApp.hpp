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
 * @file   PersistOandaCandleDataApp.hpp
 * @author Scott Brauer
 * @date   04-06-2021
 */

#ifndef OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAAPP_H_
#define OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAAPP_H_

#include "offcenter/common/framework/application/IBasicApp.hpp"
#include "offcenter/common/framework/application/BasicApp.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/threading/RunningThreadArray.hpp"

#include "offcenter/common/soci/MySQLProgramOptions.hpp"
#include "offcenter/common/soci/Session.hpp"

#include "oanda/v20/endpoint/OandaEndpoints.hpp"
using namespace oanda::v20;

#include "offcenter/trading/db/oanda/OandaTradingDB.hpp"
#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"
#include "offcenter/trading/oandapersistenceclient/ProcessInstrumentDataThread.hpp"

#include "offcenter/trading/persistoandacandledata/PersistOandaCandleDataProgramOptions.hpp"
#include "offcenter/trading/oandapersistenceclient/PersistenceManagerProgramOptions.hpp"

namespace offcenter {
namespace trading {
namespace persistoandacandledata {

/**
 *
 */
class PersistOandaCandleDataApp: public offcenter::common::framework::application::IBasicApp {
public:
	PersistOandaCandleDataApp();
	virtual ~PersistOandaCandleDataApp();

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	void createTable(const std::string& tableSchema);
	void createAndPopulateTable(const std::string& tableSchema, const std::string& tableData);

	void updateInstruments();
	void initializeInstruments();
	void downloadInstrumentData();

private:
	std::string m_oandaSource;
	offcenter::common::soci::MySQLProgramOptions::ConfigPtr m_mysqlConfig;
	offcenter::trading::persistoandacandledata::PersistOandaCandleDataProgramOptions::ConfigPtr m_programConfig;
	offcenter::trading::oandapersistenceclient::PersistenceManagerProgramOptions::ConfigPtr m_persistenceManagerConfig;

	// Oanda
	endpoint::OandaEndpoints::Ptr m_oandaEndpoints;

	//offcenter::trading::db::oanda::OandaTradingDB m_tradingDB;
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints m_persistenceEndpoints;

	offcenter::trading::oandapersistenceclient::ProcessInstrumentDataThreadArray m_processInstrumentsDataThreads;

};

} /* namespace persistoandacandledata */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_PERSISTOANDACANDLEDATA_PERSISTOANDACANDLEDATAAPP_H_ */
