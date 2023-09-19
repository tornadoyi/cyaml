
project(cyaml)

# sources
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.cc ${PROJECT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/internal)

# options
add_compile_options(-fPIC)

# print
message(STATUS "SOURCES: ${SOURCES}")

# target
add_library(cyaml SHARED ${SOURCES})

# install
install(TARGETS cyaml DESTINATION ${PROJECT_SOURCE_DIR}/../lib/${CMAKE_SYSTEM_PROCESSOR})