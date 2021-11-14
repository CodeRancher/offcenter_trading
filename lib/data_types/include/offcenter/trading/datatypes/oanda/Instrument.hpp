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
 * @date   05-19-2021
 */
#ifndef OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENT_HPP_
#define OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENT_HPP_

#include <string>

#include "offcenter/trading/datatypes/oanda/FinancingDayOfWeek.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace oanda {

/**
 * Instrument
 */
struct Instrument
{
	unsigned instrument_id;
	std::string name;
	std::string instrument_type;
	std::string display_name;
	int pip_location;
	int display_precision;
	int trade_units_precision;
	double minimum_trade_size;
	double maximum_trailing_stop_distance;
	double minimum_guaranteed_stop_loss_distance;
	double minimum_trailing_stop_distance;
	double maximum_position_size;
	double maximum_order_units;
	double margin_rate;
	double commission_commission;
	double commission_units_traded;
	double commission_minimum_commission;
	int guaranteed_stop_loss_order_mode;
	double guaranteed_stop_loss_order_execution_premium;
	double guaranteed_stop_loss_order_level_restriction_volume;
	double guaranteed_stop_loss_order_level_restriction_priceRange;
	double financing_longRate;
	double financing_shortRate;
	std::vector<FinancingDayOfWeek> financingDaysOfWeek;
};

/**
 * InstrumentWithIDs
 */
struct InstrumentWithIDs
{
	unsigned instrument_id;
	std::string name;
	int instrument_type_id;
	std::string display_name;
	int pip_location;
	int display_precision;
	int trade_units_precision;
	double minimum_trade_size;
	double maximum_trailing_stop_distance;
	double minimum_guaranteed_stop_loss_distance;
	double minimum_trailing_stop_distance;
	double maximum_position_size;
	double maximum_order_units;
	double margin_rate;
	double commission_commission;
	double commission_units_traded;
	double commission_minimum_commission;
	int guaranteed_stop_loss_order_mode;
	double guaranteed_stop_loss_order_execution_premium;
	double guaranteed_stop_loss_order_level_restriction_volume;
	double guaranteed_stop_loss_order_level_restriction_priceRange;
	double financing_longRate;
	double financing_shortRate;
	std::vector<FinancingDayOfWeek> financingDaysOfWeek;
};

} /* namespace oanda */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENT_HPP_ */
