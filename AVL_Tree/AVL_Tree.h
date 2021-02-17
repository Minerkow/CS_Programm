#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "AVL_Iterator.h"
#include "Error.h"

struct AVL_Tree;

struct Node_t;

//enum AvlError_t avlInitByArray(struct AVL_Tree* avlTree);
void avlInit(struct AVL_Tree* avlTree);

int avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize);

//*Insert data in tree and return iterator on them,
//*if such data is already stored in the tree, return an iterator on it.
struct AVL_Iterator_t avlInsert(struct AVL_Tree* avlTree, int data);

//*Erase elem by value
void avlEraseByValue(struct AVL_Tree* avlTree, int data);

//*Erase elem with iterator
void avlEraseByIt(struct AVL_Tree* avlTree, struct AVL_Iterator_t it);

size_t avlSize(struct AVL_Tree* avlTree);

//TODO:bool avlClear(struct AVL_Tree* avlTree);

//*If the data is in the table, it returns an iterator on it,
//*otherwise it returns a null iterator
struct AVL_Iterator_t avlFind(struct AVL_Tree* avlTree, int data);

//*Check on empty
bool avlEmpty(struct AVL_Tree* avlTree);

//*Check on ERROR
void avlPerror(struct AVL_Tree* avlTree);

void avlPrintTree_ (struct Node_t* top);


