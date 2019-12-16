###############################################################################
# CMakeLists.txt
#
# Defines build structure for image-filters library
#
# Author: Adam Kowalewski
# Date: 8.12.2019 12:58 CEST
###############################################################################

###############################################################################
# Global options
###############################################################################

option(IMAGE_FILTERS_BUILD_TESTING "Whether to build tests for image-filters library" ON)
option(IMAGE_FILTERS_BUILD_BENCHMARKING "Whether to build benchmarks for image-filters library" ON)

###############################################################################
# Library definition
###############################################################################

add_library(image-filters
	src/debug.cpp
	src/filter.cpp
	src/filter_omp.cpp
	src/filter_seq.cpp
	src/kernel.cpp
)

target_link_libraries(image-filters
	PUBLIC
		# Link to OpenCV both in implementation and interface
		${OpenCV_LIBRARIES}

	PRIVATE
		# Link to OpenMP only in implementation
		OpenMP::OpenMP_CXX
)

target_include_directories(image-filters
	PUBLIC
		include
)

target_compile_options(image-filters
	PRIVATE
		# Enable all warnings only in implementation
		-Wall -Wextra -pedantic
)

set_target_properties(image-filters
	PROPERTIES
		# Enable C++17 standard without compiler-specific extensions
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
)

###############################################################################
# Unit tests
###############################################################################

if(BUILD_TESTING AND IMAGE_FILTERS_BUILD_TESTING)
    add_executable(image-filters-test
	    test/test_main.cpp
    )

    target_link_libraries(image-filters-test
	    PRIVATE
		    image-filters

            doctest::doctest
    )
endif()

###############################################################################
# Benchmarks
###############################################################################

if(BUILD_BENCHMARKING AND IMAGE_FILTERS_BUILD_BENCHMARKING)
    add_executable(image-filters-bench
    	bench/bench_main.cpp
	    bench/filter_omp_bench.cpp
	    bench/filter_seq_bench.cpp
    )

    target_link_libraries(image-filters-bench
	    PRIVATE
		    image-filters

		    ${benchmark_LIBRARIES}
		    benchmark
    )
endif()
