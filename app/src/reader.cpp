///////////////////////////////////////////////////////////////////////////////
// reader.cpp
//
// Contains definitions of functions related to image reading
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 13:40 CEST
///////////////////////////////////////////////////////////////////////////////

#include "reader.hpp"

#include <opencv2/highgui.hpp>

#include <cassert>

ImageU8 read_image(const char* path)
{
    auto image = cv::imread(path, cv::IMREAD_GRAYSCALE);
    assert(image.type() == CV_8UC1);
    return image;
}
