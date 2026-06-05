// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include <cassert>
#include "safety/geofence.h"
#include "common/math/vec3.h"
using namespace gao::safety;
int main() {
    Geofence fence;
    fence.setPolygon({{0,0,0},{10,0,0},{10,10,0},{0,10,0}});
    assert(fence.checkInside(gao::math::Vec3(5,5,0)) == true);
    return 0;
}
