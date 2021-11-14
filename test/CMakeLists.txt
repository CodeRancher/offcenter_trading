
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(GoogleTest)
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(cpprestsdk REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(offcenter_trading_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_link_libraries(offcenter_trading_tests
	oanda_v20
	cpprestsdk::cpprest
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
	OpenSSL::Crypto
)

target_include_directories(offcenter_trading_tests
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${CMAKE_CURRENT_LIST_DIR}/include

	SYSTEM
		${Easyloggingpp_SOURCE_DIR}/src
)

gtest_discover_tests(offcenter_trading_tests)

add_test(NAME monolithic COMMAND offcenter_trading_tests)
