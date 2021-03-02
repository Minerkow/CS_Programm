#include "AVL_Tree.h"

int main() {
    struct AVL_Tree* avlTree = avlInit();
    int input[] = {27, 80, 8, 42, 37, 59, 90, 42, 90, 46, 92, 22, 18, 0, 99, 98, 92, 18, 16, 2, 45, 75, 30, 27, 23, 34, 50, 88, 53, 75, 73, 80, 7, 33, 22, 44, 92, 65, 86, 82};
    int res[31] = {};
    avlLoadFromArray(avlTree, input, 40);
    avlSaveInArray(avlTree, res, 31);
    avlClear(avlTree);
    return 0;
}
