///////////////////////////////////////////////////////////////////////////////
// kernel.cpp
//
// Contains definitions of helper functions for filters kernels
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 18:07 CEST
///////////////////////////////////////////////////////////////////////////////

#include "kernel.hpp"

#include <cassert>

void low_pass_kernel(Image32F& dst)
{
	// Kernel must be float-typed
	assert(dst.type() == CV_32F);

	// Kernel must be square
	assert(dst.cols == dst.rows);
	const auto size = dst.cols;

	// Kernel size must be an odd number
	assert((size % 2) == 1);

	// Will be needed further
	const auto size_sq = (size * size);

	// Simplest low-pass kernel has every value equal to 1/size^2
	const auto factor = (1.0f / size_sq);

	// We need to cast here, because 'data' pointer in OpenCV is always uchar*
	auto dst_data = reinterpret_cast<float*>(dst.data);

	// Fill kernel with same values
	for(auto i = 0; i < size_sq; ++i)
	{
		dst_data[i] = factor;
	}
}
