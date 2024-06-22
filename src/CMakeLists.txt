# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(SnowfoxProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(snowfox snowfox.cpp)
