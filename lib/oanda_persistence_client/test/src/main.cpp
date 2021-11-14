/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Scott Brauer
 Version     :
 Copyright   : Your copyright notice
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/amqp/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	// ::testing::InitGoogleMock(&argc, argv);
	START_EASYLOGGINGPP(argc, argv);


	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./OandaPersistenceClient.log");

	LOG(INFO) << "--------------------------------------------------------------------------------";
	LOG(INFO) << "Oanda Persistence Client";

	return RUN_ALL_TESTS();
}
