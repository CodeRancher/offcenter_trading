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
 * @file   CandlestickTimeRangeAmqp.hpp
 * @author Scott Brauer
 * @date   10-22-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKTIMERANGEAMQP_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKTIMERANGEAMQP_HPP_

#include "offcenter/trading/datatypes/CandlestickTimeRange.hpp"

#include "offcenter/amqp/Helper.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
struct CandlestickTimeRangeAmqp:
		public CandlestickTimeRange
{
	using MessageType = cms::MapMessage;
};

void to_cmsMessage(offcenter::trading::datatypes::CandlestickTimeRangeAmqp::MessageType* j, const offcenter::trading::datatypes::CandlestickTimeRangeAmqp& p);
void from_cmsMessage(const offcenter::trading::datatypes::CandlestickTimeRangeAmqp::MessageType* j, offcenter::trading::datatypes::CandlestickTimeRangeAmqp& p);

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKTIMERANGEAMQP_HPP_ */
