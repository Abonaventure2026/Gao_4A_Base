// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-02

#pragma once
#include <string>
#include <memory>
#include "dynamics/state.h"

namespace gao::safety {

class SafetyIsland;

class BehaviorTreeExecutor {
public:
    explicit BehaviorTreeExecutor(const std::string& bt_xml_path);
    ~BehaviorTreeExecutor();
    void start();
    void stop();
    bool check(const dynamics::State& state);
    void setSafetyIslandIntegration(SafetyIsland* island);
    std::string getLastFailureReason() const;
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

} // namespace gao::safety
