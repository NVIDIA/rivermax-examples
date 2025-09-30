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

project(rivermax-legacy
    VERSION 1.0.0
    DESCRIPTION "Legacy Rivermax applications and services"
    HOMEPAGE_URL https://github.com/NVIDIA/rivermax-examples/tree/main/legacy
    LANGUAGES CXX C
)

add_subdirectory(services)

set(RMAX_LEGACY_EXAMPLES
    generic_receiver
)

foreach(example_dir ${RMAX_LEGACY_EXAMPLES})
    add_subdirectory(${example_dir})
endforeach()
