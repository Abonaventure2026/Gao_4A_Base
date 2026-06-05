// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "DigitalTwinSync.h"
#include <iostream>

namespace gao::digital_twin {

DigitalTwinSync& DigitalTwinSync::instance() {
    static DigitalTwinSync inst;
    return inst;
}

bool DigitalTwinSync::init(const std::string& config_path) {
    enabled_ = true;
    std::cout << "DigitalTwinSync init with config: " << config_path << std::endl;
    return true;
}

void DigitalTwinSync::publishState(const dynamics::State& state, const std::string& frame_id) {
    // 占位
}

void DigitalTwinSync::publishTrajectory(const std::vector<dynamics::State>& trajectory) {}

void DigitalTwinSync::setVendorBridge(std::unique_ptr<IVendorBridge> bridge) {
    bridge_ = std::move(bridge);
}

} // namespace gao::digital_twin
