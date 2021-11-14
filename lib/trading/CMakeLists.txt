
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(offcenter_trading_trading "")

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(AMQP_LIBRARIES
	offcenter_common_threading
	offcenter_common_amqp
	offcenter_trading_data_types
	offcenter_trading_data_types_amqp
	offcenter_trading_oanda_persistence_client
	${EASYLOGGINGPP_LIBRARY}
)

target_sources(offcenter_trading_trading
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/Topics.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ProcessCurrentCandleRange.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BuildHigherTimeframeCandle.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BuildCandlestick.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BuildCandlesticks.cpp
)

target_include_directories(offcenter_trading_trading
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

target_link_libraries(offcenter_trading_trading
	${AMQP_LIBRARIES}
)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

