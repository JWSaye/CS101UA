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
    Dll(){
        head = NULL;
        _size = 0;
    }
    Dll(const Dll &src){
        head = NULL;
        _size = 0;
        DllNode *ptr = src.head;
        for(int i = 0; i < src._size; i++){
            int ins = ptr->value;
            insert(i, ins);
            if(ptr->next != NULL){
                ptr = ptr->next;
            }
        }
    } // create a deep copy of the src list
    Dll(const int arr[], int size){
        head = NULL;
        _size = 0;
        for(int i = 0; i < size; i++){
            insert(i, arr[i]);
        }
    } // create a linked list containing the elements of the array
    Dll &operator=(const Dll &src){
        head = src.head;
        return *this;
    } // create a deep copy of the src list
    ~Dll(){
        DllNode *tmp = NULL;
          while (head)
          {
              tmp = head;
              head = head->next;
              delete tmp;
          }
          head = NULL;
          free(head);
    } // free all memory

    bool empty() const{return (_size == 0);} // return if the list is empty in O(1)
    int size() const{return _size;} // return how many items are in the list in O(1)

    int &at(int rank){
        if(rank < 0 || rank >= _size){
            throw IndexOutOfRangeException("index(): Index out of range", rank);
        }

        DllNode *new1 = new DllNode;
        new1 = head;
        for(int i = 1; i <= rank; i++){
            new1 = new1->next;
        }
        return new1->value;
    } // return a reference to the value of the list at a rank/index
    void insert(int rank, int value){
        if(rank < 0 || rank > _size){
            throw IndexOutOfRangeException("index(): Index out of range", rank);
        }

        DllNode *new1 = new DllNode;
        new1->prev = NULL;
        new1->next = NULL;
        new1->value = value;

        if(_size == 0){
            head = new1;
        }
        else{
            DllNode *new2 = new DllNode;
            new2 = head;

            if(rank == 0){
                new1->next = new2;
                new2->prev = new1;
                head = new1;
                new1->prev = NULL;
            }
            else{
                for(int i = 1; i < rank; i++){
                    new2 = new2->next;
                }

                new1->next = new2->next;
                new2->next = new1;
                new1->prev = new2;

                if(new1->next != NULL){
                    new1->next->prev = new1;
                }
            }
        }
        _size++;
    } // insert a value at the rank/index
    int remove(int rank){
        if(rank < 0 || rank >= _size){
            throw IndexOutOfRangeException("index(): Index out of range", rank);
        }

        DllNode *new1 = new DllNode;
        new1 = head;

        for(int i = 0; i < rank; i++){
            new1 = new1->next;
        }

        if(new1->prev == NULL){
            if(new1->next == NULL){
                head = NULL;
            }
            else{
                new1->next->prev = NULL;
                head = new1->next;
            }
        }

        else if(new1->next == NULL){
            new1->prev->next = NULL;
        }

        else{
            new1->next->prev = new1->prev;
            new1->prev->next = new1->next;
        }

        _size--;
        return new1->value;
    } // remove the node at the rank/index and return its value

    void clear(){
        head = NULL;
        _size = 0;
    } // reset the list to an empty list
    void display(ostream &os) const{
        DllNode *ptr;
        ptr = head;
        os << "[ ";
        while(ptr != NULL){
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "]";
    } // write the contents of the list to the ostream
};

ostream &operator<<(ostream &os, const Dll &list){
    list.display(os);
    return os;
} // write the contents of the list to the ostream

#endif
