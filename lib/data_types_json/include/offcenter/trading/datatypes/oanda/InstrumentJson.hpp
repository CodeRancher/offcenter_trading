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
 * @file   InstrumentJson.hpp
 * @author Scott Brauer
 * @date   05-19-2021
 */

#ifndef OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENTJSON_HPP_
#define OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENTJSON_HPP_

#include <nlohmann/json.hpp>

#include "offcenter/trading/datatypes/oanda/Instrument.hpp"
#include "offcenter/trading/datatypes/oanda/FinancingDayOfWeekJson.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace oanda {

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
	Instrument,
	instrument_id,
	name,
	instrument_type,
	display_name,
	pip_location,
	display_precision,
	trade_units_precision,
	minimum_trade_size,
	maximum_trailing_stop_distance,
	minimum_guaranteed_stop_loss_distance,
	minimum_trailing_stop_distance,
	maximum_position_size,
	maximum_order_units,
	margin_rate,
	commission_commission,
	commission_units_traded,
	commission_minimum_commission,
	guaranteed_stop_loss_order_mode,
	guaranteed_stop_loss_order_execution_premium,
	guaranteed_stop_loss_order_level_restriction_volume,
	guaranteed_stop_loss_order_level_restriction_priceRange,
	financing_longRate,
	financing_shortRate,
	financingDaysOfWeek
)

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
	InstrumentWithIDs,
	instrument_id,
	name,
	instrument_type_id,
	display_name,
	pip_location,
	display_precision,
	trade_units_precision,
	minimum_trade_size,
	maximum_trailing_stop_distance,
	minimum_guaranteed_stop_loss_distance,
	minimum_trailing_stop_distance,
	maximum_position_size,
	maximum_order_units,
	margin_rate,
	commission_commission,
	commission_units_traded,
	commission_minimum_commission,
	guaranteed_stop_loss_order_mode,
	guaranteed_stop_loss_order_execution_premium,
	guaranteed_stop_loss_order_level_restriction_volume,
	guaranteed_stop_loss_order_level_restriction_priceRange,
	financing_longRate,
	financing_shortRate,
	financingDaysOfWeek
)

// Instrument
//void to_json(nlohmann::json& j, const Instrument& p);
//void from_json(const nlohmann::json& j, Instrument& p);

} /* namespace oanda */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENTJSON_HPP_ */
