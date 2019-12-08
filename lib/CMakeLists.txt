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

option(IMAGE_FILTERS_BUILD_TESTING "Whether to build tests or not" ON)

###############################################################################
# Library definition
###############################################################################

add_library(image-filters
	src/debug.cpp
	src/filter.cpp
	src/filter_omp.cpp
	src/filter_seq.cpp
)

target_link_libraries(image-filters
	PUBLIC
		${OpenCV_LIBRARIES}
)

target_include_directories(image-filters
	PUBLIC
		include
)

target_compile_options(image-filters
	PRIVATE
		-Wall -Wextra -pedantic
)

set_target_properties(image-filters
	PROPERTIES
		CXX_STANDARD 17
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
