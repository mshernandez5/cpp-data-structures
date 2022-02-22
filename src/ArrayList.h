#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <utility>
#include <stdexcept>
#include "List.h"

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
             * @brief Expand the array if necessary to ensure
             *        at least a certain amount of free space
             *        is available.
             * 
             * @param numSpaces The number of free spaces required.
             */
            void ensureSpace(int numSpaces)
            {
                // Return If No Resize Necessary
                if (qty + numSpaces <= capacity)
                {
                    return;
                }
                // Find Target Capacity
                int targetCapacity = capacity;
                do
                {
                    targetCapacity *= 2;
                } while (qty + numSpaces > targetCapacity);
                // Resize To Meet Target Capacity
                T *resized = new T[targetCapacity];
                for (int i = 0; i < capacity; ++i)
                {
                    resized[i] = std::move(arr[i]);
                }
                delete[] arr;
                arr = resized;
                capacity = targetCapacity;
            }

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
             * @brief Destroy the array list.
             */
            ~ArrayList()
            {
                delete[] arr;
            }

            virtual void add(const T &item)
            {
                // Ensure Array Can Accomodate 1 More Element
                ensureSpace(1);
                // Insert New Element
                arr[qty++] = item;
            }

            virtual void put(int index, const T &item)
            {
                // Check Index
                if (index < 0 || index > qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Ensure Array Can Accomodate 1 More Element
                ensureSpace(1);
                // Shift Items Right To Open Space
                for (int i = qty - 1; i >= index; --i)
                {
                    arr[i + 1] = arr[i];
                }
                arr[index] = item;
                // Increment Item Count
                ++qty;
            }

            virtual void set(int index, const T &item)
            {
                // Check Index
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Replace Item
                arr[index] = item;
            }

            virtual bool remove(const T &item)
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

            virtual void removeAt(int index)
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

            virtual T& at(int index)
            {
                // Check Index
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Return Item
                return arr[index];
            }

            virtual bool contains(const T &item)
            {
                // Return True If Item Could Be Found
                return findFirst(item) != -1;
            }

            virtual int size()
            {
                // Return Number Of Items In List
                return qty;
            }
    };
}

#endif // ARRAY_LIST_H