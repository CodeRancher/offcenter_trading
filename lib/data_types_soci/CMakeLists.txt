
find_package(MariaDBClient REQUIRED)

add_library(offcenter_trading_data_types_soci "")

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

target_sources(offcenter_trading_data_types_soci
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/InstrumentSoci.cpp
)

target_include_directories(offcenter_trading_data_types_soci
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${MariaDBClient_INCLUDE_DIRS}
		${SOCI_INCLUDE_DIR}/..
)

target_link_libraries(offcenter_trading_data_types_soci
	offcenter_trading_common
	offcenter_trading_data_types
	${SOCI_LIBRARY}
	${SOCI_mysql_PLUGIN}
	MariaDBClient::MariaDBClient
	${EASYLOGGINGPP_LIBRARY}
)
