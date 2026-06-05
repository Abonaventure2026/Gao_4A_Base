// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "dynamics/state.h"

namespace gao::digital_twin {

class IVendorBridge {
public:
    virtual ~IVendorBridge() = default;
    virtual bool connect(const std::string& url) = 0;
    virtual void sendTransform(const dynamics::State& state) = 0;
    virtual void sendTrajectory(const std::vector<dynamics::State>& traj) = 0;
};

class DigitalTwinSync {
public:
    static DigitalTwinSync& instance();
    bool init(const std::string& config_path);
    void publishState(const dynamics::State& state, const std::string& frame_id);
    void publishTrajectory(const std::vector<dynamics::State>& trajectory);
    void setVendorBridge(std::unique_ptr<IVendorBridge> bridge);
private:
    std::unique_ptr<IVendorBridge> bridge_;
    bool enabled_ = false;
};

} // namespace gao::digital_twin
