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
            /**
             * @brief Construct a new heap-based priority queue.
             */
            HeapPriorityQueue() : heap()
            {
            }

            /**
             * @brief Construct a new heap-based priority queue with a specific initial capacity.
             * 
             * @param initialCapacity The initial capacity.
             */
            HeapPriorityQueue(int initialCapacity) : heap(initialCapacity)
            {
            }

            /**
             * @brief Construct a deep copy of an existing priority queue.
             * 
             * @param original The original priority queue to copy.
             */
            HeapPriorityQueue(const HeapPriorityQueue &original) : heap(original.heap)
            {
            }

            /**
             * @brief Construct a new priority queue by taking the resources of another.
             * 
             * The original priority queue will be left in an empty but valid state.
             * 
             * @param original The original priority queue to move (R-value).
             */
            HeapPriorityQueue(HeapPriorityQueue &&original) : heap(std::move(original.heap))
            {
            }

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