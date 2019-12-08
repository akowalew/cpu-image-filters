///////////////////////////////////////////////////////////////////////////////
// main.cpp
//
// Contains implementation of entry point to `filter-image` application
//
// Author: akowalew (ram.techen@gmail.com)
// Date: 8.12.2019 13:26 CEST
///////////////////////////////////////////////////////////////////////////////

#include <cstdio>

#include "debug.hpp"
#include "reader.hpp"
#include "writer.hpp"

void filter_image(const char* input_path, const char* output_path)
{
    const auto src_image = read_image(input_path);

    // Dummy filter - noop filter
    const auto dst_image = src_image;

    write_image(output_path, dst_image);
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
    if(argc < 3)
    {
        printf("Usage: ./filter-image <input_path> <output_path>\n");
        return 1;
    }

    const auto input_path = argv[1];
    const auto output_path = argv[2];

    try
    {
        filter_image(input_path, output_path);

        wait_for_exit();
    }
    catch(std::exception& ex)
    {
        printf("Error: %s\n", ex.what());
    }
}
