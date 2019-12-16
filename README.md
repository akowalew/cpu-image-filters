# cpu-image-filters

Studies project - implementation of image filters - CPU targeted (sequential + OpenMP extensions)

## Introduction

This project was created in order to test performance of convolution image filters on multicore CPUs. It provides two implementations:

- sequential - using single core
- multithreaded - using OpenMP macros

Basically there is only one function in the whole project: `filter2d_8_seq`, which performs convolution on single channel, 8-bit, 2D image. This function is then used in simple program called `filter-image`, which reads image from a file to the grayscale, performs filtering and saves filtered image to another file. You can also benchmark this function using various image sizes and various kernel sizes.

## Build requirements

In order to build the project, you need following things:

- C++17 capable compiler (tested on GCC 7.4.0 on Linux, not tested yet on Windows)
- [CMake](https://cmake.org/download/) - minimum required 3.10.2
- [Conan package manager](https://conan.io/) - if you wouldn't like to install libraries in your system
- [OpenCV](https://opencv.org/) - Just for reading/writing images, at the moment must be provided globally by the system
- [Google Benchmark](https://github.com/google/benchmark) - Micro-Benchmarking library. Provided either via Conan or globally by the system
- [doctest](https://github.com/onqtam/doctest) - Unit-testing library, if needed to do unit-tests. Provided either via Conan or globally by the system

## Building

First, you have to create build directory (for out-of-source building):

```sh
# Create out-of-source build directory
mkdir -p build
cd build
```

If you would like to use Conan, install through it needed dependencies:

```sh
# Install conan dependencies
conan install ../ --build=missing
```

_NOTE: If you encounter later some undefined references errors, modify your `default` Conan profile to use `libstdc++11` ABI_

Configure CMake:

```sh
# Configure CMake with most needed options
cmake ../ \
	-DCMAKE_BUILD_TYPE=<Release/Debug> \
	-DBUILD_TESTING=<ON/OFF> \
	-DBUILD_BENCHMARKING=<ON/OFF> \
	-DBUILD_WITH_CONAN=<OFF/ON> \
```

Build everything:

```sh
make -j$(nproc)
```

Compiled programs will be stored inside the `bin` directory.

## Filtering an image

In order to filter image with given kernel size, just type:

```sh
# Filter simple image with kernel size 3x3 and save result to the file
./bin/filter-image <seq/omp> ../assets/sunflower.jpg sunflower_out.jpg 3
```

## Benchmark filtering algorithm

In order to benchmark filtering algorithm with given number of repeats, just type:

```sh
# Benchmark algorithms
./bin/image-filters-bench
```

## Authors:

- [akowalew](https://github.com/akowalew)
- [marcin-jamroz](https://github.com/marcin-jamroz)
