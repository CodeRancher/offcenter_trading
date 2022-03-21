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
#include "offcenter/common/Conversions.hpp"

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
	 * Generic initialization of OHLC
	 * 
	 * There must be a conversion routine to change SourceType to OHLCType
	 *
	 * @param lOpen Opening price of timeframe
	 * @param lHigh Highest price of timeframe
	 * @param lLow Lowest price of timeframe
	 * @param lClose Closing price of timeframe
	 */
	template<typename SourceType>
	OHLC(const SourceType& lOpen, const SourceType& lHigh, const SourceType& lLow, const SourceType& lClose)
	{
		using namespace offcenter::common;
		convertTo(lOpen, open);
		convertTo(lHigh, high);
		convertTo(lLow, low);
		convertTo(lClose, close);
	}

	/**
	 * Initialization of OHLC with initializer list.
	 * 
	 * There must be a conversion routine to change SourceType to OHLCType
	 *
	 * @param list OHLC data in open, high, low, close order
	 */
	template<typename SourceType>
	OHLC(std::initializer_list<SourceType> list) {
		if (list.size() != 4) { throw offcenter::trading::common::InvalidInitialization("Initializer list for OHLC must have 4 elements."); }

		std::vector<SourceType> elements(list);
		using namespace offcenter::common;
		convertTo(elements[0], open);
		convertTo(elements[1], high);
		convertTo(elements[2], low);
		convertTo(elements[3], close);
	}

	/**
	 * Copy constructor
	 * 
	 * There must be a conversion routine to change OtherOHLCType to OHLCType
	 *
	 * @param other Other OHLC to copy from
	 */
	template<typename OtherOHLCType>
	OHLC(const OHLC<OtherOHLCType>& other)
	{
		using namespace offcenter::common;
		convertTo(other.open, open);
		convertTo(other.high, high);
		convertTo(other.low, low);
		convertTo(other.close, close);
	}

	OHLCType open;	///> Open price of timeframe
	OHLCType high;	///> Highest price of timeframe
	OHLCType low;	///> Lowest price of timeframe
	OHLCType close;	///> Closing price of timeframe
};

/**
 * Candlestick data for bid and ask with start time and volume
 *
 * @tparam OHLCType Type for OHLC elements
 */
template<typename OHLCType, typename DateTimeType = offcenter::common::UTCDateTime>
struct BidAskCandlestick {
	/**
	 * Initialization of Bid/Ask Candlestick
	 * 
	 * There must be a conversion routine to change SourceOHLCType to OHLCType
	 * There must be a conversion routine to change SourceDateTimeType to DateTimeType
	 *
	 * @param lStartTime Starting time of candlestick
	 * @param lEndTime Ending time of candlestick
	 * @param lBidList Initializer list for Bid OHLC data
	 * @param lAskList Initializer list for Ask OHLC data
	 * @param lVolume Volume data for candlestick
	 */
	template<typename SourceOHLCType, typename SourceDateTimeType>
	BidAskCandlestick(
		const SourceDateTimeType& lStartTime,
		const SourceDateTimeType& lEndTime,
		std::initializer_list<SourceOHLCType> lBidList,
		std::initializer_list<SourceOHLCType> lAskList,
		unsigned lVolume
	):
		bid(lBidList),
		ask(lAskList),
		volume(lVolume)
	{
		using namespace offcenter::common;
		convertTo(lStartTime, startTime);
		convertTo(lEndTime, endTime);
	}

	/**
	 * Copy constructor.
	 *
	 * @param other BidAskCandlestick element to copy
	 * @tparam OtherOHLCType OHLCType for other element
	 */
	template<typename OtherOHLCType>
	BidAskCandlestick(const BidAskCandlestick<OtherOHLCType>& other):
		bid(other.bid),
		ask(other.ask),
		volume(other.volume)
	{
		using namespace offcenter::common;
		convertTo(other.startTime, startTime);
		convertTo(other.endTime, endTime);
	}

	DateTimeType startTime; ///> Start time of timeframe
	DateTimeType endTime; ///> End time of timeframe
	OHLC<OHLCType> bid;	///> Bid OHLC data
	OHLC<OHLCType> ask;	///> Ask OHLC data
	unsigned volume;	///> Number of elements sold during timeframe
};

} /* namespace common */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICK_HPP_ */
