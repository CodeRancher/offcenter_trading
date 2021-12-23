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
 * @file   GenerateSineCandlesticks.hpp
 * @author sbrauer
 * @date   Nov 22, 2021
 */

#ifndef OFFCENTER_TRADING_COMMON_GENERATESINECANDLESTICKS_HPP_
#define OFFCENTER_TRADING_COMMON_GENERATESINECANDLESTICKS_HPP_

#include <vector>
#include <chrono>
#include <initializer_list>
#include <cmath>

#include "offcenter/trading/datatypes/common/Candlestick.hpp"

namespace offcenter {
namespace trading {
namespace common {

template<typename FloatType>
static const FloatType pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

/**
 *
 */
template<typename FloatType>
class SineWave {
public:
	using WavelengthType = std::chrono::milliseconds;

public:
	template<typename WaveLength, typename WaveLengthShift>
	SineWave(const FloatType amplitude, const WaveLength wavelength, const FloatType amplitudeShift, const WaveLengthShift wavelengthShift):
		m_amplitude(amplitude),
		m_wavelength(std::chrono::duration_cast<std::chrono::milliseconds>(wavelength)),
		m_amplitudeShift(amplitudeShift),
		m_wavelengthShift(std::chrono::duration_cast<std::chrono::milliseconds>(wavelengthShift)),
		m_wavelengthInMillis(std::chrono::duration_cast<std::chrono::milliseconds>(m_wavelength))
	{}

	SineWave(const SineWave<FloatType>& other):
		SineWave(other.m_amplitude, other.m_wavelength, other.m_amplitudeShift, other.m_wavelengthShift)
	{}

	template<typename WaveLength>
	const FloatType y(const WaveLength x) const {
		std::chrono::milliseconds xInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(x);
		std::cout << "Wavelength: " << m_wavelength.count() << ", " << xInMillis.count() << ", " << m_wavelengthShift.count() << std::endl;

		std::cout << m_amplitudeShift << "+" << "(" << m_amplitude << "*offcenter::trading::datatypes::common::sine(((" << 2.0 << "*" << pi<FloatType> << ") /" << static_cast<FloatType>(m_wavelength.count()) << ") * " << static_cast<FloatType>(xInMillis.count()) << "+" << static_cast<FloatType>(m_wavelengthShift.count()) << "))" << std::endl;



		return m_amplitudeShift + (m_amplitude * offcenter::trading::datatypes::common::sine(((2.0 * pi<FloatType>) / static_cast<FloatType>(m_wavelength.count())) * static_cast<FloatType>(xInMillis.count()) + static_cast<FloatType>(m_wavelengthShift.count())));
	}

	FloatType amplitude() const { return m_amplitude; }
	void setAmplitude(FloatType mAmplitude)	{ m_amplitude = mAmplitude; }

	FloatType amplitudeShift() const { return m_amplitudeShift; }
	void setAmplitudeShift(FloatType mAmplitudeShift) { m_amplitudeShift = mAmplitudeShift; }

	const WavelengthType& wavelength() const { return m_wavelength; }
	void setWavelength(const WavelengthType &mWavelength) { m_wavelength = mWavelength; }

	const WavelengthType& wavelengthShift() const { return m_wavelengthShift; }
	void setWavelengthShift(const WavelengthType &mWavelengthShift) { m_wavelengthShift = mWavelengthShift; }

	const FloatType maxAmplitude() const { return +m_amplitude + m_amplitudeShift; }
	const FloatType minAmplitude() const { return -m_amplitude + m_amplitudeShift; }

private:
	FloatType m_amplitude;
	WavelengthType m_wavelength;
	FloatType m_amplitudeShift;
	WavelengthType m_wavelengthShift;
	std::chrono::milliseconds m_wavelengthInMillis;
};

/**
 *
 */
template<typename FloatType>
class SineWaves {
public:
	SineWaves():
		m_maxAmplitude(0.0),
		m_minAmplitude(0.0),
		m_amplitudeSize(0.0),
		m_sineWaves()
	{}

