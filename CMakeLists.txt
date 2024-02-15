include(cmake/cmake_env.cmake)

cmake_minimum_required(VERSION 3.15)
project(cvAutoTrack.Inface)
set(BUILD_TESTS OFF CACHE BOOL "Build tests")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
set(BUILD_TESTS ON)

set(inface_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(inface_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

#=======================================================================================================================
include(cmake/parse_version.cmake)
auto_increment_version_file("source/resource/version.hash" "source/resource/version.ver")
parse_version_file("source/resource/version.ver")
get_commit_hash(PROJECT_VERSION_HASH)
get_git_branch(PROJECT_VERSION_BRANCH)
#=======================================================================================================================


add_subdirectory(source)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()