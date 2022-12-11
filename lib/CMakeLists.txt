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
# @date   09-29-2022
#

offcenter_libs_setup()

add_subdirectory(data_types)
add_subdirectory(data_types_amqp)
add_subdirectory(data_types_json)
add_subdirectory(data_types_soci)
add_subdirectory(common)
add_subdirectory(oanda_persistence_client)
add_subdirectory(trading)
add_subdirectory(trading_db)
add_subdirectory(lib2)
#add_subdirectory(imgui_cmake)

offcenter_libs_install()
