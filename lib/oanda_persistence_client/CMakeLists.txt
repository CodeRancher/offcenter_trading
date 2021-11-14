#
# Copyright 2021 Scott Brauer
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an  BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# @file   CMakeLists.txt
# @author Scott Brauer
# @date   05-20-2021
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(offcenter_trading_oanda_persistence_client "")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

cmake_policy(SET CMP0074 NEW)
find_package(nlohmann_json REQUIRED)
find_package(cpprestsdk REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

###############################################################################
# Example Consumer
target_sources(offcenter_trading_oanda_persistence_client
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/OandaPersistenceClient.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/OandaPersistenceEndpoints.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/LookupTableData.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ProcessInstrumentDataThread.cpp
)

target_link_libraries(offcenter_trading_oanda_persistence_client
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_restserver
	offcenter_common_soci
	offcenter_common_threading
	offcenter_trading_data_types
	offcenter_trading_data_types_json
	oanda_v20
	#offcenter_common_amqp
	#offcenter_common_amqpserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	cpprestsdk::cpprest
	nlohmann_json::nlohmann_json
	${ACTIVEMQCPP_LIBRARIES}
	${CMAKE_DL_LIBS}
	Threads::Threads
)

target_include_directories(offcenter_trading_oanda_persistence_client
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()
