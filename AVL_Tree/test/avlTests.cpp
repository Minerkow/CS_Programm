#include <gtest/gtest.h>
//extern "C" {
#include "../headers/AVL_Tree.h"
#include "../headers/TestHelper.h"
//}

TEST(AVL_Tree, stressTest1) {
    AVL_Tree* avlTree = avlInit();
    ASSERT_TRUE(!avlTree);
    avlClear(avlTree);
}

TEST(AVL_Tree, stressTest2) {
    AVL_Tree* avlTree = avlInit();
    ASSERT_EQ(AVLERR_INSERT, avlInsert(avlTree, 1));
    avlClear(avlTree);
}

TEST(AVL_Tree, stressTest3) {
    AVL_Tree* avlTree = avlInit();
    avlInsert(avlTree, 1);
    ASSERT_EQ(AVLERR_INSERT, avlInsert(avlTree, 2));
    avlClear(avlTree);
}

TEST(AVL_Tree, stressTest4) {
    AVL_Tree* avlTree = avlInit();
    int arr[] = {1};
    ASSERT_EQ(AVLERR_INSERT, avlLoadFromArray(avlTree, arr, 1));
    avlClear(avlTree);
}


//---------------------------------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlInsert1) {
    AVL_Tree* avlTree = avlInit();
    avlInsert(avlTree, 1);
    ASSERT_EQ(avlGetMaxElem(avlTree), avlGetMinElem(avlTree));
    avlClear(avlTree);
}

TEST(AVL_Tree, avlInsert2) {
    int err = avlInsert(NULL, 1);
    ASSERT_EQ(err, AVLERR_NOT_INIT);
}

//-----------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlLoadFromArray1) {
    const size_t numNumbers = 100000;
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input;
    std::set<int> garantSet;
    std::srand(std::time(0));
    for (int i = 0; i < numNumbers; ++i) {
        input.push_back(std::rand() % 10000000);
        garantSet.insert(input.back());
        avlInsert(avlTree, input.back());
    }
    ASSERT_EQ(avlSize(avlTree), garantSet.size());
    std::vector<int> trueRes;
    for (auto& it : garantSet) {
        trueRes.push_back(it);
    }
    std::vector<int> res(trueRes.size());
    avlSaveInArray(avlTree, res.data(), avlSize(avlTree));
    //std::cout << std::endl;
    //avlPrintTree_(avlTree);
    ASSERT_EQ(avlSize(avlTree), garantSet.size());
    ASSERT_EQ(trueRes, res);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlLoadFromArrayStress) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = {27, 80, 8, 42, 37, 59, 90, 42, 90, 46, 92, 22, 18, 0, 99, 98, 92, 18, 16, 2, 45, 75, 30, 27, 23, 34, 50, 88, 53, 75, 73, 80, 7, 33, 22, 44, 92, 65, 86, 82};
    std::vector<int> trueRes = {0, 2, 7, 8, 16, 18, 22, 23, 27, 30, 33, 34, 37, 42, 44, 45, 46, 50, 53, 59, 65, 73, 75, 80, 82, 86, 88, 90, 92, 98, 99};
    std::vector<int> res(trueRes.size());
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(trueRes, res);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlLoadFromArray2) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = {1, 2, 3, 4, 2};
    std::vector<int> trueRes = {1, 2, 3, 4};
    std::vector<int> res(trueRes.size());
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(trueRes.size(), avlSize(avlTree));
    ASSERT_EQ(trueRes, res);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlLoadFromArray3) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 3};
    std::vector<int> trueRes = { 0, 1, 3};
    std::vector<int> res(trueRes.size());
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(trueRes, res);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlLoadFromArray4) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 1, 1, 3, 3, 4, 6, 7, 9 };
    std::vector<int> trueRes = { 0, 1, 3, 4, 6, 7, 9 };
    std::vector<int> res(trueRes.size());
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(trueRes, res);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlLoadFromArray5) {
    AVL_Tree* avlTree = avlInit();
    int arr[5];
    ASSERT_EQ(AVLERR_NULL_POINTER_ARG, avlLoadFromArray(avlTree, NULL, 1));
    ASSERT_EQ(AVLERR_NOT_INIT, avlLoadFromArray(NULL, arr, 5));
    ASSERT_EQ(AVLERR_OK, avlLoadFromArray(avlTree, arr, 0));
    avlClear(avlTree);
}

TEST(AVL_Tree, avlLoadFromArray6) {
    AVL_Tree *avlTree = avlInit();
    std::vector<int> input = {0, 1, 3, 4, 6, 7, 9};
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlClear(avlTree);
}

//-------------------------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlIsEmpty) {
    AVL_Tree* avlTree = avlInit();
    ASSERT_TRUE(avlIsEmpty(avlTree));
    ASSERT_TRUE(avlIsEmpty(NULL));
    avlInsert(avlTree, 1);
    ASSERT_FALSE(avlIsEmpty(avlTree));
    avlClear(avlTree);
}

