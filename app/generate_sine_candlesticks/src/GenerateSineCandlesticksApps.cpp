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
 * @file   GenerateSineCandlesticksApps.cpp
 * @author Scott Brauer
 * @date   11-29-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/trading/generatesinecandlesticks/GenerateSineCandlesticksApps.hpp"
#include "offcenter/trading/datatypes/common/GenerateSineCandlesticks.hpp"

namespace offcenter {
namespace trading {
namespace generatesinecandlesticks {

Sine::Sine():
		GenerateSineCandlesticksApp()
{}

Sine::~Sine()
{}

/**
 *
 */
void Sine::onExecute() {
	std::cout << "Time, Value" << std::endl;

	std::chrono::seconds duration(m_generateSineCandlesticksOptions->duration());

	// Initialize sin values
	offcenter::trading::common::CombineSine<double> combineSine;
	for (int genSineCnt = 0; genSineCnt < 4; genSineCnt++) {
		const SineDescription& sine = m_generateSineCandlesticksOptions->sine(genSineCnt);
		if (!sine.empty()) {
			offcenter::trading::common::GenerateSine<double> genSine(sine.amplitude(), 1.0 / static_cast<double>(sine.wavelength()), sine.amplitudeShift(), sine.wavelengthShift());
			combineSine.add(genSine);
		}
	}

	for (offcenter::common::UTCDateTime stepTime = m_generateSineCandlesticksOptions->startTime(); stepTime <= m_generateSineCandlesticksOptions->endTime(); stepTime += duration) {
		std::chrono::seconds secondCnt = std::chrono::duration_cast<std::chrono::seconds>(stepTime - m_generateSineCandlesticksOptions->startTime());
		std::cout
			<< offcenter::common::UTCDateTimeToISO8601(stepTime) << ", "
			<< combineSine.y(static_cast<double>(secondCnt.count()))
			<< std::endl;
	}
}

} /* namespace generatesinecandlesticks */
} /* namespace trading */
} /* namespace offcenter */
