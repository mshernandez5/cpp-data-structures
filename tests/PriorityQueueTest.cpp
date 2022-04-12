#include <catch2/catch_test_macros.hpp>
#include <LinkedList.h>

#include "HeapPriorityQueue.h"

TEST_CASE("Adding & removing a single element.")
{
    ds::HeapPriorityQueue<int> pq;
    SECTION("Priority queue is initially empty.")
    {
        REQUIRE(pq.empty());
        REQUIRE(pq.size() == 0);
    }
    SECTION("Add one element.")
    {
        int val = 5;
        pq.add(val);
        REQUIRE(!pq.empty());
        REQUIRE(pq.size() == 1);
        SECTION("Peek element multiple times.")
        {
            for (int i = 0; i < 3; ++i)
            {
                int top = pq.peek();
                REQUIRE(top == val);
                REQUIRE(!pq.empty());
                REQUIRE(pq.size() == 1);
            }
        }
        SECTION("Remove element.")
        {
            int top = pq.peek();
            pq.drop();
            REQUIRE(top == val);
            REQUIRE(pq.empty());
            REQUIRE(pq.size() == 0);
        }
    }
}

void testAddRemoveSequentialInts(ds::HeapPriorityQueue<int> &pq)
{
    // Queue Integers 1-10 In Reverse Order
    for (int i = 10; i > 0; --i)
    {
        pq.add(i);
    }
    // Check Size
    REQUIRE(!pq.empty());
    REQUIRE(pq.size() == 10);
    // Dequeue All Elements, Check Order
    for (int i = 1; i < 11; ++i)
    {
        REQUIRE(pq.peek() == i);
        pq.drop();
    }
    // Check Size
    REQUIRE(pq.empty());
    REQUIRE(pq.size() == 0);
}

TEST_CASE("Adding and removing sequential integers.")
{
    ds::HeapPriorityQueue<int> pq;
    testAddRemoveSequentialInts(pq);
    SECTION("Repeat test reusing same priority queue.")
    {
        testAddRemoveSequentialInts(pq);
    }
}

TEST_CASE("Copy populated priority queue.")
{
    ds::HeapPriorityQueue<int> pq;
    // Queue Integers 1-5 In Reverse Order
    for (int i = 5; i > 0; --i)
    {
        pq.add(i);
    }
    // Copy Queue
    ds::HeapPriorityQueue<int> copy = pq;
    // Queue Integers 10-6 In Reverse Order
    for (int i = 10; i > 5; --i)
    {
        pq.add(i);
    }
    // Check Contents
    REQUIRE(pq.size() == 10);
    REQUIRE(copy.size() == 5);
    for (int i = 1; i < 11; ++i)
    {
        REQUIRE(pq.peek() == i);
        pq.drop();
        if (i < copy.size())
        {
            REQUIRE(copy.peek() == i);
            copy.drop();
        }
    }
}

TEST_CASE("Test PriorityQueue/Heap move semantics.")
{
    // Queue Integers 1-5
    ds::HeapPriorityQueue<int> pq;
    for (int i = 5; i > 0; --i)
    {
        pq.add(i);
    }
    REQUIRE(pq.size() == 5);
    // Move PriorityQueue Resources
    ds::HeapPriorityQueue<int> moved = std::move(pq);
    // Make Sure Original Priority Queue Is Empty But Functional
    SECTION("Original priority queue is empty but in valid state.")
    {
        REQUIRE(pq.size() == 0);
        for (int i = 10; i > 5; --i)
        {
            pq.add(i);
        }
        REQUIRE(pq.size() == 5);
        for (int i = 6; i < 11; ++i)
        {
            REQUIRE(pq.peek() == i);
            pq.drop();
        }
    }
    // Check Contents Of Moved Priority Queue
    REQUIRE(moved.size() == 5);
    for (int i = 1; i < 6; ++i)
    {
        REQUIRE(moved.peek() == i);
        moved.drop();
    }
}

TEST_CASE("Test priority queue assignment operator.")
{
    // Create First Queue With Integers 1-5
    ds::HeapPriorityQueue<int> pq;
    for (int i = 5; i > 0; --i)
    {
        pq.add(i);
    }
    // Create Second Queue With Different Contents
    ds::HeapPriorityQueue<int> other;
    for (int i = 10; i > 2; --i)
    {
        other.add(i);
    }
    // Ensure Correct Sizes
    REQUIRE(pq.size() == 5);
    REQUIRE(other.size() == 8);
    // Replace Contents Of Second
    other = pq;
    // Check Contents
    REQUIRE(pq.size() == 5);
    REQUIRE(other.size() == 5);
    for (int i = 1; i < 6; ++i)
    {
        REQUIRE(pq.peek() == i);
        pq.drop();
        REQUIRE(other.peek() == i);
        other.drop();
    }
}

TEST_CASE("Test PriorityQueue/Heap ordering with alternate comparator.")
{
    // Create Max Priority Queue With std::greater
    ds::HeapPriorityQueue<int, std::greater<int>> pq;
    // Add Integers In Reverse Order
    for (int i = 0; i < 10; ++i)
    {
        pq.add(i * 2);
    }
    REQUIRE(pq.size() == 10);
    // Check Ordering
    for (int i = 9; i >= 0; --i)
    {
        REQUIRE(pq.peek() == i * 2);
        pq.drop();
    }
}