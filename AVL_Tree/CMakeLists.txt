cmake_minimum_required(VERSION 2.8)
project(AVL_Tree)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${GTEST_INCLUDE_DIRS}
)

add_executable(AVL_Tree main.c source/AVL_Tree.c headers/AVL_Tree.h source/AVL_Iterator.c headers/Error.h headers/TestHelper.h test/TestHelper.c)

add_executable(AVL_Tree_Test test/avlTests.cpp headers/AVL_Tree.h source/AVL_Tree.c source/AVL_Iterator.c test/TestHelper.c headers/TestHelper.h test/main.cpp)

target_link_libraries(
        AVL_Tree_Test ${GTEST_LIBRARIES} Threads::Threads
)
