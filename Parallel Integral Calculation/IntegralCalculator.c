#include "IntegralCalculator.h"
#include "ParseInfo.h"

struct IntegralInfo_t {
    double begin;
    double end;
    double delta;
};

struct ThreadInfo_t {
    double result;
    struct IntegralInfo_t integralInfo;
};


//---------------------------------Get Thread Info-----------------------------------

static void* GetThreadsInfo_(size_t numThread, size_t* sizeThreadsInfo);
static void UpdateThreadInfo_(void* threadsInfo, size_t sizeThreadsInfo, size_t numThread,
                              struct IntegralInfo_t* integralInfo);
static void Calculate(struct ThreadInfo_t* threadInfo, double (*func) (double x));


//---------------------------------Get Thread Info-----------------------------------


static void* GetThreadsInfo_(size_t numThread, size_t* sizeThreadsInfo) {
    assert(sizeThreadsInfo);

    long sizeCacheLine = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (sizeCacheLine < 0) {
        perror("_SC_LEVEL1_DCACHE_LINESIZE");
        return NULL;
    }

    *sizeThreadsInfo = (sizeof(struct ThreadInfo_t) / sizeCacheLine + 1) * sizeCacheLine;
    void* threadsInfo = calloc(numThread, *sizeThreadsInfo);
    return threadsInfo;
}


//Expect that end > begin
static void UpdateThreadInfo_(void* threadsInfo, size_t sizeThreadsInfo, size_t numThread,
                              struct IntegralInfo_t* integralInfo) {
    assert(threadsInfo);
    assert(integralInfo);
    assert(integralInfo->end - integralInfo->begin > 0);

    double dataStep = (integralInfo->end - integralInfo->begin) / numThread;

    for (size_t itThread = 0; itThread < numThread; ++itThread) {
        ((struct ThreadInfo_t*)(&threadsInfo[itThread*sizeThreadsInfo]))->integralInfo.begin =
                integralInfo->begin + itThread * dataStep;
        ((struct ThreadInfo_t*)(&threadsInfo[itThread*sizeThreadsInfo]))->integralInfo.end =
                integralInfo->begin + (itThread + 1) * dataStep;
        ((struct ThreadInfo_t*)(&threadsInfo[itThread*sizeThreadsInfo]))->integralInfo.delta = integralInfo->delta;
    }
}

static void PrintThreadInfo_(void* threadsInfo, size_t sizeThreadsInfo, size_t numThread) {
    assert(threadsInfo);

    fprintf(stderr, "\n==== Dump TI ====\n");
    for (size_t itThread = 0; itThread < numThread; itThread++) {
        struct ThreadInfo_t* curThreadInfo = threadsInfo + itThread * sizeThreadsInfo;
        fprintf(stderr, "---- numThread = %zu:", itThread);
        fprintf(stderr, "from [%f] to [%f] with delta = %f\n",
                curThreadInfo->integralInfo.begin, curThreadInfo->integralInfo.end, curThreadInfo->integralInfo.delta);
        fprintf(stderr, "res = %f\n", curThreadInfo->result);
    }
}

//---------------------------------API functions------------------------------------------

enum INTEGRAL_ERROR_t IntegralCalculate(struct Integral_t integral, size_t numThreads, double* res) {
    if (!res || !integral.func) {
        return NULL_POINTER_ARG;
    }

    size_t numCores = 0;
    struct CoreInfo_t* coresInfo = GetCoresInfo(&numCores);
    if (!coresInfo) {
        return CORES_INFO_ERROR;
    }

    size_t sizeThreadsInfo = 0;
    void* threadsInfo = GetThreadsInfo_(numThreads, &sizeThreadsInfo);
    if (!threadsInfo) {
        return THREADS_INFO_ERROR;
    }
    struct IntegralInfo_t integralInfo = {.begin = integral.begin,
                                          .end = integralInfo.end,
                                          .delta = DELTA};
    UpdateThreadInfo_(threadsInfo, sizeThreadsInfo, numThreads, &integralInfo);

    pthread_t* pthreads = (pthread_t*)calloc(numThreads, sizeof(pthread_t));
    if (!pthreads) {
        perror("calloc");
        return SYSTEM_ERROR;
    }

    
}


//---------------------------------Threads------------------------------------------------

static void Calculate(struct ThreadInfo_t* threadInfo, double (*func) (double x)) {
    assert(threadInfo);

    double begin = threadInfo->integralInfo.begin;
    double end = threadInfo->integralInfo.end;
    double delta = threadInfo->integralInfo.delta;

    double result = 0.0;
    for (double x = begin; x < end; x += delta) {
        result += func(x) * delta;
    }

    threadInfo->result = result;
    return;
}



//---------------------------------Test(debug) function-----------------------------------

void test() {
    size_t sizeThreadInfo = 0;
    struct IntegralInfo_t integralInfo = {0, 8, 1};
    void* threadsInfo = GetThreadsInfo_(8, &sizeThreadInfo);
    UpdateThreadInfo_(threadsInfo, sizeThreadInfo, 8, &integralInfo);
    PrintThreadInfo_(threadsInfo, sizeThreadInfo, 8);
}



