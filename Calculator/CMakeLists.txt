cmake_minimum_required(VERSION 3.23)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(Calculator Calculator.cpp Calculator.h main.cpp Data.h Calculator.h Calculator.cpp Matrix.cpp Matrix.h myStack.h Quantic.cpp Quantic.h myVector.h Fuction.cpp Fuction.h)