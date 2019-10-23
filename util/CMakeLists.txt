cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(tester_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "base_filter.cpp")
