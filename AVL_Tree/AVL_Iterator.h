#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "AVL_Tree.h"

struct AVL_Iterator_t ;

//*If the next element exists returns an iterator to it,
//*else returns a empty iterator
struct AVL_Iterator_t avlNextIt(struct AVL_Iterator_t it);

//*If the prev element exists returns an iterator to it,
//*else returns a empty iterator
struct AVL_Iterator_t avlPrevIt(struct AVL_Iterator_t it);

//*If iterator is empty return FALSE,
//*else returns TRUE
bool avlEmptyIt (struct AVL_Iterator_t it);

//*Check iterators for equality
bool avlEqualIt(struct AVL_Iterator_t it1, struct AVL_Iterator_t it2);

//*Return Data by iterator
int avlGetDataByIt(struct AVL_Iterator_t it);

//*Return begin iterator
struct AVL_Iterator_t avlBeginIt(struct AVL_Tree* avlTree);

//*Return end iterator
struct AVL_Iterator_t avlEndIt(struct AVL_Tree* avlTree);