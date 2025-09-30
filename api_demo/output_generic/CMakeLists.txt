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

project(rivermax-output-generic-demo
    VERSION 1.0.0
    DESCRIPTION "Output Generic API demo applications for Rivermax"
    HOMEPAGE_URL https://github.com/NVIDIA/rivermax-examples/tree/main/api_demo/output_generic
    LANGUAGES CXX C
)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC rivermax-api-demo)
target_sources(${PROJECT_NAME} PRIVATE
    output_generic_base.cpp
    output_generic_base.h
)

add_library(rivermax-output-generic-demo-base ALIAS ${PROJECT_NAME})

set(RMAX_API_DEMO_OUTPUT_GENERIC_EXAMPLES
    generic_send
)

foreach(app_dir ${RMAX_API_DEMO_OUTPUT_GENERIC_EXAMPLES})
    add_subdirectory(${app_dir})
endforeach()
