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
 * @file   Instrument.hpp
 * @author Scott Brauer
 * @date   05-30-2021
 */
#ifndef OFFCENTER_TRADING_DATATYPES_INSTRUMENT_HPP_
#define OFFCENTER_TRADING_DATATYPES_INSTRUMENT_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
struct Instrument
{
	unsigned instrument_id;
	std::string name;
	std::string display_name;
};

/**
 * Instrument by broker, source, and granularity
 */
struct BrokerInstrumentGranularity
{
	std::string broker_name;					///< Broker name
	std::string broker_data_source_name;		///< Data source for broker
	std::string instrument_name;				///< Name of instrument
	std::string candlestick_granularity_name;	///< Granularity of candlestick
};

} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_INSTRUMENT_HPP_ */
