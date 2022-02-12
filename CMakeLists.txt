cmake_minimum_required(VERSION 3.19)

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

add_custom_command(
	OUTPUT "${PROJECT_BINARY_DIR}/Documentation"
	COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/data/documentation" "${PROJECT_BINARY_DIR}/Documentation"
	COMMENT "Symlinking documentation to the build directory"
	VERBATIM
)

add_custom_target("symlink-docs-to-build-dir" ALL DEPENDS "${PROJECT_BINARY_DIR}/Documentation")

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${PROJECT_BINARY_DIR}/Documentation")
