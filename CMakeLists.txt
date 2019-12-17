###############################################################################
# CMakeLists.txt
#
# Defines project structure, build options and its targets
#
# Author: Adam Kowalewski
# Date: 8.12.2019 12:42 CEST
###############################################################################

cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(cpu-image-filters VERSION 0.1.0 LANGUAGES CXX)

###############################################################################
# Global options
###############################################################################

option(BUILD_TESTING "Whether to build tests or not" ON)
option(BUILD_BENCHMARKING "Whether to build benchmarks or not" ON)
option(BUILD_WITH_CONAN "Whether to use Conan package manager or not" OFF)

option(BUILD_IMAGE_FILTERS_LIB "Whether to build image-filters library or not" ON)
option(BUILD_FILTER_IMAGE_APP "Whether to build filter-image application or not" ON)

###############################################################################
# Conan package manager integration
###############################################################################

if(BUILD_WITH_CONAN)
    # Include output of conan installation
    find_file(CONANBUILDINFO_FILE conanbuildinfo.cmake HINTS ${CMAKE_BINARY_DIR})
    include(${CONANBUILDINFO_FILE})
    conan_basic_setup()
endif()

###############################################################################
# Project global options
###############################################################################

if(BUILD_TESTING)
    # Enable CMake testing suite
	enable_testing()
endif()

# Override default CMake output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###############################################################################
# External packages
###############################################################################

# We need OpenCV only for image writing/reading
find_package(OpenCV REQUIRED
    COMPONENTS
    	opencv_core
    	opencv_imgproc
    	opencv_videoio
    	opencv_highgui
    	opencv_imgcodecs
)

find_package(benchmark REQUIRED)

# We need OpenMP extensions for multithreaded algorithms
find_package(OpenMP REQUIRED)

if(BUILD_TESTING)
	# We need this framework only when testing
	find_package(doctest REQUIRED)
endif()

###############################################################################
# Project targets
###############################################################################

if(BUILD_IMAGE_FILTERS_LIB)
	add_subdirectory(lib)
endif()

if(BUILD_FILTER_IMAGE_APP)
	add_subdirectory(app)
endif()
