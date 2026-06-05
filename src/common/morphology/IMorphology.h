// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "dynamics/IDynamics.h"
#include "control/IController.h"
#include "perception/IPerception.h"
#include "planning/IPlanner.h"
#include "safety/ISafetyMonitor.h"

namespace gao::morphology {

class IMorphology {
public:
    virtual ~IMorphology() = default;
    virtual std::string getId() const = 0;
    virtual std::string getSpace() const = 0;
    virtual std::unique_ptr<dynamics::IDynamics> createDynamics() = 0;
    virtual std::unique_ptr<control::IController> createController() = 0;
    virtual std::unique_ptr<perception::IPerception> createPerception() { return nullptr; }
    virtual std::unique_ptr<planning::IPlanner> createPlanner() { return nullptr; }
    virtual std::unique_ptr<safety::ISafetyMonitor> createSafetyMonitor() { return nullptr; }
};

class MorphologyRegistry {
public:
    static MorphologyRegistry& instance();
    void registerMorphology(std::shared_ptr<IMorphology> factory);
    std::shared_ptr<IMorphology> getMorphology(const std::string& id) const;
    std::vector<std::string> listMorphologiesForSpace(const std::string& space) const;
    std::vector<std::string> listAllMorphologies() const;
private:
    MorphologyRegistry() = default;
    std::map<std::string, std::shared_ptr<IMorphology>> registry_;
};

} // namespace gao::morphology
