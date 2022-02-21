#include <iostream>
#include "LinkedList.h"

int main(int argc, char *argv[])
{
    ds::LinkedList<int> list;
    list.add(5);
    list.addFirst(4);
    list.addLast(7);
    list.put(2, 6);
    for (int i = 0; i < list.size(); ++i)
    {
        std::cout << i << ": " << list.at(i) << std::endl;
    }
}