cmake_minimum_required(VERSION 3.22)
project(SLAU)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(SLAU INTERFACE ${PROJECT_NAME} pthread)