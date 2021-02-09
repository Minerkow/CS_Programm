#include "AVL_Tree.h"
#include "AVL_Iterator.h"
#include "Error.h"

enum AvlError_t avlInit(struct AVL_Tree* avlTree, int (*Compare)(const void*, const void*)) {
    if (!avlTree && !Compare) {
        return AVL_NOT_INIT;
    }
    avlTree->Compare_ = Compare;
    return AVL_OK;
}

struct AVL_Iterator_t avlInsert(struct AVL_Tree* avlTree, void* data, size_t objectSize) {
    struct AVL_Iterator_t res;
    if (avlTree->top_ == NULL) {
        avlTree->top_ = avlCreateNode_(data, objectSize);
        avlTree->top_->balance_factor = 0;
        avlTree->top_->prev_ = NULL;
        if (!avlTree->top_) {
            res.it_ = avlTree->top_;
            return res;
        } else {
            res.it_ = NULL;
            return res;
        }
    }
    struct Node_t* tmp = avlTree->top_;
    struct Node_t* current = avlTree->top_;
    while (tmp != NULL) {
        current = tmp;
        switch (avlTree->Compare_(data, tmp->data_)) {
            case 1:
                tmp = tmp->right_; break;
            case -1:
                tmp = tmp->left_; break;
            case 0:
                res.it_ = tmp;
                return res;
            default: assert(1 && "Oooops");
        }
        if (avlTree->Compare_(data, tmp->data_)) {
            tmp = tmp->right_;
        }
        if (!avlTree->Compare_(data, tmp->data_)) {
            tmp = tmp->left_;
        }
    }

    assert(avlTree->Compare_(data, tmp->data_) == 0);

    if (avlTree->Compare_(data, tmp->data_)) {
        current->right_ = avlCreateNode_(data, objectSize);
    } else {
        current->left_ = avlCreateNode_(data, objectSize);
    }
    //TODO
}

struct AVL_Iterator_t avlFind(struct AVL_Tree* avlTree, void* data, size_t objectSize) {
    //TODO:avlFind
}

struct Node_t* avlCreateNode_(void* data, size_t objectSize) {
    struct Node_t* node = calloc(1, sizeof(struct Node_t));
    node->dataSize_ = objectSize;
    node->data_ = calloc(1, objectSize);
    memcpy(node->data_, data, objectSize);
    return node;
}

enum AvlError_t avlBalancing(struct Node_t* top) {
    if (!top) {
        return AVL_NULL_POINTER_ARG;
    }
    if (top->balance_factor == 2) {
        if (top->right_->balance_factor >= 0) {
            return avlSmallLeftRotation_(top);
        } else {
            return avlBigLeftRotation_(top);
        }
    }
    if (top->balance_factor == -2) {
        if (top->right_->balance_factor >= 0) {
            return avlSmallRightRotation_(top);
        } else {
            return avlBigRightRotation_(top);
        }
    }
    return AVL_OK;
}

