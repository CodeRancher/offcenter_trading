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

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_trading_oanda_persistence_client trading_oanda_persistence_client)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

###############################################################################
# Example Consumer
target_sources(${LIB_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/OandaPersistenceClient.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/OandaPersistenceEndpoints.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/LookupTableData.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ProcessInstrumentDataThread.cpp
)

target_include_directories(${LIB_NAME}
	BEFORE PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(${LIB_NAME}
	SYSTEM PRIVATE
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

target_link_libraries(${LIB_NAME}
	Offcenter::offcenter_common_framework
	Offcenter::offcenter_common
	Offcenter::offcenter_common_program_options
	Offcenter::offcenter_common_restserver
	Offcenter::offcenter_common_soci
	Offcenter::offcenter_common_threading
	offcenter_trading_data_types
	offcenter_trading_data_types_json
	Offcenter::oanda_v20
	#offcenter_common_amqp
	#offcenter_common_amqpserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	MariaDBClient::MariaDBClient
	cpprestsdk::cpprest
	nlohmann_json::nlohmann_json
	${ACTIVEMQCPP_LIBRARIES}
	${CMAKE_DL_LIBS}
	Threads::Threads
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()
