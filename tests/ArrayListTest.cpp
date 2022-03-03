#include <catch2/catch_test_macros.hpp>
#include <ArrayList.h>

#include "ListTest.h"

TEST_CASE("Add & remove ArrayList elements via List interface (no resize).")
{
    ds::ArrayList<int> list(100);
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

TEST_CASE("Add & remove ArrayList elements via List interface (resize required).")
{
    ds::ArrayList<int> list;
    testListAddRemove(&list);
}