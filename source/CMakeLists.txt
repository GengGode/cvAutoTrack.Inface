configure_file(resource/resource.version.hpp.in resource.version.hpp @ONLY)

add_library(cvAutoTrack.Inface SHARED)
target_compile_definitions(cvAutoTrack.Inface PRIVATE -DCVAUTOTRACE_INFACE_EXPORTS)
if(MSVC)
        target_compile_options(cvAutoTrack.Inface PRIVATE /utf-8)
else()
        target_compile_options(cvAutoTrack.Inface PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()
target_include_directories(cvAutoTrack.Inface PRIVATE ${inface_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_sources(cvAutoTrack.Inface 
INTERFACE
        ${inface_INCLUDE_DIR}/cvAutoTrack.Inface.h
PRIVATE
        module.error.cpp
        module.impl.cpp
        module.string.cpp
        module.task.cpp
        module.progress.cpp
        module.online.cpp
        module.version.cpp
        module.api.cpp
        impl/impl.api.cpp
)

