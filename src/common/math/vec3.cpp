// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "vec3.h"
#include <cmath>
#include <stdexcept>

namespace gao::math {

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}
Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}
Vec3 Vec3::operator*(double scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}
Vec3 Vec3::operator/(double scalar) const {
    if (std::fabs(scalar) < 1e-12) throw std::runtime_error("Divide by zero");
    return Vec3(x / scalar, y / scalar, z / scalar);
}
double Vec3::dot(const Vec3& other) const {
    return x*other.x + y*other.y + z*other.z;
}
Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(y*other.z - z*other.y,
                z*other.x - x*other.z,
                x*other.y - y*other.x);
}
double Vec3::norm() const {
    return std::sqrt(x*x + y*y + z*z);
}
Vec3 Vec3::normalized() const {
    double n = norm();
    if (n < 1e-12) return Vec3(0,0,0);
    return *this / n;
}
void Vec3::normalize() {
    *this = normalized();
}
std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}

} // namespace gao::math
