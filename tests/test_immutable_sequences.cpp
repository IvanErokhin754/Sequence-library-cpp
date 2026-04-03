#include <gtest/gtest.h>
#include "ImmutableArraySequence.hpp"
#include "ImmutableListSequence.hpp"
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
class ImmutableSequenceTypedTest : public ::testing::Test {
};

using ImmutableImplementations = ::testing::Types<
    ImmutableArraySequence<int>,
    ImmutableListSequence<int>
>;

TYPED_TEST_SUITE(ImmutableSequenceTypedTest, ImmutableImplementations);

TYPED_TEST(ImmutableSequenceTypedTest, AppendReturnNewSequenceAndLeaveSourceUnchanged) {
    TypeParam seq;
    
    auto* seq2 = seq.Append(10);

    ASSERT_EQ(seq.GetLength(), 0u);

    ASSERT_NE(seq2, nullptr);
    ASSERT_EQ(seq2->GetLength(), 1u);
    EXPECT_EQ(seq2->Get(0), 10);

    delete seq2;
}

TYPED_TEST(ImmutableSequenceTypedTest, PrependReturnsNewSequenceAndLeavesSourceUnchanged) {
    TypeParam seq;

    auto* seq2 = seq.Prepend(10);

    ASSERT_EQ(seq.GetLength(), 0u);

    ASSERT_NE(seq2, nullptr);
    ASSERT_EQ(seq2->GetLength(), 1u);
    ASSERT_EQ(seq2->Get(0), 10);

    delete seq2;
}


TYPED_TEST(ImmutableSequenceTypedTest, InsertAtReturnsNewSequenceAndLeaveSourceUnchanged) {
    TypeParam seq;

    auto* seq1 = seq.Append(1);
    auto* seq2 = seq1->Append(3);
    auto* seq3 = seq2->InsertAt(1, 2);

    ASSERT_EQ(seq.GetLength(), 0u);
    ASSERT_EQ(seq1->GetLength(), 1u);
    ASSERT_EQ(seq2->GetLength(), 2u);

    ASSERT_EQ(seq3->GetLength(), 3u);
    EXPECT_EQ(seq3->Get(0), 1);
    EXPECT_EQ(seq3->Get(1), 2);
    EXPECT_EQ(seq3->Get(2), 3);

    delete seq1;
    delete seq2;
    delete seq3;
}

TYPED_TEST(ImmutableSequenceTypedTest, RemoveReturnNewSequenceAndLeavesSourceUnchanged) {
    TypeParam seq;

    auto* seq1 = seq.Append(1);
    auto* seq2 = seq1->Append(2);
    auto* seq3 = seq2->Append(3);
    auto* seq4 = seq3->Remove(1);

    ASSERT_EQ(seq3->GetLength(), 3u);
    EXPECT_EQ(seq3->Get(0), 1);
    EXPECT_EQ(seq3->Get(1), 2);
    EXPECT_EQ(seq3->Get(2), 3);

    ASSERT_EQ(seq4->GetLength(), 2u);
    EXPECT_EQ(seq4->Get(0), 1);
    EXPECT_EQ(seq4->Get(1), 3);

    delete seq1;
    delete seq2;
    delete seq3;
    delete seq4;
}

TYPED_TEST(ImmutableSequenceTypedTest, ConcatReturnsNewSequenceAndLeavesSourcesUnchanged) {
    TypeParam seqA;
    auto* a1 = seqA.Append(1);
    auto* a2 = a1->Append(2);

    TypeParam seqB;
    auto* b1 = seqB.Append(3);
    auto* b2 = b1->Append(4);

    Sequence<int>* result = a2->Concat(*b2);

    ASSERT_EQ(a2->GetLength(), 2u);
    EXPECT_EQ(a2->Get(0), 1);
    EXPECT_EQ(a2->Get(1), 2);

    ASSERT_EQ(b2->GetLength(), 2u);
    EXPECT_EQ(b2->Get(0), 3);
    EXPECT_EQ(b2->Get(1), 4);

    ASSERT_EQ(result->GetLength(), 4u);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 2);
    EXPECT_EQ(result->Get(2), 3);
    EXPECT_EQ(result->Get(3), 4);

    delete a1;
    delete a2;
    delete b1;
    delete b2;
    delete result;
}

