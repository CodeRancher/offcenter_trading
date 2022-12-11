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
#
#
# @file   CMakeLists.txt
# @author Scott Brauer
# @date   04-11-2019
#

offcenter_cxx()
offcenter_elpp()
offcenter_test_constants(trading_oanda_persistence_client)

add_executable(${EXE_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/oanda_persistence_endpoint_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/persistence_endpoint_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/lookup_table_test.cpp
)

target_link_libraries(${EXE_NAME}
	Offcenter::offcenter_common_amqp
	offcenter_trading_oanda_persistence_client
	offcenter_trading_data_types_json
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	${MariaDBClient_LIBRARIES}
	${CMAKE_DL_LIBS}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::Crypto
)

target_include_directories(${EXE_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
)

message(STATUS "--------------------${EXE_NAME}: ${ACTIVEMQCPP_INCLUDE_DIR}, ${APR_INCLUDE_DIR}, ${EASYLOGGINGPP_INCLUDE_DIR}")

target_include_directories(${EXE_NAME}
	SYSTEM INTERFACE
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

offcenter_test()