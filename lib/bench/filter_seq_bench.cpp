///////////////////////////////////////////////////////////////////////////////
// filter_seq_bench.cpp
//
// Contains definitions of benchmarks for filter_seq module
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 20:14 CEST
///////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

#include "filter_seq.hpp"

#include "kernel.hpp"

//! Performs benchmarking of filter2d_8_seq function
static void filter2d_8_seq(benchmark::State& state, int width, int height, int ksize)
{
    auto src = ImageU8(width, height);
    auto dst = ImageU8(src.rows, src.cols);
    auto kernel = Image32F(ksize, ksize, CV_32F);

    for (auto _ : state)
    {
        filter2d_8_seq(src, dst, kernel);
    }
}

// BENCHMARK_CAPTURE(filter2d_8_seq, 320x240x3, 320, 240, 3);
// BENCHMARK_CAPTURE(filter2d_8_seq, 320x240x9, 320, 240, 9);
// BENCHMARK_CAPTURE(filter2d_8_seq, 640x480x3, 640, 480, 3);
BENCHMARK_CAPTURE(filter2d_8_seq, 640x480x9, 640, 480, 9);
