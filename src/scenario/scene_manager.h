// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-02

#pragma once
#include <string>

namespace gao::scenario {

struct SceneWeights {
    float rule = 0.0f;
    float va = 0.0f;
    float vla = 0.0f;
    float world_model = 0.0f;
};

struct SafetyParams {
    float min_ttc = 0.0f;
    int redundancy_level = 0;
    int grade = 1; // 1-4
};

class SceneManager {
public:
    bool load(const std::string& scene_id);
    SceneWeights getWeights() const;
    SafetyParams getSafetyParams() const;
private:
    SceneWeights weights_;
    SafetyParams safety_;
};

} // namespace gao::scenario
