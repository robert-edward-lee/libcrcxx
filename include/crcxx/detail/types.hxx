#ifndef HXX_CRCXX_DETAIL_TYPES
#define HXX_CRCXX_DETAIL_TYPES

#include <cstddef> /* size_t */

#include "crcxx/detail/defines.hxx"
#if CRCXX_STDCXX_VERSION_CHECK(201103)
#include <cstdint>
#endif

namespace crc {
using std::size_t;

#if CRCXX_STDCXX_VERSION_CHECK(201103)
typedef std::uint8_t u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;
#else // CRCXX_STDCXX_VERSION_CHECK(201103)
#if defined(__GNUC__)
typedef unsigned int u8 __attribute__((mode(QI)));
typedef unsigned int u16 __attribute__((mode(HI)));
typedef unsigned int u32 __attribute__((mode(SI)));
typedef unsigned int u64 __attribute__((mode(DI)));
#elif defined(_MSC_VER)
typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
#else
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#if defined(_WIN32) || defined(_WIN64)
typedef unsigned __int64 u64;
#else
typedef unsigned long long u64;
#endif
#endif
#endif // CRCXX_STDCXX_VERSION_CHECK(201103)

#define CRCXX_UINT64_C(w1, w2) (static_cast<u64>(CRCXX_CONCAT(w1, UL)) << 32 | CRCXX_CONCAT(w2, UL))

#if CRCXX_HAS_GNUC_INT128
#define CRCXX_HAS_128BIT_ALGO 1
typedef __uint128_t u128;
#define CRCXX_UINT128_C(w1, w2, w3, w4)                                                                                \
    (static_cast<u128>(CRCXX_CONCAT(w1, UL)) << 96 | static_cast<u128>(CRCXX_CONCAT(w2, UL)) << 64                     \
     | static_cast<u128>(CRCXX_CONCAT(w3, UL)) << 32 | CRCXX_CONCAT(w4, UL))
#else
#define CRCXX_HAS_128BIT_ALGO 0
#endif

} // namespace crc

#endif // HXX_CRCXX_DETAIL_TYPES
