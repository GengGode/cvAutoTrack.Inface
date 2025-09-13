add_library(downloader STATIC)
target_include_directories(downloader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(downloader PUBLIC cvAutoTrack.Inface-header)

target_compile_options(downloader
    PRIVATE
        /utf-8
        /Zc:preprocessor
        /std:c++23preview
)

set(downloader_impl_sources)

if (IMPL_DOWNLOADER_FROM_CPR)
    find_package(cpr REQUIRED)
    target_link_libraries(downloader INTERFACE cpr::cpr)
else()
    list(APPEND downloader_impl_sources
        impl/downloader.system-curl.cpp
    )
endif()

target_sources(downloader PRIVATE
    ${downloader_impl_sources}
)
