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
 * @file   signal_current_candle_trigger_app.cpp
 * @author Scott Brauer
 * @date   10-24-2021
 */

#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/amqpserver/AmqpServerAppManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/application/Utility.hpp"

#include "offcenter/trading/signalcurrentcandletrigger/SignalCurrentCandleTriggerApp.hpp"

int main(int argc, char **argv)
{
	try {
		START_EASYLOGGINGPP(argc, argv);

		std::cout << "--------------------------------------------------------------------------------" << std::endl;
		std::cout << "Signal Current Candle Trigger!" << std::endl;

		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./SignalCurrentCandleTrigger.log");

		LOG(INFO) << "Signal Current Candle Trigger!";

		using App = offcenter::common::amqpserver::AmqpServerAppManager<offcenter::trading::signalcurrentcandletrigger::SignalCurrentCandleTriggerApp>;
		std::thread appThread = framework::application::create_basic_app_in_thread<App>(argc, argv);
		appThread.join();
	} catch (const std::runtime_error& e) {
		std::cout << "System Error: " << e.what() << std::endl;
	}
}
