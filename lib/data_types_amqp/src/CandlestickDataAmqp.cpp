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
 * @file   CandlestickDataAmqp.cpp
 * @author Scott Brauer
 * @date   11-01-2021
 */
#include "offcenter/trading/datatypes/CandlestickDataAmqp.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

CandlestickDataAmqp& CandlestickDataAmqp::operator=(const CandlestickData& other) {
	CandlestickData::operator=(other);
	return *this;
}

void to_cmsMessage(
        offcenter::trading::datatypes::CandlestickDataAmqp::MessageType *j,
        const offcenter::trading::datatypes::CandlestickDataAmqp &p)
{
	j->setString("candlestick_data_id", std::to_string(p.candlestick_data_id));
	j->setString("candlestick_data_series_id", std::to_string(p.candlestick_data_series_id));

	std::string tmpString = offcenter::common::UTCDateTimeToISO8601(p.start_time);
	j->setString("start_time", tmpString);

	j->setString("bid_open", p.bid_open);
	j->setString("bid_high", p.bid_high);
	j->setString("bid_low", p.bid_low);
	j->setString("bid_close", p.bid_close);
	j->setString("bid_gap_open", p.bid_gap_open);
	j->setString("ask_open", p.ask_open);
	j->setString("ask_high", p.ask_high);
	j->setString("ask_low", p.ask_low);
	j->setString("ask_close", p.ask_close);
	j->setString("ask_gap_open", p.ask_gap_open);

	j->setString("volume", std::to_string(p.volume));
}

void from_cmsMessage(
        const offcenter::trading::datatypes::CandlestickDataAmqp::MessageType *j,
        offcenter::trading::datatypes::CandlestickDataAmqp &p)
{
	p.candlestick_data_id = std::stoull(j->getString("candlestick_data_id"));
	p.candlestick_data_series_id = std::stoul(j->getString("candlestick_data_series_id"));

	std::string tmpString = j->getString("start_time");
	p.start_time = offcenter::common::make_UTCDateTimeFromISO8601(tmpString);

	p.bid_open = j->getString("bid_open");
	p.bid_high = j->getString("bid_high");
	p.bid_low = j->getString("bid_low");
	p.bid_close = j->getString("bid_close");
	p.bid_gap_open = j->getString("bid_gap_open");
	p.ask_open = j->getString("ask_open");
	p.ask_high = j->getString("ask_high");
	p.ask_low = j->getString("ask_low");
	p.ask_close = j->getString("ask_close");
	p.ask_gap_open = j->getString("ask_gap_open");

	p.volume = std::stoul(j->getString("volume"));
}

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */
