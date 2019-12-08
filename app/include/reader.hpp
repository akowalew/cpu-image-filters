///////////////////////////////////////////////////////////////////////////////
// reader.hpp
//
// Contains declaration of image reading functions
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 13:39 CEST
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "image.hpp"

/**
 * @brief Reads image from specified file in BGR format
 * @details
 *
 * @param path path to the file
 * @return read image
 */
ImageU8 read_image(const char* path);
