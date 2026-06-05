// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <Eigen/Dense>

namespace gao::control {

class LQRController {
public:
    LQRController(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B,
                  const Eigen::MatrixXd& Q, const Eigen::MatrixXd& R,
                  double eps = 1e-6);
    Eigen::VectorXd compute(const Eigen::VectorXd& x);
private:
    Eigen::MatrixXd K_;
};

} // namespace gao::control
