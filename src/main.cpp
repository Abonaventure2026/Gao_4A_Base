// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <signal.h>
#include "common/watermark.h"
#include "common/morphology/IMorphology.h"
#include "dynamics/IDynamics.h"
#include "control/IController.h"
#include "safety/behavior_tree_executor.h"
#include "safety/safety_island.h"
#include "scenario/scene_manager.h"
#include "digital_twin/DigitalTwinSync.h"
#include "common/license.h"

using namespace gao;
volatile sig_atomic_t keep_running = 1;
void signal_handler(int) { keep_running = 0; }

int main(int argc, char** argv) {
    signal(SIGINT, signal_handler);
    watermark::print_watermark();
    std::cout << "Gao 4A Autopilot Base V5.0 Demo" << std::endl;

    // 演示设备指纹
    std::string fp = license::get_device_fingerprint();
    std::cout << "Device fingerprint: " << fp << std::endl;

    // 演示场景加载
    scenario::SceneManager sm;
    if (sm.load("S111")) {
        auto w = sm.getWeights();
        auto s = sm.getSafetyParams();
        std::cout << "Scene S111: rule=" << w.rule << " grade=" << s.grade << std::endl;
    }

    // 演示构型注册（需要分支预先注册，此处仅展示接口）
    auto morph = morphology::MorphologyRegistry::instance().getMorphology("T-1");
    if (morph) {
        auto dyn = morph->createDynamics();
        auto ctrl = morph->createController();
        std::cout << "Morphology T-1 loaded successfully." << std::endl;
    } else {
        std::cout << "No morphology registered. Please link a branch that registers T-1." << std::endl;
    }

    // 安全行为树
    safety::BehaviorTreeExecutor bt("config/safety_bt.xml");
    bt.start();

    // 数字孪生同步
    digital_twin::DigitalTwinSync::instance().init("config/digital_twin_config.yaml");

    // 主循环（空转）
    while (keep_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    bt.stop();
    return 0;
}
