#ifndef HPP_CXX_DETAIL_DEFINES
#define HPP_CXX_DETAIL_DEFINES

////////////////////////////////////////////////////////////////////////////////
//                                   Utils                                    //
////////////////////////////////////////////////////////////////////////////////
#define CRC_DO_CONCAT(a, b) a##b
#define CRC_CONCAT(a, b) CRC_DO_CONCAT(a, b)

#define CRC_DO_STR(s) #s
#define CRC_STR(s) CRC_DO_STR(s)

////////////////////////////////////////////////////////////////////////////////
//                          Language Standard Detect                          //
////////////////////////////////////////////////////////////////////////////////
#if defined(__cplusplus)
#if defined(_MSC_VER)
#define CRC_STDCXX_VERSION_CHECK(v) (_MSVC_LANG >= (v))
#else
#define CRC_STDCXX_VERSION_CHECK(v) (__cplusplus >= (v))
#endif
#else
#define CRC_STDCXX_VERSION_CHECK(v) 0
#endif

////////////////////////////////////////////////////////////////////////////////
//                           Language Feature-Test                            //
////////////////////////////////////////////////////////////////////////////////
#if defined(__cpp_constexpr)
#if __cpp_constexpr >= 201907
#define CRC_CONST_OR_CONSTEXPR constexpr
#define CRC_CONSTEXPR constexpr
#define CRC_CONSTEXPR_14 constexpr
#elif __cpp_constexpr >= 201304
#define CRC_CONST_OR_CONSTEXPR constexpr
#define CRC_CONSTEXPR constexpr
#define CRC_CONSTEXPR_14 constexpr
#else
#define CRC_CONST_OR_CONSTEXPR constexpr
#define CRC_CONSTEXPR constexpr
#define CRC_CONSTEXPR_14 inline
#endif
#else
#define CRC_CONST_OR_CONSTEXPR const
#define CRC_CONSTEXPR inline
#define CRC_CONSTEXPR_14 inline
#endif

#if CRC_STDCXX_VERSION_CHECK(201103)
#define CRC_DELETED = delete
#else
#define CRC_DELETED
#endif

#if CRC_STDCXX_VERSION_CHECK(201606)
#define CRC_IF_CONSTEXPR if constexpr
#else
#define CRC_IF_CONSTEXPR if
#endif

#if CRC_STDCXX_VERSION_CHECK(201103)
#define CRC_NOEXCEPT noexcept
#else
#define CRC_NOEXCEPT throw()
#endif

#if CRC_STDCXX_VERSION_CHECK(200410)
#define CRC_STATIC_ASSERT static_assert
#else
#define CRC_MAKE_ASSERT_NAME(a) CRC_CONCAT(a, __COUNTER__)
#define CRC_STATIC_ASSERT(expr, msg) typedef char CRC_MAKE_ASSERT_NAME(CRC_STATIC_ASSERTION_)[(expr) ? 1 : -1]
#endif

////////////////////////////////////////////////////////////////////////////////
//                            Compiler Intrinsics                             //
////////////////////////////////////////////////////////////////////////////////
#if !defined(__has_builtin)
#define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_convertvector) && defined(__clang__)
#define CRC_HAS_BUILTIN_BITREVERSE 1
#else
#define CRC_HAS_BUILTIN_BITREVERSE 0
#endif

#if defined(__SIZEOF_INT128__)
#define CRC_HAS_GNUC_INT128 1
#else
#define CRC_HAS_GNUC_INT128 0
#endif

#endif // HPP_CXX_DETAIL_DEFINES