TYPED_TEST(ImmutableSequenceTypedTest, GetSubsequenceReturnsCorrectRange) {
    TypeParam seq;

    auto* s1 = seq.Append(10);
    auto* s2 = s1->Append(20);
    auto* s3 = s2->Append(30);
    auto* s4 = s3->Append(40);

    Sequence<int>* sub = s4->GetSubsequence(1, 2);

    ASSERT_EQ(sub->GetLength(), 2u);
    EXPECT_EQ(sub->Get(0), 20);
    EXPECT_EQ(sub->Get(1), 30);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete sub;
}

TYPED_TEST(ImmutableSequenceTypedTest, MapReturnsNewSequenceAndLeavesSourceUnchanged) {
    TypeParam seq;

    auto* s1 = seq.Append(1);
    auto* s2 = s1->Append(2);
    auto* s3 = s2->Append(3);

    Sequence<int>* mapped = s3->Map(DoubleValue);

    ASSERT_EQ(s3->GetLength(), 3u);
    EXPECT_EQ(s3->Get(0), 1);
    EXPECT_EQ(s3->Get(1), 2);
    EXPECT_EQ(s3->Get(2), 3);

    ASSERT_EQ(mapped->GetLength(), 3u);
    EXPECT_EQ(mapped->Get(0), 2);
    EXPECT_EQ(mapped->Get(1), 4);
    EXPECT_EQ(mapped->Get(2), 6);

    delete s1;
    delete s2;
    delete s3;
    delete mapped;
}

TYPED_TEST(ImmutableSequenceTypedTest, WhereReturnsFilteredSequenceAndLeavesSourceUnchanged) {
    TypeParam seq;

    auto* s1 = seq.Append(1);
    auto* s2 = s1->Append(2);
    auto* s3 = s2->Append(3);
    auto* s4 = s3->Append(4);

    Sequence<int>* filtered = s4->Where(IsEven);

    ASSERT_EQ(s4->GetLength(), 4u);
    EXPECT_EQ(s4->Get(0), 1);
    EXPECT_EQ(s4->Get(1), 2);
    EXPECT_EQ(s4->Get(2), 3);
    EXPECT_EQ(s4->Get(3), 4);

    ASSERT_EQ(filtered->GetLength(), 2u);
    EXPECT_EQ(filtered->Get(0), 2);
    EXPECT_EQ(filtered->Get(1), 4);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete filtered;
}

TYPED_TEST(ImmutableSequenceTypedTest, ReduceComputesSum) {
    TypeParam seq;

    auto* s1 = seq.Append(1);
    auto* s2 = s1->Append(2);
    auto* s3 = s2->Append(3);
    auto* s4 = s3->Append(4);

    EXPECT_EQ(s4->Reduce(Sum, 0), 10);

    delete s1;
    delete s2;
    delete s3;
    delete s4;
}

TYPED_TEST(ImmutableSequenceTypedTest, FindFirstReturnsMatchingIndex) {
    TypeParam seq;

    auto* s1 = seq.Append(3);
    auto* s2 = s1->Append(8);
    auto* s3 = s2->Append(12);

    EXPECT_EQ(s3->FindFirst(GreaterThanTen), 2);

    delete s1;
    delete s2;
    delete s3;
}

TYPED_TEST(ImmutableSequenceTypedTest, FindFirstReturnsMinusOneWhenNotFound) {
    TypeParam seq;

    auto* s1 = seq.Append(1);
    auto* s2 = s1->Append(2);
    auto* s3 = s2->Append(3);

    EXPECT_EQ(s3->FindFirst(GreaterThanTen), -1);

    delete s1;
    delete s2;
    delete s3;
}

TYPED_TEST(ImmutableSequenceTypedTest, ThrowsOnOutOfRange) {
    TypeParam seq;

    EXPECT_THROW(seq.Get(0), std::out_of_range);

    auto* s1 = seq.Append(1);

    EXPECT_THROW(s1->Get(1), std::out_of_range);
    EXPECT_THROW(s1->Remove(1), std::out_of_range);
    EXPECT_THROW(s1->InsertAt(2, 5), std::out_of_range);

    delete s1;
}