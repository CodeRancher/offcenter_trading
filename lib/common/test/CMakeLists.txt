
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(GoogleTest)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)
find_package(cpprestsdk REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(offcenter_trading_lib1_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_link_libraries(offcenter_trading_lib1_tests
	oanda_v20
	GTest::gtest
	cpprestsdk::cpprest
	${EASYLOGGINGPP_LIBRARY}
	#nlohmann_json::nlohmann_json
	Threads::Threads
	OpenSSL::Crypto
)

target_include_directories(offcenter_trading_lib1_tests
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${CMAKE_CURRENT_LIST_DIR}/include

	#SYSTEM
	#	${Easyloggingpp_SOURCE_DIR}/src
)

gtest_discover_tests(offcenter_trading_lib1_tests)

add_test(NAME monolithic COMMAND offcenter_trading_lib1_tests)
