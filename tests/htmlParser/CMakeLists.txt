include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(/usr/local/lib)

add_executable(runHtmlParser
        htmlDocumentParserTest.cpp)

target_link_libraries(runHtmlParser gmock gmock_main)
target_link_libraries(runHtmlParser src)
target_link_libraries(runHtmlParser gumbo)
