#ifndef HPP_CRC_DETAIL_TYPES
#define HPP_CRC_DETAIL_TYPES

#include <climits>
#include <cstddef> // size_t

#include "crc/detail/defines.hpp"
#if CRC_STDCXX_VERSION_CHECK(201103)
#include <cstdint>
#endif

namespace crc {
using std::size_t;

#if CRC_STDCXX_VERSION_CHECK(201103)
typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;
#elif defined(__GNUC__)
typedef unsigned int u8 __attribute__((mode(QI)));
typedef unsigned int u16 __attribute__((mode(HI)));
typedef unsigned int u32 __attribute__((mode(SI)));
typedef unsigned int u64 __attribute__((mode(DI)));
#elif CRC_MSVC_VERSION_CHECK(1300)
typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
#else
#if UCHAR_MAX == 0xFFU
typedef unsigned char u8;
#else
#error cannot find 8-bit integer type
#endif
#if USHRT_MAX == 0xFFFFU
typedef unsigned short u16;
#elif UINT_MAX == 0xFFFFU
typedef unsigned int u16;
#else
#error cannot find 16-bit integer type
#endif
#if USHRT_MAX == 0xFFFFFFFFUL
typedef unsigned short u32;
#elif UINT_MAX == 0xFFFFFFFFUL
typedef unsigned int u32;
#elif ULONG_MAX == 0xFFFFFFFFUL
typedef unsigned long u32;
#else
#error cannot find 32-bit integer type
#endif
#if defined(_WIN32) || defined(_WIN64)
typedef unsigned __int64 u64;
#elif defined(__UINT64_TYPE__)
typedef __UINT64_TYPE__ u64;
#elif defined(_LONG_LONG)
typedef unsigned long long u64;
#else
#error cannot find 64-bit integer type
#endif
#endif // CRC_STDCXX_VERSION_CHECK(201103)

#define CRC_UINT64_C(w1, w2) (static_cast<u64>(CRC_CONCAT(w1, UL)) << 32 | CRC_CONCAT(w2, UL))

#if CRC_HAS_GNUC_INT128
#define CRC_HAS_128BIT_ALGO 1
typedef __uint128_t u128;
#define CRC_UINT128_C(w1, w2, w3, w4) \
    (static_cast<u128>(CRC_CONCAT(w1, UL)) << 96 | static_cast<u128>(CRC_CONCAT(w2, UL)) << 64 \
     | static_cast<u128>(CRC_CONCAT(w3, UL)) << 32 | CRC_CONCAT(w4, UL))
#else
#define CRC_HAS_128BIT_ALGO 0
#endif

} // namespace crc

#endif // HPP_CRC_DETAIL_TYPES
