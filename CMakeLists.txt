cmake_minimum_required(VERSION 3.19)
project(Set)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Set main.cpp src/Set.cpp src/Set.h)