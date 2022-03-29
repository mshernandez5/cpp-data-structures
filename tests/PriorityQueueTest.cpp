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