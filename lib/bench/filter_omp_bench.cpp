#include "picobench/picobench.hpp"

#include "filter_omp.hpp"

#include "kernel.hpp"
#include <stdlib.h>

//! Performs benchmarking of filter2d_8_omp function
#define FILTER_2D_8_OMP_BENCH(Width, Height, KSize) \
static void filter2d_8_omp_ ## Width ## _ ## Height ## _ ## KSize ## _(picobench::state& s) \
{ \
    auto src = ImageU8(Width, Height); \
    auto dst = ImageU8(src.rows, src.cols); \
    auto kernel = Image32F(KSize, KSize, CV_32F); \
    setenv("OMP_NUM_THREADS", "2", 1); \
\
    for (auto _ : s) \
    { \
        filter2d_8_omp(src, dst, kernel); \
    } \
} \
PICOBENCH(filter2d_8_omp_ ## Width ## _ ## Height ## _ ## KSize ## _); \


FILTER_2D_8_OMP_BENCH(320, 240, 3)
FILTER_2D_8_OMP_BENCH(640, 480, 3)
FILTER_2D_8_OMP_BENCH(1024, 768, 3)

FILTER_2D_8_OMP_BENCH(320, 240, 11)
FILTER_2D_8_OMP_BENCH(640, 480, 11)
FILTER_2D_8_OMP_BENCH(1024, 768, 11)