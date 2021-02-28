#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include <algorithm>
#include "exception.h"

template<typename Type>

class DoubleLinkedList {
public:
    class DoubleNode {
    public:
        /*
         * Constructor
         * Set volume of the node, the previous node & the next node pointer
         */
        DoubleNode(Type const & = Type(), DoubleNode * = nullptr, DoubleNode * = nullptr);

        /*
         * Return volume of the node
         */
        Type value() const;

        /*
         * Return the pointer of the previous node
         */
        DoubleNode *previous() const;

        /*
         * Return the pointer of the next node
         */
        DoubleNode *next() const;

        /*
         * Store volume of the node
         */
        Type nodeValue;
        /*
         * Store the pointer of the previous node
         */
        DoubleNode *previousNode;
        /*
         * Store the pointer of the next node
         */
        DoubleNode *nextNode;
    };

    /*
     * Constructor without input parameter
     * Set the list head & the list tail & the list size to the default volume
     */
    DoubleLinkedList();

    /*
     * Constructor with input parameter: Double linked list
     * Set the list head & the list tail & the list size to the default volume
     * Copy elements of the list to this list
     */
    DoubleLinkedList(DoubleLinkedList const &);

    /*
     * Destructor
     * While the list is not empty destroys any element.
     */
    ~DoubleLinkedList();

    // Accessors

    /*
     * Return size of the list
     */
    int size() const;

    // Check if the list size is zero or not
    bool empty() const;

    /*
     * Return the volume at the top of the list. If the list is empty
     * throws an Underflow error.
     */
    Type front() const;

    /*
     * Return the volume at the end of the list. If the list is empty
     * throws an Underflow error.
     */
    Type back() const;

    /*
     * Return the reference of the head of the list
     */
    DoubleNode *begin() const;

    /*
     * Return the reference of the tail of the list
     */
    DoubleNode *end() const;

    /*
     * Return the address of the first node whose value is equal to the value of the input parameter.
     * If the corresponding volume is not found, nullptr is returned.
    */
    DoubleNode *find(Type const &) const;

    /*
     * Return the number of elements whose volume is equal to the value of the input parameter.
     */
    int count(Type const &) const;

    // Mutators

    /*
     * Move the input link list to this linked list.
     * Swap the head, tail & size of the lists
     */
    void swap(DoubleLinkedList &);

    /*
     * Create a new node with the volume given in the input,
     * Insert it at the beginning of the list.
     * Move the list head to new node
     */
    void pushFront(Type const &);

    /*
     * Create a new node with the volume given in the input,
     * Insert it at the end of the list.
     * Move the list tail to new node.
     * Increase the list size.
     */
    void pushBack(Type const &);

    /*
     * Delete the starting node of the list. If the list is empty
     * throw an Underflow error.
     * Move the list head to next node.
     * Reduce the list size.
     */
    void popFront();

    /*
     * Delete the last node of the list. If the list is empty
     * throw an Underflow error.
     * Move the list tail to previous node.
     * Reduce the list size
     */
    void popBack();

    /*
     * Delete all nodes whose value is equal to the volume of the input parameter,
     * Return the number of deleted nodes.
     * Navigate the list, delete corresponding node
     * Link the previous & the next node
     */
    int erase(Type const &);

private:
    /*
     *Pointer to the beginning of the list
     */
    DoubleNode *listHead;
    /*
     * Pointer to the end of the list
     */
    DoubleNode *listTail;
    /*
     * Store the size of the list
     */
    int listSize;

    // Friends


    //  friend std::ostream &operator<<(std::ostream &, DoubleLinkedList<Type> const &);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template<typename Type>
DoubleLinkedList<Type>::DoubleLinkedList() :

        listHead(nullptr),
        listTail(nullptr),
        listSize(0) {

}

template<typename Type>
DoubleLinkedList<Type>::DoubleLinkedList(DoubleLinkedList const &list) :

