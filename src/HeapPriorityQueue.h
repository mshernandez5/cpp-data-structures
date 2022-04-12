#ifndef HEAP_PRIORITY_QUEUE_H
#define HEAP_PRIORITY_QUEUE_H

#include "Queue.h"
#include "Heap.h"

namespace ds
{
    /**
     * @brief A priority queue which uses a min-heap to maintain ordering.
     * 
     * The priority queue compares elements according to the functor given
     * as a template parameter, defaulting to std::less which results
     * in the "smallest" elements reaching the top of the queue.
     * 
     * @tparam T The type of item to store.
     * @tparam Compare A comparison functor type for ordering.
     */
    template<typename T, typename Compare = std::less<T>>
    class HeapPriorityQueue : public Queue<T>
    {
        private:
            ds::detail::Heap<T, Compare> heap;
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
             * @brief Construct a copy of an existing priority queue.
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

            /**
             * @brief Replaces the contents of this HeapPriorityQueue with those of another.
             * 
             * @param other The HeapPriorityQueue to copy resources from.
             * @return HeapPriorityQueue& A reference to this modified HeapPriorityQueue.
             */
            HeapPriorityQueue& operator=(HeapPriorityQueue other)
            {
                heap = other.heap;
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