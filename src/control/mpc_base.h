// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <Eigen/Dense>

namespace gao::control {

class MPCBase {
public:
    MPCBase(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B, int horizon, double dt);
    Eigen::VectorXd compute(const Eigen::VectorXd& x0, const Eigen::VectorXd& ref);
private:
    void buildPredictionMatrices();
    Eigen::MatrixXd A_, B_;
    int N_;
    double dt_;
    Eigen::MatrixXd F_bar_, Phi_bar_, Q_bar_, R_bar_;
};

} // namespace gao::control