	SineWaves(std::initializer_list<const SineWave<FloatType>> sineWaves):
		SineWaves()
	{
		for (const SineWave<FloatType>& sineWave : sineWaves) {
			add(sineWave);
		}
	}

	virtual ~SineWaves() = default;

	void add(const SineWave<FloatType>& sineWave) {
		m_sineWaves.push_back(sineWave);
		m_maxAmplitude += sineWave.maxAmplitude();
		m_minAmplitude += sineWave.minAmplitude();
		m_amplitudeSize = m_maxAmplitude - m_minAmplitude;
	}

	SineWave<FloatType>& sine(int index) { return m_sineWaves.at(index); }
	int sineCnt() { return m_sineWaves.size(); }

	const FloatType maxAmplitude() const { return m_maxAmplitude; }
	const FloatType minAmplitude() const { return m_minAmplitude; }
	const FloatType amplitudeSize() const { return m_amplitudeSize; }

	template<typename Duration>
	const FloatType y(const Duration x) const {
		FloatType result = 0.0;
		for (const SineWave<FloatType>& sineWave : m_sineWaves) {
			result += sineWave.y(x);
		}
		return result;
	}

private:
	FloatType m_maxAmplitude;
	FloatType m_minAmplitude;
	FloatType m_amplitudeSize;
	std::vector<SineWave<FloatType>> m_sineWaves;
};

/**
 *
 */
template<typename FloatType>
class OHLC {
public:
	OHLC():
		time(offcenter::common::make_UTCDateTimeSmallest()),
		open(FloatType(0.0)),
		high(FloatType(0.0)),
		low(FloatType(0.0)),
		close(FloatType(0.0))
	{}
	OHLC(offcenter::common::UTCDateTime l_time, FloatType l_open, FloatType l_high, FloatType l_low,FloatType l_close):
		time(l_time),
		open(l_open),
		high(l_high),
		low(l_low),
		close(l_close)
	{}

	void set(offcenter::common::UTCDateTime l_time, FloatType l_open, FloatType l_high, FloatType l_low,FloatType l_close) {
		time = l_time;
		open = l_open;
		high = l_high;
		low = l_low;
		close = l_close;
	}

	offcenter::common::UTCDateTime time;
	FloatType open;
	FloatType high;
	FloatType low;
	FloatType close;
};

/**
 *
 */
//template<typename FloatType>
//class SineWaveOHLC:
//	public SineWaves<FloatType>
//{
//public:
//	SineWaveOHLC(const offcenter::common::UTCDateTime& startTime, std::initializer_list<const SineWave<FloatType>> sineWaves):
//		SineWaves<FloatType>(sineWaves),
//		m_startTime(startTime)
//	{}
//
//	virtual ~SineWaveOHLC() = default;
//
//	template<typename Duration>
//	offcenter::common::UTCDateTime time(const Duration duration) {
//		return m_startTime + std::chrono::duration_cast<std::chrono::milliseconds>(duration);
//	}
//
//	template<typename WaveLength>
//	OHLC<FloatType> ohlc(const offcenter::common::UTCDateTime time) const {
//		FloatType open = 0.0;
//		for (const SineWave<FloatType>& sineWave : m_sineWaves) {
//			result += sineWave.y(x);
//		}
//		return result;
//	}
//
//
//private:
//	const offcenter::common::UTCDateTime m_startTime;
//};

/**
 *
 */
template<typename FloatType>
class SineWaveOHLCElement
{
public:
	SineWaveOHLCElement():
		m_ohlc(),
		m_time(offcenter::common::make_UTCDateTimeSmallest()),
		m_value(0.0),
		m_preGap(0),
		m_postGap(0),
		m_highGapPercent(0),
		m_lowGapPercent(0)
	{}

	virtual ~SineWaveOHLCElement() = default;

	OHLC<FloatType>& ohlc() { return  m_ohlc; }
	const FloatType y() { return  m_value; }

	void setValue(const FloatType value) { m_value = value; }
	void setGaps(std::chrono::milliseconds preGap, std::chrono::milliseconds postGap, FloatType highGapPercent, FloatType lowGapPercent) {
		m_preGap = preGap;
		m_postGap = postGap;
		m_highGapPercent = highGapPercent;
		m_lowGapPercent = lowGapPercent;
	}

