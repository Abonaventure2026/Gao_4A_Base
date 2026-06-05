// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include "intelligence/world_model_light.h"
#include "common/math/vec3.h"
using namespace gao::intelligence;
int main() {
    WorldModelLight wm;
    assert(wm.init("dummy.onnx") == true);
    gao::math::Vec3 pos(0,0,0), vel(1,0,0), cmd(0,0,0);
    WorldModelOutput out = wm.imagine(pos, vel, cmd);
    assert(out.predicted_pos.size() == 10);
    return 0;
}
