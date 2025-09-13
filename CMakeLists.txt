cmake_minimum_required(VERSION 3.25)

include(cmake/vcpkg_env.cmake)

project(cvAutoTrack.Inface LANGUAGES CXX)

include(cmake/project_setting.cmake)

include(cmake/auto_increment_version.cmake)
auto_generate_version(${CMAKE_SOURCE_DIR}/.version ${CMAKE_SOURCE_DIR}/.build_version)

set(BUILD_TESTS OFF CACHE BOOL "Build tests")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
set(BUILD_TESTS ON)

add_subdirectory(source)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
    add_subdirectory(tests/test_network)
endif()
