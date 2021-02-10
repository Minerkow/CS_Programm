#include "AVL_Tree.h"
#include "AVL_Iterator.h"
#include "Error.h"

#if UNIT_TEST
#define unit_static
#else
#define unit_static static
#endif

unit_static enum AvlError_t avlSmallLeftRotation_ (struct Node_t* top); //TODO:Unit tests

unit_static enum AvlError_t avlBigLeftRotation_ (struct Node_t* top); //TODO:Unit tests

unit_static enum AvlError_t avlSmallRightRotation_ (struct Node_t* top); //TODO:Unit tests

unit_static enum AvlError_t avlBigRightRotation_ (struct Node_t* top); //TODO

unit_static int avlGetBalanceFactor_(struct Node_t* top);

unit_static struct Node_t* avlCreateNode_(int data);

unit_static enum AvlError_t avlBalancing_(struct Node_t* top);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


struct AVL_Iterator_t avlInsert(struct AVL_Tree* avlTree, int data) {
    struct AVL_Iterator_t res;
    if (avlTree->top_ == NULL) {
        avlTree->top_ = avlCreateNode_(data);
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
        current->right_ = newNode;
    } else {
        current->left_ = newNode;
    }
    res.it_ = newNode;
    current->balance_factor = avlGetBalanceFactor_(current->right_) - avlGetBalanceFactor_(current->left_);

    while (current != NULL) {
        if (avlBalancing_(current) != AVLERR_OK) {
            fprintf(stderr, "Insert ERROR\n");
            exit(AVLERR);
        }
        current = current->prev_;
    }

    return res;
}

struct AVL_Iterator_t avlFind(struct AVL_Tree* avlTree, int data) {
    struct AVL_Iterator_t res;

    if (avlTree == NULL) {
        fprintf(stderr, "NULL argument in avlFind");
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
    return res;
}

struct Node_t* avlCreateNode_(int data) {
    struct Node_t* node = calloc(1, sizeof(struct Node_t));
    node->data_ = data;
    return node;
}

enum AvlError_t avlBalancing_(struct Node_t* top) {
    if (!top) {
        return AVLERR_NULL_POINTER_ARG;
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
    return AVLERR_OK;
}


///
///         nA                                nB
///       /    \                            /    \
///     nL      nB         ---->           nA    nR
///            /  \                       /  \
///           nC    nR                   nL  nC
///
enum AvlError_t avlSmallLeftRotation_ (struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_NULL_POINTER_ARG;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = top->right_;
    struct Node_t* nL = top->left_;
    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_ARG_ERROR;
    }

    struct Node_t* nC = nB->left_;
    struct Node_t* nR = nB->right_;

    nB->prev_ = top->prev_;
    nB->left_ = nA;

    nA->prev_ = nB;
    nA->right_ = nC;

    nC->prev_ = nA;

    nA->balance_factor = avlGetBalanceFactor_(nC) - avlGetBalanceFactor_(nL);
    nB->balance_factor = avlGetBalanceFactor_(nR) - avlGetBalanceFactor_(nA);

    return AVLERR_OK;
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
enum AvlError_t avlBigLeftRotation_ (struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_NULL_POINTER_ARG;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = top->right_;
    struct Node_t* nL = top->left_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_ARG_ERROR;
    }

    struct Node_t* nC = nB->left_;
    struct Node_t* nR = nB->right_;

    if (!nC) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_ARG_ERROR;
    }

    struct Node_t* nM = nC->left_;
    struct Node_t* nN = nC->right_;

    nC->prev_ = top;
    nC->left_ = nA;
    nC->right_ = nB;

    nA->prev_ = nC;
    nA->right_ = nM;

    nB->prev_ = nC;
    nB->left_ = nN;

    nM->prev_ = nA;
    nN->prev_ = nC;

    nA->balance_factor = avlGetBalanceFactor_(nL) - avlGetBalanceFactor_(nM);
    nB->balance_factor = avlGetBalanceFactor_(nR) - avlGetBalanceFactor_(nN);
    nC->balance_factor = avlGetBalanceFactor_(nB) - avlGetBalanceFactor_(nA);

    return AVLERR_OK;
}


///
///         nA                                nB
///       /    \                            /    \
///     nB      nR         ---->           nL    nA
///    /  \                                     /  \
///   nL   nC                                  nC   nR
///
enum AvlError_t avlSmallRightRotation_ (struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_NULL_POINTER_ARG;
    }

    struct Node_t *nA = top;
    struct Node_t *nB = top->left_;
    struct Node_t *nR = top->right_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_ARG_ERROR;
    }

    struct Node_t* nC = nB->right_;
    struct Node_t* nL = nB->left_;

    nB->prev_ = top;
    nB->right_ = nA;

    nA->prev_ = nB;
    nA->left_ = nC;

    nC->prev_ = nA;

    nA->balance_factor = avlGetBalanceFactor_(nR) - avlGetBalanceFactor_(nC);
    nB->balance_factor = avlGetBalanceFactor_(nA) - avlGetBalanceFactor_(nL);

    return AVLERR_OK;
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
enum AvlError_t avlBigRightRotation_ (struct Node_t* top) {
    if (!top) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_NULL_POINTER_ARG;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = nA->left_;
    struct Node_t* nR = nA->right_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_ARG_ERROR;
    }

    struct Node_t* nL = nB->left_;
    struct Node_t* nC = nB->right_;

    if (!nC) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return AVLERR_ARG_ERROR;
    }

    struct Node_t* nM = nC->left_;
    struct Node_t* nN = nC->right_;

    nC->right_ = nA;
    nC->left_ = nB;
    nC->prev_ = top;

    nB->right_ = nM;
    nM->prev_ = nB;

    nA->left_ = nN;
    nN->prev_ = nA;

    nA->prev_ = nC;
    nB->prev_ = nC;

    nB->balance_factor = avlGetBalanceFactor_(nM) - avlGetBalanceFactor_(nL);
    nA->balance_factor = avlGetBalanceFactor_(nR) - avlGetBalanceFactor_(nN);
    nC->balance_factor = avlGetBalanceFactor_(nA) - avlGetBalanceFactor_(nB);

    return AVLERR_OK;
}

int avlGetBalanceFactor_(struct Node_t* top) {
    if (!top) {
        return 0;
    } else {
        return top->balance_factor;
    }
}