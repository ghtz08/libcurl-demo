cmake_minimum_required(VERSION 3.10)

project(hello_curl)

# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
include(cmake/Dependencies.cmake)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
