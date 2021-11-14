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
 * @file   lookup_table_test.cpp
 * @author Scott Brauer
 * @date   06-22-2021
 */

//#include <iostream>
//#include <sstream>
//#include <thread>
//#include <chrono>

#include "easylogging++.h"

#include <gtest/gtest.h>

#include "offcenter/trading/oandapersistenceclient/OandaPersistenceEndpoints.hpp"
#include "offcenter/trading/oandapersistenceclient/LookupTableData.hpp"

TEST (LookupTable, Broker)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::BrokerLookupTablePtr records =  endpoints.brokers();
	EXPECT_EQ(records->recordsByID().size(), 1);
	EXPECT_EQ(records->recordsByName().size(), 1);
}

TEST (LookupTable, BrokerDataSource)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::BrokerDataSourceLookupTablePtr records =  endpoints.brokerDataSource();
	EXPECT_EQ(records->recordsByID().size(), 2);
	EXPECT_EQ(records->recordsByName().size(), 2);
}

TEST (LookupTable, InstrumentType)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::InstrumentTypeLookupTablePtr records =  endpoints.instrumentType();
	EXPECT_EQ(records->recordsByID().size(), 3);
	EXPECT_EQ(records->recordsByName().size(), 3);
}

TEST (LookupTable, GuaranteedStopLossOrderModeForInstrument)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::GuaranteedStopLossOrderModeForInstrumentLookupTablePtr records =  endpoints.guaranteedStopLossOrderModeForInstrument();
	EXPECT_EQ(records->recordsByID().size(), 3);
	EXPECT_EQ(records->recordsByName().size(), 3);
}

TEST (LookupTable, DayOfWeek)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::DayOfWeekLookupTablePtr records =  endpoints.dayOfWeek();
	EXPECT_EQ(records->recordsByID().size(), 7);
	EXPECT_EQ(records->recordsByName().size(), 7);
}

TEST (LookupTable, CandlestickGranularity)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::CandlestickGranularityLookupTablePtr records =  endpoints.candlestickGranularity();
	EXPECT_EQ(records->recordsByID().size(), 21);
	EXPECT_EQ(records->recordsByName().size(), 21);
}

TEST (LookupTable, Currency)
{
	offcenter::trading::oandapersistenceclient::OandaPersistenceEndpoints endpoints;

	offcenter::trading::datatypes::CurrencyLookupTablePtr records =  endpoints.currency();
	EXPECT_EQ(records->recordsByID().size(), 179);
	EXPECT_EQ(records->recordsByName().size(), 179);
}

