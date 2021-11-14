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

#include "CreateTradingDBEnvironment.hpp"
#include "globalvariables.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	// ::testing::InitGoogleMock(&argc, argv);
	START_EASYLOGGINGPP(argc, argv);

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./TradingDB.log");

	if (argc == 5) {
		g_dbname = argv[1];
		g_user = argv[2];
		g_password = argv[3];
		g_host = argv[4];

		std::cout << "Running unit tests with:"
				<< "\n\tHost:     " << g_host
				<< "\n\tDB:       " << g_dbname
				<< "\n\tUser:     " << g_user
				<< "\n\tPassword: *******";

    } else {
        std::cerr << "Usage: " << argv[0] << " <DBName> <User> <Password> <Host>" << std::endl;
        return 0;
    }

	testing::Environment* const debEnv = testing::AddGlobalTestEnvironment(new CreateTradingDBEnvironment);
	return RUN_ALL_TESTS();
}
