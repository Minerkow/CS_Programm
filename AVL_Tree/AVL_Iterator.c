#include "AVL_Iterator.h"
#include "AVL_Tree.h"

bool avlEmptyIt (struct AVL_Iterator_t it) {
    if (it.it_ == NULL) {
        return true;
    }
    return false;
}

struct AVL_Iterator_t avlNextIt(struct AVL_Iterator_t it) {
    struct AVL_Iterator_t res;
    res.it_ = NULL;
    if (avlEmptyIt(it)) {
        res.it_ = NULL;
        return res;
    }
    if (it.it_->prev_->left_ == it.it_) {
        res.it_ = it.it_->prev_;
        return res;
    }
    if (it.it_->prev_ == NULL) {
        res.it_ = it.it_->right_;
        return res;
    }
    if (it.it_->prev_->right_ == it.it_) {
        struct Node_t* tmp = it.it_->prev_;
        while (tmp->prev_ != NULL && tmp->prev_->left_ != tmp) {
            tmp = tmp->prev_;
        }
        if (tmp->prev_ == NULL) {
            res.it_ = NULL;
            return res;
        }
        res.it_ = tmp->prev_->right_;
        return res;
    }
    assert(1 && "Ooooops");
    return res;
}

struct AVL_Iterator_t avlPrevIt(struct AVL_Iterator_t it) {
    struct AVL_Iterator_t res;
    res.it_ == NULL;
    if (avlEmptyIt(it)) {
        return it;
    }
    if (it.it_->prev_->right_ == it.it_) {
        res.it_ = it.it_->prev_;
        return res;
    }
    if (it.it_->prev_ == NULL) {
        res.it_ = it.it_->left_;
        return res;
    }
    if (it.it_->prev_->left_ == it.it_) {
        struct Node_t* tmp = it.it_->prev_;
        while (tmp->prev_ != NULL && tmp->prev_->right_ == tmp) {
            tmp = tmp->prev_;
        }
        if (tmp->prev_ == NULL) {
            res.it_ = NULL;
            return res;
        }
        res.it_ = tmp->prev_->left_;
        return res;
    }
    assert(1 && "Ooooops");
    return res;
}

int avlGetDataByIt(struct AVL_Iterator_t it) {
    return it.it_->data_;
}

bool avlEqualIt(struct AVL_Iterator_t it1, struct AVL_Iterator_t it2) {
    if (it1.it_ == it2.it_) {
        return true;
    }
    return false;
}

struct AVL_Iterator_t avlBeginIt(struct AVL_Tree* avlTree) {
    struct Node_t* tmp = avlTree->top_;
    while (tmp->left_ != NULL) {
        tmp =tmp->left_;
    }
    struct AVL_Iterator_t res = {tmp};
    return res;
}

struct AVL_Iterator_t avlEndIT(struct AVL_Tree* avlTree) {
    struct Node_t* tmp = avlTree->top_;
    while (tmp->right_ != NULL) {
        tmp =tmp->right_;
    }
    struct AVL_Iterator_t res = {tmp};
    return res;
}