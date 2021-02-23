#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "AVL_Iterator.h"
#include "Error.h"

struct AVL_Tree;

struct Node_t;

//enum AvlError_t avlInitByArray(struct AVL_Tree* avlTree);
struct AVL_Tree* avlInit();

//*Load data to AVL_Tree from array
int avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize);

//*Insert data in tree and return iterator on them,
//*if such data is already stored in the tree, return an iterator on it.
void avlInsert(struct AVL_Tree* avlTree, int data);

//*Erase elem by value
void avlEraseByValue(struct AVL_Tree* avlTree, int data);

size_t avlSize(struct AVL_Tree* avlTree);

//*Clear all tree
int avlClear(struct AVL_Tree* avlTree);

//*Check on empty
bool avlEmpty(struct AVL_Tree* avlTree);

//*Check on ERROR
void avlPerror(struct AVL_Tree* avlTree);

//*Return max elem
int avlGetMaxElem(struct AVL_Tree* avlTree);

//*Return min elem
int avlGetMinElem(struct AVL_Tree* avlTree);



#ifdef DEBUG
void avlPrintTree_ (struct Node_t* top);
#endif

