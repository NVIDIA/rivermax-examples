/*
 * SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#ifndef API_DEMO_OUTPUT_MEDIA_DYNAMIC_MEDIA_SEND_H_
#define API_DEMO_OUTPUT_MEDIA_DYNAMIC_MEDIA_SEND_H_

#include <cstddef>
#include <random>

#include "output_media_base.h"
#include "rdk/rivermax_dev_kit.h"

using namespace rivermax::dev_kit::services;


constexpr const char* APP_DESCRIPTION = "NVIDIA Rivermax API Dynamic Media Send Demo App (Ancillary/ST 2110-40)";
constexpr const char* APP_EXAMPLES = \
    "Examples:\n"
    "  1. rmx_dynamic_media_send_demo_app --local-ip 1.2.3.4\n"
    "  2. rmx_dynamic_media_send_demo_app --local-ip 1.2.3.4 --dst-ip 231.1.2.3 --dst-port 60000";

/**
 * @brief Rivermax API Dynamic Media Send Demo Application (Ancillary/ST 2110-40).
 *
 * This application demonstrates the usage of the Rivermax Media Send API with dynamic packet sizes
 * for SMPTE 2110-40 ancillary data streams.
 *
 * Unlike the static stream examples, this example demonstrates
 * dynamic packet sizing where each chunk can have variable packet counts and sizes.
 */
class RmxDynamicMediaSendDemoApp : public RmxOutMediaAPIBaseDemoApp
{
public:
    RmxDynamicMediaSendDemoApp() : RmxOutMediaAPIBaseDemoApp(APP_DESCRIPTION, APP_EXAMPLES) {}
    virtual ~RmxDynamicMediaSendDemoApp() = default;
protected:
    virtual void add_cli_options() override;
    virtual ReturnStatus operator()() override;

private:
    /* Dynamic stream configuration */
    static constexpr size_t MIN_PACKETS_PER_CHUNK = 1;
    static constexpr size_t MAX_PACKETS_PER_CHUNK = 10;
    static constexpr uint16_t MIN_PACKET_PAYLOAD_SIZE = 20;

    /* Random number generator */
    std::mt19937 m_gen{std::random_device{}()};
};

#endif // API_DEMO_OUTPUT_MEDIA_DYNAMIC_MEDIA_SEND_H_
