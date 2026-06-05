// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <Eigen/Dense>
#include <functional>

namespace gao::filters {

class EKF {
public:
    EKF(int state_dim, int meas_dim);
    void predict();
    void update(const Eigen::VectorXd& z);
    void setTransitionJacobian(const Eigen::MatrixXd& F);
    void setMeasurementJacobian(const Eigen::MatrixXd& H);
    void setProcessNoise(const Eigen::MatrixXd& Q);
    void setMeasurementNoise(const Eigen::MatrixXd& R);
    void setStateTransitionFunc(std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f);
    void setMeasurementFunc(std::function<Eigen::VectorXd(const Eigen::VectorXd&)> h);
    Eigen::VectorXd getState() const { return x; }
    Eigen::MatrixXd getCovariance() const { return P; }
private:
    int dim_x, dim_z;
    Eigen::VectorXd x;
    Eigen::MatrixXd P, Q, R, F, H;
    std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f_;
    std::function<Eigen::VectorXd(const Eigen::VectorXd&)> h_;
};

} // namespace gao::filters
