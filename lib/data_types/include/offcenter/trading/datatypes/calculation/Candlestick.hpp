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

#ifndef OFFCENTER_TRADING_DATATYPES_CALCULATION_CANDLESTICK_HPP_
#define OFFCENTER_TRADING_DATATYPES_CALCULATION_CANDLESTICK_HPP_

#include <boost/multiprecision/mpfr.hpp>

#include "offcenter/common/Types.hpp"
#include "offcenter/trading/datatypes/common/Candlestick.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace calculation {

//using CandlestickPrice = boost::multiprecision::mpfr_float;
using CandlestickPrice = offcenter::common::MPF;

using BidAskCandlestick = offcenter::trading::datatypes::common::BidAskCandlestick<CandlestickPrice>;

} /* namespace calculation */

namespace common {

/**
 * Calculate max value of two CandlestickPrice values.
 *
 * @param one First value
 * @param two Second value
 */
template<>
const offcenter::trading::datatypes::calculation::CandlestickPrice max<offcenter::trading::datatypes::calculation::CandlestickPrice>(
		const offcenter::trading::datatypes::calculation::CandlestickPrice& one,
		const offcenter::trading::datatypes::calculation::CandlestickPrice& two);
/**
 * Calculate min value of two CandlestickPrice values.
 *
 * @param one First value
 * @param two Second value
 */
template<>
const offcenter::trading::datatypes::calculation::CandlestickPrice min<offcenter::trading::datatypes::calculation::CandlestickPrice>(
		const offcenter::trading::datatypes::calculation::CandlestickPrice& one,
		const offcenter::trading::datatypes::calculation::CandlestickPrice& two);

/**
 * Calculate sin of a CandlestickPrice value.
 *
 * @param value Value to calc sin of
 */
template<>
const offcenter::trading::datatypes::calculation::CandlestickPrice sine(
		const offcenter::trading::datatypes::calculation::CandlestickPrice& value);

} /* namespace common */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CALCULATION_CANDLESTICK_HPP_ */
