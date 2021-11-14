
add_library(offcenter_trading_lib2 "")

target_sources(offcenter_trading_lib2
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_include_directories(offcenter_trading_lib2
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		
	SYSTEM
		${nlohmann_json_SOURCE_DIR}/include
		${cpprestsdk_SOURCE_DIR}/include
		${Easyloggingpp_SOURCE_DIR}/src
		${oanda_SOURCE_DIR}/include
)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

