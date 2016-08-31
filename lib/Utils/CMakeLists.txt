cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES FileLineIterator.h LineWordIterator.h)

#add_library(fileLineIteratorLib ${SOURCE_FILES})