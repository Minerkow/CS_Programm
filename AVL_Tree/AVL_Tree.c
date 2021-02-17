#include "AVL_Tree.h"
#include "AVL_Iterator.h"
#include "Error.h"

struct AVL_Iterator_t {
    struct Node_t* it_;
};

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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static struct Node_t* avlSmallLeftRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO:Unit tests

static struct Node_t* avlBigLeftRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO:Unit tests

static struct Node_t* avlSmallRightRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO:Unit tests

static struct Node_t* avlBigRightRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO

static int avlGetBalanceFactor_(struct Node_t* top);

static struct Node_t* avlCreateNode_(int data);

static struct Node_t* avlBalancing_(struct AVL_Tree* avlTree, struct Node_t* top);

static void avlNodeBalancing_(struct Node_t* node);

//void avlPrintTree_ (struct Node_t* top);
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize) {
    if (avlTree == NULL || array == NULL || arraySize == 0) {
        return AVLERR_NULL_POINTER_ARG;
    }
    for (size_t i = 0; i < arraySize; ++i) {
        struct AVL_Iterator_t it = avlInsert(avlTree, array[i]);
        if (avlEmptyIt(it)) {
            fprintf(stderr, "AVL Insert ERROR");
            avlTree->avlErno_ = AVLERR_INSERT;
            return AVLERR;
        }
    }
    return AVLERR_OK;
}


struct AVL_Iterator_t avlInsert(struct AVL_Tree* avlTree, int data) {
    struct AVL_Iterator_t res;
    if (avlTree->top_ == NULL) {
        avlTree->top_ = avlCreateNode_(data);
        avlTree->top_->balance_factor = 0;
        avlTree->top_->prev_ = NULL;
        avlTree->avlErno_ = AVLERR_OK;
        res.it_ = avlTree->top_;
        avlTree->size_ = 1;
        return res;
    }
    struct Node_t* tmp = avlTree->top_;
    struct Node_t* current = avlTree->top_;
    while (tmp != NULL) {
        current = tmp;
        if (data > tmp->data_) {
            tmp = tmp->right_;
            continue;
        }
        if (data < tmp->data_) {
            tmp = tmp->left_;
            continue;
        }
        if (data == tmp->data_) {
            res.it_ = tmp;
            return res;
        }
    }
    struct Node_t* newNode = avlCreateNode_(data);
    newNode->prev_ = current;

    if (data > current->data_) {
        avlTree->size_++;
        current->right_ = newNode;
    } else {
        avlTree->size_++;
        current->left_ = newNode;
    }
    res.it_ = newNode;
    avlNodeBalancing_(current);

    while (current != NULL) {
        current = avlBalancing_(avlTree, current);

        enum AvlError_t err = avlTree->avlErno_;
        if (err != AVLERR_OK) {
            fprintf(stderr, "Insert ERROR\n");
            avlTree->avlErno_ = err;
            res.it_ = NULL;
            return res;
        }
        current = current->prev_;
    }

    return res;
}

struct AVL_Iterator_t avlFind(struct AVL_Tree* avlTree, int data) {
    struct AVL_Iterator_t res;

    if (avlTree == NULL) {
        fprintf(stderr, "NULL argument in avlFind");
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        res.it_ = NULL;
        return res;
    }

    struct Node_t* tmp = avlTree->top_;

    while (tmp != NULL) {
        if (data > tmp->data_) {
            tmp = tmp->right_;
            continue;
        }
        if (data < tmp->data_) {
            tmp = tmp->left_;
            continue;
        }
        if (data == tmp->data_) {
            res.it_ = tmp;
            return res;
        }
    }
    res.it_ = NULL;
    avlTree->avlErno_ = AVLERR_DATA_NOT_FOUND;
    return res;
}

bool avlEmpty(struct AVL_Tree* avlTree) {
    if (avlTree->top_ == NULL) {
        return true;
    }
    return false;
}

struct Node_t* avlCreateNode_(int data) {
    struct Node_t* node = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    node->data_ = data;
    return node;
}

