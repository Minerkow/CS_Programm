#include <gtest/gtest.h>
extern "C" {
    #include "../AVL_Tree.h"
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(AVL_Tree, avlEmptyTest) {
    AVL_Tree* avlTree = avlInit();
    ASSERT_TRUE(avlEmpty(avlTree));
}

TEST(AVL_Tree, avlInsert2) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> res;
    std::vector<int> truerRes = {-1, 0, 1, 2, 3};
    AVL_Iterator_t* it = avlCreateIt();
    avlInsert(avlTree, 1);
    avlInsert(avlTree, 2);
    avlInsert(avlTree, 3);
    avlInsert(avlTree, 0);
    avlInsert(avlTree, -1);
    avlBeginIt(avlTree, it);
    for (size_t i = 0; i < avlSize(avlTree); ++i) {
        res.push_back(avlGetDataByIt(it));
        it = avlNextIt(it);
    }
    ASSERT_EQ(res, truerRes);
}
//
//TEST(AVL_Tree, avlLoadFromArray) {
//    AVL_Tree* avlTree = avlInit();
//    std::vector<int> data = {3, 2, 4, 5, 1};
//    std::vector<int> res;
//    std::vector<int> trueRes = {5, 4, 3, 2, 0};
//    AVL_Iterator_t* it = avlCreateIt();
//    avlLoadFromArray(avlTree, data.data(), data.size());
//    avlEndIt(avlTree, it);
//    for (size_t i = 0; i < avlSize(avlTree); ++i) {
//        res.push_back(avlGetDataByIt(it));
//        it = avlPrevIt(it);
//    }
//    ASSERT_EQ(res, trueRes);
//}
//
//TEST(AVL_Tree, avlEraseByValue) {
//    struct AVL_Tree* avlTree = avlInit();
//    std::vector<int> data = {3, 2, 4, 5, 1};
//    std::vector<int> res;
//    std::vector<int> trueRes = {1, 2, 4, 5};
//    avlLoadFromArray(avlTree, data.data(), data.size());
//    avlEraseByValue(avlTree, 3);
//    AVL_Iterator_t* it = avlCreateIt();
//    it = avlBeginIt(avlTree, it);
//    for (size_t i = 0; i < avlSize(avlTree); ++i) {
//        res.push_back(avlGetDataByIt(it));
//        it = avlNextIt(it);
//    }
//
//    ASSERT_EQ(res, trueRes);
//}