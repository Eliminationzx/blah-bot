include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(/usr/local/lib)

add_executable(dbTest
        indexQueueDAOTest.cpp crawlQueueTest.cpp)

target_link_libraries(dbTest gmock gmock_main)
target_link_libraries(dbTest src)
target_link_libraries(dbTest gumbo)
target_link_libraries(dbTest pq pqxx)
