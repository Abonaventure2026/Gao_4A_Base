// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include "state.h"

namespace gao::dynamics {

class IDynamics {
public:
    virtual ~IDynamics() = default;
    virtual State update(const ControlInput& input, double dt) = 0;
    virtual void reset(const State& initial) = 0;
};

} // namespace gao::dynamics
