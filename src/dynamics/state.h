// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include "common/math/vec3.h"
#include "common/math/quat.h"
#include <cstdint>

namespace gao::dynamics {

struct State {
    math::Vec3 pos;
    math::Vec3 vel;
    math::Quat orientation;
    math::Vec3 angular_vel;
    uint64_t timestamp_us;
};

struct ControlInput {
    math::Vec3 force;
    math::Vec3 torque;
    double throttle[8] = {0.0};
};

struct Reference {
    math::Vec3 pos_ref;
    math::Vec3 vel_ref;
    math::Quat att_ref;
    double time_horizon;
};

} // namespace gao::dynamics
