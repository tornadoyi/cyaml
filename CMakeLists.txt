cmake_minimum_required(VERSION 3.0)

project(cyaml)


# header
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# sources
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.cc)

# enable testing
enable_testing()

# std
set(CMAKE_CXX_STANDARD 17)

# debug
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
  ADD_DEFINITIONS(-DCYBER_DEBUG)
ENDIF()


# add targets
add_subdirectory(cyaml)
add_subdirectory(test)