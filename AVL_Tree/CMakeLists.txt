cmake_minimum_required(VERSION 3.17)
project(AVL_Tree C)

set(CMAKE_C_STANDARD 11)

add_executable(AVL_Tree main.c AVL_Tree.c AVL_Tree.h AVL_Iterator.c AVL_Iterator.h Error.h)