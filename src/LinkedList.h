#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>
#include "List.h"

namespace ds
{
    /**
     * @brief A doubly-linked list.
     * 
     * @tparam T The type of item to store.
     */
    template<typename T>
    class LinkedList : public List<T>
    {
        private:
            /**
             * @brief Internal node structure used to store items.
             */
            struct Node
            {
                Node *prev;
                Node *next;
                T item;
            };

            /**
             * @brief The first node in the linked list.
             */
            Node *head;

            /**
             * @brief The last node in the linked list.
             */
            Node *tail;

            /**
             * @brief The number of nodes in the linked list.
             */
            int qty;

            /**
             * @brief Remove a node from the linked list.
             * 
             * Removes a node from the linked list and
             * decrements the node count.
             * 
             * @param node The node to remove.
             */
            void remove(Node *node)
            {
                Node* prev = node->prev;
                Node* next = node->next;
                // Relink Previous Node Or Reset Head If None Exists
                if (prev == nullptr)
                {
                    head = next;
                }
                else
                {
                    prev->next = next;
                }
                // Relink Next Node Or Reset Tail If None Exists
                if (next == nullptr)
                {
                    tail = prev;
                }
                else
                {
                    next->prev = prev;
                }
                // Deallocate Unlinked Node
                delete node;
                // Decrement Node Count
                --qty;
            }

            /**
             * @brief Finds the node corresponding to the given index.
             * 
             * @param index The index of the node.
             * @return Node* A pointer to the node.
             */
            Node* findNodeByIndex(int index)
            {
                // Throw Exception If Index Out Of Range
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Find Node Corresponding To Index
                Node *node = head;
                for (int i = 0; i < index; ++i)
                {
                    node = node->next;
                }
                return node;
            }

            /**
             * @brief Finds the first node containing the given item.
             * 
             * @param item The item to search for.
             * @return Node* A pointer to the first node containing
             *               the item or nullptr if none was found.
             */
            Node* findNodeByItem(const T &item)
            {
                // Search For Node With Item
                Node *current = head;
                while (current != nullptr)
                {
                    if (current->item == item)
                    {
                        return current;
                    }
                    current = current->next;
                }
                // No Node With Item Was Found
                return nullptr;
            }
        
        public:
            /**
             * @brief Construct a new linked list.
             */
            LinkedList()
            {
                head = nullptr;
                tail = nullptr;
                qty = 0;
            }

            /**
             * @brief Destroy the linked list.
             */
            ~LinkedList()
            {
                tail = nullptr;
                while (head != nullptr)
                {
                    Node *temp = head;
                    head = head->next;
                    delete temp;
                }
            }

            /**
             * @brief Add an item to the front of the list.
             * 
             * @param item The item to add.
             */
            void addFirst(const T &item)
            {
                // Save Reference To Previous Head
                Node *prevHead = head;
                // Move Head Pointer To New Node
                head = new Node {nullptr, head, item};
                if (prevHead == nullptr)
                {
                    // First Element, Set Tail Pointer
                    tail = head;
                }
                else
                {
                    // Link To Previous Head
                    prevHead->prev = head;
                }
                // Increment Node Count
                ++qty;
            }

            /**
             * @brief Add an item to the end of the list.
             * 
             * @param item The item to add.
             */
            void addLast(const T &item)
            {
                // Save Reference To Previous Tail
                Node *prevTail = tail;
                // Move Tail Pointer To New Node
                tail = new Node {prevTail, nullptr, item};
                if (prevTail == nullptr)
                {
                    // First Element, Set Head Pointer
                    head = tail;
                }
                else
                {
                    // Link To Previous Tail
                    prevTail->next = tail;
                }
                // Increment Node Count
                ++qty;
            }

            virtual void add(const T &item)
            {
                // Add Equivalent To Add Last
                addLast(item);
            }

            virtual void put(int index, const T &item)
            {
                // Throw Exception If Index Out Of Range
                if (index < 0 || index >= qty)
                {
                    throw std::out_of_range("Index out of range!");
                }
                // Use Special Function If Adding To Start
                if (index == 0)
                {
                    addFirst(item);
                    return;
                }
                // Use Special Function If Adding To End
                if (index == qty)
                {
                    addLast(item);
                    return;
                }
                // Find Nodes That Should Be Linked Before & After Newly Added Node
                Node *next = findNodeByIndex(index);
                Node *prev = next->prev;
                // Place New Node & Relink Surrounding Nodes
                Node *node = new Node {prev, next, item};
                prev->next = node;
                next->prev = node;
                // Increment Node Count
                ++qty;
            }

            virtual void set(int index, const T &item)
            {
                // Find Node At Index (Throws Exception If Out Of Range)
                Node *node = findNodeByIndex(index);
                // Replace Item
                node->item = item;
            }

            virtual bool remove(const T &item)
            {
                // Search For Node With Item
                Node *node = findNodeByItem(item);
                // If Item Not Found, Return False
                if (node == nullptr)
                {
                    return false;
                }
                // Remove Node With Item
                remove(node);
                return true;
            }

            virtual void removeAt(int index)
            {
                // Remove Node Found At Given Index (Throws Exception If Out Of Range)
                remove(findNodeByIndex(index));
            }

            virtual T& at(int index)
            {
                // Find Node At Given Index & Return Item (Throws Exception If Out Of Range)
                return findNodeByIndex(index)->item;
            }

            virtual bool contains(const T &item)
            {
                // Return True If Node Containing Item Could Be Found
                return findNodeByItem(item) != nullptr;
            }

            virtual int size()
            {
                // Return Number Of Items In List
                return qty;
            }
    };
}

#endif // LINKED_LIST_H