#ifndef HEAP_PRIORITY_QUEUE_H
#define HEAP_PRIORITY_QUEUE_H

#include "Queue.h"
#include "Heap.h"

namespace ds
{
    /**
     * @brief A priority queue which uses a heap to maintain ordering.
     * 
     * The priority queue sorts elements from least to greatest
     * according to comparisons using the < operator;
     * the priority queue therefore requires consistent
     * comparisons between items to function correctly.
     * 
     * @tparam T The type of item to store.
     */
    template<typename T>
    class HeapPriorityQueue : public Queue<T>
    {
        private:
            ds::detail::Heap<T> heap;
        public:
            void add(const T &item) override
            {
                heap.add(item);
            }

            T& peek() override
            {
                return heap.peek();
            }

            void drop() override
            {
                return heap.drop();
            }

            int size() override
            {
                return heap.size();
            }

            bool empty() override
            {
                return heap.empty();
            }
    };
}

#endif // HEAP_PRIORITY_QUEUE_H