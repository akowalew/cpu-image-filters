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

option(BUILD_EXTERN_LIBS "Whether to build extern libraries" ON)
option(BUILD_IMAGE_FILTERS_LIB "Whether to build image-filters library or not" ON)
option(BUILD_FILTER_IMAGE_APP "Whether to build filter-image application or not" ON)

###############################################################################
# Project global options
###############################################################################

if(BUILD_TESTING)
	enable_testing()
endif()

###############################################################################
# Conan integration
###############################################################################

# Include output of conan installation
find_file(CONANBUILDINFO_FILE conanbuildinfo.cmake HINTS ${CMAKE_BINARY_DIR})
include(${CONANBUILDINFO_FILE})
conan_basic_setup()

###############################################################################
# External packages
###############################################################################

find_package(OpenCV REQUIRED
    COMPONENTS
    	opencv_core
    	opencv_imgproc
    	opencv_videoio
    	opencv_highgui
    	opencv_imgcodecs
)

if(BUILD_TESTING)
	# We need this framework only when testing
	find_package(doctest REQUIRED)
endif()

###############################################################################
# Project targets
###############################################################################

if(BUILD_EXTERN_LIBS)
    add_subdirectory(extern)
endif()

if(BUILD_IMAGE_FILTERS_LIB)
	add_subdirectory(lib)
endif()

if(BUILD_FILTER_IMAGE_APP)
	add_subdirectory(app)
endif()
