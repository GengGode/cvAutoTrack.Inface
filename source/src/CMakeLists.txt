configure_file(resource/resource.version.hpp.in resource.version.hpp @ONLY)

add_library(cvAutoTrack.Inface SHARED)
target_compile_definitions(cvAutoTrack.Inface PRIVATE -DCVAUTOTRACE_INFACE_EXPORTS)
if(MSVC)
        target_compile_options(cvAutoTrack.Inface PRIVATE /utf-8)
else()
        target_compile_options(cvAutoTrack.Inface PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()
target_include_directories(cvAutoTrack.Inface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_sources(cvAutoTrack.Inface 
PRIVATE
        cvautotrack-impl.cpp
        free_string_span.cpp
)

add_subdirectory(configer)
add_subdirectory(downloader)
add_subdirectory(decompressor)

find_package(global_utils REQUIRED)
target_link_libraries(cvAutoTrack.Inface PRIVATE global_utils::global_utils)

target_link_libraries(cvAutoTrack.Inface PRIVATE cvAutoTrack.Inface-header)
target_link_libraries(cvAutoTrack.Inface PRIVATE configer)
target_link_libraries(cvAutoTrack.Inface PRIVATE downloader)
target_link_libraries(cvAutoTrack.Inface PRIVATE decompressor)
