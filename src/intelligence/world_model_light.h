// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../common/math/vec3.h"

namespace gao::intelligence {

struct WorldModelOutput {
    std::vector<math::Vec3> predicted_pos;
    float risk_score;
    float collision_prob;
};

class WorldModelLight {
public:
    WorldModelLight();
    ~WorldModelLight();
    bool init(const std::string& onnx_path);
    WorldModelOutput imagine(const math::Vec3& pos, const math::Vec3& vel, const math::Vec3& cmd);
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

} // namespace gao::intelligence
