###############################################################################
# CMakeLists.txt
#
# Defines build structure for extern libraries
#
# Author: Adam Kowalewski
# Date: 8.12.2019 21:10 CEST
###############################################################################

# Include benchmarking libraries only when needed
if(BUILD_BENCHMARKING)
	add_subdirectory(picobench)
endif()
