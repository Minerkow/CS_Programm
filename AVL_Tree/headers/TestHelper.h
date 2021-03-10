#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "AVL_Tree.h"

//#ifdef TEST
#define CALLOC(x, y) CallocHelper((x), (y))
//#else
//#define CALLOC(x, y) calloc((x), (y))
//#endif

void* CallocHelper(size_t nmemb, size_t size);

enum AvlError_t avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize);