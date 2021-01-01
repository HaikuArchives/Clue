cmake_minimum_required(VERSION 3.9)

project(Clue)

set(CMAKE_MODULE_PATH "${Clue_SOURCE_DIR}/CMakeModules")

include(UseHaiku)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

include_directories(source/common)

add_subdirectory(source/library)
add_subdirectory(source/viewer)
add_subdirectory(source/sample)
