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
 * @file   BrokerInstrumentGranularityAmqp.cpp
 * @author Scott Brauer
 * @date   10-21-2021
 */

#include "offcenter/trading/datatypes/InstrumentAmqp.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

void to_cmsMessage(offcenter::trading::datatypes::BrokerInstrumentGranularityAmqp::MessageType* j, const offcenter::trading::datatypes::BrokerInstrumentGranularity& p) {
	j->setString("broker_name", p.broker_name);
	j->setString("broker_data_source_name", p.broker_data_source_name);
	j->setString("instrument_name", p.instrument_name);
	j->setString("candlestick_granularity_name", p.candlestick_granularity_name);
}

void from_cmsMessage(const offcenter::trading::datatypes::BrokerInstrumentGranularityAmqp::MessageType* j, offcenter::trading::datatypes::BrokerInstrumentGranularity& p) {
	p.broker_name = j->getString("broker_name");
	p.broker_data_source_name = j->getString("broker_data_source_name");
	p.instrument_name = j->getString("instrument_name");
	p.candlestick_granularity_name = j->getString("candlestick_granularity_name");
}

void to_cmsMessage(offcenter::trading::datatypes::BrokerInstrumentGranularityAmqp::MessageType* j, const offcenter::trading::datatypes::BrokerInstrumentGranularityAmqp& p) {
	to_cmsMessage(j, static_cast<const offcenter::trading::datatypes::BrokerInstrumentGranularity&>(p));
}

void from_cmsMessage(const offcenter::trading::datatypes::BrokerInstrumentGranularityAmqp::MessageType* j, offcenter::trading::datatypes::BrokerInstrumentGranularityAmqp& p) {
	from_cmsMessage(j, static_cast<offcenter::trading::datatypes::BrokerInstrumentGranularity&>(p));
}

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */
