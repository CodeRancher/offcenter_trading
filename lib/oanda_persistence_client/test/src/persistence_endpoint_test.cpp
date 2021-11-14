/**
 * Copyright 2020 Scott Brauer
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
 * @file   persistence_endpoint_test.cpp
 * @author Scott Brauer
 * @date   06-01-2021
 */

//#include <iostream>
//#include <sstream>
//#include <thread>
//#include <chrono>

#include "easylogging++.h"

#include <gtest/gtest.h>

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"

TEST (PersistenceEndpoints, SaveInstrument)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::Instrument instrument;
	instrument.instrument_id = 0;
	instrument.name = "Test1";
	instrument.display_name = "Test 1";
	endpoints.instrumentCreate("fxpractice", instrument);

	offcenter::trading::datatypes::Instrument instrumentRead;
	instrumentRead = endpoints.instrumentRead("fxpractice", instrument.name);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);

	instrumentRead = endpoints.instrumentRead("fxpractice", instrumentRead.instrument_id);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);

	endpoints.instrumentDelete("fxpractice", instrument.name);

}

TEST (PersistenceEndpoints, SaveCandlestickDataSeries)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	std::string instrumentName = "EUR_USD";
	offcenter::trading::datatypes::Instrument instrument;
	instrument.instrument_id = 0;
	instrument.name = instrumentName;
	instrument.display_name = instrumentName;
	endpoints.instrumentCreate("fxpractice", instrument);

	offcenter::trading::datatypes::CandlestickDataSeriesByName dataSeries;
	dataSeries.candlestick_data_series_id = 0;
	dataSeries.instrument_name = instrumentName;
	dataSeries.broker_name = "oanda";
	dataSeries.broker_data_source_name = "fxpractice";
	dataSeries.candlestick_granularity_name = "S5";
	endpoints.candlestickDataSeriesCreate("fxpractice", dataSeries);

	std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete> savedSeries;
	savedSeries = endpoints.candlestickDataSeriesRead("fxpractice");
	EXPECT_EQ(savedSeries.size(), 1);

	if (savedSeries.size() > 0) {
		offcenter::trading::datatypes::CandlestickDataSeriesComplete singleSeries;
		singleSeries = endpoints.candlestickDataSeriesRead("fxpractice", savedSeries[0].candlestick_data_series_id);
		EXPECT_EQ(singleSeries.instrument_name, "EUR_USD");

		offcenter::trading::datatypes::CandlestickDataSeriesByName ds;
		ds = endpoints.candlestickDataSeriesIDRead(dataSeries.broker_data_source_name, dataSeries.broker_name, dataSeries.instrument_name, dataSeries.candlestick_granularity_name);
		EXPECT_EQ(ds.candlestick_data_series_id, savedSeries[0].candlestick_data_series_id);
		EXPECT_EQ(ds.instrument_name, dataSeries.instrument_name);
		EXPECT_EQ(ds.broker_name, dataSeries.broker_name);
		EXPECT_EQ(ds.broker_data_source_name, dataSeries.broker_data_source_name);
		EXPECT_EQ(ds.candlestick_granularity_name, dataSeries.candlestick_granularity_name);

		offcenter::trading::datatypes::common::DeleteRecord deleteRecord;
		deleteRecord = endpoints.candlestickDataSeriesDelete("fxpractice", savedSeries[0].candlestick_data_series_id);
		EXPECT_EQ(deleteRecord.success, true);
	}

	endpoints.instrumentDelete("fxpractice", instrument.name);
}

