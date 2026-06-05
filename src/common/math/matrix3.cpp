// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "matrix3.h"
#include <cmath>
#include <stdexcept>

namespace gao::math {

Matrix3::Matrix3() : data{1,0,0, 0,1,0, 0,0,1} {}
Matrix3::Matrix3(double m00, double m01, double m02,
                 double m10, double m11, double m12,
                 double m20, double m21, double m22)
    : data{m00,m01,m02, m10,m11,m12, m20,m21,m22} {}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
    Matrix3 res;
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            res.data[i*3+j] = 0;
            for (int k=0; k<3; ++k)
                res.data[i*3+j] += data[i*3+k] * other.data[k*3+j];
        }
    }
    return res;
}
Vec3 Matrix3::operator*(const Vec3& v) const {
    return Vec3(
        data[0]*v.x + data[1]*v.y + data[2]*v.z,
        data[3]*v.x + data[4]*v.y + data[5]*v.z,
        data[6]*v.x + data[7]*v.y + data[8]*v.z
    );
}
Matrix3 Matrix3::transpose() const {
    return Matrix3(data[0], data[3], data[6],
                   data[1], data[4], data[7],
                   data[2], data[5], data[8]);
}
double Matrix3::determinant() const {
    return data[0]*(data[4]*data[8]-data[5]*data[7])
         - data[1]*(data[3]*data[8]-data[5]*data[6])
         + data[2]*(data[3]*data[7]-data[4]*data[6]);
}
Matrix3 Matrix3::inverse() const {
    double det = determinant();
    if (std::fabs(det) < 1e-12) throw std::runtime_error("Singular matrix");
    double invdet = 1.0 / det;
    Matrix3 adj;
    adj.data[0] = (data[4]*data[8] - data[5]*data[7]);
    adj.data[1] = (data[2]*data[7] - data[1]*data[8]);
    adj.data[2] = (data[1]*data[5] - data[2]*data[4]);
    adj.data[3] = (data[5]*data[6] - data[3]*data[8]);
    adj.data[4] = (data[0]*data[8] - data[2]*data[6]);
    adj.data[5] = (data[2]*data[3] - data[0]*data[5]);
    adj.data[6] = (data[3]*data[7] - data[4]*data[6]);
    adj.data[7] = (data[1]*data[6] - data[0]*data[7]);
    adj.data[8] = (data[0]*data[4] - data[1]*data[3]);
    for (int i=0; i<9; ++i) adj.data[i] *= invdet;
    return adj;
}
Matrix3 Matrix3::identity() {
    return Matrix3();
}
Matrix3 Matrix3::rotationX(double angle) {
    double c = std::cos(angle), s = std::sin(angle);
    return Matrix3(1,0,0, 0,c,-s, 0,s,c);
}
Matrix3 Matrix3::rotationY(double angle) {
    double c = std::cos(angle), s = std::sin(angle);
    return Matrix3(c,0,s, 0,1,0, -s,0,c);
}
Matrix3 Matrix3::rotationZ(double angle) {
    double c = std::cos(angle), s = std::sin(angle);
    return Matrix3(c,-s,0, s,c,0, 0,0,1);
}

} // namespace gao::math
