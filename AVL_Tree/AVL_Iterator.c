#include "AVL_Iterator.h"
#include "AVL_Tree.h"


//*If the next element exists returns an iterator to it,
//*else returns a empty iterator
static struct Node_t* avlNextIt_(struct Node_t* it);

//*If the prev element exists returns an iterator to it,
//*else returns a empty iterator
static struct Node_t* avlPrevIt_(struct Node_t* it);

//*If iterator is empty return FALSE,
//*else returns TRUE
static bool avlEmptyIt_ (struct Node_t* it);

//*Check iterators for equality
static bool avlEqualIt_(struct Node_t* it1, struct Node_t* it2);

//*Return Data by iterator
static int avlGetDataByIt_(struct Node_t* it);

//*Return begin iterator
static struct Node_t* avlBeginIt_(struct AVL_Tree* avlTree);

//*Return end iterator
static struct Node_t* avlEndIt_(struct AVL_Tree* avlTree);

//-----------------------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------

bool avlEmptyIt_(struct Node_t* it) {
    if (it == NULL) {
        return true;
    }
    return false;
}

struct Node_t* avlNextIt_(struct Node_t* it) {
    if (it == NULL) {
        return it;
    }
    if (it->prev_ == NULL) {
        it = it->right_;
        return it;
    }
    if (it->right_ != NULL) {
        it = it->right_;
        return it;
    }
    if (it->prev_->left_ == it) {
        it = it->prev_;
        return it;
    }
    if (it->prev_->right_ == it) {
        struct Node_t* tmp = it->prev_;
        while (tmp->prev_ != NULL && tmp->prev_->left_ != tmp) {
            tmp = tmp->prev_;
        }
        if (tmp->prev_ == NULL) {
            it = NULL;
            return it;
        }
        it = tmp->prev_;
        return it;
    }
    assert(1 && "Ooooops");
    return it;
}

struct Node_t* avlPrevIt_(struct Node_t* it) {
    if (it == NULL) {
        return it;
    }
    if (it->prev_ == NULL) {
        it = it->left_;
        return it;
    }
    if (it->prev_->right_ == it) {
        it = it->prev_;
        return it;
    }
    if (it->prev_ == NULL) {
        it = it->left_;
        return it;
    }
    if (it->prev_->left_ == it) {
        struct Node_t* tmp = it->prev_;
        while (tmp->prev_ != NULL && tmp->prev_->right_ == tmp) {
            tmp = tmp->prev_;
        }
        if (tmp->prev_ == NULL) {
            it = NULL;
            return it;
        }
        it = tmp->prev_->left_;
        return it;
    }
    assert(1 && "Ooooops");
    return it;
}

int avlGetDataByIt_(struct Node_t* it) {
    if (it == NULL) {
        return NAN;
    }
    return it->data_;
}

bool avlEqualIt_(struct Node_t* it1, struct Node_t* it2) {
    if (it1 == it2) {
        return true;
    }
    return false;
}

struct Node_t* avlBeginIt_(struct AVL_Tree* avlTree) {
    if (avlTree == NULL) {
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }
    struct Node_t* tmp = avlTree->top_;
    while (tmp->left_ != NULL) {
        tmp =tmp->left_;
    }
    return tmp;
}

struct Node_t* avlEndIt_(struct AVL_Tree* avlTree) {
    if (avlTree == NULL) {
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }
    struct Node_t* tmp = avlTree->top_;
    while (tmp->right_ != NULL) {
        tmp =tmp->right_;
    }
    return tmp;
}

int avlGetMaxElem(struct AVL_Tree* avlTree) {
    struct Node_t* it = avlEndIt_(avlTree);
    if (avlTree->avlErno_ != AVLERR_OK) {
        return NAN;
    }
    return it->data_;
}

int avlGetMinElem(struct AVL_Tree* avlTree) {
    struct Node_t* it = avlBeginIt_(avlTree);
    if (avlTree->avlErno_ != AVLERR_OK) {
        return NAN;
    }
    return it->data_;
}