TEST (PersistenceEndpoints, SaveCandlestickData)
{
	using namespace date;
    using namespace std::chrono;

    offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

    // Add an Instrument
	std::string instrumentName = "ZAR_JPY";
	offcenter::trading::datatypes::Instrument instrument;
	instrument.instrument_id = 0;
	instrument.name = instrumentName;
	instrument.display_name = instrumentName;
	endpoints.instrumentCreate("fxpractice", instrument);

	// Add a Candlestick Data Series
	offcenter::trading::datatypes::CandlestickDataSeriesByName dataSeries;
	dataSeries.candlestick_data_series_id = 0;
	dataSeries.instrument_name = instrumentName;
	dataSeries.broker_name = "oanda";
	dataSeries.broker_data_source_name = "fxpractice";
	dataSeries.candlestick_granularity_name = "S5";
	endpoints.candlestickDataSeriesCreate("fxpractice", dataSeries);

	// Read the saved series
	std::vector<offcenter::trading::datatypes::CandlestickDataSeriesComplete> savedSeries;
	savedSeries = endpoints.candlestickDataSeriesRead("fxpractice");
	ASSERT_EQ(savedSeries.size(), 1);

	// Add Candlestick data
	offcenter::trading::datatypes::CandlestickDataCreate candlestickDataCreate;
	candlestickDataCreate.broker = dataSeries.broker_name;
	candlestickDataCreate.broker_source = dataSeries.broker_data_source_name;
	candlestickDataCreate.instrument = instrumentName;
	candlestickDataCreate.granularity = dataSeries.candlestick_granularity_name;

	using fiveSeconds = std::chrono::duration<int, std::ratio_multiply<std::ratio<5>, std::chrono::seconds::period>>;
	offcenter::trading::datatypes::CandlestickData candlestickData;
	for (int x = 0; x < 10; x++) {
		candlestickData.start_time = sys_days{2015_y/March/22} + 11h + fiveSeconds{x};

		candlestickData.bid_open = std::to_string(static_cast<double>(x) * 1.0);
		candlestickData.bid_high = std::to_string(static_cast<double>(x) * 2.0);
		candlestickData.bid_low = std::to_string(static_cast<double>(x) * 3.0);
		candlestickData.bid_close = std::to_string(static_cast<double>(x) * 4.0);
		candlestickData.bid_gap_open = std::to_string(static_cast<double>(x) * 5.0);
		candlestickData.ask_open = std::to_string(static_cast<double>(x) * 6.0);
		candlestickData.ask_high = std::to_string(static_cast<double>(x) * 7.0);
		candlestickData.ask_low = std::to_string(static_cast<double>(x) * 8.0);
		candlestickData.ask_close = std::to_string(static_cast<double>(x) * 9.0);
		candlestickData.ask_gap_open = std::to_string(static_cast<double>(x) * 10.0);
		candlestickData.volume = x * 11;

		candlestickDataCreate.candlestick_data.push_back(candlestickData);
	}
	endpoints.candlestickDataCreate("fxpractice", candlestickDataCreate);

	// Read Candlestick Data
	offcenter::trading::datatypes::CandlestickDataSearch search;
	search.broker = dataSeries.broker_name;
	search.broker_source = dataSeries.broker_data_source_name;
	search.instrument = instrumentName;
	search.granularity = dataSeries.candlestick_granularity_name;
	search.start_time = sys_days{2015_y/March/22} + 11h;
	search.end_time = sys_days{2015_y/March/22} + 11h + fiveSeconds{9};
	offcenter::trading::datatypes::CandlestickDataRange candlestickDataRange =
			endpoints.candlestickDataRead("fxpractice", search);

	EXPECT_EQ(candlestickDataRange.broker, dataSeries.broker_name);
	EXPECT_EQ(candlestickDataRange.broker_source, dataSeries.broker_data_source_name);
	EXPECT_EQ(candlestickDataRange.instrument, instrumentName);
	EXPECT_EQ(candlestickDataRange.granularity, dataSeries.candlestick_granularity_name);
	EXPECT_EQ(candlestickDataRange.start_time, search.start_time);
	EXPECT_EQ(candlestickDataRange.end_time, search.end_time);
	EXPECT_EQ(candlestickDataRange.candlestick_data.size(), 10);

	// Read First/Last Candlestick data
	offcenter::trading::datatypes::tableinfo::candlestickdata::FirstLastRecord firstLastRecord =
			endpoints.candlestickDataSeriesFirstLast("fxpractice", savedSeries[0].candlestick_data_series_id, "default");
	EXPECT_EQ(firstLastRecord.candlestick_data_series_id, savedSeries[0].candlestick_data_series_id);
	EXPECT_EQ(firstLastRecord.first_record_time, candlestickDataRange.start_time);
	EXPECT_EQ(firstLastRecord.last_record_time, candlestickDataRange.end_time);
	EXPECT_EQ(firstLastRecord.last_record_bid_close, candlestickDataCreate.candlestick_data[candlestickDataCreate.candlestick_data.size()-1].bid_close);
	EXPECT_EQ(firstLastRecord.last_record_ask_close, candlestickDataCreate.candlestick_data[candlestickDataCreate.candlestick_data.size()-1].ask_close);
	LOG(DEBUG) << "First: " << offcenter::common::UTCDateTimeToISO8601(firstLastRecord.last_record_time) << " Last: " << offcenter::common::UTCDateTimeToISO8601(candlestickDataRange.end_time);

	// Delete all data
	endpoints.instrumentDelete("fxpractice", instrument.name);
}

TEST (PersistenceEndpoints, CountInstruments)
{
    offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	std::string instrumentName = "EUR_USD";
	offcenter::trading::datatypes::Instrument instrument;
	instrument.instrument_id = 0;
	instrument.name = instrumentName;
	instrument.display_name = instrumentName;
	endpoints.instrumentCreate("fxpractice", instrument);

	offcenter::trading::datatypes::Instrument instrumentRead;
	instrumentRead = endpoints.instrumentRead("fxpractice", instrument.name);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);

	EXPECT_EQ(endpoints.instrumentsCount("fxpractice"), 1);

	//endpoints.instrumentDelete("fxpractice", instrument.name);
}

