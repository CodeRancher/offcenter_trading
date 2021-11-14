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
 * @file   LookupTablesJson.hpp
 * @author Scott Brauer
 * @date   06-23-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_LOOKUPTABLESJSON_HPP_
#define OFFCENTER_TRADING_DATATYPES_LOOKUPTABLESJSON_HPP_

#include "offcenter/trading/datatypes/LookupTables.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		BrokerDB,
		broker_id,
		name,
		display_name,
		description
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllBroker,
		records
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		BrokerDataSource,
		broker_data_source_id,
		name,
		display_name,
		description,
		broker_id
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllBrokerDataSource,
		records
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		InstrumentType,
		instrument_type_id,
		name,
		description
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllInstrumentType,
		records
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		GuaranteedStopLossOrderModeForInstrument,
		guaranteed_stop_loss_order_mode_for_instrument_id,
		name,
		description
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllGuaranteedStopLossOrderModeForInstrument,
		records
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		DayOfWeek,
		day_of_week_id,
		name,
		description
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllDayOfWeek,
		records
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		CandlestickGranularity,
		candlestick_granularity_id,
		name,
		description,
		alignment,
		duration_in_seconds
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllCandlestickGranularity,
		records
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		Currency,
		currency_id,
		name,
		currency,
		numeric_code
)

/**
 *
 */
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
		AllCurrency,
		records
)


} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_LOOKUPTABLESJSON_HPP_ */
