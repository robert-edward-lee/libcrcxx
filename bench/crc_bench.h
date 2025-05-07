#ifndef H_CRC_BENCH
#define H_CRC_BENCH

#include "crc/catalog"
#include "crc/lib"

#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include <picobench/picobench.hpp>

static const volatile char bench_data[4096] = {0};

#define crc_bench(__algo) \
    void crc_bench_##__algo(picobench::state &s) { \
        crc::__algo crc; \
        volatile crc::__algo::value_type value; \
        for(auto _: s) { \
            value = crc((const void *)bench_data, sizeof(bench_data)); \
            (void)value; \
            (void)_; \
        } \
    } \
    PICOBENCH(crc_bench_##__algo).label(#__algo)

#endif /* H_CRC_BENCH */