	std::chrono::milliseconds preGap() { return m_preGap; }
	std::chrono::milliseconds postGap() { return m_postGap; }
	FloatType highGapPercent() { return m_highGapPercent; }
	FloatType lowGapPercent() { return m_lowGapPercent; }

private:
	OHLC<FloatType> m_ohlc;
	offcenter::common::UTCDateTime m_time;
	FloatType m_value;
	std::chrono::milliseconds m_preGap;
	std::chrono::milliseconds m_postGap;
	FloatType m_highGapPercent;
	FloatType m_lowGapPercent;
};

/**
 *
 */
template<typename FloatType>
class SineWaveOHLCCollection
{
public:
	template<typename Duration>
	SineWaveOHLCCollection(int elementCount, offcenter::common::UTCDateTime startTime, const Duration duration, const std::initializer_list<const SineWave<FloatType>>& sineWaves):
		m_startTime(startTime),
		m_duration(std::chrono::duration_cast<std::chrono::milliseconds>(duration)),
		m_sineWaves(sineWaves),
		m_ohlcElements(elementCount)
	{
		calcGaps();
		calcOHLC();
	}

	virtual ~SineWaveOHLCCollection() = default;

	const OHLC<FloatType>& ohlc(int index) { return  m_ohlcElements.at(index).ohlc(); }
	const FloatType y(int index) { return  m_ohlcElements.at(index).y(); }
	std::vector<SineWaveOHLCElement<FloatType>>& ohlcElements() { return m_ohlcElements; }
	const offcenter::common::UTCDateTime startTime() { return m_startTime; }
	const offcenter::common::UTCDateTime endTime() { return m_ohlcElements.at(m_ohlcElements.size() - 1).ohlc().time; }
	const FloatType maxAmplitude() const { return m_sineWaves.maxAmplitude(); }
	const FloatType minAmplitude() const { return m_sineWaves.minAmplitude(); }
	const std::chrono::milliseconds duration() const { return m_duration; }

	void setAmplitude(int index, FloatType amplitude) {
		m_sineWaves.sine(index).setAmplitude(amplitude);
		calcOHLC();
	}

	void setAmplitudeShift(int index, FloatType amplitudeShift) {
		m_sineWaves.sine(index).setAmplitudeShift(amplitudeShift);
		calcOHLC();
	}

	template<typename Duration>
	void setWavelength(int index, Duration wavelength) {
		m_sineWaves.sine(index).setWavelength(std::chrono::duration_cast<std::chrono::milliseconds>(wavelength));
		calcOHLC();
	}

	template<typename Duration>
	void setWavelengthShift(int index, Duration wavelengthShift) {
		m_sineWaves.sine(index).setWavelengthShift(std::chrono::duration_cast<std::chrono::milliseconds>(wavelengthShift));
		calcOHLC();
	}

private:
	void calcGaps() {
		for (SineWaveOHLCElement<FloatType>& element : m_ohlcElements) {
			element.setGaps(m_duration / 2, m_duration / 2, 0.5, 0.5);
		}
	}

	void calcOHLC() {
		std::chrono::milliseconds duration(0);
		for (SineWaveOHLCElement<FloatType>& element : m_ohlcElements) {
			element.setValue(m_sineWaves.y(duration));
			FloatType preValue {m_sineWaves.y(duration - element.preGap())};
			FloatType postValue {m_sineWaves.y(duration + element.postGap())};
			FloatType absValue {std::abs(postValue - preValue)};
			element.ohlc().set(
					m_startTime + duration,
					preValue,
					std::max(preValue, postValue) + (element.highGapPercent() * absValue),
					std::min(preValue, postValue) - (element.lowGapPercent() * absValue),
					postValue
			);

			duration += m_duration;
		}
	}

private:
	offcenter::common::UTCDateTime m_startTime;
	std::chrono::milliseconds m_duration;
	SineWaves<FloatType> m_sineWaves;
	std::vector<SineWaveOHLCElement<FloatType>> m_ohlcElements;
};



/**
 *
 */
template<typename FloatType, typename FrequencyType = FloatType>
class GenerateSine {
public:
	GenerateSine(const FloatType amplitude, const FrequencyType frequency, const FloatType amplitudeShift, const FrequencyType frequencyShift):
		m_amplitude(amplitude),
		m_frequency(frequency),
		m_amplitudeShift(amplitudeShift),
		m_frequencyShift(frequencyShift)
	{}

