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
 * @file   CandlestickDataSeries.hpp
 * @author Scott Brauer
 * @date   06-01-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIES_HPP_
#define OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIES_HPP_

#include "offcenter/trading/datatypes/Instrument.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
struct CandlestickDataSeries
{
	unsigned candlestick_data_series_id;
	unsigned instrument_id;
	int broker_data_source_id;
	int candlestick_granularity_id;
};

/**
 *
 */
struct CandlestickDataSeriesByName:
		public offcenter::trading::datatypes::BrokerInstrumentGranularity
{
	unsigned candlestick_data_series_id;
};

/**
 *
 */
struct CandlestickDataSeriesComplete
{
	unsigned candlestick_data_series_id;
	unsigned instrument_id;
	std::string instrument_name;
	int broker_id;
	std::string broker_name;
	std::string broker_display_name;
	int broker_data_source_id;
	std::string broker_data_source_name;
	std::string broker_data_source_display_name;
	int candlestick_granularity_id;
	std::string candlestick_granularity_name;
};

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_CANDLESTICKDATASERIES_HPP_ */
