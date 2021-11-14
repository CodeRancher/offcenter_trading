
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(GoogleTest)
find_package(GTest REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(offcenter_trading_trading_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/build_candlesticks_test.cpp
)

target_link_libraries(offcenter_trading_trading_tests
	offcenter_trading_data_types
	offcenter_trading_trading
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
)

target_include_directories(offcenter_trading_trading_tests
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include

	#SYSTEM
	#	${Easyloggingpp_SOURCE_DIR}/src
)

gtest_discover_tests(offcenter_trading_trading_tests)

add_test(NAME monolithic COMMAND offcenter_trading_trading_tests)

