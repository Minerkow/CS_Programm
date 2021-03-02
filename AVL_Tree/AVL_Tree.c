#include "AVL_Tree.h"
#include "Error.h"


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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static struct Node_t* avlSmallLeftRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO:Unit tests

static struct Node_t* avlBigLeftRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO:Unit tests

static struct Node_t* avlSmallRightRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO:Unit tests

static struct Node_t* avlBigRightRotation_ (struct AVL_Tree* avlTree, struct Node_t* top); //TODO

static int avlGetBalanceFactor_(struct Node_t* top);

static struct Node_t* avlCreateNode_(struct AVL_Tree* avlTree, int data);

static struct Node_t* avlBalancing_(struct AVL_Tree* avlTree, struct Node_t* top);

static enum AvlError_t avlNodeBalancing_(struct Node_t* node);

//*Erase elem by pointer
static enum AvlError_t avlEraseByIt_(struct AVL_Tree* avlTree, struct Node_t* it);

//*If the data is in the table, it returns an iterator on it,
//*otherwise it returns a null iterator
struct Node_t* avlFind_(struct AVL_Tree* avlTree, int data);

static void avlPrintNode_ (struct Node_t* top);

static int avlNodeHeight_(struct Node_t* top);
static void avlInorder_(struct Node_t* top);
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum AvlError_t avlLoadFromArray(struct AVL_Tree* avlTree, int* array, size_t arraySize) {
    if (array == NULL) {
        return AVLERR_NULL_POINTER_ARG;
    }
    if (avlTree == NULL) {
        return AVLERR_NOT_INIT;
    }
    if (arraySize == 0) {
        return AVLERR_OK;
    }
    for (size_t i = 0; i < arraySize; ++i) {
        //printf("Insert: %d\n", array[i]);
        if (avlInsert(avlTree, array[i]) != AVLERR_OK) {
            fprintf(stderr, "AVL Insert ERROR");
            return AVLERR_INSERT;
        }
        //avlPrintTree_(avlTree);
        //fprintf(stdout, "\n");
    }
    return AVLERR_OK;
}


enum AvlError_t avlInsert(struct AVL_Tree* avlTree, int data) {
    if (avlTree == NULL) {
        return AVLERR_NOT_INIT;
    }
    if (avlTree->top_ == NULL) {
        avlTree->top_ = avlCreateNode_(avlTree, data);
        if (!avlTree->top_) {
            return AVLERR_INSERT;
        }
        avlTree->top_->prev_ = NULL;
        return AVLERR_OK;
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
            return AVLERR_OK;
        }
    }
    struct Node_t* newNode = avlCreateNode_(avlTree, data);
    if (!newNode) {
        return AVLERR_INSERT;
    }
    newNode->prev_ = current;

    if (data > current->data_) {
        current->right_ = newNode;
    } else {
        current->left_ = newNode;
    }
    int err = avlNodeBalancing_(current);
    if (err != AVLERR_OK) {
        return err;
    }

    while (current != NULL) {
        current = avlBalancing_(avlTree, current);
        if (current == NULL) {
            fprintf(stderr, "Insert ERROR\n");
            return AVLERR_INSERT;
        }
        current = current->prev_;
    }
    return AVLERR_OK;
}

struct Node_t* avlFind_(struct AVL_Tree* avlTree, int data) {
    if (avlTree == NULL) {
        fprintf(stderr, "NULL argument in avlFind");
        return NULL;
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
            return tmp;
        }
    }
    return NULL;
}

bool avlEmpty(struct AVL_Tree* avlTree) {
    if (avlTree == NULL) {
        return true;
    }
    if (avlTree->top_ == NULL) {
        return true;
    }
    return false;
}

struct Node_t* avlCreateNode_(struct AVL_Tree* avlTree, int data) {
    struct Node_t* node = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    if (node == NULL) {
        fprintf(stderr, "kek");
        return NULL;
    }
    node->data_ = data;
    node->height_ = 1;
    avlTree->size_++;
    return node;
}

struct Node_t* avlBalancing_(struct AVL_Tree* avlTree, struct Node_t* top) {
    if (!top) {
        return NULL;
    }
    int err = avlNodeBalancing_(top);
    if (err != AVLERR_OK) {
        return NULL;
    }

