// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-02

#pragma once
#include <functional>
#include <memory>
#include <thread>

namespace gao::safety {

class SafetyIsland {
public:
    ~SafetyIsland();
    static SafetyIsland& instance();
    void startMonitoring(std::function<bool()> health_check, int period_ms);
    void stop();
    void triggerFault();
    void reset();
    void emergencyStop();
    void initialize() {}   // 简化
    void shutdown() { stop(); }
    void engage() { emergencyStop(); }
    bool isHealthy() const { return healthy_; }
private:
    SafetyIsland() = default;
    bool running_ = false;
    bool healthy_ = true;
    std::unique_ptr<std::thread> monitor_thread_;
};

} // namespace gao::safety
