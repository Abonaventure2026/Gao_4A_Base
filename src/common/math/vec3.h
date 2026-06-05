// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <iostream>

namespace gao::math {

struct Vec3 {
    double x, y, z;
    Vec3(double x = 0, double y = 0, double z = 0);
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar) const;
    Vec3 operator/(double scalar) const;
    double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    double norm() const;
    Vec3 normalized() const;
    void normalize();
};

std::ostream& operator<<(std::ostream& os, const Vec3& v);

} // namespace gao::math
