// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "ekf.h"
#include <cmath>
#include <stdexcept>

namespace gao::filters {

EKF::EKF(int state_dim, int meas_dim)
    : dim_x(state_dim), dim_z(meas_dim),
      x(Eigen::VectorXd::Zero(state_dim)),
      P(Eigen::MatrixXd::Identity(state_dim, state_dim)),
      Q(Eigen::MatrixXd::Identity(state_dim, state_dim)),
      R(Eigen::MatrixXd::Identity(meas_dim, meas_dim)),
      F(Eigen::MatrixXd::Identity(state_dim, state_dim)),
      H(Eigen::MatrixXd::Zero(meas_dim, state_dim)) {}

void EKF::predict() {
    if (f_) {
        x = f_(x);
    } else {
        x = F * x;
    }
    P = F * P * F.transpose() + Q;
}
void EKF::update(const Eigen::VectorXd& z) {
    if (z.size() != dim_z) throw std::runtime_error("Measurement dim mismatch");
    Eigen::VectorXd y;
    if (h_) {
        y = z - h_(x);
    } else {
        y = z - H * x;
    }
    Eigen::MatrixXd S = H * P * H.transpose() + R;
    Eigen::MatrixXd K = P * H.transpose() * S.inverse();
    x = x + K * y;
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(dim_x, dim_x);
    P = (I - K * H) * P;
}
void EKF::setTransitionJacobian(const Eigen::MatrixXd& F_new) { F = F_new; }
void EKF::setMeasurementJacobian(const Eigen::MatrixXd& H_new) { H = H_new; }
void EKF::setProcessNoise(const Eigen::MatrixXd& Q_new) { Q = Q_new; }
void EKF::setMeasurementNoise(const Eigen::MatrixXd& R_new) { R = R_new; }
void EKF::setStateTransitionFunc(std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f) { f_ = f; }
void EKF::setMeasurementFunc(std::function<Eigen::VectorXd(const Eigen::VectorXd&)> h) { h_ = h; }

} // namespace gao::filters
