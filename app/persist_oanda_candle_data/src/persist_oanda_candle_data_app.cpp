#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "main.hpp"

#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/application/Utility.hpp"
using namespace offcenter::common;

#include "offcenter/trading/persistoandacandledata/PersistOandaCandleDataApp.hpp"
using namespace offcenter::trading;

int main(int argc, char **argv)
{
	try {
		START_EASYLOGGINGPP(argc, argv);

		std::cout << "Persist Oanda Candle Data App!" << std::endl;

		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./PersistOandaCandleData.log");

		LOG(INFO) << "--------------------------------------------------------------------------------";
		LOG(INFO) << "Persist Oanda Candle Data App!";

		using App = framework::application::AppManager<persistoandacandledata::PersistOandaCandleDataApp>;
		std::thread appThread = framework::application::create_basic_app_in_thread<App>(argc, argv);
		appThread.join();
	} catch (const std::runtime_error& e) {
		std::cout << "System Error: " << e.what() << std::endl;
	}
}
