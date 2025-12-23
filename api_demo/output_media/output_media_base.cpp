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
#include <cinttypes>
#include <map>
#include <string>
#include <iostream>

#include "output_media_base.h"
#include "rdk/rivermax_dev_kit.h"

using namespace rivermax::dev_kit::services;

static const std::map<std::string, SMPTEStandard> SMPTE_STANDARD_OPTIONS = {
    {"2110-20", SMPTEStandard::ST_2110_20},
    {"2110-30", SMPTEStandard::ST_2110_30},
    {"2110-40", SMPTEStandard::ST_2110_40}
};

RmxOutMediaAPIBaseDemoApp::RmxOutMediaAPIBaseDemoApp(const std::string& app_description, const std::string& app_examples) :
    RmxAPIBaseDemoApp(app_description, app_examples)
{
    m_smpte_init_map[SMPTEStandard::ST_2110_20] = [this]() { initialize_video_settings(); };
    m_smpte_init_map[SMPTEStandard::ST_2110_30] = [this]() { initialize_audio_settings(); };
    m_smpte_init_map[SMPTEStandard::ST_2110_40] = [this]() { initialize_ancillary_settings(); };
}

void RmxOutMediaAPIBaseDemoApp::add_cli_options()
{
    RmxAPIBaseDemoApp::add_cli_options();

    m_cli_parser_manager->add_option(CLIOptStr::DST_IP);
    m_cli_parser_manager->add_option(CLIOptStr::DST_PORT);

    m_cli_parser_manager->get_parser()
        ->add_option("--smpte-standard", m_smpte_standard, "SMPTE standard")
        ->default_val(SMPTEStandard::ST_2110_20)
        ->transform(CLI::CheckedTransformer(SMPTE_STANDARD_OPTIONS));
}

void RmxOutMediaAPIBaseDemoApp::post_cli_parse_initialization()
{
    auto& s = m_app_settings;

    s->num_of_total_streams = 1;

    m_smpte_init_map.at(m_smpte_standard)();

    if (m_media_settings && m_media_settings->media_settings_calculator) {
        s->media.sdp = m_media_settings->media_settings_calculator->generate_media_sdp(
            s->local_ip,
            s->source_port,
            s->destination_ip,
            s->destination_port
        );
    }
}

void RmxOutMediaAPIBaseDemoApp::calculate_media_settings(std::shared_ptr<MediaSettings> settings)
{
    settings->media_settings_calculator = IMediaSettingsCalculatorFactory::get_media_settings_calculator(*settings);
    if (!settings->media_settings_calculator) {
        std::cerr << "Failed to get media settings calculator" << std::endl;
        return;
    }

    ReturnStatus calc_status = settings->media_settings_calculator->calculate_media_settings();
    if (calc_status != ReturnStatus::success) {
        std::cerr << "Failed to calculate media settings" << std::endl;
        return;
    }

    m_media_settings = settings;
}

void RmxOutMediaAPIBaseDemoApp::initialize_video_settings()
{
    auto video_settings = std::make_shared<SMPTE_2110_20_MediaSettings>();

    video_settings->resolution = Resolution{_1080_WIDTH, _1080_HEIGHT};
    video_settings->frame_rate = {60, 1};
    video_settings->sampling_type = VideoSampling::YCbCr_4_2_2;
    video_settings->bit_depth = VideoBitDepth::_10;
    video_settings->video_scan_type = VideoScanType::Progressive;
    video_settings->sample_rate = 90000;
    video_settings->media_units_in_mem_block = 1;

    calculate_media_settings(video_settings);
}

void RmxOutMediaAPIBaseDemoApp::initialize_audio_settings()
{
    auto audio_settings = std::make_shared<SMPTE_2110_30_MediaSettings>();

    audio_settings->sampling_rate = AudioSamplingRate::_48000;
    audio_settings->encoding = AudioEncoding::L24;
    audio_settings->num_channels = 2;
    audio_settings->ptime_usec = 1000;
    audio_settings->media_units_in_mem_block = 1;

    calculate_media_settings(audio_settings);
}

void RmxOutMediaAPIBaseDemoApp::initialize_ancillary_settings()
{
    auto ancillary_settings = std::make_shared<SMPTE_2110_40_MediaSettings>();

    ancillary_settings->data_identifiers.push_back(ANCILLARY_TIMECODE_IDENTIFIER);
    ancillary_settings->media_units_in_mem_block = 1;

    calculate_media_settings(ancillary_settings);
}
