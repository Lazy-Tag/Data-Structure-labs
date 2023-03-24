cmake_minimum_required(VERSION 3.23)
project(Airline)

set(CMAKE_CXX_STANDARD 14)

add_executable(Airline main.cpp Date.cpp Date.h Airline.cpp Airline.h RouteMap.cpp RouteMap.h Heap.h)
