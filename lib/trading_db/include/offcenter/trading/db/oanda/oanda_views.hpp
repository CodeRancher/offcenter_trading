/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
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
 * @file   oanda_views.hpp
 * @author Scott Brauer
 * @date   07-08-2021
 */
#ifndef OFFCENTER_TRADING_DB_OANDA_VIEWS_HPP_
#define OFFCENTER_TRADING_DB_OANDA_VIEWS_HPP_

#include <string>

namespace offcenter {
namespace trading {
namespace db {
namespace oanda {

namespace view {

/******************************************************************************
 * Oanda Instrument
 * Fully expanded Oanda Instrument
 */
namespace oanda_instrument {

/// Create SQL for broker_source
inline std::string create = R"###(
CREATE VIEW v_oanda_instrument AS
SELECT 
	oa.instrument_id,
	oa.name,
	it.name AS instrument_type,
	oa.display_name,
	oa.pip_location,
	oa.display_precision,
	oa.trade_units_precision,
	oa.minimum_trade_size,
	oa.maximum_trailing_stop_distance,
	oa.minimum_guaranteed_stop_loss_distance,
	oa.minimum_trailing_stop_distance,
	oa.maximum_position_size,
	oa.maximum_order_units,
	oa.margin_rate,
	oa.commission_commission,
	oa.commission_units_traded,
	oa.commission_minimum_commission,
	oa.guaranteed_stop_loss_order_mode,
	oa.guaranteed_stop_loss_order_execution_premium,
	oa.guaranteed_stop_loss_order_level_restriction_volume,
	oa.guaranteed_stop_loss_order_level_restriction_priceRange,
	oa.financing_longRate,
	oa.financing_shortRate
FROM oanda_instrument oa
	INNER JOIN instrument_type it
		ON it.instrument_type_id = oa.instrument_type_id;
)###";

} /* namespace oanda_instrument */



} /* namespace view */

} /* namespace oanda */
} /* namespace db */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_DB_OANDA_VIEWS_HPP_ */
