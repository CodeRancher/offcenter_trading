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
 * @file   CandlestickTimeRangeAmqp.cpp
 * @author Scott Brauer
 * @date   10-22-2021
 */

#include "offcenter/common/DateTime.hpp"
#include "offcenter/trading/datatypes/CandlestickTimeRangeAmqp.hpp"
#include "offcenter/trading/datatypes/InstrumentAmqp.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

void to_cmsMessage(offcenter::trading::datatypes::CandlestickTimeRangeAmqp::MessageType* j, const offcenter::trading::datatypes::CandlestickTimeRangeAmqp& p) {
	to_cmsMessage(j, static_cast<const offcenter::trading::datatypes::BrokerInstrumentGranularity&>(p));

	std::string tmpString;

	tmpString = offcenter::common::UTCDateTimeToISO8601(p.range_begin);
	j->setString("range_begin", tmpString);

	tmpString = offcenter::common::UTCDateTimeToISO8601(p.range_end);
	j->setString("range_end", tmpString);
}

void from_cmsMessage(const offcenter::trading::datatypes::CandlestickTimeRangeAmqp::MessageType* j, offcenter::trading::datatypes::CandlestickTimeRangeAmqp& p) {
	from_cmsMessage(j, static_cast<offcenter::trading::datatypes::BrokerInstrumentGranularity&>(p));

	std::string tmpString;

	tmpString = j->getString("range_begin");
	p.range_begin = offcenter::common::make_UTCDateTimeFromISO8601(tmpString);

	tmpString = j->getString("range_end");
	p.range_end = offcenter::common::make_UTCDateTimeFromISO8601(tmpString);
}

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */
