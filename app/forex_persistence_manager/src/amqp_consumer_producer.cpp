#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/amqpserver/AmqpServerAppManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/application/Utility.hpp"

#include "AmqpConsumerProducerExampleApp.hpp"

int main(int argc, char **argv)
{
	try {
		START_EASYLOGGINGPP(argc, argv);

		std::cout << "AMQP Consumer/Producer Example App!" << std::endl;

		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./AmqpConsumerProducer.log");

		LOG(INFO) << "AMQP Consumer/Producer Example App!";

		using App = amqpserver::AmqpServerAppManager<AmqpConsumerProducerExampleApp>;
		std::thread appThread = framework::application::create_basic_app_in_thread<App>(argc, argv);
		appThread.join();
	} catch (const std::runtime_error& e) {
		std::cout << "System Error: " << e.what() << std::endl;
	}
}
