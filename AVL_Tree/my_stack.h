
#ifndef MYSTACK_H
#define MYSTACK_H

#include "linked_list.h"

using namespace std;

template < typename Type>
class Stack {

private:

    // List as linked list
    DoubleLinkedList<Type> linkedList;
public:

    // Check if list is empty or not
    bool empty() const;

    // Push in back of list
    void push(Type const &);

    // Pop of back of list
    Type pop();

};

template < typename Type>

bool Stack<Type>::empty() const {
    return linkedList.empty();
};

template < typename Type>

void Stack<Type>::push(Type const &value) {
    linkedList.pushBack(value);
};

template < typename Type>

Type Stack<Type>::pop() {

    Type back = linkedList.back();
    linkedList.popBack();
    return back;
};


#endif
