#
# Copyright 2022 Scott Brauer
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
# @date   11-28-2022
#

offcenter_cxx()
offcenter_elpp()

offcenter_exe_constants(create_trading_db)

add_executable (${EXE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/create_trading_db.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/CreateTradingDBApp.cpp
)

target_link_libraries(${EXE_NAME}
Offcenter::offcenter_common_framework
	Offcenter::offcenter_common
	Offcenter::offcenter_common_program_options
	Offcenter::offcenter_common_soci
	offcenter_trading_db
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	MariaDBClient::MariaDBClient
	${CMAKE_DL_LIBS}
	Threads::Threads
	OpenSSL::Crypto
)

target_include_directories(${EXE_NAME}
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		#${CMAKE_CURRENT_LIST_DIR}/../include
		#${CMAKE_CURRENT_LIST_DIR}/../../framework/include
		#${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
		#${CMAKE_CURRENT_LIST_DIR}/../../common/include
	# SYSTEM
	# 	${EASYLOGGINGPP_INCLUDE_DIR}
	# 	${MariaDBClient_INCLUDE_DIRS}
		#${SOCI_INCLUDE_DIR}/..
)

offcenter_exe_install()
