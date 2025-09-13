add_library(configer STATIC)
target_include_directories(configer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(configer
    PRIVATE
        /utf-8
        /Zc:preprocessor
        /std:c++23preview
)

set(configer_impl_sources)

find_package(meojson REQUIRED)
target_link_libraries(configer PRIVATE meojson::meojson)
list(APPEND configer_impl_sources
    impl/configer.meojson.cpp
)

target_sources(configer PRIVATE
    ${configer_impl_sources}
)
