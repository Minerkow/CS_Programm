#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "AVL_Tree.h"

struct AVL_Iterator_t {
    struct Node_t* it_;
};

//*If the next element exists returns an iterator to it,
//*else returns a empty iterator
struct AVL_Iterator_t avlNextIt(struct AVL_Iterator_t it);

//*If the prev element exists returns an iterator to it,
//*else returns a empty iterator
struct AVL_Iterator_t avlPrevIt(struct AVL_Iterator_t it);

//*If iterator is empty return FALSE,
//*else returns TRUE
bool avlEmptyIt (struct AVL_Iterator_t it);

bool avlEqualIt(struct AVL_Iterator_t it1, struct AVL_Iterator_t it2);

int avlGetDataByIt(struct AVL_Iterator_t it);

struct AVL_Iterator_t avlBeginIt(struct AVL_Tree* avlTree);

struct AVL_Iterator_t avlEndIT(struct AVL_Tree* avlTree);