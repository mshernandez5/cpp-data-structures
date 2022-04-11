#ifndef HEAP_H
#define HEAP_H

#include <utility>
#include <cstring>
#include "ArrayUtilities.h"

namespace ds::detail
{
    /**
     * @brief A min-heap implementation.
     * 
     * The heap compares elements according to the functor given as
     * a template parameter, defaulting to std::less which results
     * in the "smallest" elements reaching the top of the heap.
     * 
     * @tparam T The type to store.
     * @tparam Compare A comparison functor type for ordering.
     */
    template<typename T, typename Compare = std::less<T>>
    class Heap
    {
        private:
            const int DEFAULT_INITIAL_CAPACITY = 5;

            int capacity;
            int qty;

            T *arr;

            Compare compare;

            /**
             * @brief Turns the specified subtree into a min-heap.
             *        Child subtrees, if any, must already be min-heaps.
             * 
             * @param rootIndex The root of the subtree.
             */
            void minHeapify(int rootIndex)
            {
                int smallestValueIndex = rootIndex;
                int leftIndex = rootIndex * 2;
                int rightIndex = leftIndex + 1;
                // Find Index Of Smallest Value
                if (leftIndex <= qty && compare(arr[leftIndex], arr[smallestValueIndex]))
                {
                    smallestValueIndex = leftIndex;
                }
                if (rightIndex <= qty && compare(arr[rightIndex], arr[smallestValueIndex]))
                {
                    smallestValueIndex = rightIndex;
                }
                // Swap & Recursively Rebuild Heap If Necessary
                if (smallestValueIndex != rootIndex)
                {
                    std::swap(arr[rootIndex], arr[smallestValueIndex]);
                    minHeapify(smallestValueIndex);
                }
            }

            /**
             * @brief Swaps a newly added item upwards to its
             *        appropriate position in the heap.
             */
            void minUpHeap()
            {
                int child = qty;
                int parent = child / 2;
                while (child > 1 && compare(arr[child], arr[parent]))
                {
                    std::swap(arr[parent], arr[child]);
                    child = parent;
                    parent /= 2;
                }
            }

        public:
            /**
             * @brief Construct a new heap.
             */
            Heap()
            {
                capacity = DEFAULT_INITIAL_CAPACITY + 1; // Skipping Index 0
                qty = 0;
                arr = new T[capacity];
            }

            /**
             * @brief Construct a new heap with a specific initial capacity.
             * 
             * @param initialCapacity The initial capacity to give the internal array.
             */
            Heap(int initialCapacity)
            {
                capacity = initialCapacity + 1; // Skipping Index 0
                qty = 0;
                arr = new T[capacity];
            }

            /**
             * @brief Construct a deep copy of an existing Heap.
             * 
             * @param original The original Heap to copy.
             */
            Heap(const Heap &original)
            {
                capacity = original.capacity;
                qty = original.qty;
                arr = new T[capacity];
                std::memcpy(arr, original.arr, sizeof(T) * capacity);
            }

            /**
             * @brief Construct a new Heap by taking the resources of another.
             * 
             * The original Heap will be left in an empty but valid state.
             * 
             * @param original The original Heap to move (R-value).
             */
            Heap(Heap &&original)
            {
                // Take Resources
                capacity = original.capacity;
                qty = original.qty;
                arr = original.arr;
                // Reset State Of Original
                original.capacity = 0;
                original.qty = 0;
                original.arr = nullptr;
            }

            /**
             * @brief Destroy the heap.
             */
            ~Heap()
            {
                delete[] arr;
            }

            /**
             * @brief Adds an item to the heap.
             * 
             * @param item The item to add to the heap.
             */
            void add(const T &item)
            {
                // Ensure Array Can Accomodate 1 More Element (+2 Since Skipping Index 0)
                array_util::ensureCapacity(arr, capacity, qty + 2);
                // Insert Item At End Of Heap
                arr[++qty] = item;
                // Rebuild Heap
                minUpHeap();
            }

            /**
             * @brief Returns a reference to the item at the top
             *        of the heap without removing it.
             * 
             * This method has undefined behavior if called when
             * the heap is empty; check this beforehand.
             * 
             * @return T& A reference to the item at the top of the heap.
             */
            T& peek()
            {
                return arr[1];
            }

            /**
             * @brief Drops the item at the top of the heap.
             * 
             * This method has undefined behavior if called when
             * the heap is empty; check this beforehand.
             */
            void drop()
            {
                // Drop Item & Rebuild Heap
                arr[1] = arr[qty--];
                minHeapify(1);
            }

            /**
             * @brief Returns the number of items stored in the heap.
             * 
             * @return int The number of items stored by the heap.
             */
            int size()
            {
                return qty;
            }

            /**
             * @brief Returns true if there are no items in the heap.
             * 
             * @return true If there are no items in the heap.
             * @return false If there is at least one item in the heap.
             */
            bool empty()
            {
                return qty == 0;
            }
    };
}

#endif //HEAP_H