#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const double DELTA = 0.0001;

struct Integral_t {
    double begin;
    double end;
    double (*func) (double x);
};

enum INTEGRAL_ERROR_t{
    NULL_POINTER_ARG,
    CORES_INFO_ERROR,
    THREADS_INFO_ERROR,
    SYSTEM_ERROR
};

enum INTEGRAL_ERROR_t IntegralCalculate(struct Integral_t integral, size_t numThreads, double* res);

//static void* GetThreadsInfo(size_t numThread, size_t* sizeThreadInfo);
void test();