    struct Node_t *previous = top->prev_;
    int place = 0;
    if (previous != NULL) {
        if (previous->right_ == top) {
            place = 1;
        } else {
            place = -1;
        }
    }

    if (avlGetBalanceFactor_(top) == 2) {
        if (avlGetBalanceFactor_(top->right_) >= 0) {
            struct Node_t *tmp = avlSmallLeftRotation_(avlTree, top);
            if (tmp == NULL) {
                return NULL;
            }
            if (place == 1) {
                previous->right_ = tmp;
            }
            if (place == -1) {
                previous->left_ = tmp;
            }
        } else {
            struct Node_t *tmp = avlBigLeftRotation_(avlTree, top);
            if (tmp == NULL) {
                return NULL;
            }
            if (place == 1) {
                previous->right_ = tmp;
            }
            if (place == -1) {
                previous->left_ = tmp;
            }
        }
    }

    if (avlGetBalanceFactor_(top) == -2) {
        if (avlGetBalanceFactor_(top->left_) <= 0) {
            struct Node_t *tmp = avlSmallRightRotation_(avlTree, top);
            if (tmp == NULL) {
                return NULL;
            }
            if (place == 1) {
                previous->right_ = tmp;
            }
            if (place == -1)
                previous->left_ = tmp;
        } else {
            struct Node_t *tmp = avlBigRightRotation_(avlTree, top);
            if (tmp == NULL) {
                return NULL;
            }
            if (place == 1) {
                previous->right_ = tmp;
            }
            if (place == -1) {
                previous->left_ = tmp;
            }
    }
}
    assert(1 && "Oooops");
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

    if (!top || !avlTree) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = top->right_;
    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
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

    int err = avlNodeBalancing_(nA);
    if (err != AVLERR_OK) {
        return NULL;
    }
    err = avlNodeBalancing_(nB);
    if (err != AVLERR_OK) {
        return NULL;
    }

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
    if (!top || !avlTree) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = top->right_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t* nC = nB->left_;

    if (!nC) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
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

    if (nM != NULL) {
        nM->prev_ = nA;
    }
    if (nN != NULL) {
        nN->prev_ = nB;
    }

    int err = avlNodeBalancing_(nA);
    if (err != AVLERR_OK) {
        return NULL;
    }
    err = avlNodeBalancing_(nB);
    if (err != AVLERR_OK) {
        return NULL;
    }
    err = avlNodeBalancing_(nC);
    if (err != AVLERR_OK) {
        return NULL;
    }

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
    if (!top || !avlTree) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t *nA = top;
    struct Node_t *nB = top->left_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
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

    int err = avlNodeBalancing_(nA);
    if (err != AVLERR_OK) {
        return NULL;
    }
    err = avlNodeBalancing_(nB);
    if (err != AVLERR_OK) {
        return NULL;
    }

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

    if (!top || !avlTree) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t* nA = top;
    struct Node_t* nB = nA->left_;

    if (!nB) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t* nC = nB->right_;

    if (!nC) {
        fprintf(stderr, "\nError line - %d\n", __LINE__);
        return NULL;
    }

    struct Node_t* nM = nC->left_;
    struct Node_t* nN = nC->right_;

    nC->prev_ = top->prev_;
    nC->right_ = nA;
    nC->left_ = nB;

    nB->right_ = nM;
    if (nM != NULL) {
        nM->prev_ = nB;
    }

    nA->left_ = nN;
    if (nN != NULL) {
        nN->prev_ = nA;
    }

    nA->prev_ = nC;
    nB->prev_ = nC;

    int err = avlNodeBalancing_(nB);
    if (err != AVLERR_OK) {
        return NULL;
    }
    err = avlNodeBalancing_(nA);
    if (err != AVLERR_OK) {
        return NULL;
    }
    err = avlNodeBalancing_(nC);
    if (err != AVLERR_OK) {
        return NULL;
    }

    if (nC->prev_ == NULL) {
        avlTree->top_ = nC;
    }

    return nC;
}

