#include "../headers/AVL_Tree.h"

//*Return begin iterator
static struct Node_t* avlBeginIt_(struct AVL_Tree* avlTree);

//*Return end iterator
static struct Node_t* avlEndIt_(struct AVL_Tree* avlTree);

//*If the next element exists returns an iterator to it,
//*else returns a empty iterator
static struct Node_t* avlNextIt_(struct Node_t* it);

//*If the prev element exists returns an iterator to it,
//*else returns a empty iterator
static struct Node_t* avlPrevIt_(struct Node_t* it);

//-----------------------------------------------------------------------------------------------------------


struct Node_t {
    struct Node_t* left_;
    struct Node_t* right_;
    struct Node_t* prev_;

    int height_;

    int data_;
};

struct AVL_Tree {
    struct Node_t* top_;

    size_t size_;
};

//------------------------------------------------------------------------------------------

bool avlEmptyIt(struct Node_t* it) {
    if (it == NULL) {
        return true;
    }
    return false;
}

struct Node_t* avlNextIt_(struct Node_t* it) {
    assert(it);
    if (it->prev_ == NULL) {
        it = it->right_;
        struct Node_t* tmp = it;
        while (it != NULL) {
            tmp = it;
            it = it->left_;
        }
        return tmp;
    }
    if (it->right_ != NULL) {
        it = it->right_;
        struct Node_t* tmp = it;
        while (it != NULL) {
            tmp = it;
            it = it->left_;
        }
        return tmp;
    }
    if (it->prev_->left_ == it) {
        it = it->prev_;
        return it;
    } else {
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
}

int avlGetDataByIt(struct Node_t* it) {
    if (it == NULL) {
        return NAN;
    }
    return it->data_;
}

struct Node_t* avlBeginIt_(struct AVL_Tree* avlTree) {
    assert(avlTree);
    if (!avlTree->top_) {
        return NULL;
    }
    struct Node_t* tmp = avlTree->top_;
    while (tmp->left_ != NULL) {
        tmp =tmp->left_;
    }
    return tmp;
}

struct Node_t* avlEndIt_(struct AVL_Tree* avlTree) {
    assert(avlTree);
    if (avlTree->top_ == NULL) {
        return NULL;
    }
    struct Node_t* tmp = avlTree->top_;
    while (tmp->right_ != NULL) {
        tmp =tmp->right_;
    }
    return tmp;
}

int avlGetMaxElem(struct AVL_Tree* avlTree) {
    if (!avlTree) {
        return NAN;
    }
    struct Node_t* it = avlEndIt_(avlTree);
    if (!it) {
        return NAN;
    }
    return it->data_;
}

int avlGetMinElem(struct AVL_Tree* avlTree) {
    if (!avlTree) {
        return NAN;
    }
    struct Node_t* it = avlBeginIt_(avlTree);
    if (!it) {
        return NAN;
    }
    return it->data_;
}

enum AvlError_t avlSaveInArray(struct AVL_Tree* avlTree, int* array, size_t lenArray) {
    if (!avlTree) {
        return AVLERR_NOT_INIT;
    }
    if (lenArray == 0) {
        return AVLERR_OK;
    }
    if (array == NULL) {
        return AVLERR_NULL_POINTER_ARG;
    }
    if (avlTree->top_ == NULL) {
        return AVLERR_OK;
    }
    struct Node_t* it = avlBeginIt_(avlTree);
    for (size_t i = 0; i < lenArray; ++i) {
        array[i] = avlGetDataByIt(it);
        it = avlNextIt_(it);
    }
    return AVLERR_OK;
}

enum AvlError_t avlForEach(struct AVL_Tree* avlTree, void (*foo)(struct Node_t* it, void* data), void* data) {
    if (!avlTree) {
        return AVLERR_NOT_INIT;
    }
    if (!foo) {
        return AVLERR_NULL_POINTER_ARG;
    }
    if (!avlTree->top_) {
        return AVLERR_OK;
    }
    struct Node_t* it = avlBeginIt_(avlTree);
    for (size_t i = 0; i < avlSize(avlTree); ++i) {
        foo(it, data);
        it = avlNextIt_(it);
    }
    return AVLERR_OK;
}


//struct Node_t* avlPrevIt_(struct Node_t* it) {
//    if (it == NULL) {
//        return it;
//    }
//    if (it->prev_ == NULL) {
//        it = it->left_;
//        struct Node_t* tmp = it;
//        while (it != NULL) {
//            tmp = it;
//            it = it->right_;
//        }
//        return tmp;
//    }
//    if (it->left_ != NULL) {
//        it = it->left_;
//        struct Node_t* tmp = it;
//        while (it != NULL) {
//            tmp = it;
//            it = it->right_;
//        }
//        return tmp;
//    }
//    if (it->prev_->right_ == it) {
//        it = it->prev_;
//        return it;
//    }
//    if (it->prev_ == NULL) {
//        it = it->left_;
//        return it;
//    }
//    if (it->prev_->left_ == it) {
//        struct Node_t* tmp = it->prev_;
//        while (tmp->prev_ != NULL && tmp->prev_->right_ == tmp) {
//            tmp = tmp->prev_;
//        }
//        if (tmp->prev_ == NULL) {
//            it = NULL;
//            return it;
//        }
//        it = tmp->prev_->left_;
//        return it;
//    }
//    assert(1 && "Ooooops");
//    return it;
//}