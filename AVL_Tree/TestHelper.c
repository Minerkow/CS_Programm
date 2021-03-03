#include "TestHelper.h"

void* CallocHelper(size_t nmemb, size_t size) {
    static int flag = 0;
    if (flag == 0 || flag == 2 || flag == 5 || flag == 7) {
        flag++;
        return NULL;
    } else {
        flag++;
        return calloc(nmemb, size);
    }
}

enum AvlError_t avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize) {
    if (array == NULL) {
        return AVLERR_NULL_POINTER_ARG;
    }
    if (avlTree == NULL) {
        return AVLERR_NOT_INIT;
    }
    if (arraySize == 0) {
        return AVLERR_OK;
    }
    for (size_t i = 0; i < arraySize; ++i) {
        if (avlInsert(avlTree, array[i]) != AVLERR_OK) {
            return AVLERR_INSERT;
        }
    }
    return AVLERR_OK;
}

