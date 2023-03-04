cmake_minimum_required(VERSION 3.22)
project(SLAU)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES *.h *.cpp *.hpp)

add_library(SLAU INTERFACE ${SOURCES})