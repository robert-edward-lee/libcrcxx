#ifndef HPP_CXX_DETAIL_TRAITS
#define HPP_CXX_DETAIL_TRAITS

#include "crc/detail/defines.hpp"
#if CRC_STDCXX_VERSION_CHECK(201103)
#include <type_traits>
#endif

#include "crc/detail/types.hpp"

namespace crc { namespace detail {
#if CRC_STDCXX_VERSION_CHECK(201103)
using std::true_type;
using std::false_type;
using std::enable_if;
using std::remove_cv;
#else
template<typename T, T v> struct integral_constant {
    static const T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    operator value_type() const {
        return value;
    }
};
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template<bool, typename T = void> struct enable_if {};
template<typename T> struct enable_if<true, T> {
    typedef T type;
};

template<typename T> struct remove_cv {
    typedef T type;
};
template<typename T> struct remove_cv<const T> {
    typedef T type;
};
template<typename T> struct remove_cv<volatile T> {
    typedef T type;
};
template<typename T> struct remove_cv<const volatile T> {
    typedef T type;
};
#endif

template<typename> struct is_byte: false_type {};
template<> struct is_byte<char>: true_type {};
template<> struct is_byte<signed char>: true_type {};
template<> struct is_byte<unsigned char>: true_type {};

template<typename T> struct is_valid_crc_type_helper: false_type {};
template<> struct is_valid_crc_type_helper<u8>: true_type {};
template<> struct is_valid_crc_type_helper<u16>: true_type {};
template<> struct is_valid_crc_type_helper<u32>: true_type {};
template<> struct is_valid_crc_type_helper<u64>: true_type {};
#if CRC_HAS_128BIT_ALGO
template<> struct is_valid_crc_type_helper<u128>: true_type {};
#endif
template<typename T> struct is_valid_crc_type: is_valid_crc_type_helper<typename remove_cv<T>::type> {};
}} // namespace crc::detail

#endif // HPP_CXX_DETAIL_TRAITS
