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
 * @file   GenerateSineCandlesticksProgramOptions.hpp
 * @author Scott Brauer
 * @date   11-29-2021
 */
#ifndef OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSPROGRAMOPTIONS__H_
#define OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSPROGRAMOPTIONS__H_

#include <functional>
#include <iostream>
#include <sstream>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/generatesinecandlesticks/GenerateSineCandlesticksOptions.hpp"

namespace offcenter {
namespace trading {
namespace generatesinecandlesticks {

class GenerateSineCandlesticksProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<offcenter::trading::generatesinecandlesticks::GenerateSineCandlesticksOptions>
{
public:
	GenerateSineCandlesticksProgramOptions():
		ProgramOptionsGroup("Generate Sine Candlestick Options")
	{
		optionsDescription().add_options()
				("start,s", po::value<std::string>()->required()->notifier(boost::bind(&GenerateSineCandlesticksOptions::setStart, &optionConfig(), boost::placeholders::_1)), "Start time (2004-06-09T20:59:55.000000000Z)")
				("end,e", po::value<std::string>()->required()->notifier(boost::bind(&GenerateSineCandlesticksOptions::setEnd, &optionConfig(), boost::placeholders::_1)), "End time (2004-08-09T20:59:55.000000000Z)")
				("duration,d", po::value<int>(&optionConfig().m_duration)->required()->default_value(5), "Duration in seconds")

				("sine0.amplitude", po::value<double>(&optionConfig().m_sine0.m_amplitude)->required(), "Sine 0 amplitude")
				("sine0.wavelength", po::value<int>(&optionConfig().m_sine0.m_wavelength)->required(), "Sine 0 wavelength")
				("sine0.amplitude_shift", po::value<double>(&optionConfig().m_sine0.m_amplitudeShift)->required(), "Sine 0 amplitude shift")
				("sine0.wavelength_shift", po::value<int>(&optionConfig().m_sine0.m_wavelengthShift)->required(), "Sine 0 wavelength shift")

				("sine1.amplitude", po::value<double>(&optionConfig().m_sine1.m_amplitude), "Sine 1 amplitude")
				("sine1.wavelength", po::value<int>(&optionConfig().m_sine1.m_wavelength), "Sine 1 wavelength")
				("sine1.amplitude_shift", po::value<double>(&optionConfig().m_sine1.m_amplitudeShift), "Sine 1 amplitude shift")
				("sine1.wavelength_shift", po::value<int>(&optionConfig().m_sine1.m_wavelengthShift), "Sine 1 wavelength shift")

				("sine2.amplitude", po::value<double>(&optionConfig().m_sine2.m_amplitude), "Sine 2 amplitude")
				("sine2.wavelength", po::value<int>(&optionConfig().m_sine2.m_wavelength), "Sine 2 wavelength")
				("sine2.amplitude_shift", po::value<double>(&optionConfig().m_sine2.m_amplitudeShift), "Sine 2 amplitude shift")
				("sine2.wavelength_shift", po::value<int>(&optionConfig().m_sine2.m_wavelengthShift), "Sine 2 wavelength shift")

				("sine3.amplitude", po::value<double>(&optionConfig().m_sine3.m_amplitude), "Sine 3 amplitude")
				("sine3.wavelength", po::value<int>(&optionConfig().m_sine3.m_wavelength), "Sine 3 wavelength")
				("sine3.amplitude_shift", po::value<double>(&optionConfig().m_sine3.m_amplitudeShift), "Sine 3 amplitude shift")
				("sine3.wavelength_shift", po::value<int>(&optionConfig().m_sine3.m_wavelengthShift), "Sine 3 wavelength shift")

				;
	}

	virtual ~GenerateSineCandlesticksProgramOptions() = default;

	virtual void validateOptions(po::variables_map& vm) {

	}
};

} /* namespace generatesinecandlesticks */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSPROGRAMOPTIONS__H_ */
