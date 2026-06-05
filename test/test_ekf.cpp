// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include <cmath>
#include "common/filters/ekf.h"
#include <Eigen/Dense>
using namespace gao::filters;
int main() {
    EKF ekf(1, 1);
    Eigen::MatrixXd F(1,1); F << 1.0;
    Eigen::MatrixXd H(1,1); H << 1.0;
    ekf.setTransitionJacobian(F);
    ekf.setMeasurementJacobian(H);
    ekf.predict();
    Eigen::VectorXd z(1); z << 2.0;
    ekf.update(z);
    double state = ekf.getState()(0);
    assert(std::fabs(state - 2.0) < 1e-6);
    return 0;
}
