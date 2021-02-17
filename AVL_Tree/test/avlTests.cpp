#include <gtest/gtest.h>
extern "C" {
    #include "../AVL_Tree.h"
}

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


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(AVL_Tree, avlEmptyTest) {
    AVL_Tree avlTree{};
    ASSERT_TRUE(avlEmpty(&avlTree));
}

TEST(AVL_Tree, avlInsert1) {
    struct AVL_Tree avlTree{};
    AVL_Iterator_t it1 = avlInsert(&avlTree, 1);
    AVL_Iterator_t it2 = avlFind(&avlTree, 1);
    int res = avlGetDataByIt(it2);
    ASSERT_TRUE(avlEqualIt(it1, it2));
    ASSERT_EQ(res, 1);
}

TEST(AVL_Tree, avlInsert2) {
    struct AVL_Tree avlTree{};
    std::vector<int> res;
    std::vector<int> truerRes = {-1, 0, 1, 2, 3};
    avlInsert(&avlTree, 1);
    avlInsert(&avlTree, 2);
    avlInsert(&avlTree, 3);
    avlInsert(&avlTree, 0);
    avlInsert(&avlTree, -1);
    AVL_Iterator_t it = avlBeginIt(&avlTree);
    for (size_t i = 0; i < avlSize(&avlTree); ++i) {
        res.push_back(avlGetDataByIt(it));
        it = avlNextIt(it);
    }
    ASSERT_EQ(res, truerRes);
}

TEST(AVL_Tree, avlLoadFromArray) {
    struct AVL_Tree avlTree{};
    std::vector<int> data = {3, 2, 4, 5, 1};
    std::vector<int> res;
    std::vector<int> trueRes = {5, 4, 3, 2, 0};
    avlLoadFromArray(&avlTree, data.data(), data.size());
    AVL_Iterator_t it = avlEndIt(&avlTree);
    for (size_t i = 0; i < avlSize(&avlTree); ++i) {
        res.push_back(avlGetDataByIt(it));
        it = avlPrevIt(it);
    }
    ASSERT_EQ(res, trueRes);
}

TEST(AVL_Tree, avlEraseByValue) {
    struct AVL_Tree avlTree{};
    std::vector<int> data = {3, 2, 4, 5, 1};
    std::vector<int> trueRes = {5, 4, 2, 0};
    avlLoadFromArray(&avlTree, data.data(), data.size());
    avlPrintTree_(avlTree.top_);
    avlEraseByValue(&avlTree, 3);
    std::cout << std::endl << std::endl;
    avlPrintTree_(avlTree.top_);
}