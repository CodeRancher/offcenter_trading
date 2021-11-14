
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(GoogleTest)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)
find_package(cpprestsdk REQUIRED)

add_executable(offcenter_trading_db_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/soci_mysql_connection_options_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/oanda_trading_db_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/trading_db_test.cpp
	#${CMAKE_CURRENT_LIST_DIR}/src/lookup_table_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/globalvariables.cpp
)

target_link_libraries(offcenter_trading_db_tests
	offcenter_common_soci
	offcenter_trading_db
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	${MariaDBClient_LIBRARIES}
	${CMAKE_DL_LIBS}
	Threads::Threads
	OpenSSL::Crypto
)

target_include_directories(offcenter_trading_db_tests
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include

	#SYSTEM
	#	${Easyloggingpp_SOURCE_DIR}/src
)

target_compile_definitions(offcenter_trading_db_tests
	PUBLIC
		ELPP_THREAD_SAFE
		ELPP_FRESH_LOG_FILE
		ELPP_NO_DEFAULT_LOG_FILE
)

gtest_discover_tests(offcenter_trading_db_tests)

add_test(NAME monolithic COMMAND offcenter_trading_db_tests)

