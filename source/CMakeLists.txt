add_library(cvAutoTrack.Inface SHARED)
target_compile_definitions(cvAutoTrack.Inface PRIVATE -DCVAUTOTRACE_INFACE_EXPORTS)
target_sources(cvAutoTrack.Inface 
INTERFACE
        cvAutoTrack.Inface.h
PRIVATE
        cvAutoTrack.Inface.cpp
)
