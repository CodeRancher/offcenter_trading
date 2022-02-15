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
 * @file   GenerateSineCandlesticksOptions.hpp
 * @author Scott Brauer
 * @date   11-29-2021
 */

#ifndef OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSOPTIONS__H_
#define OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSOPTIONS__H_

#include <string>
#include <vector>

#include "offcenter/common/DateTime.hpp"
#include "offcenter/trading/common/Exceptions.hpp"

namespace offcenter {
namespace trading {
namespace generatesinecandlesticks {

/**
 *
 */
class SineDescription
{
public:
	explicit SineDescription():
		m_amplitude(0.0),
		m_wavelength(0),
		m_amplitudeShift(0.0),
		m_wavelengthShift(0)
	{}

	const double& amplitude() const { return m_amplitude; }
	const int& wavelength() const { return m_wavelength; }
	const double& amplitudeShift() const { return m_amplitudeShift; }
	const int& wavelengthShift() const { return m_wavelengthShift; }

	bool empty() const { return (m_wavelength == 0); }

	friend class GenerateSineCandlesticksProgramOptions;

private:
	double m_amplitude;
	int m_wavelength;
	double m_amplitudeShift;
	int m_wavelengthShift;
};

/**
 *
 */
class GenerateSineCandlesticksOptions
{
public:
	explicit GenerateSineCandlesticksOptions():
		m_startTime(),
		m_endTime(),
		m_duration()
	{}

	virtual ~GenerateSineCandlesticksOptions() {}

	offcenter::common::UTCDateTime startTime() const { return m_startTime; }
	const std::string startTimeAsString() const { return offcenter::common::UTCDateTimeToISO8601(m_startTime); }
	offcenter::common::UTCDateTime endTime() const { return m_endTime; }
	const std::string endTimeAsString() const { return offcenter::common::UTCDateTimeToISO8601(m_endTime); }
	const int duration() const { return m_duration; }

	const SineDescription& sine0() const { return m_sine0; }
	const SineDescription& sine1() const { return m_sine1; }
	const SineDescription& sine2() const { return m_sine2; }
	const SineDescription& sine3() const { return m_sine3; }
	const SineDescription& sine(int num) const {
		switch (num) {
			case 0: return m_sine0;
			case 1: return m_sine1;
			case 2: return m_sine2;
			case 3: return m_sine3;
			default: throw offcenter::trading::common::TradingRuntimeException("Invalid Sine description number");
		}
	}

	void setStart(const std::string value) {
		m_startTime = offcenter::common::make_UTCDateTimeFromISO8601(value);
	}

	void setEnd(const std::string value) {
		m_endTime = offcenter::common::make_UTCDateTimeFromISO8601(value);
	}

	friend class GenerateSineCandlesticksProgramOptions;

private:
	offcenter::common::UTCDateTime m_startTime;
	offcenter::common::UTCDateTime m_endTime;
	int m_duration;

	SineDescription m_sine0;
	SineDescription m_sine1;
	SineDescription m_sine2;
	SineDescription m_sine3;
};

} /* namespace generatesinecandlesticks */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSOPTIONS__H_ */
