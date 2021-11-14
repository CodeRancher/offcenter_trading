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
 * @file   ProcessInstrumentDataThread.hpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#ifndef OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PROCESSINSTRUMENTDATATHREAD_HPP_
#define OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PROCESSINSTRUMENTDATATHREAD_HPP_

#include <memory>
#include <utility>

#include "offcenter/common/threading/RunningThread.hpp"
#include "offcenter/common/threading/RunningThreadArray.hpp"

#include "offcenter/trading/datatypes/CandlestickDataSeries.hpp"
#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"

#include "oanda/v20/endpoint/OandaEndpoints.hpp"

namespace offcenter {
namespace trading {
namespace oandapersistenceclient {

/**
 *
 */
class ProcessInstrumentDataThread: public offcenter::common::threading::RunningThread
{
public:
	using Ptr = std::unique_ptr<ProcessInstrumentDataThread>;

public:
	explicit ProcessInstrumentDataThread(
			const std::string& broker,
			const std::string& brokerSource,
			const std::string& instrument,
			const std::string& granularity,
			const std::string& userAccount,
			const int recordCountToRead,
			offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints& persistenceEndpoints,
			oanda::v20::endpoint::OandaEndpoints::Ptr oandaEndpoints);
	virtual ~ProcessInstrumentDataThread();

protected:
	virtual void task();
	virtual void stopped();

private:
	using FirstRecordToRead = std::pair<offcenter::common::UTCDateTime, bool>;
	offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord getFirstLastRecord(offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord& firstLastRecord);
	FirstRecordToRead getFirstRecordToRead(const offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord& firstLastRecord);

private:
	const std::string m_broker;
	const std::string m_brokerSource;
	const std::string m_instrument;
	const std::string m_granularity;
	const std::string m_userAccount;
	const int m_recordCountToRead;

	const std::string m_loggerID;

	std::string m_lastBidClose;
	std::string m_lastAskClose;


	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints& m_persistenceEndpoints;
	offcenter::trading::datatypes::CandlestickDataSeriesByName m_candlestickDataSeries;
	offcenter::trading::datatypes::CandlestickDataCreate m_candlestickDataCreate;
	oanda::v20::endpoint::pricing::candles::Request m_candlesRequest;
	oanda::v20::endpoint::pricing::candles::Parameters m_candlesParameters;

	// Oanda
	oanda::v20::endpoint::OandaEndpoints::Ptr m_oandaEndpoints;


};

using ProcessInstrumentDataThreadArray = offcenter::common::threading::RunningThreadArray<ProcessInstrumentDataThread>;

} /* namespace oandapersistenceclient */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAPERSISTENCECLIENT_PROCESSINSTRUMENTDATATHREAD_HPP_ */
