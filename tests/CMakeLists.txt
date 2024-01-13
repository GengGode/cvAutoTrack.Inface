add_executable(test_inface main.cpp)
target_include_directories(test_inface PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_inface PRIVATE cvAutoTrack.Inface)
