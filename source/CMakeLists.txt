add_library(cvAutoTrack.Inface SHARED)
target_compile_definitions(cvAutoTrack.Inface PRIVATE -DCVAUTOTRACE_INFACE_EXPORTS)
target_include_directories(cvAutoTrack.Inface PRIVATE ${inface_INCLUDE_DIR})
target_sources(cvAutoTrack.Inface 
INTERFACE
        ${inface_INCLUDE_DIR}/cvAutoTrack.Inface.h
PRIVATE
        module.error.cpp
        module.impl.cpp
        module.inface.cpp
        module.string.cpp
        module.task.cpp
)

