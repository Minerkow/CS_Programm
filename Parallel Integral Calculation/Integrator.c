#include "Integrator.h"

struct CoreInfo_t {
    size_t coreId;

};

//-----------------------------------------------------------------------------------

static const char TOPOLOGY_PATH_[] = "sys/devices/system/cpu/cpu%zu/topology/core_id";
enum {PARSE_ERROR = -1};

//-----------------------------------------------------------------------------------

static struct CoreInfo_t* CreateCoresInfo_(size_t* size);
static size_t GetCoreId_(size_t coreNum);
static struct CoreInfo_t* UpdateCoreInfo_(struct CoreInfo_t* coresInfo, size_t size, size_t coreId, size_t numCores);
static struct CoreInfo_t* GetCoreInfo_(struct CoreInfo_t* coresInfo, size_t size, size_t coreId);

//-----------------------------------------------------------------------------------

static struct CoreInfo_t* CreateCoresInfo_(size_t* size) {
    assert(size);
    long ret = sysconf(_SC_NPROCESSORS_CONF);
    if (ret < 0) {
        perror("sysconf(_SC_NPROCESSORS_CONF):");
        return NULL;
    }

    size_t numCores = (size_t) ret;
    struct CoreInfo_t *coresInfo = (struct CoreInfo_t *) calloc(numCores, sizeof(struct CoreInfo_t));
    if (!coresInfo) {
        perror("calloc");
        return NULL;
    }

    for (size_t itCore = 0; itCore < numCores; ++itCore) {
        size_t coreId = GetCoreId_(itCore);
        if (coreId == PARSE_ERROR) {
            return NULL; //TODO: free cores info
        }

    }
}

static size_t GetCoreId_(size_t coreNum) {
    size_t coreId = PARSE_ERROR;
    char curTopologyPath[sizeof(TOPOLOGY_PATH_)] = {};
    sprintf(curTopologyPath, TOPOLOGY_PATH_, coreNum);

    FILE* topologyFile = fopen(curTopologyPath, "r");
    if (!topologyFile) {
        fprintf(stderr, "ParseError");
        return PARSE_ERROR;
    }

    fscanf(topologyFile, "%zu", &coreId);
    fclose(topologyFile);
    return coreId;
}

static struct CoreInfo_t* UpdateCoreInfo_(struct CoreInfo_t* coresInfo, size_t size, size_t coreId, size_t numCores) {
    assert(coresInfo);

    struct CoreInfo_t* curCoreInfo = GetCoreInfo_(coresInfo, size, coreId);

}

static struct CoreInfo_t* GetCoreInfo_(struct CoreInfo_t* coresInfo, size_t size, size_t coreId) {
    assert(coresInfo);

    struct CoreInfo_t* curCoreInfo = NULL;
    for (size_t itCore = 0; itCore < size; ++itCore) {
        if (coresInfo[itCore].coreId == coreId) {
            return &coresInfo[itCore];
        }
    }
    return NULL;
}
