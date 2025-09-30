/*
 * SPDX-FileCopyrightText: Copyright (c) 2024-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef API_DEMO_OUTPUT_GENERIC_OUTPUT_GENERIC_BASE_H_
#define API_DEMO_OUTPUT_GENERIC_OUTPUT_GENERIC_BASE_H_

#include <cstddef>
#include <string>

#ifdef __linux__
#include <netinet/in.h>
#else
#include <winsock2.h>
#endif

#include "api_base.h"


constexpr size_t DEFAULT_PACKET_PAYLOAD_SIZE = 1472;
constexpr size_t DEFAULT_NUM_OF_CHUNKS = 5;
constexpr size_t DEFAULT_CHUNK_SIZE = 4096;

/**
 * @brief Base class for all output generic API demo applications.
 *
 * This class provides the base functionality for all output generic API demo applications.
 * It provides common command line options and application initializations.
 */
class RmxOutGenericAPIBaseDemoApp : public RmxAPIBaseDemoApp
{
protected:
    RmxOutGenericAPIBaseDemoApp(const std::string& app_description, const std::string& app_examples);
    virtual ~RmxOutGenericAPIBaseDemoApp() = default;

    virtual void add_cli_options() override;
    virtual void post_cli_parse_initialization() override;

    /* Remote destination address */
    sockaddr_in m_destination_address;
};

#endif // API_DEMO_OUTPUT_GENERIC_OUTPUT_GENERIC_BASE_H_
