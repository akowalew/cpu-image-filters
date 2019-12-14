///////////////////////////////////////////////////////////////////////////////
// filter_seq_bench.cpp
//
// Contains definitions of benchmarks for filter_seq module
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 20:14 CEST
///////////////////////////////////////////////////////////////////////////////

#include "picobench/picobench.hpp"

#include "filter_seq.hpp"

#include "kernel.hpp"

//! Performs benchmarking of filter2d_8_seq function
#define FILTER_2D_8_SEQ_BENCH(Width, Height, KSize) \
static void filter2d_8_seq_ ## Width ## _ ## Height ## _ ## KSize ## _(picobench::state& s) \
{ \
    auto src = ImageU8(Width, Height); \
    auto dst = ImageU8(src.rows, src.cols); \
    auto kernel = Image32F(KSize, KSize, CV_32F); \
\
    for (auto _ : s) \
    { \
        filter2d_8_seq(src, dst, kernel); \
    } \
} \
PICOBENCH(filter2d_8_seq_ ## Width ## _ ## Height ## _ ## KSize ## _); \

FILTER_2D_8_SEQ_BENCH(320, 240, 3)
FILTER_2D_8_SEQ_BENCH(640, 480, 3)
FILTER_2D_8_SEQ_BENCH(1024, 768, 3)

FILTER_2D_8_SEQ_BENCH(320, 240, 11)
FILTER_2D_8_SEQ_BENCH(640, 480, 11)
FILTER_2D_8_SEQ_BENCH(1024, 768, 11)
