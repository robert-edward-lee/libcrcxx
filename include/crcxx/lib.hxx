#ifndef HXX_CRCXX_LIB
#define HXX_CRCXX_LIB

#include "detail/defines.hxx"
#include "detail/rev.hxx"
#include "detail/traits.hxx"

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
    CRCXX_STATIC_ASSERT(detail::is_valid_crc_type<ValueType>::value,
                        "ValueType must be valid: uint[8, 16, 32, 64, 128]_t");
    CRCXX_STATIC_ASSERT(Width, "Width can not be a 0");
    CRCXX_STATIC_ASSERT(Width <= 8 * sizeof(ValueType), "Crc Width can not exceed the bitwidth of ValueType");

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

    Crc(void): value(init_value(init)), table(new type[256]) {
        table_init();
    }

    ~Crc(void) CRCXX_NOEXCEPT {
        delete[] table;
    }

    type finalize(void) CRCXX_NOEXCEPT {
        type ret = value;
        value = init_value(init);

        if(refin != refout) {
            ret = detail::rev(ret);
        }

        if(!refout) {
            ret >>= real_width - width;
        }

        return ret ^ xorout;
    }

    template<typename T>
    CRCXX_CONSTEXPR_14 typename detail::enable_if<detail::is_byte<T>::value>::type update(T byte) CRCXX_NOEXCEPT {
        if(real_width == 8) {
            value = table[value ^ byte];
        } else if(refin) {
            value = table[(value & 0xFF) ^ byte] ^ (value >> 8);
        } else {
            value = table[(value >> (real_width - 8)) ^ byte] ^ (value << 8);
        }
    }
    template<typename T>
    CRCXX_CONSTEXPR_14 typename detail::enable_if<detail::is_byte<T>::value, type>::type
    checksum(T byte) CRCXX_NOEXCEPT {
        update(byte);
        return finalize();
    }
    template<typename T>
    CRCXX_CONSTEXPR_14 typename detail::enable_if<detail::is_byte<T>::value, type>::type
    operator()(T byte) CRCXX_NOEXCEPT {
        return checksum(byte);
    }

    void update(const void *data, size_t size) CRCXX_NOEXCEPT {
        if(!data) {
            return;
        }

        for(size_t i = 0; i < size; i++) {
            update(reinterpret_cast<const uint8_t *>(data)[i]);
        }
    }
    CRCXX_CONSTEXPR_14 type checksum(const void *data, size_t size) CRCXX_NOEXCEPT {
        update(data, size);
        return finalize();
    }
    CRCXX_CONSTEXPR_14 type operator()(const void *data, size_t size) CRCXX_NOEXCEPT {
        return checksum(data, size);
    }

    void update(const void *begin, const void *end) CRCXX_NOEXCEPT {
        if(!begin) {
            return;
        }

        for(const uint8_t *byte = reinterpret_cast<const uint8_t *>(begin); byte < end; byte++) {
            update(*byte);
        }
    }
    CRCXX_CONSTEXPR_14 type checksum(const void *begin, const void *end) CRCXX_NOEXCEPT {
        update(begin, end);
        return finalize();
    }
    CRCXX_CONSTEXPR_14 type operator()(const void *begin, const void *end) CRCXX_NOEXCEPT {
        return checksum(begin, end);
    }

private:
    Crc(const Crc &);
    Crc &operator=(const Crc &);

    static CRCXX_CONSTEXPR type init_value(type init) CRCXX_NOEXCEPT {
        return refin ? detail::rev(init) >> (real_width - width) : init << (real_width - width);
    }

    static CRCXX_CONSTEXPR_14 type crc(type value) CRCXX_NOEXCEPT {
        int i = 8;

        if(refin) {
            while(i--) {
                value = (value >> 1) ^ (init_value(poly) & -(value & 1));
            }
        } else {
            value <<= real_width - 8;
            while(i--) {
                value = (value << 1) ^ (init_value(poly) & -((value >> (real_width - 1)) & 1));
            }
        }

        return value;
    }

    void table_init(void) CRCXX_NOEXCEPT {
        int i = 256;
        while(i--) {
            table[i] = crc(i);
        }
    }

    type value;
    type *table;
};

} // namespace crc

#endif // HXX_CRCXX_LIB