	GenerateSine(const GenerateSine<FloatType>& other):
		GenerateSine(other.m_amplitude, other.m_frequency, other.m_amplitudeShift, other.m_frequencyShift)
	{}

	virtual ~GenerateSine() = default;

	const FloatType y(const FloatType x) const {
		return (m_amplitude * offcenter::trading::datatypes::common::sine(2.0 * pi<FloatType> * m_frequency * x + m_frequencyShift)) + m_amplitudeShift;
	}

	const FloatType amplitude() const { return m_amplitude; }
	void setAmplitude(const FloatType value) { m_amplitude = value; }

	const FrequencyType frequency() const { return m_frequency; }
	void setFrequency(const FrequencyType value) { m_frequency = value; }

	const FloatType amplitudeShift() const { return m_amplitudeShift; }
	void setAmplitudeShift(const FloatType value) { m_amplitudeShift = value; }

	const FrequencyType frequencyShift() const { return m_frequencyShift; }
	void setFrequencyShift(const FrequencyType value) { m_frequencyShift = value; }

	const FloatType maxAmplitude() const { return +m_amplitude + m_amplitudeShift; }
	const FloatType minAmplitude() const { return -m_amplitude + m_amplitudeShift; }

private:
	FloatType m_amplitude;
	FrequencyType m_frequency;
	FloatType m_amplitudeShift;
	FrequencyType m_frequencyShift;
};

/**
 *
 */
template<typename FloatType>
class GenerateSine<FloatType, offcenter::common::UTCDateTime::duration> {
public:
	GenerateSine(
			const FloatType amplitude,
			const offcenter::common::UTCDateTime::duration frequency,
			const FloatType amplitudeShift,
			const offcenter::common::UTCDateTime::duration frequencyShift
	):
		m_amplitude(amplitude),
		m_frequency(frequency),
		m_amplitudeShift(amplitudeShift),
		m_frequencyShift(frequencyShift)
	{}

	GenerateSine(const GenerateSine<FloatType>& other):
		GenerateSine(other.m_amplitude, other.m_frequency, other.m_amplitudeShift, other.m_frequencyShift)
	{}

	virtual ~GenerateSine() = default;

	const FloatType y(const std::chrono::milliseconds x) const {
		return (m_amplitude * offcenter::trading::datatypes::common::sine(2.0 * pi<FloatType> * m_frequency.count() * x.count() + m_frequencyShift.count())) + m_amplitudeShift;
	}

	const FloatType amplitude() const { return m_amplitude; }
	void setAmplitude(const FloatType value) { m_amplitude = value; }

	const offcenter::common::UTCDateTime::duration frequency() const { return m_frequency; }
	void setFrequency(const offcenter::common::UTCDateTime::duration value) { m_frequency = value; }

	const FloatType amplitudeShift() const { return m_amplitudeShift; }
	void setAmplitudeShift(const FloatType value) { m_amplitudeShift = value; }

	const offcenter::common::UTCDateTime::duration frequencyShift() const { return m_frequencyShift; }
	void setFrequencyShift(const offcenter::common::UTCDateTime::duration value) { m_frequencyShift = value; }

	const FloatType maxAmplitude() const { return +m_amplitude + m_amplitudeShift; }
	const FloatType minAmplitude() const { return -m_amplitude + m_amplitudeShift; }

private:
	FloatType m_amplitude;
	offcenter::common::UTCDateTime::duration m_frequency;
	FloatType m_amplitudeShift;
	offcenter::common::UTCDateTime::duration m_frequencyShift;
};

/**
 *
 */
template<typename FloatType>
class CombineSine {
public:
	CombineSine():
		m_maxAmplitude(0.0),
		m_minAmplitude(0.0),
		m_amplitudeSize(0.0),
		m_sines()
	{}

