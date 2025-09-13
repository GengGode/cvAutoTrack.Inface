add_library(decompressor STATIC)
target_include_directories(decompressor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(decompressor PUBLIC cvAutoTrack.Inface-header)

target_compile_options(decompressor
    PRIVATE
        /utf-8
        /Zc:preprocessor
        /std:c++23preview
)

set(decompressor_impl_sources)

if (IMPL_DECOMPRESSOR_FROM_OTHER)
else()
    list(APPEND decompressor_impl_sources
        impl/decompressor.powershell.cpp
    )
endif()

target_sources(decompressor PRIVATE
    ${decompressor_impl_sources}
)
