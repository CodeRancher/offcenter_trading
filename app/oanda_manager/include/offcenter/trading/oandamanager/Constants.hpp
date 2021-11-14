/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the );
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
 * @file   Constants.hpp
 * @author Scott Brauer
 * @date   05-10-2021
 */

#ifndef OFFCENTER_TRADING_OANDAMANAGER_CONSTANTS_HPP_
#define OFFCENTER_TRADING_OANDAMANAGER_CONSTANTS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace oandamanager {

namespace queuename {

//	inline constexpr std::string base = "offcenter.trade.";
//	constexpr std::string add_broker {"add.broker.<broker_id>"};
//	constexpr std::string add_broker_server {"add.<broker_id>.server.<server_id>"};
//	constexpr std::string add_broker_server_instrument {"add.<broker_id>.<server_id>.instrument.<instrument_id>"};
//	constexpr std::string add_broker_server_instrument_candlestick_timeframe {"add.<broker_id>.<server_id>.<instrument_id>.candlestick.<timeframe_id>"};

} /* namespace queuename */

namespace oanda {

	inline constexpr char id[] = "oanda";
	inline constexpr char name[] = "Oanda";
	inline constexpr char description[] = "Co-founded by Dr. Stumm, a computer scientist and Dr. Olsen, an economist, the company was born out of the belief that the Internet and technology would open up the markets for both currency data and trading.";

} /* namespace oanda */

} /* namespace oandamanager */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_OANDAMANAGER_CONSTANTS_HPP_ */
