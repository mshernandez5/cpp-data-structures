#include <iostream>
#include "ArrayList.h"
#include "LinkedList.h"

void printElements(ds::List<int> &list)
{
    for (int i = 0; i < list.size(); ++i)
    {
        std::cout << i << ": " << list.at(i) << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    // Linked List
    ds::LinkedList<int> linkedList;
    linkedList.add(5);
    linkedList.addFirst(4);
    linkedList.addLast(7);
    linkedList.put(2, 6);
    std::cout << "Linked List:" << std::endl;
    printElements(linkedList);

    // Array List
    ds::ArrayList<int> arrayList(1);
    arrayList.add(5);
    arrayList.put(0, 4);
    arrayList.add(7);
    arrayList.put(2, 6);
    std::cout << "Array List:" << std::endl;
    printElements(arrayList);
}