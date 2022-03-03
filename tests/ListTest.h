#ifndef LINKED_LIST_TEST_H
#define LINKED_LIST_TEST_H

#include <List.h>

/**
 * @brief Test adding & removing elements.
 * 
 * @param list An empty list.
 */
void testListAddRemove(ds::List<int> *list);

/**
 * @brief Test putting elements into specific positions.
 * 
 * @param list An empty list.
 */
void testListPut(ds::List<int> *list);

/**
 * @brief Tests setting values at specific positions.
 * 
 * @param list An empty list.
 */
void testListSet(ds::List<int> *list);

#endif //LINKED_LIST_TEST_H