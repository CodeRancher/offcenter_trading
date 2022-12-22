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
 * @file   date_time_test.cpp
 * @author Scott Brauer
 * @date   06-12-2021
 */

#include <gtest/gtest.h>

#include "easylogging++.h"

#include "offcenter/trading/datatypes/common/ForexDateTime.hpp"

template<typename DateTime>
void testDateTimeConversion(const std::string& scope)
{
		using namespace offcenter::trading::datatypes;
	using namespace std::chrono;

	SCOPED_TRACE(scope);
	const std::string sdt{"2000-01-01T00:00:00Z"};
	DateTime dt = make_CustomDateTimeFromISO8601<DateTime>(sdt);
	EXPECT_EQ(sdt, CustomDateTimeToISO8601(dt));
	unsigned long long timeStamp = CustomDateTimeSecondsFromEpoch(dt);
	EXPECT_EQ(dt, make_CustomDateTimeFromTimestamp<DateTime>(timeStamp));
	EXPECT_EQ(dt, make_CustomDateTimeFromTimestamp<DateTime>(std::to_string(timeStamp)));
}

TEST (DateTime, DateTimeConversion)
{
	using namespace offcenter::trading::datatypes;
	using namespace std::chrono;

	testDateTimeConversion<ForexDateTime_S5>("ForexDateTime_S5");
	testDateTimeConversion<ForexDateTime_S10>("ForexDateTime_S10");
	testDateTimeConversion<ForexDateTime_S15>("ForexDateTime_S15");
	testDateTimeConversion<ForexDateTime_S30>("ForexDateTime_S30");
	testDateTimeConversion<ForexDateTime_M1>("ForexDateTime_M1");
	testDateTimeConversion<ForexDateTime_M2>("ForexDateTime_M2");
	testDateTimeConversion<ForexDateTime_M4>("ForexDateTime_M4");
	testDateTimeConversion<ForexDateTime_M5>("ForexDateTime_M5");
	testDateTimeConversion<ForexDateTime_M10>("ForexDateTime_M10");
	testDateTimeConversion<ForexDateTime_M15>("ForexDateTime_M15");
	testDateTimeConversion<ForexDateTime_M30>("ForexDateTime_M30");
	testDateTimeConversion<ForexDateTime_H1>("ForexDateTime_H1");
	testDateTimeConversion<ForexDateTime_H2>("ForexDateTime_H2");
	testDateTimeConversion<ForexDateTime_H3>("ForexDateTime_H3");
	testDateTimeConversion<ForexDateTime_H4>("ForexDateTime_H4");
	testDateTimeConversion<ForexDateTime_H6>("ForexDateTime_H6");
	testDateTimeConversion<ForexDateTime_H8>("ForexDateTime_H8");
	testDateTimeConversion<ForexDateTime_H12>("ForexDateTime_H12");
	testDateTimeConversion<ForexDateTime_D>("ForexDateTime_D");
	testDateTimeConversion<ForexDateTime_W>("ForexDateTime_W");
	testDateTimeConversion<ForexDateTime_M>("ForexDateTime_M");
}

TEST (DateTime, S5)
{
		using namespace offcenter::trading::datatypes;
	using namespace std::chrono;
	using TF = ForexDateTime_S5;

	EXPECT_EQ(make_CustomDateTimeFromISO8601<TF>("2000-01-01T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<TF>("2000-01-01T00:00:04.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<TF>("2000-01-01T00:00:05.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:05.000000000Z"));



}

TEST (DateTime, M1)
{
		using namespace offcenter::trading::datatypes;
	using namespace std::chrono;

	ForexDateTime_M1 start = make_CustomDateTimeFromISO8601<ForexDateTime_M1>("2000-01-01T00:00:00.000000000Z");

	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_M1>("2000-01-01T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_M1>("2000-01-01T00:00:59.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_M1>("2000-01-01T00:01:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:01:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_M1>("2000-01-01T00:01:01.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:01:00.000000000Z"));
}

TEST (DateTime, H8)
{
		using namespace offcenter::trading::datatypes;
	using namespace std::chrono;

	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-01T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-01T07:59:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-01T08:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T08:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-01T15:59:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T08:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-01T16:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T16:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-01T23:59:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T16:00:00.000000000Z"));
	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_H8>("2000-01-02T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-02T00:00:00.000000000Z"));
}

TEST (DateTime, W)
{
		using namespace offcenter::trading::datatypes;
	using namespace std::chrono;

	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-01T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-02T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-03T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-04T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-05T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-06T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-07T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-08T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-09T00:00:00.000000000Z"));
	LOG(INFO) << CustomDateTimeToISO8601(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-10T00:00:00.000000000Z"));

//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-01T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-02T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-03T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-04T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-05T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-06T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-07T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-08T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
//	EXPECT_EQ(make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-09T00:00:00.000000000Z"), make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
}

TEST (DateTime, Weekly) {
		using namespace offcenter::trading::datatypes;
	using namespace std::chrono;

	ForexDateTime_W dt = make_CustomDateTimeFromISO8601<ForexDateTime_W>("2000-01-01T10:00:00Z");



}
