
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

cmake_policy(SET CMP0074 NEW)
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(MariaDBClient REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable (offcenter_create_trading_db
    ${CMAKE_CURRENT_LIST_DIR}/src/create_trading_db.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/CreateTradingDBApp.cpp
)

target_link_libraries(offcenter_create_trading_db
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_soci
	offcenter_trading_db
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	MariaDBClient::MariaDBClient
	${CMAKE_DL_LIBS}
	Threads::Threads
	OpenSSL::Crypto
)

target_include_directories(offcenter_create_trading_db
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		#${CMAKE_CURRENT_LIST_DIR}/../include
		#${CMAKE_CURRENT_LIST_DIR}/../../framework/include
		#${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
		#${CMAKE_CURRENT_LIST_DIR}/../../common/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${MariaDBClient_INCLUDE_DIRS}
		#${SOCI_INCLUDE_DIR}/..
)

message(STATUS "soci_create_simple_db EASYLOGGINGPP_INCLUDE_DIR(${EASYLOGGINGPP_INCLUDE_DIR}), MariaDBClient_INCLUDE_DIRS(${MariaDBClient_INCLUDE_DIRS}, SOCI_INCLUDE_DIR(${SOCI_INCLUDE_DIR}) ")
message(STATUS "soci_create_simple_db EASYLOGGINGPP_LIBRARY(${EASYLOGGINGPP_LIBRARY}), SOCI_mysql_PLUGIN(${SOCI_mysql_PLUGIN}), SOCI_LIBRARY(${SOCI_LIBRARY}), MariaDBClient_LIBRARIES(${MariaDBClient_LIBRARIES}),")
