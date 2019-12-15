###############################################################################
# CMakeLists.txt
#
# Defines build structure for filter-image application
#
# Author: Adam Kowalewski
# Date: 8.12.2019 13:27 CEST
###############################################################################

###############################################################################
# Global options
###############################################################################

option(FILTER_IMAGE_BUILD_TESTING "Whether to build tests or not" ON)

###############################################################################
# Common object files
###############################################################################

# Define common objects build target
add_executable(filter-image
	src/main.cpp
	src/reader.cpp
	src/writer.cpp
)

target_link_libraries(filter-image
	PRIVATE
		${OpenCV_LIBRARIES}
		image-filters
)

target_include_directories(filter-image
	PRIVATE
		include
)

target_compile_options(filter-image
	PRIVATE
		-Wall -Wextra -pedantic -fopenmp
)

set_target_properties(filter-image
	PROPERTIES
		CXX_STANDARD 17
)

###############################################################################
# Unit tests
###############################################################################

if(BUILD_TESTING AND FILTER_IMAGE_BUILD_TESTING)
# TODO
endif()
