#ifndef HPP_CRC_LIB
#define HPP_CRC_LIB

#include "crc/detail/defines.hpp"
#include "crc/detail/rev.hpp"
#include "crc/detail/traits.hpp"
#include "crc/detail/types.hpp"

namespace crc {
template<typename ValueType,
         size_t Width,
         ValueType Poly,
         ValueType Init,
         bool RefIn,
         bool RefOut,
         ValueType XorOut,
         ValueType Check>
class Crc {
    CRC_STATIC_ASSERT(detail::is_valid_crc_type<ValueType>::value, "ValueType must be valid");
    CRC_STATIC_ASSERT(Width, "Width can not be a 0");
    CRC_STATIC_ASSERT((Width <= 8 * sizeof(ValueType)), "Crc Width can not exceed the bitwidth of ValueType");

    Crc(const Crc &) CRC_DELETED;
    Crc &operator=(const Crc &) CRC_DELETED;
#if CRC_STDCXX_VERSION_CHECK(201103)
    Crc(Crc &&) CRC_DELETED;
    Crc &operator=(Crc &&) CRC_DELETED;
#endif

public:
    typedef ValueType value_type;

    static CRC_CONST_OR_CONSTEXPR size_t real_width = 8 * sizeof(value_type);
    static CRC_CONST_OR_CONSTEXPR size_t width = Width;
    static CRC_CONST_OR_CONSTEXPR value_type poly = Poly;
    static CRC_CONST_OR_CONSTEXPR value_type init = Init;
    static CRC_CONST_OR_CONSTEXPR bool refin = RefIn;
    static CRC_CONST_OR_CONSTEXPR bool refout = RefOut;
    static CRC_CONST_OR_CONSTEXPR value_type xorout = XorOut;
    static CRC_CONST_OR_CONSTEXPR value_type check = Check;

    Crc() CRC_NOEXCEPT: m_value(fit_value(init)) {
        table_init();
    }

    CRC_CONSTEXPR_14 value_type finalize() CRC_NOEXCEPT {
        value_type ret = m_value;
        m_value = fit_value(init);

        CRC_IF_CONSTEXPR(refin != refout) {
            ret = detail::rev(ret);
        }

        CRC_IF_CONSTEXPR(!refout) {
            ret >>= real_width - width;
        }

        return ret ^ xorout;
    }

    template<typename T>
    CRC_CONSTEXPR_14 typename detail::enable_if<detail::is_byte<T>::value>::type update(T byte) CRC_NOEXCEPT {
        CRC_IF_CONSTEXPR(real_width == 8) {
            m_value = m_table[m_value ^ byte];
        } else CRC_IF_CONSTEXPR(refin) {
            m_value = m_table[(m_value & 0xFF) ^ byte] ^ (m_value >> 8);
        } else {
            m_value = m_table[(m_value >> (real_width - 8)) ^ byte] ^ (m_value << 8);
        }
    }
    template<typename T>
    typename detail::enable_if<detail::is_byte<T>::value, value_type>::type checksum(T byte) CRC_NOEXCEPT {
        update(byte);
        return finalize();
    }
    template<typename T>
    typename detail::enable_if<detail::is_byte<T>::value, value_type>::type operator()(T byte) CRC_NOEXCEPT {
        return checksum(byte);
    }

    void update(const void *begin, const void *end) CRC_NOEXCEPT {
        if(!begin) {
            return;
        }

        for(const u8 *byte = reinterpret_cast<const u8 *>(begin); byte != end; ++byte) {
            update(*byte);
        }
    }
    value_type checksum(const void *begin, const void *end) CRC_NOEXCEPT {
        update(begin, end);
        return finalize();
    }
    value_type operator()(const void *begin, const void *end) CRC_NOEXCEPT {
        return checksum(begin, end);
    }

    void update(const void *data, size_t size) CRC_NOEXCEPT {
        update(data, reinterpret_cast<const u8 *>(data) + size);
    }
    value_type checksum(const void *data, size_t size) CRC_NOEXCEPT {
        update(data, size);
        return finalize();
    }
    value_type operator()(const void *data, size_t size) CRC_NOEXCEPT {
        return checksum(data, size);
    }

private:
    static CRC_CONSTEXPR value_type fit_value(value_type value) CRC_NOEXCEPT {
        return refin ? detail::rev(value) >> (real_width - width) : value << (real_width - width);
    }
    static CRC_CONSTEXPR_14 value_type crc(value_type value) CRC_NOEXCEPT {
        int i = 8;

        CRC_IF_CONSTEXPR(refin) {
            while(i--) {
                value = (value >> 1) ^ (fit_value(poly) * (value & 1));
            }
        } else {
            value <<= real_width - 8;
            while(i--) {
                value = (value << 1) ^ (fit_value(poly) * ((value >> (real_width - 1)) & 1));
            }
        }

        return value;
    }
    void table_init() CRC_NOEXCEPT {
        u8 i = 255;
        do {
            m_table[i] = crc(i);
        } while(--i != 255);
    }

    value_type m_value;
    value_type m_table[256];
};

} // namespace crc

#endif // HPP_CRC_LIB
