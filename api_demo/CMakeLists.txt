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

project(rivermax-api-demo
    VERSION 1.0.0
    DESCRIPTION "Demo applications demonstrating the usage of Rivermax API"
    HOMEPAGE_URL https://github.com/NVIDIA/rivermax-examples/tree/main/api_demo
    LANGUAGES CXX C
)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC rivermax-dev-kit)
target_sources(${PROJECT_NAME} PRIVATE
    api_base.cpp
    api_base.h
)

set(RMAX_API_DEMO_EXAMPLES
    input
    output_generic
    output_media
)

foreach(example_dir ${RMAX_API_DEMO_EXAMPLES})
    add_subdirectory(${example_dir})
endforeach()
