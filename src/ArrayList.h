#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <utility>
#include <stdexcept>
#include <cstring>
#include "List.h"
#include "ArrayUtilities.h"

namespace ds
{
    /**
     * @brief A list utilizing an array to store items.
     * 
     * @tparam T The type of item to store.
     */
    template<typename T>
    class ArrayList : public List<T>
    {
        private:
            const int DEFAULT_INITIAL_CAPACITY = 5;

            int capacity;
            int qty;

            T *arr;

            /**
             * @brief Return the index corresponding to the first
             *        occurence of an item or -1 if none was found.
             * 
             * @param item The item to search for.
             * @return int The index of the item, or -1 if none was found.
             */
            int findFirst(const T &item)
            {
                for (int i = 0; i < qty; ++i)
                {
                    if (arr[i] == item)
                    {
                        return i;
                    }
                }
                return -1;
            }

        public:
            /**
             * @brief Construct a new array list.
             */
            ArrayList()
            {
                capacity = DEFAULT_INITIAL_CAPACITY;
                qty = 0;
                arr = new T[capacity];
            }

            /**
             * @brief Construct a new array list with a specific initial capacity.
             * 
             * @param initialCapacity The initial capacity to give the internal array.
             */
            ArrayList(int initialCapacity)
            {
                capacity = initialCapacity;
                qty = 0;
                arr = new T[capacity];
            }

            /**
             * @brief Construct a deep copy of an existing ArrayList.
             * 
             * @param original The original ArrayList to copy.
             */
            ArrayList(const ArrayList &original)
            {
                capacity = original.capacity;
                qty = original.qty;
                arr = new T[capacity];
                std::memcpy(arr, original.arr, sizeof(T) * capacity);
            }

            /**
             * @brief Destroy the array list.
             */
            ~ArrayList()
            {
                delete[] arr;
            }

            void add(const T &item) override
            {
                // Ensure Array Can Accomodate 1 More Element
                ds::detail::array_util::ensureCapacity(arr, capacity, qty + 1);
                // Insert New Element
                arr[qty++] = item;
            }

            void put(int index, const T &item) override
            {
                // Check Index
                if (index < 0 || index > qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Ensure Array Can Accomodate 1 More Element
                ds::detail::array_util::ensureCapacity(arr, capacity, qty + 1);
                // Shift Items Right To Open Space
                for (int i = qty - 1; i >= index; --i)
                {
                    arr[i + 1] = arr[i];
                }
                arr[index] = item;
                // Increment Item Count
                ++qty;
            }

            void set(int index, const T &item) override
            {
                // Check Index
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Replace Item
                arr[index] = item;
            }

            bool remove(const T &item) override
            {
                // Search For First Item Occurence
                int index = findFirst(item);
                // Return False If Not Found
                if (index == -1)
                {
                    return false;
                }
                // Shift Items Left To Fill Space
                for (int i = index + 1; i < qty; ++i)
                {
                    arr[i - 1] = arr[i];
                }
                // Decrement Item Count
                --qty;
                return true;
            }

            void removeAt(int index) override
            {
                // Check Index
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Shift Items Left To Fill Space
                for (int i = index + 1; i < qty; ++i)
                {
                    arr[i - 1] = arr[i];
                }
                // Decrement Item Count
                --qty;
            }

            T& at(int index) override
            {
                // Check Index
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Return Item
                return arr[index];
            }

            bool contains(const T &item) override
            {
                // Return True If Item Could Be Found
                return findFirst(item) != -1;
            }

            int size() override
            {
                // Return Number Of Items In List
                return qty;
            }

            bool empty() override
            {
                return qty == 0;
            }
    };
}

#endif // ARRAY_LIST_H