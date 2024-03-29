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
offcenter_test_constants(data_types)

add_executable(${EXE_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/date_time_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/candlestick_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/generate_sine_candlesticks_test.cpp
)

target_link_libraries(${EXE_NAME}
	Offcenter::offcenter_common
	offcenter_trading_common
	offcenter_trading_data_types
	Boost::headers
	GTest::gtest
	GTest::gmock
	${EASYLOGGINGPP_LIBRARY}
	${MPFR_LIBRARIES}
	${GMP_LIBRARIES}
)

target_include_directories(${EXE_NAME}
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include

	#SYSTEM
	#	${Easyloggingpp_SOURCE_DIR}/src
)

offcenter_test()