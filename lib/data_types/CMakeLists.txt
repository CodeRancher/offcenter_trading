
add_library(offcenter_trading_data_types "")

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

target_sources(offcenter_trading_data_types
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/Broker.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BrokerServer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ForexDateTime.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/calculation/Candlestick.cpp
)

target_include_directories(offcenter_trading_data_types
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

target_link_libraries(offcenter_trading_data_types
	offcenter_trading_common
	offcenter_common_amqp
	Boost::headers
	${EASYLOGGINGPP_LIBRARY}
	${MPFR_LIBRARIES}
	${GMP_LIBRARIES}
)

add_subdirectory(example)
if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

