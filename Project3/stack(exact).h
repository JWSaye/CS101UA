#ifndef __STACK_H__
#define __STACK_H__

#include "exceptions.h"
#include "dll.h"

class Stack {
private:
    Dll store;
public:
    Stack(); // create an empty stack
    void push(int value); // add an item to the top of the stack
    int pop(); // remove of the value at the top of the stack and return its value
    int peek(); // return the value at the top of the stack, keeping it in the stack
    int size() const; // return how many items are in the stack
    bool empty() const; // return if the stack is empty
    void display(ostream &os) const; // write the contents of the stack to the ostream
};

ostream &operator<<(ostream &os, const Stack &stack); // write the contents of the stack to the ostream

#endif