struct Node_t* avlBalancing_(struct AVL_Tree* avlTree, struct Node_t* top) {
    if (!top) {
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }
    avlNodeBalancing_(top);
    struct Node_t* previous = top->prev_;
    int place = 0;
    if (previous != NULL) {
        if (previous->right_ == top) {
            place = 1;
        } else {
            place = -1;
        }
    }
    if (top->balance_factor == 2) {
        if (avlGetBalanceFactor_(top->right_) >= 0) {
            struct Node_t* newTop = avlSmallLeftRotation_(avlTree, top);
            if (place == 1) {
                previous->right_ = newTop;
            }
            if (place == -1) {
                previous->left_ = newTop;
            }
            return newTop;
        } else {
            struct Node_t* newTop = avlBigLeftRotation_(avlTree, top);
            if (place == 1) {
                previous->right_ = newTop;
            }
            if (place == -1) {
                previous->left_ = newTop;
            }
            return newTop;
        }
    }
    if (top->balance_factor == -2) {
        if (avlGetBalanceFactor_(top->right_) >= 0) {
            struct Node_t* newTop = avlSmallRightRotation_(avlTree, top);
            if (place == 1) {
                previous->right_ = newTop;
            }
            if (place == -1) {
                previous->left_ = newTop;
            }
            return newTop;
        } else {
            struct Node_t* newTop = avlBigRightRotation_(avlTree, top);
            if (place == 1) {
                previous->right_ = newTop;
            }
            if (place == -1) {
                previous->left_ = newTop;
            }
            return newTop;
        }
    }
    return top;
}


///
///         nA                                nB
///       /    \                            /    \
///     nL      nB         ---->           nA    nR
///            /  \                       /  \
///           nC    nR                   nL  nC
///
struct Node_t* avlSmallLeftRotation_ (struct AVL_Tree* avlTree, struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = top->right_;
    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_ARG_ERROR;
        return NULL;
    }

    struct Node_t* nC = nB->left_;

    nB->prev_ = top->prev_;
    nB->left_ = nA;

    nA->prev_ = nB;
    nA->right_ = nC;

    if (nC != NULL) {
        nC->prev_ = nA;
    }

    avlNodeBalancing_(nA);
    avlNodeBalancing_(nB);

    if (nB->prev_ == NULL) {
        avlTree->top_ = nB;
    }

    return nB;
}

///
///     nA                               nC
///   /    \                           /    \
///  nL     nB          ---->         nA     nB
///        /  \                      /  \   /  \
///       nC   nR                   nL  nM nN   nR
///      /  \
///     nM  nN
///
struct Node_t* avlBigLeftRotation_ (struct AVL_Tree* avlTree, struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = top->right_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_ARG_ERROR;
        return NULL;
    }

    struct Node_t* nC = nB->left_;

    if (!nC) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_ARG_ERROR;
        return NULL;
    }

    struct Node_t* nM = nC->left_;
    struct Node_t* nN = nC->right_;

    nC->prev_ = top->prev_;
    nC->left_ = nA;
    nC->right_ = nB;

    nA->prev_ = nC;
    nA->right_ = nM;

    nB->prev_ = nC;
    nB->left_ = nN;

    nM->prev_ = nA;
    nN->prev_ = nC;

    avlNodeBalancing_(nA);
    avlNodeBalancing_(nB);
    avlNodeBalancing_(nC);

    if (nC->prev_ == NULL) {
        avlTree->top_ = nC;
    }

    return nC;
}


///
///         nA                                nB
///       /    \                            /    \
///     nB      nR         ---->           nL    nA
///    /  \                                     /  \
///   nL   nC                                  nC   nR
///
struct Node_t* avlSmallRightRotation_ (struct AVL_Tree* avlTree, struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }

    struct Node_t *nA = top;
    struct Node_t *nB = top->left_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_ARG_ERROR;
        return NULL;
    }

    struct Node_t* nC = nB->right_;

    nB->prev_ = top->prev_;
    nB->right_ = nA;

    nA->prev_ = nB;
    nA->left_ = nC;

    if (nC != NULL) {
        nC->prev_ = nA;
    }
    avlNodeBalancing_(nA);
    avlNodeBalancing_(nB);

    if (nB->prev_ == NULL) {
        avlTree->top_ = nB;
    }

    return nB;
}



///
///       nA                               nC
///     /    \                           /    \
///    nB     nR          ---->         nB     nA
///   /  \                             /  \   /  \
///  nL   nC                          nL  nM nN   nR
///      /  \
///     nM  nN
///
struct Node_t* avlBigRightRotation_ (struct AVL_Tree* avlTree, struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
        return NULL;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = nA->left_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_ARG_ERROR;
        return NULL;
    }

    struct Node_t* nC = nB->right_;

    if (!nC) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        avlTree->avlErno_ = AVLERR_ARG_ERROR;
        return NULL;
    }

    struct Node_t* nM = nC->left_;
    struct Node_t* nN = nC->right_;

    nC->right_ = nA;
    nC->left_ = nB;
    nC->prev_ = top->prev_;

    nB->right_ = nM;
    nM->prev_ = nB;

    nA->left_ = nN;
    nN->prev_ = nA;

    nA->prev_ = nC;
    nB->prev_ = nC;

    avlNodeBalancing_(nB);
    avlNodeBalancing_(nA);
    avlNodeBalancing_(nC);

    if (nC->prev_ == NULL) {
        avlTree->top_ = nC;
    }

    return nC;
}

