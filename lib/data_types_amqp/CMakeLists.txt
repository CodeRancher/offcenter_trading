
add_library(offcenter_trading_data_types_amqp "")


target_sources(offcenter_trading_data_types_amqp
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/CandlestickDataAmqp.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/InstrumentAmqp.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/CandlestickTimeRangeAmqp.cpp
)

target_include_directories(offcenter_trading_data_types_amqp
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(offcenter_trading_data_types_amqp
	offcenter_trading_data_types
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
)
