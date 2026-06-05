// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include "safety/behavior_tree_executor.h"
#include "dynamics/state.h"
int main() {
    gao::safety::BehaviorTreeExecutor bt("config/safety_bt.xml");
    bt.start();
    gao::dynamics::State state;
    bool safe = bt.check(state);
    assert(safe == true);
    bt.stop();
    return 0;
}
