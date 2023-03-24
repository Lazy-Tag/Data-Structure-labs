cmake_minimum_required(VERSION 3.23)
project(BBST)

set(CMAKE_CXX_STANDARD 17)

add_executable(BBST main.cpp AVLTree.h RBTree.h BST.h BST.cpp AVLTree.cpp RBTree.cpp)
