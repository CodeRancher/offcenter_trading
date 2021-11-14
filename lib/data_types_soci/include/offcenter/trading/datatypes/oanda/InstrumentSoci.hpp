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

#ifndef OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENTSOCI_HPP_
#define OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENTSOCI_HPP_

#include "soci/soci.h"

#include "offcenter/trading/datatypes/oanda/Instrument.hpp"

namespace soci {

template<>
struct type_conversion<offcenter::trading::datatypes::oanda::Instrument>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::oanda::Instrument & p)
	{
		p.instrument_id = v.get<unsigned>("instrument_id");
		p.name = v.get<std::string>("name");
		p.instrument_type = v.get<std::string>("instrument_type");
		p.display_name = v.get<std::string>("display_name");
		p.pip_location = v.get<int>("pip_location");
		p.display_precision = v.get<int>("display_precision");
		p.trade_units_precision = v.get<int>("trade_units_precision");
		p.minimum_trade_size = v.get<double>("minimum_trade_size");
		p.maximum_trailing_stop_distance = v.get<double>("maximum_trailing_stop_distance");
		p.minimum_guaranteed_stop_loss_distance = v.get<double>("minimum_guaranteed_stop_loss_distance");
		p.minimum_trailing_stop_distance = v.get<double>("minimum_trailing_stop_distance");
		p.maximum_position_size = v.get<double>("maximum_position_size");
		p.maximum_order_units = v.get<double>("maximum_order_units");
		p.margin_rate = v.get<double>("margin_rate");
		p.commission_commission = v.get<double>("commission_commission");
		p.commission_units_traded = v.get<double>("commission_units_traded");
		p.commission_minimum_commission = v.get<double>("commission_minimum_commission");
		p.guaranteed_stop_loss_order_mode = v.get<int>("guaranteed_stop_loss_order_mode");
		p.guaranteed_stop_loss_order_execution_premium = v.get<double>("guaranteed_stop_loss_order_execution_premium");
		p.guaranteed_stop_loss_order_level_restriction_volume = v.get<double>("guaranteed_stop_loss_order_level_restriction_volume");
		p.guaranteed_stop_loss_order_level_restriction_priceRange = v.get<double>("guaranteed_stop_loss_order_level_restriction_priceRange");
		p.financing_longRate = v.get<double>("financing_longRate");
		p.financing_shortRate = v.get<double>("financing_shortRate");
	}

	static void to_base(offcenter::trading::datatypes::oanda::Instrument const & p, values & v, indicator & ind)
	{
		v.set("instrument_id", p.instrument_id);
		v.set("name", p.name);
		v.set("instrument_type", p.instrument_type);
		v.set("display_name", p.display_name);
		v.set("pip_location", p.pip_location);
		v.set("display_precision", p.display_precision);
		v.set("trade_units_precision", p.trade_units_precision);
		v.set("minimum_trade_size", p.minimum_trade_size);
		v.set("maximum_trailing_stop_distance", p.maximum_trailing_stop_distance);
		v.set("minimum_guaranteed_stop_loss_distance", p.minimum_guaranteed_stop_loss_distance);
		v.set("minimum_trailing_stop_distance", p.minimum_trailing_stop_distance);
		v.set("maximum_position_size", p.maximum_position_size);
		v.set("maximum_order_units", p.maximum_order_units);
		v.set("margin_rate", p.margin_rate);
		v.set("commission_commission", p.commission_commission);
		v.set("commission_units_traded", p.commission_units_traded);
		v.set("commission_minimum_commission", p.commission_minimum_commission);
		v.set("guaranteed_stop_loss_order_mode", p.guaranteed_stop_loss_order_mode);
		v.set("guaranteed_stop_loss_order_execution_premium", p.guaranteed_stop_loss_order_execution_premium);
		v.set("guaranteed_stop_loss_order_level_restriction_volume", p.guaranteed_stop_loss_order_level_restriction_volume);
		v.set("guaranteed_stop_loss_order_level_restriction_priceRange", p.guaranteed_stop_loss_order_level_restriction_priceRange);
		v.set("financing_longRate", p.financing_longRate);
		v.set("financing_shortRate", p.financing_shortRate);
		ind = i_ok;
	}
};

