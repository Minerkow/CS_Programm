#include <stdio.h>
#include "ParseThreadInfo.h"

int main() {
    size_t size = 0;
    struct CoreInfo_t* coreInfo = GetCoresInfo(&size);
    //fprintf(stderr, "\n%p\n", coreInfo);
    PrintCoresInfo(coreInfo, size);
    return 0;
}
