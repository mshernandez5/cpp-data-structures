#include <catch2/catch_test_macros.hpp>
#include <LinkedList.h>

#include "ListTest.h"

TEST_CASE("Add & remove LinkedList elements via List interface.")
{
    ds::LinkedList<int> list;
    testListAddRemove(&list);
}

TEST_CASE("Put elements in LinkedList via List interface.")
{
    ds::LinkedList<int> list;
    testListPut(&list);
}

TEST_CASE("Set elements values in LinkedList via List interface.")
{
    ds::LinkedList<int> list;
    testListSet(&list);
}

TEST_CASE("Add to front/back of LinkedList.")
{
    ds::LinkedList<int> list;
    int qty = 5;
    int vals[qty] = {1, 2, 3, 4, 5};
    SECTION("Add all from front.")
    {
        for (int i = qty - 1; i >= 0; --i)
        {
            list.addFirst(vals[i]);
            REQUIRE(list.contains(vals[i]));
            REQUIRE(list.size() == qty - i);
        }
        for (int i = 0; i < qty; ++i)
        {
            REQUIRE(vals[i] == list.at(i));
        }
    }
    SECTION("Add all from back.")
    {
        for (int i = 0; i < qty; ++i)
        {
            list.addLast(vals[i]);
            REQUIRE(list.contains(vals[i]));
            REQUIRE(list.size() == i + 1);
        }
        for (int i = 0; i < qty; ++i)
        {
            REQUIRE(vals[i] == list.at(i));
        }
    }
    SECTION("Add in non-standard order.")
    {
        list.add(3);
        REQUIRE(list.contains(3));
        REQUIRE(list.size() == 1);
        list.addFirst(2);
        REQUIRE(list.contains(2));
        REQUIRE(list.size() == 2);
        list.put(0, 1);
        REQUIRE(list.contains(1));
        REQUIRE(list.size() == 3);
        list.addLast(5);
        REQUIRE(list.contains(5));
        REQUIRE(list.size() == 4);
        list.put(3, 4);
        REQUIRE(list.contains(4));
        REQUIRE(list.size() == 5);
        for (int i = 0; i < qty; ++i)
        {
            REQUIRE(vals[i] == list.at(i));
        }
    }
}