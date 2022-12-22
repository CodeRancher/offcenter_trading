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
 * @file   CreateTradingDBApp.cpp
 * @author Scott Brauer
 * @date   03-31-2021
 */

#include <iostream>

#include "easylogging++.h"

#include "offcenter/trading/createtradingdb/CreateTradingDBApp.hpp"
#include "offcenter/trading/db/lookup_tables.hpp"
#include "offcenter/trading/db/data_tables.hpp"
#include "offcenter/trading/db/views.hpp"
#include "offcenter/trading/db/oanda/oanda_data_tables.hpp"
#include "offcenter/trading/db/oanda/oanda_views.hpp"
using namespace offcenter::trading::db;

namespace offcenter {
namespace trading {
namespace createtradingdb {

CreateTradingDBApp::CreateTradingDBApp():
		IApp(),
		m_mysqlConfig(),
		m_createTradingDB(),
		m_createTradingDBConfig()
{
}

CreateTradingDBApp::~CreateTradingDBApp() {
	// TODO Auto-generated destructor stub
}

void CreateTradingDBApp::onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager)
{
	m_mysqlConfig = optionsManager.add<offcenter::common::soci::MySQLProgramOptions>();
	m_createTradingDBConfig = optionsManager.add<offcenter::trading::createtradingdb::CreateTradingDBProgramOptions>();
}

void CreateTradingDBApp::onSetUp()
{
	m_createTradingDB.dropDatabase(*m_mysqlConfig);
	m_createTradingDB.openDatabase(*m_mysqlConfig, true);
}

void CreateTradingDBApp::onExecute()
{
	m_createTradingDB.createDatabase();
}

void CreateTradingDBApp::onTearDown()
{
	m_createTradingDB.closeDatabase();
}

/**
 * Display command line help
 */
void CreateTradingDBApp::onHelp(const std::string& help)
{
	std::cout << help << std::endl;
}

void CreateTradingDBApp::onVersion()
{
	std::cout << "onVersion" << std::endl;

}

} /* namespace createtradingdb */
} /* namespace trading */
} /* namespace offcenter */
