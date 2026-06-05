// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include <string>
#include <memory>

namespace gao::cross_domain {

class DomainDiscovery {
public:
    static DomainDiscovery& instance();
    bool init();
    void broadcastPresence(const std::string& space, const std::string& morph_id);
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl_;
};

} // namespace gao::cross_domain