template<>
struct type_conversion<offcenter::trading::datatypes::oanda::InstrumentWithIDs>
{
	typedef values base_type;

	static void from_base(values const & v, indicator /* ind */, offcenter::trading::datatypes::oanda::InstrumentWithIDs & p)
	{
		p.instrument_id = v.get<unsigned>("instrument_id");
		p.name = v.get<std::string>("name");
		p.instrument_type_id = v.get<int>("instrument_type_id");
		p.display_name = v.get<std::string>("display_name");
		p.pip_location = v.get<int>("pip_location");
		p.display_precision = v.get<int>("display_precision");
		p.trade_units_precision = v.get<int>("trade_units_precision");
		p.minimum_trade_size = v.get<double>("minimum_trade_size");
		p.maximum_trailing_stop_distance = v.get<double>("maximum_trailing_stop_distance");
		p.minimum_guaranteed_stop_loss_distance = v.get<double>("minimum_guaranteed_stop_loss_distance");
		p.minimum_trailing_stop_distance = v.get<double>("minimum_trailing_stop_distance");
		p.maximum_position_size = v.get<double>("maximum_position_size");
		p.maximum_order_units = v.get<double>("maximum_order_units");
		p.margin_rate = v.get<double>("margin_rate");
		p.commission_commission = v.get<double>("commission_commission");
		p.commission_units_traded = v.get<double>("commission_units_traded");
		p.commission_minimum_commission = v.get<double>("commission_minimum_commission");
		p.guaranteed_stop_loss_order_mode = v.get<int>("guaranteed_stop_loss_order_mode");
		p.guaranteed_stop_loss_order_execution_premium = v.get<double>("guaranteed_stop_loss_order_execution_premium");
		p.guaranteed_stop_loss_order_level_restriction_volume = v.get<double>("guaranteed_stop_loss_order_level_restriction_volume");
		p.guaranteed_stop_loss_order_level_restriction_priceRange = v.get<double>("guaranteed_stop_loss_order_level_restriction_priceRange");
		p.financing_longRate = v.get<double>("financing_longRate");
		p.financing_shortRate = v.get<double>("financing_shortRate");
	}

	static void to_base(offcenter::trading::datatypes::oanda::InstrumentWithIDs const & p, values & v, indicator & ind)
	{
		v.set("instrument_id", p.instrument_id);
		v.set("name", p.name);
		v.set("instrument_type_id", p.instrument_type_id);
		v.set("display_name", p.display_name);
		v.set("pip_location", p.pip_location);
		v.set("display_precision", p.display_precision);
		v.set("trade_units_precision", p.trade_units_precision);
		v.set("minimum_trade_size", p.minimum_trade_size);
		v.set("maximum_trailing_stop_distance", p.maximum_trailing_stop_distance);
		v.set("minimum_guaranteed_stop_loss_distance", p.minimum_guaranteed_stop_loss_distance);
		v.set("minimum_trailing_stop_distance", p.minimum_trailing_stop_distance);
		v.set("maximum_position_size", p.maximum_position_size);
		v.set("maximum_order_units", p.maximum_order_units);
		v.set("margin_rate", p.margin_rate);
		v.set("commission_commission", p.commission_commission);
		v.set("commission_units_traded", p.commission_units_traded);
		v.set("commission_minimum_commission", p.commission_minimum_commission);
		v.set("guaranteed_stop_loss_order_mode", p.guaranteed_stop_loss_order_mode);
		v.set("guaranteed_stop_loss_order_execution_premium", p.guaranteed_stop_loss_order_execution_premium);
		v.set("guaranteed_stop_loss_order_level_restriction_volume", p.guaranteed_stop_loss_order_level_restriction_volume);
		v.set("guaranteed_stop_loss_order_level_restriction_priceRange", p.guaranteed_stop_loss_order_level_restriction_priceRange);
		v.set("financing_longRate", p.financing_longRate);
		v.set("financing_shortRate", p.financing_shortRate);
		ind = i_ok;
	}
};

} /* namespace soci */


#endif /* OFFCENTER_TRADING_DATATYPES_OANDA_INSTRUMENTSOCI_HPP_ */
