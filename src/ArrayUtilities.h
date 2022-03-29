#ifndef ARRAY_UTILITIES_H
#define ARRAY_UTILITIES_H

#include <utility>

namespace ds::detail::array_util
{
    /**
     * @brief Expands an array if necessary to ensure
     *        at least a certain amount of free space
     *        is available.
     * 
     * After this function is called the array must
     * have a capacity at least as large as the
     * requiredCapacity.
     * 
     * The array pointer and capacity will be changed
     * by reference if expanded. The old array will
     * be deleted in this case - don't use pointers to
     * the previous array after calling this method.
     * 
     * @tparam T The type being stored by the array.
     * @param arr The array pointer, passed by reference (will be pointed to a new array if expanded).
     * @param capacity A reference to capacity of the array (will be modified if changed).
     * @param requiredCapacity The minimum capacity the array must accomodate.
     */
    template<typename T>
    void ensureCapacity(T *&arr, int &capacity, int requiredCapacity)
    {
        // Return If No Resize Necessary
        if (requiredCapacity <= capacity)
        {
            return;
        }
        // Find Target Capacity
        int targetCapacity = capacity;
        do
        {
            targetCapacity *= 2;
        } while (requiredCapacity > targetCapacity);
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
}

#endif // ARRAY_UTILITIES_H