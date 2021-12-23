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
 * @file   date_time_test.cpp
 * @author Scott Brauer
 * @date   06-12-2021
 */

#include <gtest/gtest.h>

#include "easylogging++.h"

#include "offcenter/trading/datatypes/common/Candlestick.hpp"
#include "offcenter/trading/datatypes/calculation/Candlestick.hpp"

TEST (OHLC, Creation)
{
	offcenter::trading::datatypes::common::OHLC<int> ohlc_int({1, 2, 3, 4});
	EXPECT_EQ(ohlc_int.open,  1);
	EXPECT_EQ(ohlc_int.high,  2);
	EXPECT_EQ(ohlc_int.low,   3);
	EXPECT_EQ(ohlc_int.close, 4);

	offcenter::trading::datatypes::common::OHLC<std::string> ohlc_string({"1.0", "1.1", "1.2", "1.3"});
	EXPECT_EQ(ohlc_string.open,  "1.0");
	EXPECT_EQ(ohlc_string.high,  "1.1");
	EXPECT_EQ(ohlc_string.low,   "1.2");
	EXPECT_EQ(ohlc_string.close, "1.3");
}

TEST (OHLC, InvalidInitialization)
{
	EXPECT_THROW(
			offcenter::trading::datatypes::common::OHLC<int> ohlc_int({1, 2, 3, 4, 5}),
			offcenter::trading::common::InvalidInitialization);

	EXPECT_THROW(
			offcenter::trading::datatypes::common::OHLC<std::string> ohlc_string({"1.0", "1.1", "1.2", "1.3", "1.4"}),
			offcenter::trading::common::InvalidInitialization);
}

TEST (BidAskCandlestick, Creation)
{
	const std::string startTimeStr("2000-01-01T00:00:00.000000000Z");
	const offcenter::common::UTCDateTime startTime{offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z")};

	offcenter::trading::datatypes::common::BidAskCandlestick<int> candle_int(startTime, {1, 2, 3, 4}, {5, 6, 7, 8}, 10);
	EXPECT_EQ(candle_int.startTime, startTime);
	EXPECT_EQ(candle_int.bid.open,  1);
	EXPECT_EQ(candle_int.bid.high,  2);
	EXPECT_EQ(candle_int.bid.low,   3);
	EXPECT_EQ(candle_int.bid.close, 4);
	EXPECT_EQ(candle_int.ask.open,  5);
	EXPECT_EQ(candle_int.ask.high,  6);
	EXPECT_EQ(candle_int.ask.low,   7);
	EXPECT_EQ(candle_int.ask.close, 8);
	EXPECT_EQ(candle_int.volume,  10);

	offcenter::trading::datatypes::common::BidAskCandlestick<std::string> candle_string(startTimeStr, {"1.0", "1.1", "1.2", "1.3"}, {"2.0", "2.1", "2.2", "2.3"}, 10);
	EXPECT_EQ(candle_string.startTime, startTime);
	EXPECT_EQ(candle_string.bid.open,  "1.0");
	EXPECT_EQ(candle_string.bid.high,  "1.1");
	EXPECT_EQ(candle_string.bid.low,   "1.2");
	EXPECT_EQ(candle_string.bid.close, "1.3");
	EXPECT_EQ(candle_string.ask.open,  "2.0");
	EXPECT_EQ(candle_string.ask.high,  "2.1");
	EXPECT_EQ(candle_string.ask.low,   "2.2");
	EXPECT_EQ(candle_string.ask.close, "2.3");
	EXPECT_EQ(candle_string.volume,  10);
}

TEST (BidAskCandlestick_Calculation, Creation)
{
	const std::string startTimeStr("2000-01-01T00:00:00.000000000Z");
	const offcenter::common::UTCDateTime startTime{offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z")};

	offcenter::trading::datatypes::calculation::BidAskCandlestick candle1(startTime, {1, 2, 3, 4}, {5, 6, 7, 8}, 10);
	EXPECT_EQ(candle1.startTime, startTime);
	EXPECT_EQ(candle1.bid.open,  1);
	EXPECT_EQ(candle1.bid.high,  2);
	EXPECT_EQ(candle1.bid.low,   3);
	EXPECT_EQ(candle1.bid.close, 4);
	EXPECT_EQ(candle1.ask.open,  5);
	EXPECT_EQ(candle1.ask.high,  6);
	EXPECT_EQ(candle1.ask.low,   7);
	EXPECT_EQ(candle1.ask.close, 8);
	EXPECT_EQ(candle1.volume,  10);

	offcenter::trading::datatypes::common::BidAskCandlestick<std::string> candle_string(startTimeStr, {"1.0", "2.0", "3.0", "4.0"}, {"5.0", "6.0", "7.0", "8.0"}, 10);
	offcenter::trading::datatypes::calculation::BidAskCandlestick candle2(candle_string);
	EXPECT_EQ(candle2.startTime, startTime);
	EXPECT_EQ(candle2.bid.open,  1.0);
	EXPECT_EQ(candle2.bid.high,  2.0);
	EXPECT_EQ(candle2.bid.low,   3.0);
	EXPECT_EQ(candle2.bid.close, 4.0);
	EXPECT_EQ(candle2.ask.open,  5.0);
	EXPECT_EQ(candle2.ask.high,  6.0);
	EXPECT_EQ(candle2.ask.low,   7.0);
	EXPECT_EQ(candle2.ask.close, 8.0);
	EXPECT_EQ(candle2.volume,  10);
}

