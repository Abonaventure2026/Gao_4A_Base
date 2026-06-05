// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "scene_manager.h"
#include <iostream>
#ifdef GAO_CONFIG_NO_YAML
#warning "yaml-cpp not found, using default scene config"
#else
#include <yaml-cpp/yaml.h>
#endif

namespace gao::scenario {
bool SceneManager::load(const std::string& scene_id) {
#ifdef GAO_CONFIG_NO_YAML
    std::cout << "Using default scene config for " << scene_id << std::endl;
    return true;
#else
    std::string path = "config/atomic_scenes/" + scene_id + ".yaml";
    try {
        YAML::Node cfg = YAML::LoadFile(path);
        weights_.rule = cfg["fusion_weights"]["rule"].as<float>();
        weights_.va = cfg["fusion_weights"]["va"].as<float>();
        weights_.vla = cfg["fusion_weights"]["vla"].as<float>();
        weights_.world_model = cfg["fusion_weights"]["world_model"].as<float>();
        safety_.min_ttc = cfg["safety"]["min_ttc"].as<float>();
        safety_.redundancy_level = cfg["safety"]["redundancy_level"].as<int>();
        std::string grade_str = cfg["safety"]["grade"].as<std::string>();
        if (grade_str == "G1") safety_.grade = 1;
        else if (grade_str == "G2") safety_.grade = 2;
        else if (grade_str == "G3") safety_.grade = 3;
        else if (grade_str == "G4") safety_.grade = 4;
        else safety_.grade = 1;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load scene: " << scene_id << " - " << e.what() << std::endl;
        return false;
    }
#endif
}
SceneWeights SceneManager::getWeights() const { return weights_; }
SafetyParams SceneManager::getSafetyParams() const { return safety_; }
} // namespace gao::scenario