	CombineSine(const GenerateSine<FloatType>& sine1):
		CombineSine()
	{
		add(sine1);
	}

	CombineSine(const GenerateSine<FloatType>& sine1, const GenerateSine<FloatType>& sine2):
		CombineSine(sine1)
	{
		add(sine2);
	}

	CombineSine(const GenerateSine<FloatType>& sine1, const GenerateSine<FloatType>& sine2, const GenerateSine<FloatType>& sine3):
		CombineSine(sine1, sine2)
	{
		add(sine3);
	}

	virtual ~CombineSine() = default;

	void add(const GenerateSine<FloatType>& sine) {
		m_sines.push_back(sine);
		//std::cout << "Add: maxAmplitude(" << sine.maxAmplitude() << ") minAmplitude(" << sine.minAmplitude() << ")" << std::endl;
		m_maxAmplitude += sine.maxAmplitude();
		m_minAmplitude += sine.minAmplitude();
		m_amplitudeSize = m_maxAmplitude - m_minAmplitude;
		//std::cout << "	m_maxAmplitude(" << m_maxAmplitude << ") m_minAmplitude(" << m_minAmplitude << ") m_amplitudeSize(" << m_amplitudeSize << ")" << std::endl;
	}

	GenerateSine<FloatType>& sine(int index) { return m_sines.at(index); }
	int sineCnt() { return m_sines.size(); }

	const FloatType maxAmplitude() const { return m_maxAmplitude; }
	const FloatType minAmplitude() const { return m_minAmplitude; }
	const FloatType amplitudeSize() const { return m_amplitudeSize; }

	const FloatType y(FloatType x) const { return calcY(x); }

protected:
	virtual const FloatType calcY(FloatType x) const {
		FloatType result = 0.0;
		for (const GenerateSine<FloatType> sine : m_sines) {
			result += sine.y(x);
		}
		return result;
	}

private:
	FloatType m_maxAmplitude;
	FloatType m_minAmplitude;
	FloatType m_amplitudeSize;
	std::vector<GenerateSine<FloatType>> m_sines;
};

/**
 *
 */
template<typename FloatType>
class CombineSineAdjustToRange: public CombineSine<FloatType> {
public:
	CombineSineAdjustToRange(const FloatType yMin, const FloatType yMax, const GenerateSine<FloatType>& sine1, const GenerateSine<FloatType>& sine2):
		CombineSine<FloatType>(sine1, sine2),
		m_yMin(0.0),
		m_yMax(0.0)
	{}

	CombineSineAdjustToRange(const FloatType yMin, const FloatType yMax, const GenerateSine<FloatType>& sine1, const GenerateSine<FloatType>& sine2, const GenerateSine<FloatType>& sine3):
		CombineSine<FloatType>(sine1, sine2, sine3),
		m_yMin(0.0),
		m_yMax(0.0),
		m_yRange(yMax - yMin),
		m_addConst(CombineSine<FloatType>::minAmplitude() + m_yMin),
		m_multConst(m_yRange / CombineSine<FloatType>::amplitudeSize())
	{}

protected:
	const FloatType calcY(FloatType time) const override {
		return (CombineSine<FloatType>::calcY(time) - m_addConst) * m_multConst;
	}

private:
	const FloatType m_yMin;
	const FloatType m_yMax;
	const FloatType m_yRange;
	const FloatType m_addConst;
	const FloatType m_multConst;
};

/**
 * Creates a series of candlesticks based on a sine curve
 *
 * @tparam FloatType	Type used to store the OHLC data
 * @tparam Duration		Chrono duration for times in between each candlestick
 * @tparam DurationSize	Number of Durations for time between candlesticks
 */
template<typename FloatType, typename Duration, int DurationSize>
class GenerateSineCandlesticks
{
public:
	using CandlestickDuration = Duration;

public:
	GenerateSineCandlesticks(const offcenter::common::UTCDateTime& startTime, const CombineSine<FloatType>& sines, const FloatType stepPerDuration):
		m_startTime(startTime),
		m_sines(sines),
		m_stepPerDuration(stepPerDuration),
		m_durationInSeconds(DurationSize),
		m_duration(DurationSize)
	{}

