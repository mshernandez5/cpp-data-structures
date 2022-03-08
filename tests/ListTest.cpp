#include <catch2/catch_test_macros.hpp>
#include <List.h>

void testListAddRemove(ds::List<int> *list)
{
    SECTION("Initial size is zero.")
    {
        REQUIRE(list->size() == 0);
    }
    SECTION("Add one element.")
    {
        int val = 5;
        list->add(val);
        REQUIRE(list->size() == 1);
        REQUIRE(list->at(0) == val);
        REQUIRE(list->contains(val));
        SECTION("Remove by index.")
        {
            list->removeAt(0);
            REQUIRE(list->size() == 0);
            REQUIRE(!list->contains(val));
        }
        SECTION("Remove by value.")
        {
            list->remove(5);
            REQUIRE(list->size() == 0);
            REQUIRE(!list->contains(val));
        }
    }
    SECTION("Add multiple elements.")
    {
        const int qty = 6;
        int a[qty] = {1, 2, 3, 4, 5, 5};
        for (int i = 0; i < qty; ++i)
        {
            list->add(a[i]);
            REQUIRE(list->size() == i + 1);
            REQUIRE(list->contains(a[i]));
        }
        SECTION("Remove each element by first index.")
        {
            for (int i = 0; i < qty; ++i)
            {
                list->removeAt(0);
                REQUIRE(list->size() == qty - 1 - i);
            }
        }
        SECTION("Remove each element by value.")
        {
            for (int i = 0; i < qty; ++i)
            {
                REQUIRE(list->remove(a[i]));
                REQUIRE(list->size() == qty - 1 - i);
            }
        }
    }
}

void testListPut(ds::List<int> *list)
{
    const int qty = 6;
    int a[qty] = {1, 2, 3, 4, 5, 5};
    SECTION("Put all elements in from front.")
    {
        for (int i = qty - 1; i >= 0; --i)
        {
            list->put(0, a[i]);
            REQUIRE(list->size() == qty - i);
            REQUIRE(list->contains(a[i]));
        }
    }
    SECTION("Put all elements in from back.")
    {
        for (int i = 0; i < qty; ++i)
        {
            list->put(i, a[i]);
            REQUIRE(list->size() == i + 1);
            REQUIRE(list->contains(a[i]));
        }
    }
    for (int i = 0; i < qty; ++i)
    {
        REQUIRE(a[i] == list->at(i));
    }
}

void testListSet(ds::List<int> *list)
{
    const int qty = 5;
    int a[qty] = {1, 2, 3, 4, 5};
    for (int i = 0; i < qty; ++i)
    {
        list->add(0);
    }
    for (int i = 0; i < qty; ++i)
    {
        list->set(i, a[i]);
    }
    for (int i = 0; i < qty; ++i)
    {
        REQUIRE(a[i] == list->at(i));
    }
}