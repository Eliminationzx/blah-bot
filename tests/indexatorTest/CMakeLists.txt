include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runIndexatorTest
        tokenizeTest.cpp indexatorHeader.h
        stemmingTest.cpp)

target_link_libraries(runIndexatorTest gmock gmock_main)
target_link_libraries(runIndexatorTest gumbo)
target_link_libraries(runIndexatorTest boost_system boost_filesystem)
target_link_libraries(runIndexatorTest src)
