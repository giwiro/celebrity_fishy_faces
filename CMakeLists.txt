cmake_minimum_required(VERSION 3.8)
project(celebrity_fishy_faces)

set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp detect.cpp detect.h options.cpp options.h)
add_executable(celebrity_fishy_faces ${SOURCE_FILES})
target_link_libraries( celebrity_fishy_faces ${OpenCV_LIBS} )