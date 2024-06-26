#ifndef HXX_CRCXX_LIB
#define HXX_CRCXX_LIB

#include "crcxx/detail/defines.hxx"
#include "crcxx/detail/rev.hxx"
#include "crcxx/detail/traits.hxx"
#include "crcxx/detail/types.hxx"

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
    CRCXX_STATIC_ASSERT(detail::is_valid_crc_type<ValueType>::value, "ValueType must be valid");
    CRCXX_STATIC_ASSERT(Width, "Width can not be a 0");
    CRCXX_STATIC_ASSERT((Width <= 8 * sizeof(ValueType)), "Crc Width can not exceed the bitwidth of ValueType");

public:
    typedef ValueType type;

    static CRCXX_CONST_OR_CONSTEXPR size_t real_width = 8 * sizeof(type);
    static CRCXX_CONST_OR_CONSTEXPR size_t width = Width;
    static CRCXX_CONST_OR_CONSTEXPR type poly = Poly;
    static CRCXX_CONST_OR_CONSTEXPR type init = Init;
    static CRCXX_CONST_OR_CONSTEXPR bool refin = RefIn;
    static CRCXX_CONST_OR_CONSTEXPR bool refout = RefOut;
    static CRCXX_CONST_OR_CONSTEXPR type xorout = XorOut;
    static CRCXX_CONST_OR_CONSTEXPR type check = Check;

    Crc(void): m_value(fit_value(init)), m_table(new type[256]) {
        table_init();
    }

    ~Crc(void) CRCXX_NOEXCEPT {
        delete[] m_table;
    }

    CRCXX_CONSTEXPR_14 type finalize(void) CRCXX_NOEXCEPT {
        type ret = m_value;
        m_value = fit_value(init);

        CRCXX_IF_CONSTEXPR(refin != refout) {
            ret = detail::rev(ret);
        }

        CRCXX_IF_CONSTEXPR(!refout) {
            ret >>= real_width - width;
        }

        return ret ^ xorout;
    }

    template<typename T>
    CRCXX_CONSTEXPR_14 typename detail::enable_if<detail::is_byte<T>::value>::type update(T byte) CRCXX_NOEXCEPT {
        CRCXX_IF_CONSTEXPR(real_width == 8) {
            m_value = m_table[m_value ^ byte];
        } else CRCXX_IF_CONSTEXPR(refin) {
            m_value = m_table[(m_value & 0xFF) ^ byte] ^ (m_value >> 8);
        } else {
            m_value = m_table[(m_value >> (real_width - 8)) ^ byte] ^ (m_value << 8);
        }
    }
    template<typename T>
    typename detail::enable_if<detail::is_byte<T>::value, type>::type checksum(T byte) CRCXX_NOEXCEPT {
        update(byte);
        return finalize();
    }
    template<typename T>
    typename detail::enable_if<detail::is_byte<T>::value, type>::type operator()(T byte) CRCXX_NOEXCEPT {
        return checksum(byte);
    }

    void update(const void *begin, const void *end) CRCXX_NOEXCEPT {
        if(!begin) {
            return;
        }

        for(const uint8_t *byte = reinterpret_cast<const uint8_t *>(begin); byte != end; ++byte) {
            update(*byte);
        }
    }
    type checksum(const void *begin, const void *end) CRCXX_NOEXCEPT {
        update(begin, end);
        return finalize();
    }
    type operator()(const void *begin, const void *end) CRCXX_NOEXCEPT {
        return checksum(begin, end);
    }

    void update(const void *data, size_t size) CRCXX_NOEXCEPT {
        update(data, reinterpret_cast<const uint8_t *>(data) + size);
    }
    type checksum(const void *data, size_t size) CRCXX_NOEXCEPT {
        update(data, size);
        return finalize();
    }
    type operator()(const void *data, size_t size) CRCXX_NOEXCEPT {
        return checksum(data, size);
    }

private:
    static CRCXX_CONSTEXPR type fit_value(type value) CRCXX_NOEXCEPT {
        return refin ? detail::rev(value) >> (real_width - width) : value << (real_width - width);
    }

    static CRCXX_CONSTEXPR_14 type crc(type value) CRCXX_NOEXCEPT {
        int i = 8;

        CRCXX_IF_CONSTEXPR(refin) {
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

    void table_init(void) CRCXX_NOEXCEPT {
        type i = 255;
        while(i) {
            m_table[i] = crc(i);
            --i;
        }
        m_table[i] = crc(i);
    }

    type m_value;
    type *m_table;
};

} // namespace crc

#endif // HXX_CRCXX_LIB
