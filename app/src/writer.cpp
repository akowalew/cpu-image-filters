///////////////////////////////////////////////////////////////////////////////
// writer.cpp
//
// Contains definitions of functions related to image writing
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 13:40 CEST
///////////////////////////////////////////////////////////////////////////////

#include "writer.hpp"

#include <opencv2/highgui.hpp>

#include <cassert>

void write_image(const char* path, ImageU8 image)
{
	const auto written = cv::imwrite(path, image);
	if(!written)
	{
		throw std::runtime_error("Could not write image");
	}
}
