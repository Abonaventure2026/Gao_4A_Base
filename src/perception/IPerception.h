// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once
#include "common/math/vec3.h"
namespace gao::perception {
class IPerception {
public:
    virtual ~IPerception() = default;
};
struct SensorData {};
} // namespace
