#ifndef LIST_H
#define LIST_H

namespace ds
{
    /**
     * @brief An abstract interface for List implementations.
     * 
     * Represents a data structure which stores items in order
     * of insertion where items can be accessed by index.
     * 
     * @tparam T The type of item to store.
     */
    template<typename T>
    class List
    {
        public:
            /**
             * @brief Add an item to the list.
             * 
             * @param item The item to add.
             */
            virtual void add(const T &item) = 0;

            /**
             * @brief Add an item at the given index.
             * 
             * @throws std::out_of_range If the specified index is out of range.
             * 
             * @param index The index.
             * @param item The item to add.
             */
            virtual void put(int index, const T &item) = 0;

            /**
             * @brief Replace the item at the given index.
             * 
             * @throws std::out_of_range If the specified index is out of range.
             * 
             * @param index The index.
             * @param item The new item to set at the given index.
             */
            virtual void set(int index, const T &item) = 0;
            
            /**
             * @brief Remove the first occurrence of an item from the list.
             * 
             * @param item The item to remove.
             * @return true If the item was found and removed.
             * @return false If the item could not be found in the list.
             */
            virtual bool remove(const T &item) = 0;

            /**
             * @brief Remove the item at the given index.
             * 
             * @throws std::out_of_range If the specified index is out of range.
             * 
             * @param index The index of the item to remove. 
             */
            virtual void removeAt(int index) = 0;

            /**
             * @brief Get the item at the given index.
             * 
             * @throws std::out_of_range If the specified index is out of range.
             * 
             * @param index The index of the item.
             * @return T& A reference to the item.
             */
            virtual T& at(int index) = 0;

            /**
             * @brief Checks whether the list contains an item.
             * 
             * @param item The item to search for.
             * @return true If the list contains the item.
             * @return false If the list does not contain the item.
             */
            virtual bool contains(const T &item) = 0;

            /**
             * @brief Returns the number of items stored in the list.
             * 
             * @return int The number of items stored by the list.
             */
            virtual int size() = 0;

            /**
             * @brief Returns true if there are no items in the list.
             * 
             * @return true If there are no items in the list.
             * @return false If there is at least one item in the list.
             */
            virtual bool empty() = 0;
    };
}

#endif // LIST_H