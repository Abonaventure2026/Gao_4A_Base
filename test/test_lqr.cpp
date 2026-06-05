// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include <cmath>
#include "control/lqr_controller.h"
#include <Eigen/Dense>
using namespace gao::control;
int main() {
    Eigen::MatrixXd A(2,2); A << 1.0, 0.1, 0.0, 1.0;
    Eigen::MatrixXd B(2,1); B << 0.0, 0.1;
    Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(2,2);
    Eigen::MatrixXd R(1,1); R << 1.0;
    LQRController lqr(A, B, Q, R);
    Eigen::VectorXd x(2); x << 1.0, 0.0;
    Eigen::VectorXd u = lqr.compute(x);
    assert(u.size() == 1 && std::isfinite(u(0)));
    return 0;
}
