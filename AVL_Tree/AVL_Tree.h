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

    void* data_;
    size_t dataSize_;
};

struct AVL_Tree {
    int (*Compare_)(const void*, const void*);
    struct Node_t* top_;
};

enum AvlError_t avlInit(struct AVL_Tree* avlTree, int (*Compare)(const void*, const void*));

//TODO:bool avlLoadFromArray(struct AVL_Tree* avlTree, void* array, size_t arraySize, size_t objectSize);

struct AVL_Iterator_t avlInsert(struct AVL_Tree* avlTree, void* data, size_t objectSize);

//TODO:void* avlGetDataFromIt(struct AVL_Tree avlTree, struct AVL_Iterator_t it);

//TODO:struct AVL_Iterator_t avlEraseByValue(struct AVL_Tree* avlTree, void* data, size_t objectSize);

//TODO:struct AVL_Iterator_t avlEraseByIt(struct AVL_Tree* avlTree, struct AVL_Iterator_t it);

//TODO:struct AVL_Iterator_t avlBegin(struct AVL_Tree* avlTree);

//TODO:struct AVL_Iterator_t avlEnd(struct AVL_Tree* avlTree);

//TODO:bool avlEmpty(struct AVL_Tree* avlTree);

//TODO:size_t avlSize(struct AVL_Tree* avlTree);

//TODO:bool avlClear(struct AVL_Tree* avlTree);

struct AVL_Iterator_t avlFind(struct AVL_Tree* avlTree, void* data, size_t objectSize);

struct Node_t* avlCreateNode_(void* data, size_t objectSize);

enum AvlError_t avlBalancing(struct Node_t* top);

enum AvlError_t avlSmallLeftRotation_ (struct Node_t* top); //TODO

enum AvlError_t avlBigLeftRotation_ (struct Node_t* top); //TODO

enum AvlError_t avlSmallRightRotation_ (struct Node_t* top); //TODO

enum AvlError_t avlBigRightRotation_ (struct Node_t* top); //TODO