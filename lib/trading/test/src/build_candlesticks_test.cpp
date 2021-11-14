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
 * @file   build_candlesticks_test.cpp
 * @author Scott Brauer
 * @date   11-02-2021
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "offcenter/trading/processing/BuildCandlesticks.hpp"

TEST (BuildCandlesticks, OptionsFromCommandLine)
{
	using namespace std::chrono_literals;
	offcenter::trading::processing::BuildCandlesticks buildCandlesticks;

	offcenter::trading::datatypes::CandlestickData candlestickData;
	candlestickData.start_time = offcenter::common::make_UTCDateTimeFromISO8601("1970-01-01T00:00:00.000000000Z");
	candlestickData.candlestick_data_series_id = 10;

	for (int x = 1; x < 1000; x++) {

		candlestickData.candlestick_data_id = x;
		candlestickData.bid_open = std::to_string(x - 0.5);
		candlestickData.bid_high = std::to_string(x + 0.5);
		candlestickData.bid_low = std::to_string(x - 0.75);
		candlestickData.bid_close = std::to_string(x + 0.75);
		candlestickData.bid_gap_open = "0.0";
		candlestickData.ask_open = std::to_string(x - 0.75);
		candlestickData.ask_high = std::to_string(x + 0.25);
		candlestickData.ask_low = std::to_string(x - 1.00);
		candlestickData.ask_close = std::to_string(x + 0.5);
		candlestickData.ask_gap_open = "0.0";
		candlestickData.volume = x;
		buildCandlesticks.addCandlestick(candlestickData);
		candlestickData.start_time += 5s;
	}
}
