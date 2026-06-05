// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "lqr_controller.h"
#include <cmath>
#include <stdexcept>

namespace gao::control {

LQRController::LQRController(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B,
                             const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R,
                             double eps) {
    int n = A.rows(), m = B.cols();
    Eigen::MatrixXd P = Q;
    Eigen::MatrixXd P_next;
    double diff;
    do {
        P_next = A.transpose() * P * A - A.transpose() * P * B *
                 (R + B.transpose() * P * B).inverse() * B.transpose() * P * A + Q;
        diff = (P_next - P).norm();
        P = P_next;
    } while (diff > eps);
    K_ = (R + B.transpose() * P * B).inverse() * B.transpose() * P * A;
}
Eigen::VectorXd LQRController::compute(const Eigen::VectorXd& x) {
    return -K_ * x;
}

} // namespace gao::control