int avlGetBalanceFactor_(struct Node_t* top) {
    if (!top) {
        return 0;
    } else {
        return top->balance_factor;
    }
}

void avlPerror(struct AVL_Tree* avlTree) {
    switch (avlTree->avlErno_) {
        case AVLERR_NOT_INIT:
            fprintf(stderr, "AVL: AVL Tree don't init\n"); return;
        case AVLERR_NULL_POINTER_ARG:
            fprintf(stderr, "AVL: NULL argument is supplied as an argument\n"); return;
        case AVLERR_ARG_ERROR:
            fprintf(stderr, "AVL: Invalid argument passed\n"); return;
        case AVLERR:
            fprintf(stderr, "AVL: Error\n"); return;
        case AVLERR_INSERT:
            fprintf(stderr, "AVL: Insert ERROR\n"); return;
        case AVLERR_TREE_ALREADY_INIT:
            fprintf(stderr, "AVL: AVL Tree already init\n"); return;
        case AVLERR_DATA_NOT_FOUND:
            fprintf(stderr, "AVL: Node not found\n"); return;
        default:
            return;
    }
}

void avlInit(struct AVL_Tree* avlTree) {
    if (avlTree == NULL) {
        avlTree->avlErno_ = AVLERR_OK;
        avlTree->size_ = 0;
        avlTree->top_ = NULL;
    } else {
        avlTree->avlErno_ = AVLERR_NOT_INIT;
    }
}

void avlNodeBalancing_(struct Node_t* node) {
    node->balance_factor = avlGetBalanceFactor_(node->right_) + avlGetBalanceFactor_(node->left_);
    if (node->right_ != NULL) {
        node->balance_factor++;
    }
    if (node->left_ != NULL) {
        node->balance_factor--;
    }
}

void avlPrintTree_ (struct Node_t* top) {
    if (top == NULL){
        fprintf (stderr, "Error: top is NULL, line - %d\n", __LINE__);
        return;
    }
    if (top->left_ == NULL && top->right_ == NULL)
        return;

    printf("%d ", top->data_);

    if (top->left_ == NULL) {
        printf ("NULL ");
        //return;
    } else {
        printf("%d ", top->left_->data_);
    }

    if (top->right_ == NULL)
    {
        //printf ("_%d_", top->right->lexem.lex.num);
        printf("NULL ");
        //return;
    } else {
        printf("%d ", top->right_->data_);
    }

    printf ("\n");
    if (top->left_ != NULL) {
        avlPrintTree_(top->left_);
    }
    if (top->right_ != NULL) {
        avlPrintTree_(top->right_);
    }
}

size_t avlSize(struct AVL_Tree* avlTree) {
    if (avlTree == NULL) {
        avlTree->avlErno_ = AVLERR_NULL_POINTER_ARG;
    }
    return avlTree->size_;
}

void avlEraseByValue(struct AVL_Tree* avlTree, int data) {
    struct AVL_Iterator_t it = avlFind(avlTree, data);
    if (it.it_ == NULL) {
        return;
    }
    avlEraseByIt(avlTree, it);
}

void avlEraseByIt(struct AVL_Tree* avlTree, struct AVL_Iterator_t it) {
    struct Node_t* ptr = it.it_;
    if (ptr->left_ == NULL && ptr->right_ == NULL) {
        if (ptr->prev_ == NULL) {
            free(ptr);
            avlTree->size_--;
            avlTree->top_ = NULL;
            return;
        }
        if (ptr->prev_->left_ == ptr) {
            ptr->prev_->left_ = NULL;
            free(ptr);
        } else {
            ptr->prev_->right_ = NULL;
            free(ptr);
        }
    } else {
        struct Node_t* tmp = ptr->left_;
        struct Node_t* current = tmp;
        while (tmp != NULL) {
            current = tmp;
            tmp = tmp->right_;
        }
        assert(current->right_ == NULL);

        struct Node_t* prev = current->prev_;
        ptr->data_ = current->data_;
        ptr->left_ = current->left_;
        prev->right_ = NULL;
        free(current);
        avlTree->size_--;

        while (prev != ptr) {
            avlBalancing_(avlTree, prev);
            prev = prev->prev_;
        }
    }
    struct Node_t* tmp = ptr;
    while (tmp != NULL) {
        tmp = avlBalancing_(avlTree, tmp);
        tmp = tmp->prev_;
    }
}