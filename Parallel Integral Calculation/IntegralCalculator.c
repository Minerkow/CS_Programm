#include "IntegralCalculator.h"
#include "ParseInfo.h"

const double DELTA = 0.0001;

struct IntegralInfo_t {
    double begin;
    double end;
    double delta;
    double (*func) (double x);
};

struct ThreadInfo_t {
    double result;
    struct IntegralInfo_t integralInfo;
};

struct CoreInfo_t {
    size_t coreId;
    size_t numCpu;
    size_t* cpusNum;
    size_t numAllocCpus;
    size_t numWorkingCpu;
};

//---------------------------------Get Thread Info-----------------------------------

static void* GetThreadsInfo_(size_t numThread, size_t* sizeThreadsInfo);
static void DistributeLoadThreads_(void* threadsInfo, size_t sizeThreadsInfo, size_t numThread,
                                   struct IntegralInfo_t* integralInfo);
static void Calculate(struct ThreadInfo_t* threadInfo);
static int InitPthreadAttr(struct CoreInfo_t* coreInfo, pthread_attr_t* attr);
static size_t GetNumHyperThreads_(struct CoreInfo_t* coreInfo, size_t numCore);
static size_t GetCoreId_(struct CoreInfo_t* coreInfo, size_t numCore, size_t threadNum);
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
static void DistributeLoadThreads_(void* threadsInfo, size_t sizeThreadsInfo, size_t numThread,
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
        ((struct ThreadInfo_t*)(&threadsInfo[itThread*sizeThreadsInfo]))->integralInfo.func = integralInfo->func;
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
    //PrintCoresInfo(coresInfo, numCores);
    size_t sizeThreadInfo = 0;
    void* threadsInfo = GetThreadsInfo_(numThreads, &sizeThreadInfo);
    if (!threadsInfo) {
        return THREADS_INFO_ERROR;
    }
    struct IntegralInfo_t integralInfo = {.begin = integral.begin,
                                          .end = integral.end,
                                          .delta = DELTA,
                                          .func = integral.func};
    DistributeLoadThreads_(threadsInfo, sizeThreadInfo, numThreads, &integralInfo);
    //PrintThreadInfo_(threadsInfo, sizeThreadInfo, numThreads);
    //size_t numHyperThread = GetNumHyperThreads_(coresInfo, numCores);
    pthread_t* pthreads = (pthread_t*)calloc(numThreads, sizeof(pthread_t));
    if (!pthreads) {
        perror("calloc");
        return SYSTEM_ERROR;
    }

    for (size_t itThread = 0; itThread < numThreads; ++itThread) {
        size_t curCore = GetCoreId_(coresInfo, numCores, itThread);
        fprintf(stderr, "[%zu]", curCore);
        struct CoreInfo_t* curCoreInfo = GetCoreInfoById(coresInfo, numCores, curCore);
        if (!curCoreInfo) {
            return CORES_INFO_ERROR;
        }

        pthread_attr_t pthreadAttr = {};
        if (InitPthreadAttr(curCoreInfo, &pthreadAttr) < 0) {
            return SYSTEM_ERROR;
        }

        if (pthread_create(&pthreads[itThread], &pthreadAttr, Calculate, threadsInfo + itThread * sizeThreadInfo)) {
            return SYSTEM_ERROR;
        }

        pthread_attr_destroy(&pthreadAttr);
    }


    for (size_t itThread = 0; itThread < numThreads; ++itThread) {
        if (pthread_join(pthreads[itThread], NULL) != 0) {
            return SYSTEM_ERROR;
        }
        *res += ((struct ThreadInfo_t*)(threadsInfo + itThread * sizeThreadInfo))->result;
    }

    PrintThreadInfo_(threadsInfo, sizeThreadInfo, numThreads);

    PrintCoresInfo(coresInfo, numCores);

    free(pthreads);
    free(threadsInfo);
    FreeCoresInfo(coresInfo, numCores);
    return SUCCESS;
}


//---------------------------------Threads------------------------------------------------

static void Calculate(struct ThreadInfo_t* threadInfo) {
    assert(threadInfo);

    double begin = threadInfo->integralInfo.begin;
    double end = threadInfo->integralInfo.end;
    double delta = threadInfo->integralInfo.delta;

    double result = 0.0;
    for (double x = begin; x < end; x += delta) {
        result += threadInfo->integralInfo.func(x) * delta;
    }

    threadInfo->result = result;
    return;
}

static int InitPthreadAttr(struct CoreInfo_t* coreInfo, pthread_attr_t* attr) {
    assert(coreInfo);
    assert(attr);
    assert(coreInfo->cpusNum);

    size_t itCpu = coreInfo->numWorkingCpu % coreInfo->numCpu;
    size_t cpuId = coreInfo->cpusNum[itCpu];

    cpu_set_t cpuSet = {};
    CPU_ZERO(&cpuSet);
    CPU_SET(cpuId, &cpuSet);

    if (pthread_attr_setaffinity_np(attr, sizeof(cpuSet), &cpuSet) != 0) {
        return -1;
    }

    coreInfo->numWorkingCpu++;
    return 1;
}

static size_t GetNumHyperThreads_(struct CoreInfo_t* coreInfo, size_t numCore) {
    size_t res = 0;
    for (size_t itCore = 0; itCore < numCore; ++itCore) {
        res += coreInfo[itCore].numCpu;
    }
    return res;
}

static size_t GetCoreId_(struct CoreInfo_t* coreInfo, size_t numCore, size_t threadNum) {
    size_t counter = threadNum;
    while (1) {
        for (size_t itCore = 0; itCore < numCore; ++itCore) {
            if (counter < coreInfo[itCore].numCpu) {
                return itCore;
            }
            counter -= coreInfo[itCore].numCpu;
        }
    }
}


//---------------------------------Test(debug) function-----------------------------------

//void test() {
//    size_t sizeThreadInfo = 0;
//    struct IntegralInfo_t integralInfo = {0, 8, 1};
//    void* threadsInfo = GetThreadsInfo_(8, &sizeThreadInfo);
//    DistributeLoadThreads_(threadsInfo, sizeThreadInfo, 8, &integralInfo);
//    PrintThreadInfo_(threadsInfo, sizeThreadInfo, 8);
//}



