///////////////////////////////////////////////////////////////////////////////
// filter.hpp
//
// Contains declarations of image filtering functions - OpenMP version
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 14:18 CEST
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "image.hpp"

/**
 * @brief Performs convolution filtering on given image
 * @details
 *
 * @param src source image
 * @param dst destination image
 * @param kernel kernel of the filter (squared)
 */
void filter2d_8_omp(const ImageU8& src, ImageU8& dst, const Image32F& kernel);
