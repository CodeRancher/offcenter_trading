/**
 * Copyright 2020 Scott Brauer
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
 * @file   oanda_persistence_endpoint_test.cpp
 * @author Scott Brauer
 * @date   05-20-2021
 */

//#include <iostream>
//#include <sstream>
//#include <thread>
//#include <chrono>

#include <gtest/gtest.h>

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"

TEST (OandaPersistenceEndpoints, OandaSaveInstrument)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::oanda::InstrumentWithIDs instrument;
	instrument.instrument_id = 1;
	instrument.name = "Test1";
	instrument.instrument_type_id = endpoints.instrumentType()->recordByName("CURRENCY").instrument_type_id;
	instrument.display_name = "Test 1";
	instrument.pip_location = 4;
	instrument.display_precision = 5;
	instrument.trade_units_precision = 6;
	instrument.minimum_trade_size = 0.1;
	instrument.maximum_trailing_stop_distance = 0.2;
	instrument.minimum_guaranteed_stop_loss_distance = 0.3;
	instrument.minimum_trailing_stop_distance = 0.5;
	instrument.maximum_position_size = 0.6;
	instrument.maximum_order_units = 0.7;
	instrument.margin_rate = 0.8;
	instrument.commission_commission = 0.9;
	instrument.commission_units_traded = 1.0;
	instrument.commission_minimum_commission = 1.1;
	instrument.guaranteed_stop_loss_order_mode = 7;
	instrument.guaranteed_stop_loss_order_execution_premium = 1.2;
	instrument.guaranteed_stop_loss_order_level_restriction_volume = 1.3;
	instrument.guaranteed_stop_loss_order_level_restriction_priceRange = 1.4;
	instrument.financing_longRate = 1.5;
	instrument.financing_shortRate = 1.6;

	offcenter::trading::datatypes::oanda::FinancingDayOfWeek financingDayOfWeek;
	financingDayOfWeek.day_of_week_id = 1;
	financingDayOfWeek.days_charged = 1;
	instrument.financingDaysOfWeek.push_back(financingDayOfWeek);
	financingDayOfWeek.day_of_week_id = 3;
	financingDayOfWeek.days_charged = 3;
	instrument.financingDaysOfWeek.push_back(financingDayOfWeek);

	endpoints.oandaInstrumentCreate("fxpractice", instrument);

	offcenter::trading::datatypes::oanda::Instrument instrumentRead;
	instrumentRead = endpoints.oandaInstrumentRead("fxpractice", instrument.name);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);

	instrumentRead = endpoints.oandaInstrumentRead("fxpractice", instrumentRead.instrument_id);
	EXPECT_EQ(instrumentRead.name, instrument.name);
	EXPECT_EQ(instrumentRead.display_name, instrument.display_name);

	//endpoints.oandaInstrumentUpdate("fxpractice", instrument);
	endpoints.oandaInstrumentDelete("fxpractice", instrument.name);

}

