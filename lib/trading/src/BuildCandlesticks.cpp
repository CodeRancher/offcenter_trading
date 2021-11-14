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
 * @file   BuildCandlesticks.cpp
 * @author Scott Brauer
 * @date   11-02-2021
 */

#include "easylogging++.h"

#include "offcenter/trading/processing/BuildCandlesticks.hpp"

namespace offcenter {
namespace trading {
namespace processing {

BuildCandlesticks::BuildCandlesticks()
{
	// TODO Auto-generated constructor stub

}



BuildCandlesticks::~BuildCandlesticks()
{
	// TODO Auto-generated destructor stub
}

void BuildCandlesticks::addCandlestick(
        offcenter::trading::datatypes::CandlestickData& candlestickData)
{
	LOG(INFO) << offcenter::common::UTCDateTimeToISO8601(candlestickData.start_time);
}

} /* namespace processing */
} /* namespace trading */
} /* namespace offcenter */
