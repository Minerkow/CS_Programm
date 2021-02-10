#pragma once

#include <stdio.h>
#include <stdbool.h>

struct AVL_Iterator_t {
    struct Node_t* it_;
};

//TODO:struct AVL_Iterator_t avlNextIt(struct AVL_Iterator_t it);
//TODO:struct AVL_Iterator_t avlPrevIt(struct AVL_Iterator_t it);

bool avlEmptyIt (struct AVL_Iterator_t it);

