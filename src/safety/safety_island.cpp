// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "safety_island.h"
#include <chrono>
#include <thread>
#include <iostream>

namespace gao::safety {
SafetyIsland::~SafetyIsland() { stop(); }
SafetyIsland& SafetyIsland::instance() {
    static SafetyIsland inst;
    return inst;
}
void SafetyIsland::startMonitoring(std::function<bool()> health_check, int period_ms) {
    if (running_) return;
    running_ = true;
    monitor_thread_ = std::make_unique<std::thread>([this, health_check, period_ms]() {
        while (running_) {
            if (!health_check()) {
                triggerFault();
                emergencyStop();
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(period_ms));
        }
    });
}
void SafetyIsland::stop() {
    running_ = false;
    if (monitor_thread_ && monitor_thread_->joinable())
        monitor_thread_->join();
}
void SafetyIsland::triggerFault() {
    healthy_ = false;
    std::cerr << "SafetyIsland: fault triggered!" << std::endl;
}
void SafetyIsland::reset() { healthy_ = true; }
void SafetyIsland::emergencyStop() {
    std::cout << "SafetyIsland: executing emergency stop (G4 procedure)" << std::endl;
}
} // namespace gao::safety
