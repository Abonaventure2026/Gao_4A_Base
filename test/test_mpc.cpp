// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include <cmath>
#include "control/mpc_base.h"
#include <Eigen/Dense>
using namespace gao::control;
int main() {
    Eigen::MatrixXd A(1,1); A << 1.0;
    Eigen::MatrixXd B(1,1); B << 0.1;
    MPCBase mpc(A, B, 5, 0.1);
    Eigen::VectorXd x0(1); x0 << 0.0;
    Eigen::VectorXd ref(1); ref << 1.0;
    Eigen::VectorXd u = mpc.compute(x0, ref);
    assert(u.size() == 1 && std::isfinite(u(0)));
    return 0;
}
