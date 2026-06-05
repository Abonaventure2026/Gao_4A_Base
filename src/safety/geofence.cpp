// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "geofence.h"
namespace gao::safety {
void Geofence::setPolygon(const std::vector<math::Vec3>& vertices) { vertices_ = vertices; }
bool Geofence::checkInside(const math::Vec3& point) const {
    if (vertices_.size() < 3) return false;
    bool inside = false;
    for (size_t i = 0, j = vertices_.size()-1; i < vertices_.size(); j = i++) {
        if (((vertices_[i].y > point.y) != (vertices_[j].y > point.y)) &&
            (point.x < (vertices_[j].x - vertices_[i].x) * (point.y - vertices_[i].y) /
             (vertices_[j].y - vertices_[i].y) + vertices_[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}
} // namespace gao::safety
