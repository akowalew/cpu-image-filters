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

Image read_image(const char* path)
{
    auto image = cv::imread(path, cv::IMREAD_COLOR);
    assert(image.type() == CV_8UC3);
    assert(image.channels() == 3);
    return image;
}
