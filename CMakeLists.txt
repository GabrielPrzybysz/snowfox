# Specify the minimum version
cmake_minimum_required(VERSION 3.10)

# Define the project
project(SnowFox)

# Specify source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(snowfox ${SOURCE_FILES})

# Include the header files from the child directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
