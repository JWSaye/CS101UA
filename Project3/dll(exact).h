#ifndef __DLL_H__
#define __DLL_H__

#include "exceptions.h"

class DllNode {
public:
    int value;
    DllNode *prev;
    DllNode *next;
};

class Dll {
private:
    DllNode *head;
    int _size;
public:
    Dll(); // create an empty list
    Dll(const Dll &src); // create a deep copy of the src list
    Dll(const int arr[], int size); // create a linked list containing the elements of the array
    Dll &operator=(const Dll &src); // create a deep copy of the src list
    ~Dll(); // free all memory

    bool empty() const; // return if the list is empty in O(1)
    int size() const; // return how many items are in the list in O(1)

    int &at(int rank); // return a reference to the value of the list at a rank/index
    void insert(int rank, int value); // insert a value at the rank/index
    int remove(int rank); // remove the node at the rank/index and return its value

    void clear(); // reset the list to an empty list
    void display(ostream &os) const; // write the contents of the list to the ostream
};

ostream &operator<<(ostream &os, const Dll &list); // write the contents of the list to the ostream

#endif
