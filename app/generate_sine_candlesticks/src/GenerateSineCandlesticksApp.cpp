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
 * @file   GenerateSineCandlesticksApp.cpp
 * @author Scott Brauer
 * @date   11-29-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/trading/generatesinecandlesticks/GenerateSineCandlesticksApp.hpp"

namespace offcenter {
namespace trading {
namespace generatesinecandlesticks {

GenerateSineCandlesticksApp::GenerateSineCandlesticksApp():
		IApp()
{

}

GenerateSineCandlesticksApp::~GenerateSineCandlesticksApp() {
	// TODO Auto-generated destructor stub
}

void GenerateSineCandlesticksApp::onInitProgramOptions(
        program_options::ProgramOptionsManager &optionsManager)
{
	m_generateSineCandlesticksOptions = optionsManager.add<offcenter::trading::generatesinecandlesticks::GenerateSineCandlesticksProgramOptions>();
}

void GenerateSineCandlesticksApp::onSetUp()
{
}

void GenerateSineCandlesticksApp::onTearDown()
{
}

/**
 * Called when help should be displayed.
 *
 * @param help A string that contains the help
 */
void GenerateSineCandlesticksApp::onHelp(const std::string &help)
{
	std::cout << help << std::endl;
}

void GenerateSineCandlesticksApp::onVersion()
{
}

} /* namespace generatesinecandlesticks */
} /* namespace trading */
} /* namespace offcenter */
