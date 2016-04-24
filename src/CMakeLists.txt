include_directories("../include")
add_library (Rinex ObsParser.cpp)
add_executable (demo main.cpp)
target_link_libraries (demo Rinex ${ARMADILLO_LIBRARIES})