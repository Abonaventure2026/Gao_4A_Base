// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "common/morphology/IMorphology.h"
#include <algorithm>

namespace gao::morphology {

MorphologyRegistry& MorphologyRegistry::instance() {
    static MorphologyRegistry inst;
    return inst;
}

void MorphologyRegistry::registerMorphology(std::shared_ptr<IMorphology> factory) {
    registry_[factory->getId()] = factory;
}

std::shared_ptr<IMorphology> MorphologyRegistry::getMorphology(const std::string& id) const {
    auto it = registry_.find(id);
    return (it != registry_.end()) ? it->second : nullptr;
}

std::vector<std::string> MorphologyRegistry::listMorphologiesForSpace(const std::string& space) const {
    std::vector<std::string> out;
    for (const auto& [id, factory] : registry_) {
        if (factory->getSpace() == space) out.push_back(id);
    }
    return out;
}

std::vector<std::string> MorphologyRegistry::listAllMorphologies() const {
    std::vector<std::string> out;
    for (const auto& [id, _] : registry_) out.push_back(id);
    return out;
}

} // namespace gao::morphology
