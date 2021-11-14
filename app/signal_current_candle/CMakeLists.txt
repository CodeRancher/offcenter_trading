
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(AMQP_LIBRARIES
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_amqp
	offcenter_common_amqpserver
	offcenter_common_threading
	offcenter_trading_data_types
	offcenter_trading_data_types_amqp
	offcenter_trading_trading
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
add_executable (offcenter_signal_current_candle
    ${CMAKE_CURRENT_LIST_DIR}/src/signal_current_candle_app.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SignalCurrentCandleApp.cpp
)

target_link_libraries(offcenter_signal_current_candle
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_signal_current_candle
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)