	~GenerateSineCandlesticks() = default;

	const offcenter::common::UTCDateTime startTime() { return m_startTime; }
	int durationInSeconds() { return m_durationInSeconds; }

	CombineSine<FloatType>& sines() { return m_sines; }

	const FloatType y(FloatType time) const {
		std::cout << time << " : " << offcenter::common::UTCDateTimeToISO8601(offcenter::common::make_UTCDateTimeFromTimestamp(time)) << std::endl;
		return calcY(time);
	}

protected:
	virtual const FloatType calcY(FloatType time) const {
		//std::cout << time << " : " << m_sines.y(time) << " : " << m_duration.count() << " : " << m_sines.y(time) * m_duration.count() << std::endl;
		return m_sines.y(time) * m_duration.count();
	}



	/*
	offcenter::trading::datatypes::common::OHLC<FloatType> calcOHLC(int step, FloatType stepAdjust) {

		FloatType stepInRange = step % m_steps;
		FloatType open = calcSin(step, -0.5 + stepAdjust);
		FloatType close = calcSin(step, +0.5 + stepAdjust);
		FloatType lMax = offcenter::trading::datatypes::common::max(open, close);
		FloatType lMin = offcenter::trading::datatypes::common::min(open, close);
		FloatType lHeight = lMax - lMin;
		FloatType high = lMax + offcenter::trading::datatypes::common::max(static_cast<FloatType>(0.2 * lHeight), static_cast<FloatType>(1.0));
		FloatType low = lMin - offcenter::trading::datatypes::common::max(static_cast<FloatType>(0.2 * lHeight), static_cast<FloatType>(1.0));

		//std::cout << m_steps << ":" << m_stepSize << ":" << (2.0 * pi) << ":" << ((2.0 * pi) / static_cast<float>(m_steps)) << std::endl;
		offcenter::trading::datatypes::common::OHLC<FloatType> retVal{ open, high, low, close };
		return retVal;
	}
	*/

	/**
	 * Calculates a candlestick at step past start
	 *
	 * @param step Step past start
	 * @return Candlestick at step past start
	 */
	/*
	const offcenter::trading::datatypes::common::BidAskCandlestick<FloatType> calcCandlestick(int step) {
		offcenter::trading::datatypes::common::OHLC<FloatType> bidOHLC = calcOHLC(step, -0.1);
		offcenter::trading::datatypes::common::OHLC<FloatType> askOHLC = calcOHLC(step, 0.0);
		offcenter::trading::datatypes::common::BidAskCandlestick<FloatType>
				candlestick(stepTime(step), {bidOHLC.open, bidOHLC.high, bidOHLC.low, bidOHLC.close}, {askOHLC.open, askOHLC.high, askOHLC.low, askOHLC.close}, 10);
		return candlestick;
	}
	*/

private:
	const offcenter::common::UTCDateTime m_startTime;
	CombineSine<FloatType> m_sines;
	FloatType m_stepPerDuration;
	int m_durationInSeconds;
	Duration m_duration;
};







/**
 * Creates a series of candlesticks based on a sine curve
 *
 * @tparam FloatType	Type used to store the OHLC data
 * @tparam Duration		Chrono duration for times in between each candlestick
 * @tparam DurationSize	Number of Durations for time between candlesticks
 */
template<typename FloatType, typename Duration, int DurationSize>
class GenerateSineCandlesticksOrig {
public:
	/**
	 * Initialize candlestick generator
	 *
	 * @param startTime Time of first candlestick in series
	 * @param yMin Wanted value for minimum candlesticks
	 * @param yMax Wanted value for maximum candlesticks
	 * @param steps Number of steps in each cycle of the sine curve
	 */
	GenerateSineCandlesticksOrig(const offcenter::common::UTCDateTime& startTime, const FloatType yMin, const FloatType yMax, int steps):
		m_startTime(startTime),
		m_yMin(yMin),
		m_yMax(yMax),
		m_steps(steps),
		m_stepSize((2.0 * pi<FloatType>) / static_cast<float>(m_steps)),
		m_yRange(yMax - yMin),
		m_stepDuration(DurationSize)
	{}

