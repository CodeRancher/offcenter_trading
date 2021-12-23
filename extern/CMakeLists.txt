# set minimum cmake version
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# project name and language
project(extern LANGUAGES CXX)

# require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(FetchContent)
include(ExternalProject)

# FetchContent_Declare(
# 	nlohmann_json
#     GIT_REPOSITORY	https://github.com/nlohmann/json.git
#     GIT_TAG			v3.9.1
# )

# FetchContent_Declare(
# 	cpprestsdk
#     GIT_REPOSITORY	https://github.com/microsoft/cpprestsdk.git
#     GIT_TAG			v2.10.16
# )

set(build_static_lib ON)
# FetchContent_Declare(
# 	easyloggingpp
#     GIT_REPOSITORY	https://github.com/amrayn/easyloggingpp.git
#     GIT_TAG			v9.97.0
# )

# FetchContent_Declare(
# 	oanda
#     GIT_REPOSITORY	git@gitlab:Offcenter/trading/brokers/oanda.git
# )

# if(ENABLE_UNIT_TESTS)
#   # the following code to fetch googletest
#   # is inspired by and adapted after:
#   #   - https://cmake.org/cmake/help/v3.11/module/FetchContent.html

# 	FetchContent_Declare(
#     	googletest
#     	GIT_REPOSITORY https://github.com/google/googletest.git
#     	GIT_TAG        release-1.10.0
# 	)

# 	FetchContent_MakeAvailable(
# 		googletest
# 	)

# endif()

set(PYTHON_VERSION 3)

# FetchContent_MakeAvailable(
#     nlohmann_json
#     cpprestsdk
#     easyloggingpp
#     oanda
# )

##message(STATUS "NLOHMANN_JSON include dir: ${NLOHMANN_JSON_INCLUDE_DIR}")
##message(STATUS "NLOHMANN_JSON binary dir: ${NLOHMANN_JSON_BINARY_DIR}")

#message(STATUS "NLOHMANN_JSON include dir: ${OANDA_INCLUDE_DIR}")
#message(STATUS "NLOHMANN_JSON binary dir: ${OANDA_BINARY_DIR}")

set(CMAKE_VERBOSE_MAKEFILE ON)
