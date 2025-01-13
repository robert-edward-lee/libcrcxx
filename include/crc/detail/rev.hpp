#ifndef HPP_CRC_DETAIL_REV
#define HPP_CRC_DETAIL_REV

#include "crc/detail/defines.hpp"
#include "crc/detail/types.hpp"

namespace crc { namespace detail {
static CRC_CONSTEXPR_14 u8 rev(u8 x) CRC_NOEXCEPT {
#if CRC_HAS_BUILTIN_BITREVERSE
    return __builtin_bitreverse8(x);
#else
    x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
    x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2);
    return x << 4 | x >> 4;
#endif
}
static CRC_CONSTEXPR_14 u16 rev(u16 x) CRC_NOEXCEPT {
#if CRC_HAS_BUILTIN_BITREVERSE
    return __builtin_bitreverse16(x);
#else
    x = ((x & 0x5555) << 1) | ((x & 0xAAAA) >> 1);
    x = ((x & 0x3333) << 2) | ((x & 0xCCCC) >> 2);
    x = ((x & 0x0F0F) << 4) | ((x & 0xF0F0) >> 4);
    return x << 8 | x >> 8;
#endif
}
static CRC_CONSTEXPR_14 u32 rev(u32 x) CRC_NOEXCEPT {
#if CRC_HAS_BUILTIN_BITREVERSE
    return __builtin_bitreverse32(x);
#else
    x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
    x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
    x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
    x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
    return x << 16 | x >> 16;
#endif
}
static CRC_CONSTEXPR_14 u64 rev(u64 x) CRC_NOEXCEPT {
#if CRC_HAS_BUILTIN_BITREVERSE
    return __builtin_bitreverse64(x);
#else
    x = ((x & (CRC_UINT64_C(0x55555555, 0x55555555))) << 1) | ((x & (CRC_UINT64_C(0xAAAAAAAA, 0xAAAAAAAA))) >> 1);
    x = ((x & (CRC_UINT64_C(0x33333333, 0x33333333))) << 2) | ((x & (CRC_UINT64_C(0xCCCCCCCC, 0xCCCCCCCC))) >> 2);
    x = ((x & (CRC_UINT64_C(0x0F0F0F0F, 0x0F0F0F0F))) << 4) | ((x & (CRC_UINT64_C(0xF0F0F0F0, 0xF0F0F0F0))) >> 4);
    x = ((x & (CRC_UINT64_C(0x00FF00FF, 0x00FF00FF))) << 8) | ((x & (CRC_UINT64_C(0xFF00FF00, 0xFF00FF00))) >> 8);
    x = ((x & (CRC_UINT64_C(0x0000FFFF, 0x0000FFFF))) << 16) | ((x & (CRC_UINT64_C(0xFFFF0000, 0xFFFF0000))) >> 16);
    return x << 32 | x >> 32;
#endif
}

#if CRC_HAS_128BIT_ALGO
static CRC_CONSTEXPR_14 u128 rev(u128 x) CRC_NOEXCEPT {
    return static_cast<u128>(rev(static_cast<u64>(x))) << 64 | rev(static_cast<u64>(x >> 64));
}
#endif

}} // namespace crc::detail

#endif // HPP_CRC_DETAIL_REV
