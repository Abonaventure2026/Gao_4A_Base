// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "lowpass.h"
namespace gao::filters {
LowPass::LowPass(double alpha) : alpha_(alpha), y_prev_(0.0) {}
double LowPass::filter(double input) {
    y_prev_ = alpha_ * input + (1-alpha_)*y_prev_;
    return y_prev_;
}
void LowPass::reset() { y_prev_ = 0.0; }
} // namespace gao::filters
