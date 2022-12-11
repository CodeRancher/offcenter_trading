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
 * @file   CreateTradingDBEnvironment.hpp
 * @author Scott Brauer
 * @date   08-31-2021
 */

#include <gtest/gtest.h>

#include "offcenter/common/soci/MySQLProgramOptions.hpp"
#include "offcenter/trading/db/CreateTradingDB.hpp"

#include "globalvariables.hpp"

#ifndef TEST_SRC_CREATETRADINGDBENVIRONMENT_HPP_
#define TEST_SRC_CREATETRADINGDBENVIRONMENT_HPP_

/**
 *
 */
class CreateTradingDBEnvironment : public ::testing::Environment
{
public:
	CreateTradingDBEnvironment():
		Environment(),
		m_createTradingDB(),
		m_connectionOptions(getConnectionOptions())
	{
	}

	virtual ~CreateTradingDBEnvironment() override {

	}

	virtual void SetUp() override {
		m_createTradingDB.dropDatabase(*m_connectionOptions);
		m_createTradingDB.openDatabase(*m_connectionOptions);
		m_createTradingDB.createDatabase();
	}

	virtual void TearDown() override {
		m_createTradingDB.dropDatabase(*m_connectionOptions);
		m_createTradingDB.closeDatabase();
	}

private:
	offcenter::trading::db::CreateTradingDB m_createTradingDB;
	std::shared_ptr<offcenter::soci::MySQLOptions> m_connectionOptions;

};

#endif /* TEST_SRC_CREATETRADINGDBENVIRONMENT_HPP_ */
