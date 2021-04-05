#include "ParseInfo.h"

struct CoreInfo_t {
    size_t coreId;
    size_t numCpu;
    size_t* cpusNum;
    size_t numAllocCpus;
    size_t numWorkingCpu;
};


//-----------------------------------------------------------------------------------

static const char TOPOLOGY_PATH_[] = "/sys/devices/system/cpu/cpu%zu/topology/core_id";
enum {PARSE_ERROR = -1};

//---------------------------------Parse Core Info-----------------------------------

static size_t GetCoreId_(size_t coreNum);
static struct CoreInfo_t* UpdateCoreInfo_(struct CoreInfo_t* coresInfo, size_t size, size_t coreId, size_t numCpu);
static struct CoreInfo_t* CreateCoreInfo_(struct CoreInfo_t* coresInfo, size_t size);
static size_t ShrinkToFitCoreInfos(struct CoreInfo_t** coresInfo, size_t curSize);

//---------------------------------Parse Core Info-----------------------------------

struct CoreInfo_t* GetCoresInfo(size_t* size) {
    assert(size);
    long ret = sysconf(_SC_NPROCESSORS_CONF);
    if (ret < 0) {
        perror("sysconf(_SC_NPROCESSORS_CONF):");
        return NULL;
    }

    size_t numCPU = (size_t) ret;
    struct CoreInfo_t *coresInfo = (struct CoreInfo_t *) calloc(numCPU, sizeof(struct CoreInfo_t));
    if (!coresInfo) {
        perror("calloc");
        return NULL;
    }

    for (size_t itCPU = 0; itCPU < numCPU; ++itCPU) {
        size_t curCoreId = GetCoreId_(itCPU);
        if (curCoreId == PARSE_ERROR) {
            //TODO: free cores info
            return NULL;
        }

        struct CoreInfo_t* curCoreInfo = UpdateCoreInfo_(coresInfo, numCPU, curCoreId, itCPU);
        if (!curCoreInfo) {
            //TODO: free cores info
            return NULL;
        }
    }
    *size = ShrinkToFitCoreInfos(&coresInfo, numCPU);

    return coresInfo;
}

static size_t GetCoreId_(size_t coreNum) {
    size_t coreId = PARSE_ERROR;
    char curTopologyPath[sizeof(TOPOLOGY_PATH_)] = {};
    sprintf(curTopologyPath, TOPOLOGY_PATH_, coreNum);
    //fprintf(stderr, "\n%s\n", curTopologyPath);

    FILE* topologyFile = fopen(curTopologyPath, "r");
    if (!topologyFile) {
        fprintf(stderr, "ParseError");
        return PARSE_ERROR;
    }

    fscanf(topologyFile, "%zu", &coreId);
    fclose(topologyFile);
    return coreId;
}

static struct CoreInfo_t* UpdateCoreInfo_(struct CoreInfo_t* coresInfo, size_t size, size_t coreId, size_t numCpu) {
    assert(coresInfo);

    struct CoreInfo_t* curCoreInfo = GetCoreInfoById(coresInfo, size, coreId);

    if (curCoreInfo == NULL || curCoreInfo->numCpu == 0) {
        curCoreInfo = CreateCoreInfo_(coresInfo, size);
        if (curCoreInfo == NULL) {
            return NULL;
        }
        curCoreInfo->coreId = coreId;
    }

    if (curCoreInfo->numCpu == curCoreInfo->numAllocCpus) {
        curCoreInfo->cpusNum = (size_t*) realloc(curCoreInfo->cpusNum, 2 * curCoreInfo->numAllocCpus * sizeof(size_t));
        if (curCoreInfo->cpusNum == NULL) {
            perror("calloc");
            return NULL;
        }
        curCoreInfo->numAllocCpus = 2 * curCoreInfo->numAllocCpus;
    }

    curCoreInfo->cpusNum[curCoreInfo->numCpu] = numCpu;
    curCoreInfo->numCpu++;
    return curCoreInfo;
}

struct CoreInfo_t* GetCoreInfoById(struct CoreInfo_t* coresInfo, size_t size, size_t coreId) {
    assert(coresInfo);
    for (size_t itCore = 0; itCore < size; ++itCore) {
        if (coresInfo[itCore].coreId == coreId) {
            return &coresInfo[itCore];
        }
    }
    return NULL;
}

static struct CoreInfo_t* CreateCoreInfo_(struct CoreInfo_t* coresInfo, size_t size) {
    assert(coresInfo);
    struct CoreInfo_t* curCoreInfo = NULL;

    for (size_t itCoreInfo = 0; itCoreInfo < size; ++itCoreInfo) {
        if (coresInfo[itCoreInfo].numCpu == 0) {
            curCoreInfo = &coresInfo[itCoreInfo];
            break;
        }
    }
    curCoreInfo->cpusNum = (size_t*)calloc(1, sizeof(size_t));
    if (curCoreInfo->cpusNum == NULL) {
        perror("calloc");
        return  NULL;
    }
    curCoreInfo->numAllocCpus = 1;
    return curCoreInfo;
}

static size_t ShrinkToFitCoreInfos(struct CoreInfo_t** ptrCoresInfo, size_t curSize) {
   assert(ptrCoresInfo);

   struct CoreInfo_t* coreInfo = *ptrCoresInfo;
    size_t newSize = curSize;
    for (size_t itCoreInfo = 0; itCoreInfo < curSize; ++itCoreInfo) {
        if (coreInfo[itCoreInfo].numCpu == 0) {
            free(coreInfo[itCoreInfo].numCpu);
            newSize--;
        }
    }
    coreInfo = (struct CoreInfo_t*)realloc(coreInfo, newSize * sizeof(struct CoreInfo_t));
    if (coreInfo == NULL) {
        perror("realloc");
        return 0;
    }
    *ptrCoresInfo = coreInfo;
    return newSize;
}

void FreeCoresInfo(struct CoreInfo_t* coreInfo, size_t size) {
    assert(coreInfo);

    for (size_t itCoreInfo = 0; itCoreInfo < size; ++itCoreInfo) {
        free(coreInfo[itCoreInfo].cpusNum);
    }
    free(coreInfo);
}

void PrintCoresInfo(const struct CoreInfo_t* coreInfo, size_t size)
{
    assert(coreInfo);

    fprintf(stderr, "\n====== Cores Info ======\n");
    for (size_t itCoresInfo = 0; itCoresInfo < size; ++itCoresInfo) {
        fprintf(stderr, "\n--- Core id = %zu ---\n", coreInfo[itCoresInfo].coreId);
        fprintf(stderr, "num CPUs = %zu, ",      coreInfo[itCoresInfo].numCpu);
        fprintf(stderr, "num alloc CPUs = %zu, ", coreInfo[itCoresInfo].numAllocCpus);
        //fprintf(stderr, "num busy CPUs = %zu:\n", CIs[iNumCI].nBusyCpus);
        fprintf(stderr, "numCpus : [");
        //assert(coreInfo[itCoresInfo].cpusNum);
        for (size_t itCpu = 0; itCpu < coreInfo[itCoresInfo].numCpu; itCpu++)
            fprintf(stderr, " %zu",  coreInfo[itCoresInfo].cpusNum[itCpu]);
            fprintf(stderr, "]\n");
    }
}


