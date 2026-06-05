// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include <cmath>
#include "control/pid_controller.h"
using namespace gao::control;
int main() {
    PIDController pid(1.0, 0.1, 0.05, 0.01, 100.0);
    double out = pid.compute(10.0, 5.0);
    assert(std::fabs(out - 5.0) < 1e-6);
    return 0;
}
