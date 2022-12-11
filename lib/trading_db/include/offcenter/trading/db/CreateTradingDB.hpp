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
 * @file   CreateTradingDB.hpp
 * @author Scott Brauer
 * @date   08-29-2021
 */

#ifndef TRADING_LIB_TRADING_DB_SRC_CREATETRADINGDB_HPP_
#define TRADING_LIB_TRADING_DB_SRC_CREATETRADINGDB_HPP_

#include "offcenter/common/soci/Session.hpp"
#include "offcenter/common/soci/MySQLOptions.hpp"

namespace offcenter {
namespace trading {
namespace db {

/**
 *
 */
class CreateTradingDB
{
public:
	const static int g_sessionPoolSize = 4;

public:
	CreateTradingDB();
	virtual ~CreateTradingDB();

	void dropDatabase(const offcenter::soci::MySQLOptions& options);
	void openDatabase(const offcenter::soci::MySQLOptions& options, bool createIfNotFound = true);
	void closeDatabase();
	void createDatabase();

	void setHideStdOut(bool hideStdOut) { m_hideStdOut = hideStdOut; }

private:
	void createLookupTables();
	void createDataTables();
	void createOandaDataTables();
	void createOandaViews();
	void createViews();

	void createAndPopulateTable(const std::string& tableSchema, const std::string& tableData);
	void createTable(const std::string& tableSchema);
	void createView(const std::string& tableSchema);

private:
	offcenter::soci::SessionPoolManager m_sessionPoolManager;
	bool m_hideStdOut;
};

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* TRADING_LIB_TRADING_DB_SRC_CREATETRADINGDB_HPP_ */
