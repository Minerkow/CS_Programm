#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Error.h"

struct AVL_Tree;

struct Node_t;

//enum AvlError_t avlInitByArray(struct AVL_Tree* avlTree);
struct AVL_Tree* avlInit();

//*Load data to AVL_Tree from array
enum AvlError_t avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize);

//*Insert data in tree and return iterator on them,
//*if such data is already stored in the tree, return an iterator on it.
enum AvlError_t avlInsert(struct AVL_Tree* avlTree, int data);

//*Erase elem by value
enum AvlError_t avlEraseByValue(struct AVL_Tree* avlTree, int data);

//*Return size of avlTree, if avlTree not init return NAN
size_t avlSize(struct AVL_Tree* avlTree);

//*Clear all tree
int avlClear(struct AVL_Tree* avlTree);

//*Check on empty
bool avlEmpty(struct AVL_Tree* avlTree);

//*Check on ERROR
void avlPerror(enum AvlError_t err);

//*Return max elem
int avlGetMaxElem(struct AVL_Tree* avlTree);

//*Return min elem
int avlGetMinElem(struct AVL_Tree* avlTree);

//*Save in array first lenArray elem,
//*else return NULL
enum AvlError_t avlSaveInArray(struct AVL_Tree* avlTree, int* array, size_t lenArray);

void avlForEach(void (*foo)(struct Node_t* it, void* data), void* data);

//#ifdef DEBUG
void avlPrintTree_(struct AVL_Tree* avlTree);
struct Node_t* avlFind_(struct AVL_Tree* avlTree, int data);
//#endif



