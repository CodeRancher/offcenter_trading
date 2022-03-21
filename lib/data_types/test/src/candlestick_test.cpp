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
#include <gmock/gmock.h>

#include "easylogging++.h"

#include "offcenter/trading/datatypes/common/Candlestick.hpp"
#include "offcenter/trading/datatypes/calculation/Candlestick.hpp"

MATCHER_P2(MPFEq, val, range, "Not in range") {
  return (val - range) <= arg && arg <= (val + range);
}

TEST (OHLC, Creation)
{
	offcenter::trading::datatypes::common::OHLC<int> ohlcInt({1, 2, 3, 4});
	EXPECT_EQ(ohlcInt.open,  1);
	EXPECT_EQ(ohlcInt.high,  2);
	EXPECT_EQ(ohlcInt.low,   3);
	EXPECT_EQ(ohlcInt.close, 4);

	offcenter::trading::datatypes::common::OHLC<std::string> ohlcString({"1.0", "1.1", "1.2", "1.3"});
	EXPECT_EQ(ohlcString.open,  "1.0");
	EXPECT_EQ(ohlcString.high,  "1.1");
	EXPECT_EQ(ohlcString.low,   "1.2");
	EXPECT_EQ(ohlcString.close, "1.3");
}

TEST (OHLC, CopyStringToDouble)
{
	offcenter::trading::datatypes::common::OHLC<std::string> ohlcString({"1.0", "1.1", "1.2", "1.3"});
	offcenter::trading::datatypes::common::OHLC<double> ohlcDouble(ohlcString);
	EXPECT_EQ(ohlcDouble.open,  1.0);
	EXPECT_EQ(ohlcDouble.high,  1.1);
	EXPECT_EQ(ohlcDouble.low,   1.2);
	EXPECT_EQ(ohlcDouble.close, 1.3);
}

TEST (OHLC, CopyStringToCandlestickPrice)
{
	offcenter::trading::datatypes::common::OHLC<std::string> ohlcString({"1.0", "1.1", "1.2", "1.3"});
	offcenter::trading::datatypes::common::OHLC<offcenter::trading::datatypes::calculation::CandlestickPrice> ohlcCandlestickPrice(ohlcString);
	offcenter::common::MPF range(0.00000000001);
	EXPECT_THAT(ohlcCandlestickPrice.open,  MPFEq(offcenter::common::MPF(1.0), range));
	EXPECT_THAT(ohlcCandlestickPrice.high,  MPFEq(offcenter::common::MPF(1.1), range));
	EXPECT_THAT(ohlcCandlestickPrice.low,   MPFEq(offcenter::common::MPF(1.2), range));
	EXPECT_THAT(ohlcCandlestickPrice.close, MPFEq(offcenter::common::MPF(1.3), range));
}

TEST (OHLC, InvalidInitialization)
{
	EXPECT_THROW(
			offcenter::trading::datatypes::common::OHLC<int> ohlcInt({1, 2, 3, 4, 5}),
			offcenter::trading::common::InvalidInitialization);

	EXPECT_THROW(
			offcenter::trading::datatypes::common::OHLC<std::string> ohlcString({"1.0", "1.1", "1.2", "1.3", "1.4"}),
			offcenter::trading::common::InvalidInitialization);
}

