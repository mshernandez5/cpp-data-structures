#ifndef QUEUE_H
#define QUEUE_H

namespace ds
{
    /**
     * @brief An abstract interface for Queue implementations.
     * 
     * Represents a data structure which stores items in a
     * defined order, typically FIFO.
     * 
     * Unlike an ordered list, ordering is maintained by
     * the container itself and only the element at the front
     * of the queue is required to be publicly accessible.
     * 
     * @tparam T The type of item to store.
     */
    template<typename T>
    class Queue
    {
        public:
            /**
             * @brief Add an item to the queue.
             * 
             * @param item The item to add to the queue.
             */
            virtual void add(const T &item) = 0;

            /**
             * @brief Returns a reference to the front item in
             *        the queue without removing it.
             * 
             * This method has undefined behavior if called when
             * the queue is empty; check this beforehand.
             * 
             * @return T& A reference to the item at the front of the queue.
             */
            virtual T& peek() = 0;

            /**
             * @brief Drops the item at the front of the queue.
             * 
             * This method has undefined behavior if called when
             * the queue is empty; check this beforehand.
             */
            virtual void drop() = 0;

            /**
             * @brief Returns the number of items in the queue.
             * 
             * @return int The number of items in the queue.
             */
            virtual int size() = 0;

            /**
             * @brief Returns true if there are no items in the queue.
             * 
             * @return true If there are no items in the queue.
             * @return false If there is at least one item in the queue.
             */
            virtual bool empty() = 0;
    };
}

#endif // QUEUE_H