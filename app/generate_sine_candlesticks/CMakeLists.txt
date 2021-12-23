
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

cmake_policy(SET CMP0074 NEW)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

#find_package(Boost
#	1.74
#	COMPONENTS program_options atomic thread system regex filesystem random chrono serialization log multiprecision
#)

set(AMQP_LIBRARIES
	offcenter_common_framework
	offcenter_common
	offcenter_trading_data_types
	offcenter_trading_data_types_amqp
	offcenter_trading_trading
	offcenter_common_program_options
	offcenter_common_amqp
	offcenter_common_amqpserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::SSL
) 

###############################################################################
# Copy config file
#configure_file(${CMAKE_CURRENT_LIST_DIR}/config.ini config.ini COPYONLY)
#file(COPY ${CMAKE_CURRENT_LIST_DIR}/signal_current_candle.config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin)
#message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/signal_current_candle.config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin")


###############################################################################
# Example Consumer
add_executable (offcenter_generate_sine_candlesticks.sin
    ${CMAKE_CURRENT_LIST_DIR}/src/generate_sine_candlesticks_app.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/GenerateSineCandlesticksApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/GenerateSineCandlesticksApps.cpp
)

target_compile_definitions(offcenter_generate_sine_candlesticks.sin
	PRIVATE
		APP_TYPE=Sine
)

target_link_libraries(offcenter_generate_sine_candlesticks.sin
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_generate_sine_candlesticks.sin
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)


