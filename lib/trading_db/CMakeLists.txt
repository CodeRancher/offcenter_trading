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
# @date   04-06-2021
#

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(MariaDBClient REQUIRED)

add_library(offcenter_trading_db "")

target_sources(offcenter_trading_db
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/TradingDB.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/OandaTradingDB.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/CreateTradingDB.cpp
)

target_include_directories(offcenter_trading_db
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		
	SYSTEM
		${MariaDBClient_INCLUDE_DIRS}
		${SOCI_INCLUDE_DIR}/..
		${nlohmann_json_SOURCE_DIR}/include
		${cpprestsdk_SOURCE_DIR}/include
		${Easyloggingpp_SOURCE_DIR}/src
		${oanda_SOURCE_DIR}/include
)

target_link_libraries(offcenter_trading_db
	offcenter_trading_data_types
	offcenter_trading_data_types_soci
	offcenter_common_soci
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	MariaDBClient::MariaDBClient
	${CMAKE_DL_LIBS}
	Threads::Threads
	OpenSSL::Crypto
)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

