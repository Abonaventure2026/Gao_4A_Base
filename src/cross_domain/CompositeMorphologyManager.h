// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace gao::cross_domain {

class CompositeMorphologyManager {
public:
    static CompositeMorphologyManager& instance();
    bool loadDefinitions(const std::string& yaml_path);
    bool executeComposite(const std::string& composite_id,
                          const std::vector<double>& params,
                          std::function<void(const std::string&)> step_callback = nullptr);
    void enableDigitalTwinSync(bool enable);
    void registerActionHandler(const std::string& action_name,
                               std::function<bool(const std::string&, const std::vector<double>&)> handler);
private:
    CompositeMorphologyManager() = default;
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

} // namespace gao::cross_domain
