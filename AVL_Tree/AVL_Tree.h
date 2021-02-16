#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "AVL_Iterator.h"
#include "Error.h"

struct Node_t {
    struct Node_t* left_;
    struct Node_t* right_;
    struct Node_t* prev_;

    int balance_factor;

    int data_;
};

struct AVL_Tree {
    struct Node_t* top_;

    enum AvlError_t avlErno_;
    size_t size_;
};

//enum AvlError_t avlInitByArray(struct AVL_Tree* avlTree);//TODO
void avlInit(struct AVL_Tree* avlTree);

int avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize);

//*Insert data in tree and return iterator on them,
//*if such data is already stored in the tree, return an iterator on it.
struct AVL_Iterator_t avlInsert(struct AVL_Tree* avlTree, int data);

//TODO:void* avlGetDataFromIt(struct AVL_Tree avlTree, struct AVL_Iterator_t it);

//TODO:struct AVL_Iterator_t avlEraseByValue(struct AVL_Tree* avlTree, void* data, size_t objectSize);

//TODO:struct AVL_Iterator_t avlEraseByIt(struct AVL_Tree* avlTree, struct AVL_Iterator_t it);

//TODO:struct AVL_Iterator_t avlBegin(struct AVL_Tree* avlTree);

//TODO:struct AVL_Iterator_t avlEnd(struct AVL_Tree* avlTree);

//TODO:bool avlEmpty(struct AVL_Tree* avlTree);

//TODO:size_t avlSize(struct AVL_Tree* avlTree);

//TODO:bool avlClear(struct AVL_Tree* avlTree);

//*if the data is in the table, it returns an iterator on it,
//*otherwise it returns a null iterator
struct AVL_Iterator_t avlFind(struct AVL_Tree* avlTree, int data);

//*check on empty
bool avlEmpty(struct AVL_Tree* avlTree);

void avlPerror(struct AVL_Tree* avlTree);

void avlPrintTree_ (struct Node_t* top);

