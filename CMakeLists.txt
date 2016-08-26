cmake_minimum_required(VERSION 3.5)
project(indexer)

link_directories(/usr/local/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")

set (SOURCE_FILES main.cpp)
add_executable (indexer ${SOURCE_FILES})

include_directories(src)
include_directories(lib)

add_subdirectory(tests)
add_subdirectory(src)


target_link_libraries(indexer src)
target_link_libraries(indexer curl)
target_link_libraries(indexer pthread)
target_link_libraries(indexer gumbo)
target_link_libraries(indexer pq pqxx)