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
 * @file   OandaTradingDB.hpp
 * @author Scott Brauer
 * @date   04-06-2021
 */

#ifndef TRADING_DB_OANDA_OANDATRADINGDB_HPP_
#define TRADING_DB_OANDA_OANDATRADINGDB_HPP_

#include <vector>

#include "offcenter/common/soci/Session.hpp"
#include "offcenter/common/soci/MySQLOptions.hpp"

#include "offcenter/trading/datatypes/oanda/Instrument.hpp"

namespace offcenter {
namespace trading {
namespace db {
namespace oanda {

/**
 *
 */
class OandaTradingDB
{
public:
	const static int g_sessionPoolSize = 4;

public:
	OandaTradingDB();
	virtual ~OandaTradingDB();

	void initialize(const offcenter::common::soci::MySQLOptions &options);

	void instrumentCreate(const offcenter::trading::datatypes::oanda::InstrumentWithIDs& instrument);
	void instrumentRead(offcenter::trading::datatypes::oanda::Instrument& instrument, const std::string name);
	void instrumentRead(offcenter::trading::datatypes::oanda::Instrument& instrument, unsigned instrument_id);
	void instrumentUpdate(const offcenter::trading::datatypes::oanda::Instrument& instrument);
	void instrumentDelete(const std::string name);
	void instrumentDelete(unsigned instrument_id);

	unsigned int instrumentCount();

	void financingDayOfWeekCreate(const offcenter::trading::datatypes::oanda::FinancingDayOfWeek& financingDayOfWeek, unsigned int instrument_id = 0);
	void financingDayOfWeekCreate(const std::vector<offcenter::trading::datatypes::oanda::FinancingDayOfWeek>& financingDayOfWeek, unsigned int instrument_id = 0);

	void financingDayOfWeekUpdate(const offcenter::trading::datatypes::oanda::FinancingDayOfWeek& financingDayOfWeek);
	void financingDayOfWeekUpdate(const std::vector<offcenter::trading::datatypes::oanda::FinancingDayOfWeek>& financingDayOfWeek, unsigned int instrument_id);

private:
	offcenter::common::soci::SessionPoolManager m_sessionPoolManager;
};

} /* namespace oanda */
} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* TRADING_DB_OANDA_OANDATRADINGDB_HPP_ */
