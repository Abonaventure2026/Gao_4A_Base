// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "quat.h"
#include <cmath>
#include <stdexcept>

namespace gao::math {

Quat::Quat(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}

Quat Quat::operator*(const Quat& other) const {
    return Quat(
        w*other.w - x*other.x - y*other.y - z*other.z,
        w*other.x + x*other.w + y*other.z - z*other.y,
        w*other.y - x*other.z + y*other.w + z*other.x,
        w*other.z + x*other.y - y*other.x + z*other.w
    );
}
Quat Quat::conjugate() const {
    return Quat(w, -x, -y, -z);
}
double Quat::norm() const {
    return std::sqrt(w*w + x*x + y*y + z*z);
}
Quat Quat::normalized() const {
    double n = norm();
    if (n < 1e-12) return Quat(1,0,0,0);
    return Quat(w/n, x/n, y/n, z/n);
}
Vec3 Quat::rotate(const Vec3& v) const {
    Quat p(0, v.x, v.y, v.z);
    Quat q = *this;
    Quat rotated = q * p * q.conjugate();
    return Vec3(rotated.x, rotated.y, rotated.z);
}
double Quat::yaw() const {
    // 四元数转欧拉角（ZYX顺序）
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    return std::atan2(siny_cosp, cosy_cosp);
}
Quat fromAxisAngle(const Vec3& axis, double angle) {
    double half = angle * 0.5;
    double s = std::sin(half);
    Vec3 a = axis.normalized();
    return Quat(std::cos(half), a.x * s, a.y * s, a.z * s);
}

} // namespace gao::math
