// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include "vec3.h"

namespace gao::math {

class Matrix3 {
public:
    Matrix3();
    Matrix3(double m00, double m01, double m02,
            double m10, double m11, double m12,
            double m20, double m21, double m22);
    Matrix3 operator*(const Matrix3& other) const;
    Vec3 operator*(const Vec3& v) const;
    Matrix3 transpose() const;
    double determinant() const;
    Matrix3 inverse() const;
    static Matrix3 identity();
    static Matrix3 rotationX(double angle);
    static Matrix3 rotationY(double angle);
    static Matrix3 rotationZ(double angle);
private:
    double data[9];
};

} // namespace gao::math
