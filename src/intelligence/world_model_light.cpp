// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "world_model_light.h"
#include <iostream>
#include <cmath>

namespace gao::intelligence {
struct WorldModelLight::Impl {
    std::vector<float> latent;
    Impl() : latent(32, 0.0f) {}
};
WorldModelLight::WorldModelLight() : pImpl_(std::make_unique<Impl>()) {}
WorldModelLight::~WorldModelLight() = default;
bool WorldModelLight::init(const std::string& onnx_path) {
    std::cout << "[WorldModelLight] ONNX support disabled, using stub." << std::endl;
    return true;
}
WorldModelOutput WorldModelLight::imagine(const math::Vec3& pos, const math::Vec3& vel, const math::Vec3& cmd) {
    WorldModelOutput out;
    out.predicted_pos.resize(10);
    for (int i=0; i<10; ++i) {
        out.predicted_pos[i] = pos + vel * (i * 0.1);
    }
    out.risk_score = 0.0f;
    out.collision_prob = 0.0f;
    return out;
}
} // namespace gao::intelligence
