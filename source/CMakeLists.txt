include(FetchContent)
# spdlog
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0 GIT_SHALLOW 1)
FetchContent_MakeAvailable(spdlog)


add_library(cvAutoTrack.Inface SHARED)
target_compile_definitions(cvAutoTrack.Inface PRIVATE -DCVAUTOTRACE_INFACE_EXPORTS)
target_sources(cvAutoTrack.Inface 
INTERFACE
        cvAutoTrack.Inface.h
PRIVATE
        cvAutoTrack.Inface.cpp
)
# target_link_libraries(cvAutoTrack.Inface PRIVATE spdlog::spdlog_header_only)