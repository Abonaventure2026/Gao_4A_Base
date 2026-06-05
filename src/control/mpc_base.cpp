// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "mpc_base.h"
#include <Eigen/QR>
#include <stdexcept>

namespace gao::control {

MPCBase::MPCBase(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B,
                 int horizon, double dt)
    : A_(A), B_(B), N_(horizon), dt_(dt) {
    buildPredictionMatrices();
}
void MPCBase::buildPredictionMatrices() {
    int nx = A_.rows(), nu = B_.cols();
    int n_total = N_ * nx;
    int m_total = N_ * nu;
    F_bar_.resize(n_total, nx);
    Phi_bar_.resize(n_total, m_total);
    Eigen::MatrixXd A_pow = Eigen::MatrixXd::Identity(nx, nx);
    for (int i = 0; i < N_; ++i) {
        A_pow = A_pow * A_;
        F_bar_.block(i*nx, 0, nx, nx) = A_pow;
        for (int j = 0; j < N_; ++j) {
            if (j <= i) {
                Eigen::MatrixXd A_pow_ij = Eigen::MatrixXd::Identity(nx, nx);
                for (int k = 0; k < i-j; ++k) A_pow_ij = A_pow_ij * A_;
                Phi_bar_.block(i*nx, j*nu, nx, nu) = A_pow_ij * B_;
            }
        }
    }
    Q_bar_ = Eigen::MatrixXd::Identity(n_total, n_total);
    R_bar_ = Eigen::MatrixXd::Identity(m_total, m_total);
}
Eigen::VectorXd MPCBase::compute(const Eigen::VectorXd& x0, const Eigen::VectorXd& ref) {
    int nx = A_.rows(), nu = B_.cols();
    int n_total = N_ * nx;
    Eigen::VectorXd ref_bar = Eigen::VectorXd::Zero(n_total);
    for (int i=0; i<N_; ++i) ref_bar.segment(i*nx, nx) = ref;
    Eigen::MatrixXd H = Phi_bar_.transpose() * Q_bar_ * Phi_bar_ + R_bar_;
    Eigen::VectorXd g = Phi_bar_.transpose() * Q_bar_ * (F_bar_ * x0 - ref_bar);
    Eigen::VectorXd u_opt = H.ldlt().solve(-g);
    return u_opt.head(nu);
}

} // namespace gao::control
