// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#pragma once

namespace gao::filters {

class LowPass {
public:
    explicit LowPass(double alpha);
    double filter(double input);
    void reset();
private:
    double alpha_;
    double y_prev_;
};

} // namespace gao::filters
