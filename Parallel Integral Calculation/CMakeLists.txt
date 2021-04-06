cmake_minimum_required(VERSION 3.17)
project(Parallel_Integral_Calculation C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")


add_executable(Parallel_Integral_Calculation
                    main.c
                    ParseInfo.h
                    ParseInfo.c
                    IntegralCalculator.h
                    IntegralCalculator.c
        )