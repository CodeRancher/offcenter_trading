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
 * @file   CreateTradingDB.cpp
 * @author Scott Brauer
 * @date   08-29-2021
 */

#include <iostream>

#include "offcenter/trading/db/CreateTradingDB.hpp"

#include "offcenter/trading/db/lookup_tables.hpp"
#include "offcenter/trading/db/data_tables.hpp"
#include "offcenter/trading/db/views.hpp"
#include "offcenter/trading/db/oanda/oanda_data_tables.hpp"
#include "offcenter/trading/db/oanda/oanda_views.hpp"
using namespace offcenter::trading::db;

namespace offcenter {
namespace trading {
namespace db {

CreateTradingDB::CreateTradingDB():
		m_sessionPoolManager(g_sessionPoolSize, true),
		m_hideStdOut(false)
{

}

CreateTradingDB::~CreateTradingDB()
{

}

void CreateTradingDB::dropDatabase(const offcenter::soci::MySQLOptions &options)
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Drop database: " << options.host() << ":" << options.dbname() << std::endl;
	}

	m_sessionPoolManager.dropDB(options);
}

void CreateTradingDB::openDatabase(const offcenter::soci::MySQLOptions &options, bool createIfNotFound)
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Open database: " << options.host() << ":" << options.dbname() << std::endl;
	}

	m_sessionPoolManager.open(options, createIfNotFound);
}

void CreateTradingDB::closeDatabase()
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Closing database: " << std::endl;
	}

	m_sessionPoolManager.close();
}

void CreateTradingDB::createDatabase()
{
	createLookupTables();
	createDataTables();
	createOandaDataTables();
	createOandaViews();
	createViews();
}

void CreateTradingDB::createLookupTables()
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Creating lookup tables" << std::endl;
	}

	createAndPopulateTable(table::broker::create, table::broker::populate);
	createAndPopulateTable(table::broker_data_source::create, table::broker_data_source::populate);

	createAndPopulateTable(table::instrument_type::create, table::instrument_type::populate);
	createAndPopulateTable(table::guaranteed_stop_loss_order_mode_for_instrument::create, table::guaranteed_stop_loss_order_mode_for_instrument::populate);
	createAndPopulateTable(table::day_of_week::create, table::day_of_week::populate);
	createAndPopulateTable(table::candlestick_granularity::create, table::candlestick_granularity::populate);
	createAndPopulateTable(table::currency::create, table::currency::populate);
}

void CreateTradingDB::createDataTables()
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Creating data tables" << std::endl;
	}

	createTable(table::instrument::create);
	createTable(table::candlestick_data_series::create);
	createTable(table::candlestick_data::create);
}

void CreateTradingDB::createOandaDataTables()
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Creating Oanda data tables" << std::endl;
	}

	createTable(oanda::table::oanda_instrument::create);
	createTable(oanda::table::oanda_financing_day_of_week::create);
	createTable(oanda::table::oanda_instrument_tags::create);
}

void CreateTradingDB::createOandaViews()
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Creating Oanda views" << std::endl;
	}

	createView(oanda::view::oanda_instrument::create);
}

void CreateTradingDB::createViews()
{
	if (!m_hideStdOut) {
		std::cout << std::endl << "Creating views" << std::endl;
	}

	createView(view::broker_source::create);
	createView(view::candlestick_data_series::create);
}

void CreateTradingDB::createAndPopulateTable(const std::string &tableSchema, const std::string &tableData)
{
	if (!m_hideStdOut) {
		std::cout << "Create and populate: " << offcenter::soci::parseTableName(tableSchema) << std::endl;
	}

	offcenter::soci::SessionActions sessionActions(m_sessionPoolManager);
	sessionActions.createAndPopulateTable(tableSchema, tableData);
}

void CreateTradingDB::createTable(const std::string &tableSchema)
{
	if (!m_hideStdOut) {
		std::cout << "Create: " << offcenter::soci::parseTableName(tableSchema) << std::endl;
	}

	offcenter::soci::SessionActions sessionActions(m_sessionPoolManager);
	sessionActions.createTable(tableSchema);
}

void CreateTradingDB::createView(const std::string &tableSchema)
{
	if (!m_hideStdOut) {
		std::cout << "Create: " << offcenter::soci::parseTableName(tableSchema) << std::endl;
	}

	offcenter::soci::SessionActions sessionActions(m_sessionPoolManager);
	sessionActions.createView(tableSchema);
}

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */
