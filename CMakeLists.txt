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
# @date   05-27-2019
#

cmake_minimum_required (VERSION 3.19 FATAL_ERROR)

set(PROJECT_NAME offcenter_trading)
project (${PROJECT_NAME} LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extern/cmake)

include(OffcenterBuild)
offcenter_proj_setup(${PROJECT_NAME} 0 0 1)

###############################################################################
# Libraries

#include(FetchContent)
#include(ExternalProject)
INCLUDE(FindPackageHandleStandardArgs)

cmake_policy(SET CMP0074 NEW)

# LoggingCpp
find_package(EASYLOGGINGPP REQUIRED)
find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(Soci REQUIRED)
find_package(MariaDBClient REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(TBB REQUIRED)
find_package(APR REQUIRED)
find_package(ActiveMQcpp REQUIRED)
find_package(date REQUIRED)
find_package(oanda_v20 REQUIRED)

offcenter_find_threads()
offcenter_find_boost()
offcenter_find_openssl()

find_package(offcenter_common REQUIRED)
#find_package(offcenter_common_amqp REQUIRED)

		
#find_package(OffcenterTradingDataTypes REQUIRED)

offcenter_cpp_check(OFF)
offcenter_unit_tests(ON)
offcenter_v20_logging(OFF)

###############################################################################
# sub projects
add_subdirectory(extern)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(app)
add_subdirectory(doc)

offcenter_proj_install()