	virtual ~GenerateSineCandlesticksOrig() = default;

	/**
	 * Calculate an OHLC value
	 *
	 * @tparam FloatType Type for storing OHLC values
	 * @param step The step from the starting value
	 * @param stepAdjust Used to shift the values slighty up (positive) or down (negative
	 * @return OHLC vales of candlestick
	 */
	offcenter::trading::datatypes::common::OHLC<FloatType> calcOHLC(int step, FloatType stepAdjust) {
		FloatType stepInRange = step % m_steps;
		FloatType open = calcSin(step, -0.5 + stepAdjust);
		FloatType close = calcSin(step, +0.5 + stepAdjust);
		FloatType lMax = offcenter::trading::datatypes::common::max(open, close);
		FloatType lMin = offcenter::trading::datatypes::common::min(open, close);
		FloatType lHeight = lMax - lMin;
		FloatType high = lMax + offcenter::trading::datatypes::common::max(static_cast<FloatType>(0.2 * lHeight), static_cast<FloatType>(1.0));
		FloatType low = lMin - offcenter::trading::datatypes::common::max(static_cast<FloatType>(0.2 * lHeight), static_cast<FloatType>(1.0));

		//std::cout << m_steps << ":" << m_stepSize << ":" << (2.0 * pi) << ":" << ((2.0 * pi) / static_cast<float>(m_steps)) << std::endl;
		offcenter::trading::datatypes::common::OHLC<FloatType> retVal{ open, high, low, close };
		return retVal;
	}

	/**
	 * Calculate the UTCDateTime at step past start
	 *
	 * @param step Step past start
	 * @return UTCDateTime past start
	 */
	const offcenter::common::UTCDateTime stepTime(int step) {
		return m_startTime + (m_stepDuration * step);
	}

	/**
	 * Calculates a candlestick at step past start
	 *
	 * @param step Step past start
	 * @return Candlestick at step past start
	 */
	const offcenter::trading::datatypes::common::BidAskCandlestick<FloatType> calcCandlestick(int step) {
		offcenter::trading::datatypes::common::OHLC<FloatType> bidOHLC = calcOHLC(step, -0.1);
		offcenter::trading::datatypes::common::OHLC<FloatType> askOHLC = calcOHLC(step, 0.0);
		offcenter::trading::datatypes::common::BidAskCandlestick<FloatType>
				candlestick(stepTime(step), {bidOHLC.open, bidOHLC.high, bidOHLC.low, bidOHLC.close}, {askOHLC.open, askOHLC.high, askOHLC.low, askOHLC.close}, 10);
		return candlestick;
	}

private:
	FloatType calcSin(int step, FloatType stepAdjust) const {
		FloatType adjustedStep = ((step % m_steps) + stepAdjust) * m_stepSize;
		return (((offcenter::trading::datatypes::common::sine(adjustedStep) / 2.0) + 0.5) * m_yRange) + m_yMin;
	}

private:
	const offcenter::common::UTCDateTime m_startTime;
	const FloatType m_yMin;
	const FloatType m_yMax;
	const int m_steps;
	const FloatType m_stepSize;
	const FloatType m_yRange;
	const Duration m_stepDuration;
};

/**
 * Creates a series of candlesticks based on a sine curve
 *
 * @tparam FloatType	Type used to store the OHLC data
 * @tparam Duration		Chrono duration for times in between each candlestick
 * @tparam DurationSize	Number of Durations for time between candlesticks
 */
template<typename FloatType, typename Duration, int DurationSize>
class GenerateDoubleSineCandlesticks {
public:
	GenerateDoubleSineCandlesticks() {

	}
};

} /* namespace common */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_COMMON_GENERATESINECANDLESTICKS_HPP_ */
