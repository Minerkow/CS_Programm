cmake_minimum_required(VERSION 3.17)
project(Parallel_Integral_Calculation C)

set(CMAKE_C_STANDARD 11)

add_executable(Parallel_Integral_Calculation main.c ParseThreadInfo.h ParseThreadInfo.c)