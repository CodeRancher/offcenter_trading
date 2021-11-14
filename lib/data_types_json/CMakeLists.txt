
find_package(nlohmann_json REQUIRED)

add_library(offcenter_trading_data_types_json "")

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

target_sources(offcenter_trading_data_types_json
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/InstrumentJson.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/InstrumentCountJson.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/DateTimeJson.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/JsonConversion.cpp
)

target_include_directories(offcenter_trading_data_types_json
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
)

target_link_libraries(offcenter_trading_data_types_json
	offcenter_trading_common
	offcenter_trading_data_types
	${EASYLOGGINGPP_LIBRARY}
	nlohmann_json::nlohmann_json
)
