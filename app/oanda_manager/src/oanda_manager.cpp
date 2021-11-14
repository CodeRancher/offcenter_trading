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
 * @file   oanda_manager.cpp
 * @author Scott Brauer
 * @date   05-18-2021
 */

#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/amqpserver/AmqpServerAppManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/application/Utility.hpp"
using namespace offcenter::common;

#include "offcenter/trading/oandamanager/OandaManagerApp.hpp"
using namespace offcenter::trading;

int main(int argc, char **argv)
{
	try {
		START_EASYLOGGINGPP(argc, argv);

		std::cout << "Oanda Manager App!" << std::endl;

		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./OandaManager.log");

		LOG(INFO) << "--------------------------------------------------------------------------------";
		LOG(INFO) << "Begin Oanda Manager App!";

		using App = amqpserver::AmqpServerAppManager<oandamanager::OandaManagerApp>;
		std::thread appThread = framework::application::create_basic_app_in_thread<App>(argc, argv);
		appThread.join();
	} catch (const std::runtime_error& e) {
		std::cout << "System Error: " << e.what() << std::endl;
	}

	LOG(INFO) << "Exit Oanda Manager App!";
}
