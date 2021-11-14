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
 * @file   BuildCandlesticks.hpp
 * @author Scott Brauer
 * @date   11-02-2021
 */

#ifndef OFFCENTER_TRADING_PROCESSING_BUILDCANDLESTICKS_HPP_
#define OFFCENTER_TRADING_PROCESSING_BUILDCANDLESTICKS_HPP_

#include "offcenter/trading/datatypes/CandlestickData.hpp"

namespace offcenter {
namespace trading {
namespace processing {

/**
 *
 */
class BuildCandlesticks
{
public:
	BuildCandlesticks();
	virtual ~BuildCandlesticks();

	void addCandlestick(offcenter::trading::datatypes::CandlestickData& candlestickData);

private:
	//BuildCandlestick

};

/*
	('S5',	'5 second candlesticks',	'minute alignment',						5),
	('S10', '10 second candlesticks',	'minute alignment',						10),
	('S15', '15 second candlesticks',	'minute alignment',						15),
	('S30', '30 second candlesticks',	'minute alignment',						30),
	('M1',	'1 minute candlesticks',	'minute alignment',						60 * 1),
	('M2',	'2 minute candlesticks',	'hour alignment',						60 * 2),
	('M4',	'4 minute candlesticks',	'hour alignment',						60 * 4),
	('M5',	'5 minute candlesticks',	'hour alignment',						60 * 5),
	('M10',	'10 minute candlesticks',	'hour alignment',						60 * 10),
	('M15',	'15 minute candlesticks',	'hour alignment',						60 * 15),
	('M30',	'30 minute candlesticks',	'hour alignment',						60 * 30),
	('H1',	'1 hour candlesticks',		'hour alignment',						60 * 60 * 1),
	('H2',	'2 hour candlesticks',		'day alignment',						60 * 60 * 2),
	('H3',	'3 hour candlesticks',		'day alignment',						60 * 60 * 3),
	('H4',	'4 hour candlesticks',		'day alignment',						60 * 60 * 4),
	('H6',	'6 hour candlesticks',		'day alignment',						60 * 60 * 6),
	('H8',	'8 hour candlesticks',		'day alignment',						60 * 60 * 8),
	('H12',	'12 hour candlesticks',		'day alignment',						60 * 60 * 12),
	('D',	'1 day candlesticks',		'day alignment',						60 * 60 * 24),
	('W',	'1 week candlesticks',		'aligned to start of week',				60 * 60 * 24 * 7),
	('M',	'1 month candlesticks',		'aligned to first day of the month',	60 * 60 * 24 * 30);
 */

} /* namespace processing */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_PROCESSING_BUILDCANDLESTICKS_HPP_ */