        listHead(nullptr),
        listTail(nullptr),
        listSize(0) {

    DoubleNode *ptr = list.begin();
    while (ptr != nullptr) {

        pushBack(ptr->value());
        ptr = ptr->next();
    }

}

template<typename Type>

DoubleLinkedList<Type>::~DoubleLinkedList() {

    while (!empty()) {


        popFront();
    }


}

template<typename Type>

int DoubleLinkedList<Type>::size() const {

    return listSize;
}

template<typename Type>

bool DoubleLinkedList<Type>::empty() const {

    return listSize == 0;
}

template<typename Type>

Type DoubleLinkedList<Type>::front() const {

    if (empty()) {
        throw Underflow();
    }

    return begin()->value();
}

template<typename Type>

Type DoubleLinkedList<Type>::back() const {

    if (empty()) {
        throw Underflow();
    }

    return end()->value();
}

template<typename Type>

typename DoubleLinkedList<Type>::DoubleNode *DoubleLinkedList<Type>::begin() const {

    return listHead;
}

template<typename Type>

typename DoubleLinkedList<Type>::DoubleNode *DoubleLinkedList<Type>::end() const {

    return listTail;
}

template<typename Type>

typename DoubleLinkedList<Type>::DoubleNode *DoubleLinkedList<Type>::find(Type const &value) const {

    DoubleNode *node = listHead;

    while (node != nullptr) {
        if (node->value() == value) return node;

        node = node->next();
    }

    return nullptr;
}

template<typename Type>

int DoubleLinkedList<Type>::count(Type const &value) const {

    int listCount = 0;

    DoubleNode *node = listHead;

    while (node != nullptr) {
        if (node->value() == value) listCount++;

        node = node->next();
    }

    return listCount;
}

template<typename Type>

void DoubleLinkedList<Type>::swap(DoubleLinkedList &list) {

    std::swap(this->listHead, list.listHead);
    std::swap(this->listTail, list.listTail);
    std::swap(this->listSize, list.listSize);

}

template<typename Type>

void DoubleLinkedList<Type>::pushFront(Type const &value) {

    // Next node is old head
    auto *newNode = new DoubleNode(value, nullptr, begin());

    if (empty()) {
        // If list is empty the tail & the head are equal
        listTail = newNode;
    } else {
        listHead->previousNode = newNode;
    }

    listHead = newNode;

    listSize++;

}

template<typename Type>

void DoubleLinkedList<Type>::pushBack(Type const &value)  {

    // Previous node is old tail
    auto *newNode = new DoubleNode(value, end(), nullptr);

    if (empty()) {
        // If list is empty the tail & the head are equal
        listHead = newNode;
    } else {
        listTail->nextNode = newNode;
    }

    listTail = newNode;

    listSize++;

}

template<typename Type>

void DoubleLinkedList<Type>::popFront() {


    if (!empty()) {

        listSize--;

        DoubleNode *temp = begin();
        listHead = begin()->next();

        // If the list is empty the listHead will be NULL so it has not previous node then the listTail is NULL too
        if (!empty()) {

            listHead->previousNode = nullptr;
        }

        else
            listTail = nullptr;

        delete temp;


    } else throw Underflow();

}

template<typename Type>

void DoubleLinkedList<Type>::popBack() {

    if (!empty()) {

        listSize--;

        DoubleNode *temp = end();
        listTail = end()->previous();

        // If the list is empty the listTail will be NULL so it has not next node then the listHead is NULL too
        if (!empty())
            listTail->nextNode = nullptr;
        else
            listHead = nullptr;

        delete temp;

    } else throw Underflow();

}

template<typename Type>

int DoubleLinkedList<Type>::erase(Type const &value) {

    int number = 0;

    DoubleNode *node = listHead;

    while (node != nullptr) {

        if (node->value() == value) {

            DoubleNode *temp = node;

            // If node is the head, It must move to next node
            if (node != begin())
                node->previous()->nextNode = node->next();
            else
                listHead = node->next();

            // If node is the tail, It must move to previous node
            if (node != end())
                node->next()->previousNode = node->previous();
            else
                listTail = node->previous();

            delete temp;

            listSize--;
            number++;
        }

        node = node->next();
    }

    return number;
}

template<typename Type>

DoubleLinkedList<Type>::DoubleNode::DoubleNode(
        Type const &nv,
        DoubleLinkedList::DoubleNode *pn,
        DoubleLinkedList::DoubleNode *nn) :

        nodeValue(nv),
        previousNode(pn),
        nextNode(nn) {

}

template<typename Type>

Type DoubleLinkedList<Type>::DoubleNode::value() const {

    return nodeValue;
}

template<typename Type>

typename DoubleLinkedList<Type>::DoubleNode *DoubleLinkedList<Type>::DoubleNode::previous() const {

    return previousNode;
}

template<typename Type>

typename DoubleLinkedList<Type>::DoubleNode *DoubleLinkedList<Type>::DoubleNode::next() const {

    return nextNode;
}



#endif