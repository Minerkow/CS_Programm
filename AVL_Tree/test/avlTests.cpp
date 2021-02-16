#include <gtest/gtest.h>
extern "C" {
    #include "../AVL_Tree.h"
}
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
    avlInsert(&avlTree, 1);
    avlInsert(&avlTree, 2);
    avlInsert(&avlTree, 3);
    avlInsert(&avlTree, 0);
    avlInsert(&avlTree, -1);
    avlPrintTree_(avlTree.top_);
    //printf("%d", avlGetDataByIt(res));
}

//TEST(AVL_Tree, avlLoadFromArray) {
//    struct AVL_Tree avlTree{};
//    int arr[] = {3, 2, 4, 5, 1};
//    avlLoadFromArray(&avlTree, arr, 5);
//}