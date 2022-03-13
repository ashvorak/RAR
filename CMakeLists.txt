cmake_minimum_required(VERSION 3.19)
project(RAR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(RAR main.cpp Compression.h LzwCompression.h LzwCompression.cpp FileCompressor.cpp FileCompressor.h Utils.h Utils.cpp)