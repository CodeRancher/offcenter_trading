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
# @date   04-07-2019
#

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_trading_trading trading_trading)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/Topics.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ProcessCurrentCandleRange.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BuildHigherTimeframeCandle.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BuildCandlestick.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/BuildCandlesticks.cpp
)

target_include_directories(${LIB_NAME}
	PUBLIC
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
	Offcenter::offcenter_common_threading
	Offcenter::offcenter_common_amqp
	offcenter_trading_data_types
	offcenter_trading_data_types_amqp
	offcenter_trading_oanda_persistence_client
	${EASYLOGGINGPP_LIBRARY}
	${AMQP_LIBRARIES}
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

