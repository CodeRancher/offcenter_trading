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
 * @file   InstrumentJson.cpp
 * @author Scott Brauer
 * @date   05-19-2021
 */

#include "offcenter/trading/datatypes/oanda/InstrumentJson.hpp"
#include "offcenter/trading/common/JsonConversion.hpp"
#include "offcenter/trading/common/JsonExceptions.hpp"

namespace offcenter {
namespace trading {
namespace datatypes {
namespace oanda {

/*
void to_json(nlohmann::json& j, const Instrument& p) {
	j = nlohmann::json {
		{"instrument_id", p.instrument_id},
		{"name", p.name},
		{"instrument_type_id", p.instrument_type_id},
		{"display_name", p.display_name},
		{"pip_location", p.pip_location},
		{"display_precision", p.display_precision},
		{"trade_units_precision", p.trade_units_precision},
		{"minimum_trade_size", p.minimum_trade_size},
		{"maximum_trailing_stop_distance", p.maximum_trailing_stop_distance},
		{"minimum_guaranteed_stop_loss_distance", p.minimum_guaranteed_stop_loss_distance},
		{"minimum_trailing_stop_distance", p.minimum_trailing_stop_distance},
		{"maximum_position_size", p.maximum_position_size},
		{"maximum_order_units", p.maximum_order_units},
		{"margin_rate", p.margin_rate},
		{"commission_commission", p.commission_commission},
		{"commission_units_traded", p.commission_units_traded},
		{"commission_minimum_commission", p.commission_minimum_commission},
		{"guaranteed_stop_loss_order_mode", p.guaranteed_stop_loss_order_mode},
		{"guaranteed_stop_loss_order_execution_premium", p.guaranteed_stop_loss_order_execution_premium},
		{"guaranteed_stop_loss_order_level_restriction_volume", p.guaranteed_stop_loss_order_level_restriction_volume},
		{"guaranteed_stop_loss_order_level_restriction_priceRange", p.guaranteed_stop_loss_order_level_restriction_priceRange},
		{"financing_longRate", p.financing_longRate},
		{"financing_shortRate", p.financing_shortRate}
	};
}

void from_json(const nlohmann::json& j, Instrument& p) {
	try {
		offcenter::trading::common::convertJson(j, "instrument_id", p.instrument_id);
		offcenter::trading::common::convertJson(j, "name", p.name);
		offcenter::trading::common::convertJson(j, "instrument_type_id", p.instrument_type_id);
		offcenter::trading::common::convertJson(j, "display_name", p.display_name);
		offcenter::trading::common::convertJson(j, "pip_location", p.pip_location);
		offcenter::trading::common::convertJson(j, "display_precision", p.display_precision);
		offcenter::trading::common::convertJson(j, "trade_units_precision", p.trade_units_precision);
		offcenter::trading::common::convertJson(j, "minimum_trade_size", p.minimum_trade_size);
		offcenter::trading::common::convertJson(j, "maximum_trailing_stop_distance", p.maximum_trailing_stop_distance);
		offcenter::trading::common::convertJson(j, "minimum_guaranteed_stop_loss_distance", p.minimum_guaranteed_stop_loss_distance);
		offcenter::trading::common::convertJson(j, "minimum_trailing_stop_distance", p.minimum_trailing_stop_distance);
		offcenter::trading::common::convertJson(j, "maximum_position_size", p.maximum_position_size);
		offcenter::trading::common::convertJson(j, "maximum_order_units", p.maximum_order_units);
		offcenter::trading::common::convertJson(j, "margin_rate", p.margin_rate);
		offcenter::trading::common::convertJson(j, "commission_commission", p.commission_commission);
		offcenter::trading::common::convertJson(j, "commission_units_traded", p.commission_units_traded);
		offcenter::trading::common::convertJson(j, "commission_minimum_commission", p.commission_minimum_commission);
		offcenter::trading::common::convertJson(j, "guaranteed_stop_loss_order_mode", p.guaranteed_stop_loss_order_mode);
		offcenter::trading::common::convertJson(j, "guaranteed_stop_loss_order_execution_premium", p.guaranteed_stop_loss_order_execution_premium);
		offcenter::trading::common::convertJson(j, "guaranteed_stop_loss_order_level_restriction_volume", p.guaranteed_stop_loss_order_level_restriction_volume);
		offcenter::trading::common::convertJson(j, "guaranteed_stop_loss_order_level_restriction_priceRange", p.guaranteed_stop_loss_order_level_restriction_priceRange);
		offcenter::trading::common::convertJson(j, "financing_longRate", p.financing_longRate);
		offcenter::trading::common::convertJson(j, "financing_shortRate", p.financing_shortRate);

	} catch(nlohmann::json::exception& e) {
		throw offcenter::trading::common::TradingJsonException(e);
	}
}
*/


} /* namespace oanda */
} /* namespace datatypes */
} /* namespace trading */
} /* namespace offcenter */