//-------------------------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlSize) {
    AVL_Tree *avlTree = avlInit();
    std::vector<int> input = {0, 1, 1, 1, 3, 3, 4, 6, 7, 9};
    avlLoadFromArray(avlTree, input.data(), input.size());
    ASSERT_EQ(avlSize(avlTree), 7);
    ASSERT_EQ(0, std::isnan(avlSize(NULL)));
    avlClear(avlTree);
}

//-------------------------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlEraseByValue1) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 3, 4, 6, 7, 9 };
    avlLoadFromArray(avlTree, input.data(), input.size());
    ASSERT_EQ(AVLERR_NULL_POINTER_ARG, avlEraseByValue(NULL, -1));
    ASSERT_EQ(AVLERR_OK, avlEraseByValue(avlTree, -1));
    ASSERT_EQ(AVLERR_OK, avlEraseByValue(avlTree, 1));
    std::vector<int> res(6);
    std::vector<int> trueRes = {0, 3, 4, 6, 7, 9};
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue2) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 3, 4, 6, 7, 9 };
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 1);
    std::vector<int> res(6);
    std::vector<int> trueRes = {0, 3, 4, 6, 7, 9 };
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue3) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 3, 4, 6, 7, 9 };
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 3);
    std::vector<int> res(6);
    std::vector<int> trueRes = {0, 1, 4, 6, 7, 9 };
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue4) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 3, 4, 6, 7, 9 };
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 4);
    std::vector<int> res(6);
    std::vector<int> trueRes = {0, 1, 3, 6, 7, 9 };
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue5) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1, 3, 4, 6, 7, 9 };
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 6);
    std::vector<int> res(6);
    std::vector<int> trueRes = {0, 1, 3, 4, 7, 9 };
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue6) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0};
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 0);
    ASSERT_TRUE(avlIsEmpty(avlTree));
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue7) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 0, 1};
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 0);
    std::vector<int> res(1);
    std::vector<int> trueRes = {1};
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlEraseByValue8) {
    AVL_Tree* avlTree = avlInit();
    std::vector<int> input = { 1, 3, 0, -1, -2};
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlEraseByValue(avlTree, 0);
    std::vector<int> res(4);
    std::vector<int> trueRes = {-2, -1, 1, 3};
    avlSaveInArray(avlTree, res.data(), res.size());
    ASSERT_EQ(res, trueRes);
    avlClear(avlTree);
}

//-------------------------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlSaveInArray) {
    AVL_Tree* avlTree = avlInit();
    int arr[5] = {};
    ASSERT_EQ(avlSaveInArray(NULL, NULL, 0), AVLERR_NOT_INIT);
    ASSERT_EQ(avlSaveInArray(avlTree, arr, 0), AVLERR_OK);
    ASSERT_EQ(avlSaveInArray(avlTree, NULL, 5), AVLERR_NULL_POINTER_ARG);
    ASSERT_EQ(avlSaveInArray(avlTree, arr, 1), AVLERR_OK);
    avlClear(avlTree);
}

//-------------------------------------------------------------------------------------------------------------------------------

TEST(AVL_Tree, avlClear) {
    avlClear(NULL);
}

void Sum(Node_t* it, void* data) {
    if (avlEmptyIt(it)) {
        return;
    }
    avlEmptyIt(NULL);
    avlGetDataByIt(NULL);
    int* ptr = (int*)data;
    *ptr += avlGetDataByIt(it);
}

TEST(AVL_Tree, avlForEach1) {
    AVL_Tree* avlTree = avlInit();
    int sum = 0;
    std::vector<int> input = { 0, 1, 2, 3, 4};
    avlLoadFromArray(avlTree, input.data(), input.size());
    avlForEach(avlTree, Sum, &sum);
    ASSERT_EQ(sum, 10);
    avlClear(avlTree);
}

TEST(AVL_Tree, avlForEach2) {
    AVL_Tree* avlTree = avlInit();
    ASSERT_EQ(AVLERR_NOT_INIT, avlForEach(NULL, Sum, NULL));
    ASSERT_EQ(AVLERR_OK, avlForEach(avlTree, Sum, NULL));
    ASSERT_EQ(AVLERR_NULL_POINTER_ARG, avlForEach(avlTree, NULL, NULL));
    avlClear(avlTree);
}

TEST(AVL_Tree, avlGetMaxElem) {
    ASSERT_TRUE(!isnan(avlGetMaxElem(NULL)));
    AVL_Tree* avlTree = avlInit();
    ASSERT_TRUE(!isnan(avlGetMaxElem(avlTree)));
    avlClear(avlTree);
}

TEST(AVL_Tree, avlGetMinElem) {
    ASSERT_TRUE(!isnan(avlGetMinElem(NULL)));
    AVL_Tree* avlTree = avlInit();
    ASSERT_TRUE(!isnan(avlGetMinElem(avlTree)));
    avlClear(avlTree);
}
