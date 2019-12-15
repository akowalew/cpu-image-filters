///////////////////////////////////////////////////////////////////////////////
// filter.cpp
//
// Contains definitions of image filtering functions - OpenMP version
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 13:13 CEST
///////////////////////////////////////////////////////////////////////////////

#include "filter.hpp"

#include <limits>
#include <cstdio>
#include <cassert>
#include <omp.h>
 #include <iostream>

/**
 * @brief Helper function for clamping values between two incompatible types
 * @details It calculates first (at compile time), how min/max values in
 * destination type will look in source type and performs bound-checking
 * of source value.
 *
 * @param src source value
 * @tparam Dst destination type
 * @tparam Src source type
 * @return source value clamped to range valid for destination value
 */
template<typename Dst, typename Src>
Dst clamp_to(Src src)
{
	// Get min/max range of destination type
	constexpr auto MaxDst = std::numeric_limits<Dst>::max();
	constexpr auto MinDst = std::numeric_limits<Dst>::min();

	// Get min/max expressed in source type values
	constexpr auto MaxSrc = static_cast<Src>(MaxDst);
	constexpr auto MinSrc = static_cast<Src>(MinDst);

	// Perform bound-checkings
	if(src > MaxSrc)
	{
		// Source is greater than allowed destination max. Return dest's max
		return MaxDst;
	}
	else if(src < MinSrc)
	{
		// Source is smaller than allowed destination min. Return dest's min
		return MinDst;
	}
	else
	{
		// Source is in destination range. Cast it to dest and return
		return static_cast<Dst>(src);
	}
}

void filter2d_8_omp(const Image& src, Image& dst, const Image& kernel)
{
    omp_set_nested(1);
    // omp_set_num_threads(2);
    // int max_threads = omp_get_max_threads();
    // std::cout << "Max num of threads: " << max_threads << std::endl;

    // Filtering cannot be done in-place
	assert(src.data != dst.data);

	// Images must be continuous so we can operate on memory directly
	assert(src.isContinuous() && dst.isContinuous());

	// Images sizes must be equal
	assert((src.cols == dst.cols) && (src.rows == dst.rows));
	const auto cols = src.cols;
	const auto rows = src.rows;

	// Number of channels must be equal
	assert(src.channels() == dst.channels());

	// Images types must be equal to CV_8UC1 - single channel U8
	assert(src.type() == CV_8UC1 && dst.type() == CV_8UC1);
	using Value = unsigned char;

	// Kernel must be squared
	assert(kernel.cols == kernel.rows);
	const auto kernel_size = kernel.cols;

	// Kernel size must be an odd number
	assert((kernel_size % 2) == 1);

	// Kernel must be continuous
	assert(kernel.isContinuous());

	// Kernel must be float-typed, and so is the accumulator
	assert(kernel.type() == CV_32F);
	using Accumulator = float;

	// We need this in further calculations
	const auto half_kernel_size = (kernel_size / 2);

	// After filtering width and height of the final image is reduced
	const auto width = (cols - 2 * half_kernel_size);
	const auto height = (rows - 2 * half_kernel_size);

	// Since width and height is reduced, we have to start from different place
	const auto dst_offset = ((half_kernel_size * cols) + half_kernel_size);

	// Start convolution filtering
	auto dst_it_i = (dst.data + dst_offset);
	auto src_it_i = src.data;

	// For each row do...
	#pragma omp for
	for(auto i = 0; i < height; ++i)
	{
		
        auto src_it_j = src_it_i;
		auto dst_it_j = dst_it_i;


		// For each column do...
		for(auto j = 0; j < width; ++j)
		{
			// Initialize accumulator to zero
			auto acc = Accumulator{0};

			auto src_it_m = src_it_j;
			auto kernel_it = reinterpret_cast<float*>(kernel.data);

			// For each kernel row do...
			for(auto m = 0; m < kernel_size; ++m)
			{
				auto src_it_n = src_it_m;

				// For each kernel column do...
				for(auto n = 0; n < kernel_size; ++n)
				{
					// Fetch source and kernel values
					const auto src_value = *(src_it_n);
					const auto kernel_value = *(kernel_it);

					// Increase accumulator by multiply of source and kernel values
					acc += (src_value * kernel_value);

					// Jump to next columns in source and kernel
					++src_it_n;
					++kernel_it;
				}

				// Jump to next row in source (only)
				src_it_m += cols;

				// Altough we don't do this in kernel, because it is continuous
			}

			// Clamp accumulator value to fit in destination type
			const auto clamped = clamp_to<Value>(acc);

			// Store clamped value to destination
			*dst_it_j = clamped;

			// Jump to next columns in source and destination
			++src_it_j;
			++dst_it_j;
		}

		// Jump to next rows in source and destination
		src_it_i += cols;
		dst_it_i += cols;
	}
}
