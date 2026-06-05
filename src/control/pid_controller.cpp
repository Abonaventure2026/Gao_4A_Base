// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "pid_controller.h"
#include <algorithm>
#include <cmath>

namespace gao::control {

PIDController::PIDController(double kp, double ki, double kd, double dt, double output_limit)
    : kp_(kp), ki_(ki), kd_(kd), dt_(dt), output_limit_(output_limit),
      integral_(0.0), prev_error_(0.0) {}
double PIDController::compute(double setpoint, double measurement) {
    double error = setpoint - measurement;
    integral_ += error * dt_;
    integral_ = std::clamp(integral_, -output_limit_ / ki_, output_limit_ / ki_);
    double derivative = (error - prev_error_) / dt_;
    double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    prev_error_ = error;
    return std::clamp(output, -output_limit_, output_limit_);
}
void PIDController::reset() {
    integral_ = 0.0;
    prev_error_ = 0.0;
}

} // namespace gao::control
