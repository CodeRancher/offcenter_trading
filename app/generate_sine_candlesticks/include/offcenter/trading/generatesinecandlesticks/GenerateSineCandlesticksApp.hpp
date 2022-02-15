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
 * @file   GenerateSineCandlesticksApp.hpp
 * @author Scott Brauer
 * @date   11-29-2021
 */

#ifndef OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSAPP_H_
#define OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSAPP_H_

#include "offcenter/common/framework/application/IApp.hpp"

#include "offcenter/trading/generatesinecandlesticks/GenerateSineCandlesticksProgramOptions.hpp"

namespace offcenter {
namespace trading {
namespace generatesinecandlesticks {

/**
 *
 */
class GenerateSineCandlesticksApp
		: public offcenter::common::framework::application::IApp {
public:
	explicit GenerateSineCandlesticksApp();
	virtual ~GenerateSineCandlesticksApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

protected:
	offcenter::trading::generatesinecandlesticks::GenerateSineCandlesticksProgramOptions::ConfigPtr m_generateSineCandlesticksOptions;
};

} /* namespace generatesinecandlesticks */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_GENERATESINECANDLESTICKS_GENERATESINECANDLESTICKSAPP_H_ */
