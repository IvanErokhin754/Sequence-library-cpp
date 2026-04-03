#include <gtest/gtest.h>
#include "DynamicArray.hpp"
#include <stdexcept>

TEST(DynamicArrayTest, DefaultConstructorCreatesEmptyArray) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.GetSize(), 0u);
}

TEST(DynamicArrayTest, SizedConstructorCreatesArrayWithCorrectSize) {
    DynamicArray<int> arr (5);
    EXPECT_EQ(arr.GetSize(), 5u);
}

TEST(DynamicArrayTest, OperatorAccessAllowsReadAndWrite) {
    DynamicArray<int> arr(3);

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(DynamicArrayTest, CopyConstructorCreatesIndependentCopy) {
    DynamicArray<int> arr(2);
    arr[0] = 1;
    arr[1] = 2;

    DynamicArray<int> copy(arr);

    ASSERT_EQ(copy.GetSize(), 2u);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);

    copy[0] = 100;

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(copy[0], 100);
}

TEST(DynamicArrayTest, AssignmentOperatorCreatesIndependentCopy) {
    DynamicArray<int> arr1(3);
    arr1[0] = 5;
    arr1[1] = 6;
    arr1[2] = 7;

    DynamicArray<int> arr2(3);
    arr2 = arr1;

    ASSERT_EQ(arr2.GetSize(), 3u);
    EXPECT_EQ(arr2[0], 5);
    EXPECT_EQ(arr2[1], 6);
    EXPECT_EQ(arr2[2], 7);
    
    arr2[1] = 52;

    EXPECT_EQ(arr1[0], 5);
    EXPECT_EQ(arr1[1], 6);
    EXPECT_EQ(arr1[2], 7);
    EXPECT_EQ(arr2[1], 52);
}

TEST(DynamicArrayTest, SelfAssignmentDoesNotBreakArray) {
    DynamicArray<int> arr(2);
    arr[0] = 11;
    arr[1] = 22;

    arr = arr;

    ASSERT_EQ(arr.GetSize(), 2u);
    EXPECT_EQ(arr[0], 11);
    EXPECT_EQ(arr[1], 22);
}

TEST(DynamicArrayTest, ResizeIncreasesSize) {
    DynamicArray<int> arr(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.Resize(4);

    EXPECT_EQ(arr.GetSize(), 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(DynamicArrayTest, ResizeDecreasesSize) {
    DynamicArray<int> arr(4);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;

    arr.Resize(2);

    ASSERT_EQ(arr.GetSize(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_THROW(arr[2], std::out_of_range);
}

TEST(DynamicArrayTest, ResizeToZeroMakesArrayEmpty) {
    DynamicArray<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr.Resize(0);

    EXPECT_EQ(arr.GetSize(), 0u);
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(DynamicArrayTest, ResizeFromEmptyCreatesUsableArray) {
    DynamicArray<int> arr;

    arr.Resize(3);

    ASSERT_EQ(arr.GetSize(), 3u);

    arr[0] = 7;
    arr[1] = 8;
    arr[2] = 9;

    EXPECT_EQ(arr[0], 7);
    EXPECT_EQ(arr[1], 8);
    EXPECT_EQ(arr[2], 9);
}

TEST(DynamicArrayTest, OperatorThrowsOnOutOfRange) {
    DynamicArray<int> arr(2);

    EXPECT_THROW(arr[2], std::out_of_range);
    EXPECT_THROW(arr[100], std::out_of_range);
}