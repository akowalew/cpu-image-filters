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

If you would like to use Conan, define first needed remotes, and then install needed dependencies:

```sh
# Install Conan configuration based on `conan` subdirectory
conan config install ../conan/

# Install Conan dependencies with C++11 ABI
conan install ../ --build=missing --setting compiler.libcxx=libstdc++11
```

_NOTE: Setting of C++11 ABI is especially needed for Google Benchmark, because without this, you will get segfaults at runtime_

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

Before you do any benchmark, make sure that you've build project in at least `Release` version:

```sh
cmake ../ -DCMAKE_BUILD_TYPE=Release
```

Ensure also, that CPU frequency scalling is disabled:

```sh
sudo cpupower frequency-set --governor performance
```

Now, to perform benchmarking, just type:

```sh
# Benchmark algorithms
./bin/image-filters-bench
```

Benchmarks are implemented using Google Benchmark, so you can use its CLI directly (setting number of iterations, filtering tests etc). As example to run tests with 25 repeatitions and display only summary:

```sh
# Run benchmark with 25 repetitions and display summary only
./bin/image-filters-bench --benchmark_repetitions=25 --benchmark_report_aggregates_only=true
```

After finished benchmarking, back to powersave governor:

```sh
sudo cpupower frequency-set --governor powersave
```

## Authors:

- [akowalew](https://github.com/akowalew)
- [marcin-jamroz](https://github.com/marcin-jamroz)
