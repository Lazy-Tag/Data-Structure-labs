cmake_minimum_required(VERSION 3.23)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab5 main.cpp DataBuilder.cpp DataBuilder.h HashTable/HashTable.h Hash/Hash.h Hash/Hash4Ascii.h Collection/Collection.h Hash/Hash4UTF_8.h Collection/CollectionInClose.h Collection/CollectionInOpen.h HashTable/Node.h Collection/CollectionInOpenWithStep.h Collection/CollectionInOpenWithDoubleSquare.h Test.h)
