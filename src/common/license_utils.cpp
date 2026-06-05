// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "license.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#ifdef __linux__
#include <unistd.h>
#endif

namespace gao::license {
std::string get_device_fingerprint() {
    std::string fingerprint = "DEMO_FINGERPRINT";
#ifdef __linux__
    std::ifstream uuid_file("/sys/class/dmi/id/product_uuid");
    if (uuid_file.is_open()) {
        std::getline(uuid_file, fingerprint);
    } else {
        char hostname[256];
        gethostname(hostname, sizeof(hostname));
        fingerprint = hostname;
    }
#endif
    return fingerprint;
}
bool verify_license(const std::string& license_file, const std::string& sig_file) {
    // TODO: 实现真实验签
    return true;
}
std::vector<uint8_t> decrypt_core_library(const std::vector<uint8_t>& encrypted, const std::string& key) {
    // TODO: 实现真实解密
    return encrypted;
}
} // namespace gao::license
