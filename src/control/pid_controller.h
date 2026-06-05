// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once

namespace gao::control {

class PIDController {
public:
    PIDController(double kp, double ki, double kd, double dt, double output_limit);
    double compute(double setpoint, double measurement);
    void reset();
private:
    double kp_, ki_, kd_, dt_, output_limit_;
    double integral_, prev_error_;
};

} // namespace gao::control
