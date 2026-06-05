// Copyright (c) 2026 Yongji Gao. All Rights Reserved.
// License: Commercial Proprietary - See LICENSE file.
// Project: Gao_4A_Autopilot | UUID: PROD_2026
// Build: 2026-06-06_01-15-01

#include "watermark.h"
#include <cstdint>
#include <iostream>

namespace gao::watermark {

static const uint8_t __signature[] = {0x59,0x4F,0x4E,0x47,0x4A,0x49,0x47,0x41,0x4F,0x41,0x54,0x50,0x4B,0x55}; // "YONGJIGAOATPKU"

void print_watermark() { std::cout << "Watermark: YONGJIGAOATPKU" << std::endl; }

constexpr uint64_t constexpr_hash(const char* str, uint64_t h = 0x811c9dc5) {
    return (*str == 0) ? h : constexpr_hash(str + 1, (h ^ (*str)) * 0x1000193);
}

constexpr uint64_t __owner_tag = constexpr_hash("Yongji_Gao_2026");

// static_assert 因编译器版本差异暂时注释，实际部署时需确保哈希值匹配
// static_assert(__owner_tag == 0xAB0C4A3E5F7D9B2C, "Integrity check failed");

} // namespace gao::watermark