int avlGetBalanceFactor_(struct Node_t* top) {
    int balanceFactor = 0;
    if (top == NULL) {
        return 0;
    } else {
         balanceFactor = avlNodeHeight_(top->right_) -
                    avlNodeHeight_(top->left_);
    }
    return balanceFactor;
}

struct AVL_Tree* avlInit() {
    struct AVL_Tree* avlTree = calloc(1, sizeof(struct AVL_Tree));
    avlTree->size_ = 0;
    if (avlTree == NULL) {
        return NULL;
    }
    return avlTree;
}

enum AvlError_t avlNodeBalancing_(struct Node_t* node) {
    if (!node) {
        return AVLERR_BALANCE;
    }
    if (avlNodeHeight_(node->right_) >
                        avlNodeHeight_(node->left_)) {
        node->height_ = avlNodeHeight_(node->right_) + 1;
    } else {
        node->height_ = avlNodeHeight_(node->left_) + 1;
    }
    return AVLERR_OK;
}

size_t avlSize(struct AVL_Tree* avlTree) {
    if (avlTree == NULL) {
        return 0;
    }
    return avlTree->size_;
}

enum AvlError_t avlEraseByValue(struct AVL_Tree* avlTree, int data) {
    if (avlTree == NULL) {
        return AVLERR_NULL_POINTER_ARG;
    }
    struct Node_t* it = avlFind_(avlTree, data);
    if (it == NULL) {
        return AVLERR_OK;
    }
    return avlEraseByIt_(avlTree, it);
}

enum AvlError_t avlEraseByIt_(struct AVL_Tree* avlTree, struct Node_t* it) {
    if (avlTree == NULL || it == NULL) {
        return AVLERR_NULL_POINTER_ARG;
    }
    struct Node_t* ptr = it;
    if (ptr->left_ == NULL && ptr->right_ == NULL) {
        if (ptr->prev_ == NULL) {
            free(ptr);
            avlTree->size_--;
            avlTree->top_ = NULL;
            return AVLERR_OK;
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
        if (current == NULL) {
            avlTree->top_ = ptr->right_;
            ptr->right_->prev_ = NULL;
            free(ptr);
            return AVLERR_OK;
        }
        while (tmp != NULL) {
            current = tmp;
            tmp = tmp->right_;
        }

        struct Node_t* prev = current->prev_;
        ptr->data_ = current->data_;

        if (current->prev_->right_ == current) {
            current->prev_->right_ = current->left_;
            current->left_->prev_ = current->prev_;
        }
        if (current->prev_->left_ == current) {
            current->prev_->left_ = current->left_;
            current->left_->prev_ = current->prev_;
        }


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
    return AVLERR_OK;
}

void avlForEach(void (*foo)(struct Node_t* it, void* data), void* data) {

}

int avlNodeHeight_(struct Node_t* top) {
    if (top == NULL) {
        return 0;
    } else {
        return top->height_;
    }
}

int avlClear(struct AVL_Tree* avlTree) {
    if (!avlTree) {
        return -1;
    }
    avlInorder_(avlTree->top_);
    free(avlTree);
    return 1;
}

void avlInorder_(struct Node_t* top) {
    if (top == NULL)
        return;
    avlInorder_(top->left_);
    avlInorder_(top->right_);
    free(top);
}

void avlPerror(enum AvlError_t err) {
    switch (err) {
        case AVLERR_NOT_INIT:
            fprintf(stderr, "AVL: AVL Tree don't init\n"); return;
        case AVLERR_NULL_POINTER_ARG:
            fprintf(stderr, "AVL: NULL argument is supplied as an argument\n"); return;
        case AVLERR:
            fprintf(stderr, "AVL: Error\n"); return;
        case AVLERR_INSERT:
            fprintf(stderr, "AVL: Insert ERROR\n"); return;
        default:
            return;
    }
}

void avlPrintTree_(struct AVL_Tree* avlTree) {
    avlPrintNode_(avlTree->top_);
}

void avlPrintNode_(struct Node_t* top) {
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
        avlPrintNode_(top->left_);
    }
    if (top->right_ != NULL) {
        avlPrintNode_(top->right_);
    }
}