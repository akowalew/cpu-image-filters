///////////////////////////////////////////////////////////////////////////////
// main.cpp
//
// Contains implementation of entry point to `filter-image` application
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 13:26 CEST
///////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>

#include <system_error>

#include "debug.hpp"
#include "reader.hpp"
#include "writer.hpp"
#include "kernel.hpp"
#include "filter_seq.hpp"

int parse_kernel_size(const char* str)
{
    int kernel_size = std::stoi(str);
    if(kernel_size <= 0)
    {
        throw std::system_error(EINVAL, std::generic_category(),
            "Kernel size must be greater than zero");
    }
    else if((kernel_size % 2) != 1)
    {
        throw std::system_error(EINVAL, std::generic_category(),
            "Kernel size must be an odd number");
    }

    return kernel_size;
}

void filter_image(const char* input_path, const char* output_path, int kernel_size)
{
    const auto src = read_image(input_path);
    show_image("Source image", src);

    auto kernel = Image32F(kernel_size, kernel_size, CV_32F);
    low_pass_kernel(kernel);

    auto dst = ImageU8(src.rows, src.cols, src.type());
    filter2d_8_seq(src, dst, kernel);

    write_image(output_path, dst);
    show_image("Destination image", dst);
}

/**
 * @brief Main program routine
 * @details It parses command line arguments,
 * reads image from specified file, processes it and writes it
 * to specified file.
 *
 * @param argc argument counter
 * @param argv argument vector
 *
 * @return status code
 */
int main(int argc, char** argv)
{
    if(argc < 4)
    {
        printf("Usage: ./filter-image <input_path> <output_path> <kernel_size>\n");
        return 1;
    }

    try
    {
        const auto input_path = argv[1];
        const auto output_path = argv[2];
        const auto kernel_size = parse_kernel_size(argv[3]);

        filter_image(input_path, output_path, kernel_size);

        wait_for_exit();
    }
    catch(std::exception& ex)
    {
        printf("Error: %s\n", ex.what());
    }
}
