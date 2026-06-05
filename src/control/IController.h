// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include "dynamics/state.h"

namespace gao::control {

class IController {
public:
    virtual ~IController() = default;
    virtual dynamics::ControlInput compute(const dynamics::State& state, const dynamics::Reference& ref) = 0;
};

} // namespace gao::control
