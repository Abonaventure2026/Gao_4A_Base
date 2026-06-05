// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <string>
#include <vector>

namespace gao::license {

std::string get_device_fingerprint();
bool verify_license(const std::string& license_file, const std::string& sig_file);
std::vector<uint8_t> decrypt_core_library(const std::vector<uint8_t>& encrypted, const std::string& key);

} // namespace gao::license
