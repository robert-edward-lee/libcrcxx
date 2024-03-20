#ifndef HXX_CRC_TEST
#define HXX_CRC_TEST

#include <iostream>
#include <stdint.h>

std::string check = "123456789";

template<typename T> inline void print_hex(T a) {
    const uint8_t *as_u8 = reinterpret_cast<const uint8_t *>(&a);
    printf("0x");
    for(int i = sizeof(a) - 1; i >= 0; i--) {
        printf("%02X", as_u8[i]);
    }
}

#define crc_test(__algo, __)                                                                                           \
    {                                                                                                                  \
        __algo crc;                                                                                                    \
        __algo::type value = crc(check.c_str(), check.size());                                                         \
        if(__algo::check != value) {                                                                                   \
            printf("Invalid CRC check for " #__algo ": ");                                                             \
            print_hex(value);                                                                                          \
            printf(", expected = ");                                                                                   \
            print_hex(__algo::check);                                                                                  \
            printf("\n");                                                                                              \
            errors++;                                                                                                  \
        } else {                                                                                                       \
            printf(#__algo " passed\n");                                                                               \
            passed++;                                                                                                  \
        }                                                                                                              \
    }

#endif // HXX_CRC_TEST
