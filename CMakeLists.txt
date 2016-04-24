cmake_minimum_required( VERSION 2.8.4 )
project("RINEX2LatLng")

find_package(Armadillo REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "/usr/local/include" ${ARMADILLO_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(tests)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")