
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

cmake_policy(SET CMP0074 NEW)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(AMQP_LIBRARIES
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_amqp
	offcenter_common_amqpserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	#cpprestsdk::cpprest
	#nlohmann_json::nlohmann_json
	${ACTIVEMQCPP_LIBRARIES}
	Threads::Threads
) 

###############################################################################
# Copy config file
#configure_file(${CMAKE_CURRENT_LIST_DIR}/config.ini config.ini COPYONLY)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin)
message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin")


###############################################################################
# Example Consumer
add_executable (offcenter_amqpserver_example_consumer
    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_consumer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpConsumerExampleApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
)

target_link_libraries(offcenter_amqpserver_example_consumer
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_amqpserver_example_consumer
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

###############################################################################
# Example Consumer Producer
add_executable (offcenter_amqpserver_example_consumer_producer
    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_consumer_producer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpConsumerProducerExampleApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
)

target_link_libraries(offcenter_amqpserver_example_consumer_producer
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_amqpserver_example_consumer_producer
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

###############################################################################
# Example Producer
add_executable (offcenter_amqpserver_example_producer
    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_producer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpProducerExampleApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
)

target_link_libraries(offcenter_amqpserver_example_producer
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_amqpserver_example_producer
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

