// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-02

#pragma once
#include <vector>
#include "../common/math/vec3.h"

namespace gao::safety {

class Geofence {
public:
    void setPolygon(const std::vector<math::Vec3>& vertices);
    bool checkInside(const math::Vec3& point) const;
private:
    std::vector<math::Vec3> vertices_;
};

} // namespace gao::safety
