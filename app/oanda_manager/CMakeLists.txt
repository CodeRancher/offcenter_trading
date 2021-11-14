
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

cmake_policy(SET CMP0074 NEW)
find_package(nlohmann_json REQUIRED)
find_package(cpprestsdk REQUIRED)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

find_package(Boost
	1.74
	COMPONENTS program_options atomic thread system regex filesystem random chrono serialization 
)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(AMQP_LIBRARIES
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_amqp
	offcenter_common_amqpserver
	offcenter_trading_data_types
	offcenter_trading_trading
	oanda_v20
	cpprestsdk::cpprest
	nlohmann_json::nlohmann_json
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
file(COPY ${CMAKE_CURRENT_LIST_DIR}/oanda_manager.config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin)
message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/oanda_manager.config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin")

###############################################################################
# Example Producer
add_executable (offcenter_trading_oanda_manager
    ${CMAKE_CURRENT_LIST_DIR}/src/oanda_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/OandaManagerApp.cpp
)

target_link_libraries(offcenter_trading_oanda_manager
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_trading_oanda_manager
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

