add_executable(test_network main.cpp)
target_include_directories(test_network PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(test_network PRIVATE ${CMAKE_SOURCE_DIR}/source)
target_link_libraries(test_network)
