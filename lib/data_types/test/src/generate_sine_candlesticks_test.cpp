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
 * @file   generate_sin_candlesticks_test.cpp
 * @author sbrauer
 * @date   Nov 22, 2021
 */

#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/offcenter/trading/datatypes/common/GenerateSineCandlesticks.hpp"
#include "offcenter/trading/datatypes/common/Candlestick.hpp"
#include "offcenter/trading/datatypes/calculation/Candlestick.hpp"

TEST (SineWaveOHLCCollection, CollectionTest)
{
	const int indexCnt = 120;
	using FloatType = double;
	FloatType amplitude {10.0};
	std::chrono::seconds wavelength {60};

	offcenter::trading::common::SineWave<FloatType> sineWave(amplitude, wavelength, 10, std::chrono::seconds(0));
	offcenter::trading::common::SineWaveOHLCCollection<FloatType> collection(
			indexCnt,
			offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"),
			std::chrono::seconds(1),
			{sineWave}
	);

	for (int index = 0; index < indexCnt; index++) {
		offcenter::trading::common::OHLC ohlc = collection.ohlc(index);
		std::cout
			<< offcenter::common::UTCDateTimeToISO8601(ohlc.time) << ", "
			<< collection.y(index) << ", "
			<< ohlc.open << ", "
			<< ohlc.high << ", "
			<< ohlc.low << ", "
			<< ohlc.close
			<< std::endl;
	}
}

TEST (GenerateSinCandlesticks, DISABLED_CalcStepTime)
{
//	offcenter::trading::common::GenerateSineCandlesticks<double, std::chrono::seconds, 5> gen(offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"), 50.0, 100.0, 16);
//
//	for (int step = 0; step < 32; step++) {
//		offcenter::common::UTCDateTime stepTime = gen.stepTime(step);
//		std::cout << offcenter::common::CustomDateTimeToISO8601(stepTime) << std::endl;
//	}
}

TEST (GenerateSinCandlesticks, DISABLED_CalcCandlestick)
{
//	using FloatType = double;
//	offcenter::trading::common::GenerateSineCandlesticks<FloatType, std::chrono::seconds, 5> gen(offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"), 50.0, 100.0, 16);
//
//	for (int step = 0; step < 32; step++) {
//		offcenter::trading::datatypes::common::BidAskCandlestick<FloatType> candlestick = gen.calcCandlestick(step);
//		std::cout
//			<< offcenter::common::CustomDateTimeToISO8601(candlestick.startTime) << ", "
//			<< candlestick.bid.open << ", "
//			<< candlestick.bid.high << ", "
//			<< candlestick.bid.low << ", "
//			<< candlestick.bid.close << ", "
//			<< candlestick.ask.open << ", "
//			<< candlestick.ask.high << ", "
//			<< candlestick.ask.low << ", "
//			<< candlestick.ask.close << ", "
//			<< candlestick.volume
//			<< std::endl;
//	}
}

TEST (GenerateSinCandlesticks, DISABLED_MultiprecisionCandlestick)
{
//	using FloatType = offcenter::trading::datatypes::calculation::CandlestickPrice;
//	offcenter::trading::common::GenerateSineCandlesticks<FloatType, std::chrono::seconds, 5> gen(offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"), 50.0, 100.0, 16);
//
//	for (int step = 0; step < 32; step++) {
//		offcenter::trading::datatypes::common::BidAskCandlestick<FloatType> candlestick = gen.calcCandlestick(step);
//		std::cout
//			<< offcenter::common::CustomDateTimeToISO8601(candlestick.startTime) << ", "
//			<< candlestick.bid.open << ", "
//			<< candlestick.bid.high << ", "
//			<< candlestick.bid.low << ", "
//			<< candlestick.bid.close << ", "
//			<< candlestick.ask.open << ", "
//			<< candlestick.ask.high << ", "
//			<< candlestick.ask.low << ", "
//			<< candlestick.ask.close << ", "
//			<< candlestick.volume
//			<< std::endl;
//	}
}

TEST (GenerateSinCandlesticks, DISABLED_Test)
{
//	offcenter::trading::common::GenerateSineCandlesticks<double, std::chrono::seconds, 5> gen(offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"), 50.0, 100.0, 16);
//
//	for (int step = 0; step < 32; step++) {
//		offcenter::common::UTCDateTime stepTime = gen.stepTime(step);
//		std::cout << offcenter::common::CustomDateTimeToISO8601(stepTime) << std::endl;
//	}
}

TEST (GenerateSin, DISABLED_BasicSineWave)
{
	using FloatType = double;
	const FloatType xPerWave = 5.0;
	const FloatType xStep = xPerWave / 100.0;

	offcenter::trading::common::GenerateSine<FloatType> sine(1.0, 1.0 / xPerWave, 0.0, 0.0);

	for (FloatType x = 0.0; x < xPerWave + (xStep / 2.0); x += xStep) {
		std::cout << x << ", " << sine.y(x) << std::endl;
	}
}

