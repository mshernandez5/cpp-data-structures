#include <catch2/catch_test_macros.hpp>
#include <ArrayList.h>

#include "ListTest.h"

TEST_CASE("Add & remove ArrayList elements via List interface (no resize).")
{
    ds::ArrayList<int> list(100);
    testListAddRemove(&list);
}

TEST_CASE("Add & remove ArrayList elements via List interface (resize required).")
{
    ds::ArrayList<int> list;
    testListAddRemove(&list);
}

TEST_CASE("Put elements in ArrayList via List interface.")
{
    ds::ArrayList<int> list;
    testListPut(&list);
}

TEST_CASE("Set elements values in ArrayList via List interface.")
{
    ds::ArrayList<int> list;
    testListSet(&list);
}

TEST_CASE("Copy ArrayList with contents.")
{
    ds::ArrayList<int> list;
    // Add Integers 1-5
    for (int i = 1; i < 6; ++i)
    {
        list.add(i);
    }
    // Copy List
    ds::ArrayList<int> copy = list;
    // Check That The Lists Are Equivalent
    REQUIRE(list.size() == 5);
    REQUIRE(copy.size() == 5);
    for (int i = 0; i < list.size(); ++i)
    {
        int expected = i + 1;
        REQUIRE(list.at(i) == expected);
        REQUIRE(copy.at(i) == expected);
    }
    // Add Integers 6-10 To Original List
    for (int i = 6; i < 11; ++i)
    {
        list.add(i);
    }
    // Check That Lists Are Now Different
    REQUIRE(list.size() == 10);
    REQUIRE(copy.size() == 5);
    for (int i = 0; i < list.size(); ++i)
    {
        int expected = i + 1;
        REQUIRE(list.at(i) == expected);
        if (i < copy.size())
        {
            REQUIRE(copy.at(i) == expected);
        }
    }
}

TEST_CASE("Test move semantics.")
{
    // Create & Populate List
    ds::ArrayList<int> list;
    for (int i = 0; i < 10; ++i)
    {
        list.add(i * 2);
    }
    REQUIRE(list.size() == 10);
    // Move List Resources & Check Contents
    ds::ArrayList<int> moved = std::move(list);
    REQUIRE(moved.size() == 10);
    for (int i = 0; i < 10; ++i)
    {
        REQUIRE(moved.at(i) == i * 2);
    }
    // Make Sure Moved List Is Empty But Functional
    SECTION("Moved list must be in empty but valid state.")
    {
        REQUIRE(list.size() == 0);
        for (int i = 0; i < 10; ++i)
        {
            list.add(i * 3);
        }
        REQUIRE(list.size() == 10);
        for (int i = 0; i < 10; ++i)
        {
            REQUIRE(list.at(i) == i * 3);
        }
    }
}