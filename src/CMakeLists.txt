cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES bf.c)
add_library(src ${SOURCE_FILES})