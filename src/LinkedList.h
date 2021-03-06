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
             * @brief Swaps the underlying resources/data of two linked lists.
             * 
             * @param other The linked list to swap resources with.
             */
            void swapResources(LinkedList &other)
            {
                std::swap(head, other.head);
                std::swap(tail, other.tail);
                std::swap(qty, other.qty);
            }

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
             * @brief Construct a copy of an existing LinkedList.
             * 
             * @param original The original LinkedList to copy.
             */
            LinkedList(const LinkedList &original)
            {
                qty = original.qty;
                // Head & Tail Null If Original List Is Empty
                if (qty == 0)
                {
                    head = nullptr;
                    tail = nullptr;
                    return;
                }
                // Original List Populated, Must Copy Node Chain
                Node *og = original.head;
                head = new Node {nullptr, nullptr, og->item};
                Node *cur = head;
                for (int i = 1; i < qty; ++i)
                {
                    og = og->next;
                    cur->next = new Node {cur, nullptr, og->item};
                    cur = cur->next;
                }
                tail = cur;
            }

            /**
             * @brief Construct a new LinkedList by taking the resources of another.
             * 
             * The original LinkedList will be left in an empty but valid state.
             * 
             * @param original The original LinkedList to move (R-value).
             */
            LinkedList(LinkedList &&original)
            {
                // Take Resources
                head = original.head;
                tail = original.tail;
                qty = original.qty;
                // Reset State Of Original
                original.head = nullptr;
                original.tail = nullptr;
                original.qty = 0;
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
             * @brief Replaces the contents of this linked list with those of another.
             * 
             * @param other The linked list to copy resources from.
             * @return LinkedList& A reference to this modified linked list.
             */
            LinkedList& operator=(LinkedList other)
            {
                // Swap Resources With Local Copy
                swapResources(other);
                // Return Modified Object
                return *this;
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

            void add(const T &item) override
            {
                // Add Equivalent To Add Last
                addLast(item);
            }

            void put(int index, const T &item) override
            {
                // Throw Exception If Index Out Of Range
                if (index < 0 || index > qty)
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

            void set(int index, const T &item) override
            {
                // Find Node At Index (Throws Exception If Out Of Range)
                Node *node = findNodeByIndex(index);
                // Replace Item
                node->item = item;
            }

            bool remove(const T &item) override
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

            void removeAt(int index) override
            {
                // Remove Node Found At Given Index (Throws Exception If Out Of Range)
                remove(findNodeByIndex(index));
            }

            T& at(int index) override
            {
                // Find Node At Given Index & Return Item (Throws Exception If Out Of Range)
                return findNodeByIndex(index)->item;
            }

            bool contains(const T &item) override
            {
                // Return True If Node Containing Item Could Be Found
                return findNodeByItem(item) != nullptr;
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

#endif // LINKED_LIST_H