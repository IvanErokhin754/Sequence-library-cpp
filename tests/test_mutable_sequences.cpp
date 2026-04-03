#include <gtest/gtest.h>
#include "MutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include <stdexcept>

static int DoubleValue(const int& value) {
    return value * 2;
}

static bool IsEven(const int& value) {
    return value % 2 == 0;
}

static int Sum(const int& a, const int& b) {
    return a + b;
}

static bool GreaterThanTen(const int& value) {
    return value > 10;
}

template<typename T>
class MutableSequenceTypedTest : public ::testing::Test {
};

using MutableImplementations = ::testing::Types<
    MutableArraySequence<int>,
    MutableListSequence<int>
>;

TYPED_TEST_SUITE(MutableSequenceTypedTest, MutableImplementations);

TYPED_TEST(MutableSequenceTypedTest, AppendAddsElementToEnd) {
    TypeParam seq;
    seq.Append(10);
    seq.Append(20);

    ASSERT_EQ(seq.GetLength(), 2u);
    EXPECT_EQ(seq.Get(0), 10);
    EXPECT_EQ(seq.Get(1), 20);
    EXPECT_EQ(seq.GetFirst(), 10);
    EXPECT_EQ(seq.GetLast(), 20);
}

TYPED_TEST(MutableSequenceTypedTest, PrependAddsElementToFront) {
    TypeParam seq;
    seq.Prepend(20);
    seq.Prepend(10);

    ASSERT_EQ(seq.GetLength(), 2u);
    EXPECT_EQ(seq.Get(0), 10);
    EXPECT_EQ(seq.Get(1), 20);
    EXPECT_EQ(seq.GetFirst(), 10);
    EXPECT_EQ(seq.GetLast(), 20);
}

TYPED_TEST(MutableSequenceTypedTest, InsertAtInsertsElement) {
    TypeParam seq;
    seq.Append(1);
    seq.Append(3);

    seq.InsertAt(1, 2);

    ASSERT_EQ(seq.GetLength(), 3u);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
}

TYPED_TEST(MutableSequenceTypedTest, RemoveDeletesElement) {
    TypeParam seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    seq.Remove(1);

    ASSERT_EQ(seq.GetLength(), 2u);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 3);
}

TYPED_TEST(MutableSequenceTypedTest, GetReturnsCorrectElement) {
    TypeParam seq;
    seq.Append(5);
    seq.Append(6);
    seq.Append(7);

    EXPECT_EQ(seq.Get(0), 5);
    EXPECT_EQ(seq.Get(1), 6);
    EXPECT_EQ(seq.Get(2), 7);
}

TYPED_TEST(MutableSequenceTypedTest, ConcatJoinsTwoSequences) {
    TypeParam seq1;
    seq1.Append(1);
    seq1.Append(2);

    TypeParam seq2;
    seq2.Append(3);
    seq2.Append(4);

    Sequence<int>* result = seq1.Concat(seq2);

    ASSERT_EQ(result->GetLength(), 4u);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 2);
    EXPECT_EQ(result->Get(2), 3);
    EXPECT_EQ(result->Get(3), 4);
    
    delete result;
}

TYPED_TEST(MutableSequenceTypedTest, MapTransformsElements) {
    TypeParam seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    Sequence<int>* result = seq.Map(DoubleValue);

    ASSERT_EQ(result->GetLength(), 3u);
    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);
    EXPECT_EQ(result->Get(2), 6);

    delete result;
}

TYPED_TEST(MutableSequenceTypedTest, WhereFiltersElements) {
    TypeParam seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);

    Sequence<int>* result = seq.Where(IsEven);

    ASSERT_EQ(result->GetLength(), 2u);
    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);

    delete result;
}

TYPED_TEST(MutableSequenceTypedTest, FindFirstReturnsMatchingIndex) {
    TypeParam seq;
    seq.Append(3);
    seq.Append(8);
    seq.Append(12);

    EXPECT_EQ(seq.FindFirst(GreaterThanTen), 2);
}

TYPED_TEST(MutableSequenceTypedTest, FindFirstReturnsMinusOneWhenNotFound) {
    TypeParam seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);

    EXPECT_EQ(seq.FindFirst(GreaterThanTen), -1);
}

TYPED_TEST(MutableSequenceTypedTest, ThrowsOnOutOfRange) {
    TypeParam seq;
    seq.Append(1);

    EXPECT_THROW(seq.Get(1), std::out_of_range);
    EXPECT_THROW(seq.Remove(1), std::out_of_range);
    EXPECT_THROW(seq.InsertAt(2, 5), std::out_of_range);
}

TYPED_TEST(MutableSequenceTypedTest, ReduceComputesSum) {
    TypeParam seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);

    EXPECT_EQ(seq.Reduce(Sum, 0), 10);
}

TYPED_TEST(MutableSequenceTypedTest, GetSubsequenceReturnsCorrectRange) {
    TypeParam seq;
    seq.Append(10);
    seq.Append(20);
    seq.Append(30);
    seq.Append(40);

    Sequence<int>* sub = seq.GetSubsequence(1, 2);

    ASSERT_EQ(sub->GetLength(), 2u);
    EXPECT_EQ(sub->Get(0), 20);
    EXPECT_EQ(sub->Get(1), 30);

    delete sub;
}
