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
 * @file   trading_db_test.cpp
 * @author Scott Brauer
 * @date   05-24-2021
 */

#include <gtest/gtest.h>

#include "offcenter/trading/db/TradingDB.hpp"
#include "offcenter/trading/datatypes/Instrument.hpp"
#include "offcenter/trading/common/Exceptions.hpp"

#include "globalvariables.hpp"

TEST (TradingDBTest, Instrument)
{
	// Connect to the database
	std::shared_ptr<offcenter::common::soci::MySQLOptions> connectionOptions = getConnectionOptions();
	offcenter::trading::db::TradingDB tradingDB;
	tradingDB.initialize(*connectionOptions);

	// Save an instrument
	offcenter::trading::datatypes::Instrument instrument;
	instrument.instrument_id = 0;
	instrument.name = "Test1";
	instrument.display_name = "Test 1";
	tradingDB.instrumentCreate(instrument);

	// Test adding duplicate record
	EXPECT_THROW(
			tradingDB.instrumentCreate(instrument),
			offcenter::trading::common::DuplicateRecord);

	offcenter::trading::datatypes::Instrument instrumentRead;

	// Read instrument by name
	tradingDB.instrumentRead(instrumentRead, instrument.name);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);
	tradingDB.instrumentDelete(instrument.name);

	// Read instrument by ID
	tradingDB.instrumentRead(instrumentRead, instrumentRead.instrument_id);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);
	tradingDB.instrumentDelete(instrument.instrument_id);
}

TEST (TradingDBTest, CandlestickFirstLastRecord)
{
	// Connect to the database
	std::shared_ptr<offcenter::common::soci::MySQLOptions> connectionOptions = getConnectionOptions();
	offcenter::trading::db::TradingDB tradingDB;
	tradingDB.initialize(*connectionOptions);

	// Save an instrument
	offcenter::trading::datatypes::Instrument instrument;
	instrument.instrument_id = 0;
	instrument.name = "FirstLastRecord";
	instrument.display_name = "FirstLastRecord";
	tradingDB.instrumentCreate(instrument);

	offcenter::trading::datatypes::CandlestickDataSeriesByName candlestickDataSeries;
	candlestickDataSeries.instrument_name = instrument.name;
	candlestickDataSeries.broker_name = "oanda";
	candlestickDataSeries.broker_data_source_name = "fxpractice";
	candlestickDataSeries.candlestick_granularity_name = "S5";
	tradingDB.candlestickDataSeriesCreate(candlestickDataSeries, false);

	offcenter::trading::datatypes::CandlestickDataSeriesByName candlestickDataSeriesInDB;
	tradingDB.candlestickDataSeriesIDRead(
			candlestickDataSeriesInDB,
			candlestickDataSeries.broker_data_source_name,
			candlestickDataSeries.broker_name,
			candlestickDataSeries.instrument_name,
			candlestickDataSeries.candlestick_granularity_name);
	EXPECT_NE(candlestickDataSeriesInDB.candlestick_data_series_id, 0);

	offcenter::trading::datatypes::CandlestickDataCreate candlestickDataCreate;
	candlestickDataCreate.broker = candlestickDataSeries.broker_name;
	candlestickDataCreate.broker_source = candlestickDataSeries.broker_data_source_name;
	candlestickDataCreate.instrument = candlestickDataSeries.instrument_name;
	candlestickDataCreate.granularity = candlestickDataSeries.candlestick_granularity_name;

	offcenter::common::UTCDateTime startTime = offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z");
	offcenter::common::UTCDateTime endTime = offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T01:00:00.000000000Z");
	offcenter::trading::datatypes::CandlestickData candlestickData;
	candlestickData.candlestick_data_id = 0;
	candlestickData.candlestick_data_series_id = candlestickDataSeriesInDB.candlestick_data_series_id;
	candlestickData.start_time = startTime;
	candlestickData.bid_open = "100.0";
	candlestickData.bid_high = "101.0";
	candlestickData.bid_low = "98.0";
	candlestickData.bid_close = "99.0";
	candlestickData.bid_gap_open = "100.5";
	candlestickData.ask_open = "200.0";
	candlestickData.ask_high = "201.0";
	candlestickData.ask_low = "198.0";
	candlestickData.ask_close = "199.0";
	candlestickData.ask_gap_open = "200.5";
	candlestickData.volume = 100;
	candlestickDataCreate.candlestick_data.push_back(candlestickData);

	candlestickData.start_time = endTime;
	candlestickData.bid_open = "99.0";
	candlestickData.bid_high = "100.0";
	candlestickData.bid_low = "97.0";
	candlestickData.bid_close = "98.0";
	candlestickData.bid_gap_open = "99.5";
	candlestickData.ask_open = "199.0";
	candlestickData.ask_high = "200.0";
	candlestickData.ask_low = "197.0";
	candlestickData.ask_close = "198.0";
	candlestickData.ask_gap_open = "199.5";
	candlestickData.volume = 200;
	candlestickDataCreate.candlestick_data.push_back(candlestickData);

	tradingDB.candlestickDataCreate(candlestickDataCreate);

	offcenter::trading::datatypes::CandlestickDataSearch candlestickSearch;
	candlestickSearch.broker = candlestickDataSeries.broker_name;
	candlestickSearch.broker_source = candlestickDataSeries.broker_data_source_name;
	candlestickSearch.instrument = candlestickDataSeries.instrument_name;
	candlestickSearch.granularity = candlestickDataSeries.candlestick_granularity_name;
	candlestickSearch.start_time = startTime;
	candlestickSearch.end_time = endTime;
	candlestickSearch.include_start_time = true;

	offcenter::trading::datatypes::CandlestickDataRange candlestickDataRange;
	tradingDB.candlestickDataRead(candlestickDataRange, candlestickSearch);

	offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord firstLastRecord;
	tradingDB.candlestickDataFirstLastRecord(candlestickDataSeriesInDB.candlestick_data_series_id, firstLastRecord);
	EXPECT_EQ(firstLastRecord.candlestick_data_series_id, candlestickDataSeriesInDB.candlestick_data_series_id);
	EXPECT_EQ(firstLastRecord.first_record_time, startTime);
	EXPECT_EQ(firstLastRecord.first_record_id, candlestickDataRange.candlestick_data[0].candlestick_data_id);
	EXPECT_EQ(firstLastRecord.last_record_time, endTime);
	EXPECT_EQ(firstLastRecord.last_record_id, candlestickDataRange.candlestick_data[1].candlestick_data_id);
	EXPECT_EQ(firstLastRecord.last_record_bid_close, candlestickData.bid_close);
	EXPECT_EQ(firstLastRecord.last_record_ask_close, candlestickData.ask_close);

	tradingDB.instrumentDelete(instrument.name);
}

