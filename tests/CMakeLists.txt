include_directories("../include")
add_executable(Test tests.cpp)
target_link_libraries(Test Rinex ${ARMADILLO_LIBRARIES})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")