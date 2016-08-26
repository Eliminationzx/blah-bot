include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(/usr/local/lib)

add_executable(runParser
        htmlDocumentParserTest.cpp)

target_link_libraries(runParser gmock gmock_main)
target_link_libraries(runParser src)

target_link_libraries(runParser gumbo)
