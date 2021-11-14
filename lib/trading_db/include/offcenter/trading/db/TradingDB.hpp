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
 * @file   TradingDB.hpp
 * @author Scott Brauer
 * @date   03-19-2021
 */
#ifndef OFFCENTER_TRADING_DB_TRADINGDB_HPP_
#define OFFCENTER_TRADING_DB_TRADINGDB_HPP_

#include "offcenter/soci/Session.hpp"
#include "offcenter/soci/MySQLOptions.hpp"

#include "offcenter/trading/datatypes/Instrument.hpp"
#include "offcenter/trading/datatypes/CandlestickDataSeries.hpp"
#include "offcenter/trading/datatypes/CandlestickData.hpp"
#include "offcenter/trading/datatypes/LookupTables.hpp"
#include "offcenter/trading/datatypes/TableInfo.hpp"

namespace offcenter {
namespace trading {
namespace db {

class TradingDB
{
public:
	const static int g_sessionPoolSize = 4;

public:
	TradingDB();
	virtual ~TradingDB();

	virtual void initialize(const offcenter::soci::MySQLOptions& options);

	void instrumentCreate(const offcenter::trading::datatypes::Instrument& instrument);
	void instrumentRead(offcenter::trading::datatypes::Instrument& instrument, const std::string& name);
	void instrumentRead(offcenter::trading::datatypes::Instrument& instrument, unsigned instrument_id);
	void instrumentUpdate(const offcenter::trading::datatypes::Instrument& instrument);
	void instrumentDelete(const std::string& name);
	void instrumentDelete(unsigned instrument_id);
	unsigned int  instrumentsCount();

	void candlestickDataSeriesCreate(const offcenter::trading::datatypes::CandlestickDataSeriesByName& candlestick_data_series, bool updateOnDuplicate = false);

	void candlestickDataSeriesIDRead(
			offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series,
			const std::string& broker_data_source_name,
	        const std::string& broker_name,
	        const std::string& instrument_name,
	        const std::string& candlestick_granularity_name);

	void candlestickDataSeriesRead(std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete>& candlestick_data_series);
	void candlestickDataSeriesRead(offcenter::trading::datatypes::CandlestickDataSeriesComplete& candlestick_data_series, unsigned candlestick_data_series_id);
	void candlestickDataSeriesRead(
			unsigned& candlestick_data_series_id,
	        const offcenter::trading::datatypes::CandlestickDataSeriesByName &candlestick_data_series_by_name);
	void candlestickDataSeriesUpdate(const offcenter::trading::datatypes::CandlestickDataSeriesByName& candlestick_data_series);
	void candlestickDataSeriesDelete(unsigned candlestick_data_series_id);

	void candlestickDataCreate(const offcenter::trading::datatypes::CandlestickDataCreate& candlestick_data_create);
	void candlestickDataRead(offcenter::trading::datatypes::CandlestickDataRange &candlestick_range, const offcenter::trading::datatypes::CandlestickDataSearch& candlestick_data_search);
	void candlestickDataUpdate(const offcenter::trading::datatypes::CandlestickData& candlestick_data);
	void candlestickDataDelete(unsigned candlestick_data_id);
	void candlestickDataAfterDate(offcenter::trading::datatypes::CandlestickData& candlestick_data, const offcenter::trading::datatypes::CandlestickDataAfterDate& candlestick_search);

	unsigned int currencyPairCount();

	void brokersRead(offcenter::trading::datatypes::AllBroker& records);
	void brokerDataSourceRead(offcenter::trading::datatypes::AllBrokerDataSource& records);

	void instrumentTypeRead(offcenter::trading::datatypes::AllInstrumentType& records);
	void guaranteedStopLossOrderModeForInstrumentRead(offcenter::trading::datatypes::AllGuaranteedStopLossOrderModeForInstrument& records);
	void dayOfWeek(offcenter::trading::datatypes::AllDayOfWeek& records);
	void candlestickGranularity(offcenter::trading::datatypes::AllCandlestickGranularity& records);
	void currency(offcenter::trading::datatypes::AllCurrency& records);

	void candlestickDataFirstRecord(unsigned candlestick_data_series_id, offcenter::common::UTCDateTime& record_time, unsigned long long& record_id);
	void candlestickDataLastRecord(unsigned candlestick_data_series_id, offcenter::common::UTCDateTime& record_time, unsigned long long& record_id,
			std::string& last_record_bid_close,
			std::string& last_record_ask_close);
	void candlestickDataFirstLastRecord(unsigned candlestick_data_series_id, offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord &record);

private:
	enum class SOCIDataExchange {
		WithDataExchange,
		WithoutDataExchange
	};

	enum class SOCITransaction {
		WithTransaction,
		WithoutTransaction
	};

	bool executeStatement(::soci::statement& st, SOCIDataExchange withDataExchange, SOCITransaction withTransaction, offcenter::soci::Session* session = nullptr);

private:
	offcenter::soci::SessionPoolManager m_sessionPoolManager;
};

} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_TRADINGDB_HPP_ */
