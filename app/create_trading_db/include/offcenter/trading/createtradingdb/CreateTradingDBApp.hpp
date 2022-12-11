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
 * @file   CreateTradingDBApp.hpp
 * @author Scott Brauer
 * @date   03-31-2021
 */

#ifndef OFFCENTER_TRADING_CREATETRADINGDB_CREATETRADINGDBAPP_H_
#define OFFCENTER_TRADING_CREATETRADINGDB_CREATETRADINGDBAPP_H_

#include "offcenter/common/framework/application/IApp.hpp"
//#include "offcenter/common/framework/application/BasicApp.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

#include "offcenter/common/soci/MySQLProgramOptions.hpp"
//#include "offcenter/common/soci/Session.hpp"

#include "offcenter/trading/db/CreateTradingDB.hpp"
#include "offcenter/trading/createtradingdb/CreateTradingDBProgramOptions.hpp"

namespace offcenter {
namespace trading {
namespace createtradingdb {

/**
 *
 */
class CreateTradingDBApp: public framework::application::IApp {
public:
	CreateTradingDBApp();
	virtual ~CreateTradingDBApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	offcenter::soci::MySQLProgramOptions::ConfigPtr m_mysqlConfig;
	offcenter::trading::db::CreateTradingDB m_createTradingDB;
	offcenter::trading::createtradingdb::CreateTradingDBProgramOptions::ConfigPtr m_createTradingDBConfig;

};

} /* namespace createtradingdb */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_CREATETRADINGDB_CREATETRADINGDBAPP_H_ */
