# SPDX-FileCopyrightText: Copyright (c) 2022-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_executable(rivermax_player)

# TODO: Fix the deprecated warnings and remove this script-block
if (MSVC)
    target_compile_options(rivermax_player PRIVATE /wd4996)
else()
    target_compile_options(rivermax_player PRIVATE -Wno-deprecated-declarations)
endif()

target_include_directories(rivermax_player PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(rivermax_player
    PRIVATE
        rivermax_player.cpp
)

include(FetchFFmpeg)
find_package(FFmpeg REQUIRED)

find_package(Rivermax 1.51.6 REQUIRED)

target_link_libraries(rivermax_player PRIVATE rivermax-dev-kit rivermax-app-services FFmpeg::FFmpeg)
