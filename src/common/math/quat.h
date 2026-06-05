// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include "vec3.h"

namespace gao::math {

struct Quat {
    double w, x, y, z;
    Quat(double w = 1, double x = 0, double y = 0, double z = 0);
    Quat operator*(const Quat& other) const;
    Quat conjugate() const;
    double norm() const;
    Quat normalized() const;
    Vec3 rotate(const Vec3& v) const;
    double yaw() const;   // 返回欧拉角偏航角（弧度），范围 [-π, π]
};

Quat fromAxisAngle(const Vec3& axis, double angle);

} // namespace gao::math
