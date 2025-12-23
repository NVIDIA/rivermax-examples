/*
 * SPDX-FileCopyrightText: Copyright (c) 2024-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#ifndef API_DEMO_OUTPUT_MEDIA_OUTPUT_MEDIA_BASE_H_
#define API_DEMO_OUTPUT_MEDIA_OUTPUT_MEDIA_BASE_H_

#include <cinttypes>
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "api_base.h"
#include "rdk/rivermax_dev_kit.h"

using namespace rivermax::dev_kit::services;

/**
 * @brief Base class for all output media API demo applications.
 *
 * This class provides the base functionality for all output media API demo applications.
 * It provides common command line options and application initializations.
 */
class RmxOutMediaAPIBaseDemoApp : public RmxAPIBaseDemoApp
{
protected:
    RmxOutMediaAPIBaseDemoApp(const std::string& app_description, const std::string& app_examples);
    virtual ~RmxOutMediaAPIBaseDemoApp() = default;

    virtual void add_cli_options() override;
    virtual void post_cli_parse_initialization() override;

    /* Selected SMPTE standard */
    SMPTEStandard m_smpte_standard = SMPTEStandard::ST_2110_20;
    /* Stream settings (per SMPTE standard) */
    std::shared_ptr<MediaSettings> m_media_settings;

private:
    std::map<SMPTEStandard, std::function<void()>> m_smpte_init_map;

    void initialize_video_settings();
    void initialize_audio_settings();
    void initialize_ancillary_settings();

    void calculate_media_settings(std::shared_ptr<MediaSettings> settings);
};

#endif // API_DEMO_OUTPUT_MEDIA_OUTPUT_MEDIA_BASE_H_