TEST (GenerateCombinedSin, DISABLED_SineWaveOnTime)
{
	/*
	using FloatType = double;
	const offcenter::common::UTCDateTime startTime(offcenter::common::make_UTCDateTimeFromISO8601("2000-01-01T00:00:00.000000000Z"));
	std::chrono::seconds stepDurationInSeconds(5);
	const offcenter::common::UTCDateTime::duration stepDuration(std::chrono::duration_cast<offcenter::common::UTCDateTime::duration>(stepDurationInSeconds));
	std::chrono::seconds zeroDurationInSeconds(0);
	const offcenter::common::UTCDateTime::duration zeroDuration(std::chrono::duration_cast<offcenter::common::UTCDateTime::duration>(zeroDurationInSeconds));
	const offcenter::common::UTCDateTime::duration xStep = std::chrono::duration_cast<offcenter::common::UTCDateTime::duration>(stepDuration / 1000.0);
	const std::chrono::milliseconds frequency(1000 / 5000);

	offcenter::trading::common::GenerateSine<FloatType, offcenter::common::UTCDateTime::duration> sine(1.0, frequency, 0.0, zeroDurationInSeconds);

	for (offcenter::common::UTCDateTime x = startTime; x <= startTime + stepDurationInSeconds; x += xStep) {
		//std::cout << offcenter::common::UTCDateTimeToISO8601(x) << ", " << sine.y(std::chrono::duration_cast<offcenter::common::UTCDateTime::duration>(x - startTime)) << std::endl;
	}
	*/
}

double calcY(double x, double amplitude, double wavelength) {
	return amplitude * std::sin(((2.0 * offcenter::trading::common::pi<double>) / wavelength) * x);
}

double calcY(std::chrono::milliseconds x, double amplitude, std::chrono::seconds wavelength) {
	std::chrono::milliseconds wavelengthInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(wavelength);
	//std::cout << "x: " << x.count() << " amplitude: " << amplitude << " wavelength: " << wavelengthInMillis.count() << std::endl;
	return amplitude * std::sin(((2.0 * offcenter::trading::common::pi<double>) / wavelengthInMillis.count()) * x.count());
}

TEST (GenerateCombinedSin, DISABLED_SineWaveOnWavelength)
{
	using FloatType = double;
	FloatType amplitude {1.0};
	FloatType wavelength {1.0};

	for (FloatType x = 0.0; x <= 2.025; x += 0.05) {
		std::cout << x << ", " << calcY(x, amplitude, wavelength) << std::endl;
	}
}

TEST (GenerateCombinedSin, DISABLED_SineWaveOnWavelengthUsingDuration)
{
	using FloatType = double;
	FloatType amplitude {1.0};
	std::cout
		<< "offcenter::common::UTCDateTime::duration: "
		//<< offcenter::common::UTCDateTime::duration::rep << ", "
		<< offcenter::common::UTCDateTime::duration::period::den << ", "
		<< offcenter::common::UTCDateTime::duration::period::num << std::endl;
	std::chrono::seconds wavelength {1};
	std::cout << "wavelength: " << wavelength.count() << std::endl;
	std::chrono::milliseconds wavelengthMS = std::chrono::duration_cast<std::chrono::milliseconds>(wavelength);
	std::cout << "wavelength(ms): " << wavelengthMS.count() << std::endl;

	std::chrono::milliseconds maxX = std::chrono::duration_cast<std::chrono::milliseconds>(wavelength * 2);
	std::chrono::milliseconds xStep {maxX / 40};
	std::cout
		<< "std::chrono::milliseconds: "
		//<< std::chrono::milliseconds::rep << ", "
		<< std::chrono::milliseconds::period::den << ", "
		<< std::chrono::milliseconds::period::num << std::endl;

	std::cout << "amplitude: " << amplitude << " wavelength(ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(wavelength).count() << " maxX(ms): " << maxX.count() << " xStep(ms): " << xStep.count() << std::endl;

	offcenter::trading::common::SineWave<double> sineWave(amplitude, wavelength, 0, std::chrono::seconds(0));
	offcenter::trading::common::SineWaves<double> sineWaves({sineWave});


	for (std::chrono::milliseconds x {0}; x <= maxX; x += xStep) {
		std::cout << x.count() << ", " << calcY(x, amplitude, wavelength) << " = " << sineWave.y(x) << " = " << sineWaves.y(x) << std::endl;
	}
}

TEST (GenerateCombinedSin3, DISABLED_Test)
{
//	using FloatType = double;
//
//	offcenter::trading::common::CombineSine<FloatType> sines(
//			offcenter::trading::common::GenerateSine<FloatType>(1.0, 4.0, 0.0, 0.0),
//			offcenter::trading::common::GenerateSine<FloatType>(4.0, 0.5, 0.0, 5.0),
//			offcenter::trading::common::GenerateSine<FloatType>(16.0, 0.1, 21.0, 16.0)
//	);
//
//	for (FloatType time = 0; time <= 2.0; time+=0.01) {
//		std::cout << time << ", " << sines.y(time) << std::endl;
//	}
}
