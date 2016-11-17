include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(/usr/local/lib)

add_executable(configTest
        configTest.cpp)

target_link_libraries(configTest gmock gmock_main)
target_link_libraries(configTest src)
target_link_libraries(configTest boost_system boost_filesystem)
