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
 * @file   Candlestick.hpp
 * @author sbrauer
 * @date   Nov 22, 2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICK_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICK_HPP_

#include <cmath>

#include "offcenter/trading/common/Exceptions.hpp"
#include "offcenter/common/DateTime.hpp"


namespace offcenter {
namespace trading {
namespace datatypes {
namespace common {

/**
 * Calculate max value of two values.
 *
 * @tparam CalcType Type for calculation must work with std::max
 * @param one First value
 * @param two Second value
 */
template<typename CalcType>
const CalcType max(const CalcType& one, const CalcType& two) { return std::max(one, two); }

/**
 * Calculate min value of two values.
 *
 * @tparam CalcType Type for calculation must work with std::min
 * @param one First value
 * @param two Second value
 */
template<typename CalcType>
const CalcType min(const CalcType& one, const CalcType& two) { return std::min(one, two); }

/**
 * Calculate sine of a value.
 *
 * @tparam CalcType Type for calculation must work with std::sin
 * @param value Value to calc sine of
 */
template<typename CalcType>
const CalcType sine(const CalcType& value) { return std::sin(value); }

/**
 * Basic candlestick data with Open, High, Low, and Close
 *
 * @tparam OHLCType Type of OHLC elements
 */
template<typename OHLCType>
struct OHLC {
	/**
	 * Simple initialization of OHLC
	 */
	OHLC():
		open(),
		high(),
		low(),
		close() {}

	/**
	 * Simple initialization of OHLC
	 *
	 * @param lOpen Opening price of timeframe
	 * @param lHigh Highest price of timeframe
	 * @param lLow Lowest price of timeframe
	 * @param lClose Closing price of timeframe
	 */
	OHLC(OHLCType lOpen, OHLCType lHigh, OHLCType lLow, OHLCType lClose):
		open(lOpen),
		high(lHigh),
		low(lLow),
		close(lClose) {}

	/**
	 * Initialization of OHLC with initializer list.
	 *
	 * @param list OHLC data in open, high, low, close order
	 */
	OHLC(std::initializer_list<OHLCType> list) {
		if (list.size() != 4) { throw offcenter::trading::common::InvalidInitialization("Initializer list for OHLC must have 4 elements."); }

		std::vector<OHLCType> elements(list);
		open = elements[0];
		high = elements[1];
		low = elements[2];
		close = elements[3];
	}

	/**
	 * Copy constructor
	 *
	 * @param other Other OHLC to copy from
	 */
	template<typename OtherOHLCType>
	OHLC(const OHLC<OtherOHLCType>& other):
		open(other.open),
		high(other.high),
		low(other.low),
		close(other.close)
	{}

	OHLCType open;	///> Open price of timeframe
	OHLCType high;	///> Highest price of timeframe
	OHLCType low;	///> Lowest price of timeframe
	OHLCType close;	///> Closing price of timeframe
};

/**
 * Basic candlestick data with Open, High, Low, and Close.
 *
 * Specialization for string
 */
template<>
struct OHLC<std::string> {
	/**
	 * Simple initialization of OHLC
	 *
	 * @param lOpen Opening price of timeframe
	 * @param lHigh Highest price of timeframe
	 * @param lLow Lowest price of timeframe
	 * @param lClose Closing price of timeframe
	 */
	OHLC(std::string lOpen, std::string lHigh, std::string lLow, std::string lClose):
		open(lOpen),
		high(lHigh),
		low(lLow),
		close(lClose)
	{}

	/**
	 * Initialization of OHLC with initializer list.
	 *
	 * @param list OHLC data in that order
	 */
	OHLC(std::initializer_list<std::string> list) {
		if (list.size() != 4) { throw offcenter::trading::common::InvalidInitialization("Initializer list for OHLC must have 4 elements."); }

		std::vector<std::string> elements(list);
		open = elements[0];
		high = elements[1];
		low = elements[2];
		close = elements[3];
	}

	/**
	 * Copy constructor
	 *
	 * @param other OHLC element to copy
	 */
	template<typename OtherOHLCType>
	OHLC(const OHLC<OtherOHLCType>& other):
		open(other.open),
		high(other.high),
		low(other.low),
		close(other.close)
	{}

	std::string open;	///> Open price of timeframe
	std::string high;	///> Highest price of timeframe
	std::string low;	///> Lowest price of timeframe
	std::string close;	///> Closing price of timeframe
};

/**
 * Candlestick data for bid and ask with start time and volume
 *
 * @tparam OHLCType Type for OHLC elements
 */
template<typename OHLCType>
struct BidAskCandlestick {
	/**
	 * Initialization of Bid/Ask Candlestick
	 *
	 * @param lStartTime Starting time of candlestick
	 * @param lBidList Initializer list for Bid OHLC data
	 * @param lAskList Initializer list for Ask OHLC data
	 * @param lVolume Volume data for candlestick
	 */
	BidAskCandlestick(
		const offcenter::common::UTCDateTime& lStartTime,
		std::initializer_list<OHLCType> lBidList,
		std::initializer_list<OHLCType> lAskList,
		unsigned lVolume
	):
		startTime(lStartTime),
		bid(lBidList),
		ask(lAskList),
		volume(lVolume)
	{}

	/**
	 * Initialization of Bid/Ask Candlestick
	 *
	 * @param lStartTime Starting time of candlestick
	 * @param lBidList Initializer list for Bid OHLC data
	 * @param lAskList Initializer list for Ask OHLC data
	 * @param lVolume Volume data for candlestick
	 */
	BidAskCandlestick(
		const std::string& lStartTime,
		std::initializer_list<OHLCType> lBidList,
		std::initializer_list<OHLCType> lAskList,
		unsigned lVolume
	):
		startTime(offcenter::common::make_UTCDateTimeFromISO8601(lStartTime)),
		bid(lBidList),
		ask(lAskList),
		volume(lVolume)
	{}

	/**
	 * Copy constructor.
	 *
	 * @param other BidAskCandlestick element to copy
	 * @tparam OtherOHLCType OHLCType for other element
	 */
	template<typename OtherOHLCType>
	BidAskCandlestick(const BidAskCandlestick<OtherOHLCType>& other):
		startTime(other.startTime),
		bid(other.bid),
		ask(other.ask),
		volume(other.volume)
	{}

	offcenter::common::UTCDateTime startTime; ///> Start time of timeframe
	OHLC<OHLCType> bid;	///> Bid OHLC data
	OHLC<OHLCType> ask;	///> Ask OHLC data
	unsigned volume;	///> Number of elements sold during timeframe
};

} /* namespace common */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICK_HPP_ */
