cmake_minimum_required(VERSION 3.25)
project(K_VCC)

set(CMAKE_CXX_STANDARD 20)

add_executable(K_VCC main.cpp Graph.h)
add_definitions(-Wl,--stack,16777216)

