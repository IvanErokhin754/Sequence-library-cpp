#include <gtest/gtest.h>
#include "LinkedList.hpp"
#include <stdexcept>

TEST(LinkedListTest, DefaultConstructorCreatesEmptyList) {
    LinkedList<int> list;
    EXPECT_EQ(list.GetSize(), 0u);
}

TEST(LinkedListTest, AppendAddsElementToEnd) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetFirst(), 10);
    EXPECT_EQ(list.GetLast(), 20);
    EXPECT_EQ(list.GetElement(0), 10);
    EXPECT_EQ(list.GetElement(1), 20);
}

TEST(LinkedListTest, PrependAddsElementToFront) {
    LinkedList<int> list;
    list.Prepend(20);
    list.Prepend(10);

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetFirst(), 10);
    EXPECT_EQ(list.GetLast(), 20);
    EXPECT_EQ(list.GetElement(0), 10);
    EXPECT_EQ(list.GetElement(1), 20);
}

TEST(LinkedListTest, GetFirstReturnsFirstElement) {
    LinkedList<int> list;
    list.Append(5);
    list.Append(7);

    EXPECT_EQ(list.GetFirst(), 5);
}

TEST(LinkedListTest, GetLastReturnsLastElement) {
    LinkedList<int> list;
    list.Append(5);
    list.Append(7);

    EXPECT_EQ(list.GetLast(), 7);
}

TEST(LinkedListTest, GetElementReturnsCorrectElement) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);

    EXPECT_EQ(list.GetElement(0), 1);
    EXPECT_EQ(list.GetElement(1), 2);
    EXPECT_EQ(list.GetElement(2), 3);
}

TEST(LinkedListTest, InsertAtInsertsInMiddle) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(3);

    list.InsertAt(1, 2);

    ASSERT_EQ(list.GetSize(), 3u);
    EXPECT_EQ(list.GetElement(0), 1);
    EXPECT_EQ(list.GetElement(1), 2);
    EXPECT_EQ(list.GetElement(2), 3);
}

TEST(LinkedListTest, InsertAtZeroPrepends) {
    LinkedList<int> list;
    list.Append(2);
    list.InsertAt(0, 1);

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetFirst(), 1);
    EXPECT_EQ(list.GetLast(), 2);
}

TEST(LinkedListTest, InsertAtSizeAppends) {
    LinkedList<int> list;
    list.Append(1);
    list.InsertAt(1, 2);

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetFirst(), 1);
    EXPECT_EQ(list.GetLast(), 2);
}

TEST(LinkedListTest, RemoveAtRemovesMiddleElement) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);

    list.RemoveAt(1);

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetElement(0), 1);
    EXPECT_EQ(list.GetElement(1), 3);
}

TEST(LinkedListTest, RemoveAtZeroRemovesHead) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);

    list.RemoveAt(0);

    ASSERT_EQ(list.GetSize(), 1u);
    EXPECT_EQ(list.GetFirst(), 2);
    EXPECT_EQ(list.GetLast(), 2);
}

TEST(LinkedListTest, RemoveAtLastRemovesTail) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);

    list.RemoveAt(2);

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetFirst(), 1);
    EXPECT_EQ(list.GetLast(), 2);
}

TEST(LinkedListTest, CopyConstructorCreatesIndependentCopy) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);

    LinkedList<int> copy(list);

    ASSERT_EQ(copy.GetSize(), 2u);
    EXPECT_EQ(copy.GetElement(0), 1);
    EXPECT_EQ(copy.GetElement(1), 2);

    copy.SetElement(0, 100);

    EXPECT_EQ(list.GetElement(0), 1);
    EXPECT_EQ(copy.GetElement(0), 100);
}

TEST(LinkedListTest, AssignmentOperatorCreatesIndependentCopy) {
    LinkedList<int> list1;
    list1.Append(5);
    list1.Append(6);
    list1.Append(7);

    LinkedList<int> list2;
    list2 = list1;

    ASSERT_EQ(list2.GetSize(), 3u);
    EXPECT_EQ(list2.GetElement(0), 5);
    EXPECT_EQ(list2.GetElement(1), 6);
    EXPECT_EQ(list2.GetElement(2), 7);

    list2.SetElement(1, 52);

    EXPECT_EQ(list1.GetElement(0), 5);
    EXPECT_EQ(list1.GetElement(1), 6);
    EXPECT_EQ(list1.GetElement(2), 7);
    EXPECT_EQ(list2.GetElement(1), 52);
}

TEST(LinkedListTest, SelfAssignmentDoesNotBreakList) {
    LinkedList<int> list;
    list.Append(11);
    list.Append(22);

    list = list;

    ASSERT_EQ(list.GetSize(), 2u);
    EXPECT_EQ(list.GetElement(0), 11);
    EXPECT_EQ(list.GetElement(1), 22);
}

TEST(LinkedListTest, ThrowsOnOutOfRange) {
    LinkedList<int> list;
    list.Append(1);

    EXPECT_THROW(list.GetElement(1), std::out_of_range);
    EXPECT_THROW(list.InsertAt(2, 5), std::out_of_range);
    EXPECT_THROW(list.RemoveAt(1), std::out_of_range);
}

TEST(LinkedListTest, EmptyListThrowsOnGetFirstAndGetLast) {
    LinkedList<int> list;
    
    EXPECT_THROW(list.GetFirst(), std::out_of_range);
    EXPECT_THROW(list.GetLast(), std::out_of_range);
}

TEST(LinkedListTest, RemoveOnlyElementMakesListEmpty) {
    LinkedList<int> list;
    list.Append(52);

    list.RemoveAt(0);

    EXPECT_EQ(list.GetSize(), 0u);
    EXPECT_THROW(list.GetFirst(), std::out_of_range);
    EXPECT_THROW(list.GetLast(), std::out_of_range);
}

TEST(LinkedListTest, SetElementChangesCorrectNode) {
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Append(3);

    list.SetElement(1, 100);

    EXPECT_EQ(list.GetElement(0), 1);
    EXPECT_EQ(list.GetElement(1), 100);
    EXPECT_EQ(list.GetElement(2), 3);
}

TEST(LinkedListTest, SetElementThrowsOutOfRange) {
    LinkedList<int> list;
    EXPECT_THROW(list.SetElement(0, 1), std::out_of_range);
}

