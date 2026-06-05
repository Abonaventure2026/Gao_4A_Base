// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "behavior_tree_executor.h"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef GAO_ENABLE_BEHAVIOR_TREE
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#endif

namespace gao::safety {

struct BehaviorTreeExecutor::Impl {
#ifdef GAO_ENABLE_BEHAVIOR_TREE
    BT::BehaviorTreeFactory factory;
    std::unique_ptr<BT::Tree> tree;
    std::unique_ptr<BT::StdCoutLogger> logger;
#endif
    SafetyIsland* island = nullptr;
    std::string last_failure;
    bool running = false;
    std::thread worker;
    std::string xml_path;
};

BehaviorTreeExecutor::BehaviorTreeExecutor(const std::string& bt_xml_path)
    : pImpl_(std::make_unique<Impl>()) {
    pImpl_->xml_path = bt_xml_path;
#ifdef GAO_ENABLE_BEHAVIOR_TREE
    // 注册自定义节点（示例）
    pImpl_->factory.registerSimpleCondition("SensorFault",
        [](BT::TreeNode&) { return false; });
    pImpl_->factory.registerSimpleAction("TriggerFailsafe",
        [](BT::TreeNode&) { return BT::NodeStatus::SUCCESS; });
    pImpl_->tree = std::make_unique<BT::Tree>(
        pImpl_->factory.createTreeFromFile(bt_xml_path));
    pImpl_->logger = std::make_unique<BT::StdCoutLogger>(*(pImpl_->tree));
#else
    std::cout << "Warning: BehaviorTree support disabled. Stub enabled." << std::endl;
#endif
}

BehaviorTreeExecutor::~BehaviorTreeExecutor() { stop(); }

void BehaviorTreeExecutor::start() {
    if (pImpl_->running) return;
    pImpl_->running = true;
    pImpl_->worker = std::thread([this]() {
        while (pImpl_->running) {
#ifdef GAO_ENABLE_BEHAVIOR_TREE
            auto status = pImpl_->tree->tickWhileRunning(std::chrono::milliseconds(10));
            if (status == BT::NodeStatus::FAILURE) {
                pImpl_->last_failure = "Behavior tree returned FAILURE";
                if (pImpl_->island) pImpl_->island->engage();
            }
#endif
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
}

void BehaviorTreeExecutor::stop() {
    pImpl_->running = false;
    if (pImpl_->worker.joinable()) pImpl_->worker.join();
}

bool BehaviorTreeExecutor::check(const dynamics::State& state) {
#ifdef GAO_ENABLE_BEHAVIOR_TREE
    auto& blackboard = pImpl_->tree->rootBlackboard();
    blackboard.set("state_vel_norm", state.vel.norm());
    auto status = pImpl_->tree->tickOnce();
    return status == BT::NodeStatus::SUCCESS;
#else
    return true;   // stub: always safe
#endif
}

void BehaviorTreeExecutor::setSafetyIslandIntegration(SafetyIsland* island) {
    pImpl_->island = island;
}

std::string BehaviorTreeExecutor::getLastFailureReason() const {
    return pImpl_->last_failure;
}

} // namespace gao::safety
