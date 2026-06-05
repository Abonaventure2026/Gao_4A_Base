// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include <cmath>
#include "common/math/vec3.h"
#include "common/math/quat.h"
#include "common/math/matrix3.h"

using namespace gao::math;

int main() {
    Vec3 a(1,2,3), b(4,5,6);
    assert((a+b).x == 5 && (a+b).y == 7 && (a+b).z == 9);
    assert((a-b).x == -3 && (a-b).y == -3 && (a-b).z == -3);
    assert(std::fabs(a.dot(b) - 32.0) < 1e-9);
    Vec3 c = a.cross(b);
    assert(std::fabs(c.x - (-3)) < 1e-9 && std::fabs(c.y - 6) < 1e-9 && std::fabs(c.z - (-3)) < 1e-9);
    assert(std::fabs(a.norm() - std::sqrt(14.0)) < 1e-9);
    Quat q = fromAxisAngle(Vec3(0,0,1), M_PI/2);
    Vec3 v(1,0,0);
    Vec3 rot = q.rotate(v);
    assert(std::fabs(rot.x - 0) < 1e-6 && std::fabs(rot.y - 1) < 1e-6);
    Matrix3 I = Matrix3::identity();
    Vec3 v2(2,3,4);
    assert((I * v2).x == 2 && (I * v2).y == 3 && (I * v2).z == 4);
    Matrix3 R = Matrix3::rotationZ(M_PI/2);
    Vec3 v3(1,0,0);
    Vec3 rotated = R * v3;
    assert(std::fabs(rotated.x) < 1e-9 && std::fabs(rotated.y - 1) < 1e-9);
    // test yaw
    Quat q2 = fromAxisAngle(Vec3(0,0,1), 0.5);
    assert(std::fabs(q2.yaw() - 0.5) < 1e-6);
    return 0;
}