TEST (BidAskCandlestick, Creation)
{
	const std::string startTimeStr{"2000-01-01T00:00:00.000000000Z"};
	const std::string endTimeStr{"2000-01-02T00:00:00.000000000Z"};
	const offcenter::common::UTCDateTime startTime{offcenter::common::make_UTCDateTimeFromISO8601(startTimeStr)};
	const offcenter::common::UTCDateTime endTime{offcenter::common::make_UTCDateTimeFromISO8601(endTimeStr)};

	offcenter::trading::datatypes::common::BidAskCandlestick<int> candleInt(startTime, endTime, {1, 2, 3, 4}, {5, 6, 7, 8}, 10);
	EXPECT_EQ(candleInt.startTime, startTime);
	EXPECT_EQ(candleInt.endTime, endTime);
	EXPECT_EQ(candleInt.bid.open,  1);
	EXPECT_EQ(candleInt.bid.high,  2);
	EXPECT_EQ(candleInt.bid.low,   3);
	EXPECT_EQ(candleInt.bid.close, 4);
	EXPECT_EQ(candleInt.ask.open,  5);
	EXPECT_EQ(candleInt.ask.high,  6);
	EXPECT_EQ(candleInt.ask.low,   7);
	EXPECT_EQ(candleInt.ask.close, 8);
	EXPECT_EQ(candleInt.volume,  10);

	offcenter::trading::datatypes::common::BidAskCandlestick<std::string> candleString(startTimeStr, endTimeStr, {"1.0", "1.1", "1.2", "1.3"}, {"2.0", "2.1", "2.2", "2.3"}, 10);
	EXPECT_EQ(candleString.startTime, startTime);
	EXPECT_EQ(candleString.endTime, endTime);
	EXPECT_EQ(candleString.bid.open,  "1.0");
	EXPECT_EQ(candleString.bid.high,  "1.1");
	EXPECT_EQ(candleString.bid.low,   "1.2");
	EXPECT_EQ(candleString.bid.close, "1.3");
	EXPECT_EQ(candleString.ask.open,  "2.0");
	EXPECT_EQ(candleString.ask.high,  "2.1");
	EXPECT_EQ(candleString.ask.low,   "2.2");
	EXPECT_EQ(candleString.ask.close, "2.3");
	EXPECT_EQ(candleString.volume,  10);

	offcenter::trading::datatypes::common::BidAskCandlestick<double> candleDouble(startTimeStr, endTimeStr, {"1.0", "1.1", "1.2", "1.3"}, {"2.0", "2.1", "2.2", "2.3"}, 10);
	EXPECT_EQ(candleDouble.startTime, startTime);
	EXPECT_EQ(candleDouble.endTime, endTime);
	EXPECT_EQ(candleDouble.bid.open,  1.0);
	EXPECT_EQ(candleDouble.bid.high,  1.1);
	EXPECT_EQ(candleDouble.bid.low,   1.2);
	EXPECT_EQ(candleDouble.bid.close, 1.3);
	EXPECT_EQ(candleDouble.ask.open,  2.0);
	EXPECT_EQ(candleDouble.ask.high,  2.1);
	EXPECT_EQ(candleDouble.ask.low,   2.2);
	EXPECT_EQ(candleDouble.ask.close, 2.3);
	EXPECT_EQ(candleDouble.volume,  10);
}

TEST (BidAskCandlestick_Calculation, Creation)
{
	const std::string startTimeStr("2000-01-01T00:00:00.000000000Z");
	const std::string endTimeStr("2000-01-01T00:00:00.000000000Z");
	const offcenter::common::UTCDateTime startTime{offcenter::common::make_UTCDateTimeFromISO8601(startTimeStr)};
	const offcenter::common::UTCDateTime endTime{offcenter::common::make_UTCDateTimeFromISO8601(endTimeStr)};

	offcenter::trading::datatypes::calculation::BidAskCandlestick candle1(startTime, endTime, {1, 2, 3, 4}, {5, 6, 7, 8}, 10);
	EXPECT_EQ(candle1.startTime, startTime);
	EXPECT_EQ(candle1.endTime, endTime);
	EXPECT_EQ(candle1.bid.open,  1);
	EXPECT_EQ(candle1.bid.high,  2);
	EXPECT_EQ(candle1.bid.low,   3);
	EXPECT_EQ(candle1.bid.close, 4);
	EXPECT_EQ(candle1.ask.open,  5);
	EXPECT_EQ(candle1.ask.high,  6);
	EXPECT_EQ(candle1.ask.low,   7);
	EXPECT_EQ(candle1.ask.close, 8);
	EXPECT_EQ(candle1.volume,  10);

	offcenter::trading::datatypes::common::BidAskCandlestick<std::string> candle_string(startTimeStr, endTimeStr, {"1.0", "2.0", "3.0", "4.0"}, {"5.0", "6.0", "7.0", "8.0"}, 10);
	offcenter::trading::datatypes::calculation::BidAskCandlestick candle2(candle_string);
	EXPECT_EQ(candle2.startTime, startTime);
	EXPECT_EQ(candle2.endTime, endTime);
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

