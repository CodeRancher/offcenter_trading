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
 * @file   TradingDB.cpp
 * @author Scott Brauer
 * @date   03-19-2021
 */

#include "offcenter/trading/amqp/TradingDB.hpp"

namespace offcenter {
namespace trading {
namespace db {

TradingDB::TradingDB()
{
	// TODO Auto-generated constructor stub

}

TradingDB::~TradingDB()
{
	// TODO Auto-generated destructor stub
}

void TradingDB::initialize(const offcenter::common::soci::MySQLOptions &options)
{
	m_session.open(options);
}

unsigned int TradingDB::currencyPairCount()
{
	unsigned int recordCount = 0;
	::soci::statement st = (m_session().prepare << "SELECT COUNT(currency_pair_id) FROM currency_pair", ::soci::into(recordCount));
	st.execute();
	return recordCount;
}

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */
