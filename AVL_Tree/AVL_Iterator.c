#include "AVL_Iterator.h"

bool avlEmptyIt (struct AVL_Iterator_t it) {
    if (it.it_ == NULL) {
        return false;
    }
    return true;
}
