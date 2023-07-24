cmake_minimum_required(VERSION 3.26)
project(Conv2D)

set(CMAKE_CXX_STANDARD 14
)
find_package(OpenMP REQUIRED)
find_package(OpenCV 4 REQUIRED)

add_executable(thread_conv2d thread_conv2d.cpp)
add_executable(conv2d conv2d.cpp)

target_link_libraries(thread_conv2d PRIVATE OpenMP::OpenMP_CXX ${OpenCV_LIBS})
target_link_libraries(conv2d PRIVATE ${OpenCV_LIBS})

