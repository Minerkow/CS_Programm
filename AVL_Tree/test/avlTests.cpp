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

TEST(AVL_Tree, avlInsert1) {
    AVL_Tree* avlTree = avlInit();
    avlInsert(avlTree, 1);
    ASSERT_EQ(avlGetMaxElem(avlTree), avlGetMinElem(avlTree));
}

TEST(AVL_Tree, avlInsert2) {
    int err = avlInsert(NULL, 1);
    ASSERT_EQ(err, AVLERR_NOT_INIT);
}


//TEST(AVL_Tree, avlLoadFromArray1) {
//    AVL_Tree* avlTree = avlInit();
//    std::vector<int> input;
//    std::srand(std::time(0));
//    for (int i = 0; i < 10; ++i) {
//        input.push_back(std::rand() % 10);
//    }
//    std::vector<int> trueRes = input;
//    std::sort(trueRes.begin(), trueRes.end());
//    std::vector<int> res(input.size());
//    avlLoadFromArray(avlTree, input.data(), input.size());
//    avlSaveInArray(avlTree, res.data(), res.size());
//    ASSERT_EQ(trueRes, res);
//}

TEST(AVL_Tree, avlLoadFromArray2) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = {1, 2, 3, 4, 2};
    std::vector<int> trueRes = {1, 2, 3, 4};
    std::vector<int> res(trueRes.size());
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(trueRes, res);
}

TEST(AVL_Tree, avlLoadFromArray3) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 1, 1, 3, 3, 4, 6, 7, 9 };
    std::vector<int> trueRes = { 0, 1, 3, 4, 6, 7, 9 };
    std::vector<int> res(trueRes.size());
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlPrintTree_(avlTree);
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(trueRes, res);
}