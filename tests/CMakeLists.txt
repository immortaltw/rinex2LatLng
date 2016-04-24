include_directories("../include")
add_executable(Test tests.cpp)
target_link_libraries(Test Rinex)