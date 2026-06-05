// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include "scenario/scene_manager.h"
using namespace gao::scenario;
int main() {
    SceneManager sm;
    bool loaded = sm.load("S111");
    assert(loaded);
    auto w = sm.getWeights();
    assert(std::fabs(w.rule - 0.95) < 1e-6);
    return 0;
}
