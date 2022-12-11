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

offcenter_exe_constants(signal_current_candle_trigger)

###############################################################################
# Example Consumer
add_executable (${EXE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/signal_current_candle_trigger_app.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/SignalCurrentCandleTriggerApp.cpp
)

target_link_libraries(${EXE_NAME}
	Offcenter::offcenter_common_framework
	Offcenter::offcenter_common
	offcenter_trading_data_types
	offcenter_trading_data_types_amqp
	offcenter_trading_trading
	Offcenter::offcenter_common_program_options
	Offcenter::offcenter_common_amqp
	Offcenter::offcenter_common_amqpserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::SSL
)

target_include_directories(${EXE_NAME}
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	# SYSTEM
	# 	${EASYLOGGINGPP_INCLUDE_DIR}
	# 	${ACTIVEMQCPP_INCLUDE_DIR}
	# 	${APR_INCLUDE_DIR}
)

offcenter_exe_install()
