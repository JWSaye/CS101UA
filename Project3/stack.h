#ifndef __STACK_H__
#define __STACK_H__

#include "exceptions.h"
#include "dll.h"

class Stack {
private:
    Dll store;
public:
    Stack() {} // create an empty stack

    void push(int value){
        //cout << "Pushing " << value << " to " << store.size() << endl;
        store.insert(store.size(), value);
    } // add an item to the top of the stack
    int pop(){
        if(this->empty()){
            throw InvalidOperationException("Stack empty.");
        }
        return store.remove(store.size() - 1);
    } // remove of the value at the top of the stack and return its value
    int peek(){
        if(this->empty()){
            throw InvalidOperationException("Stack empty.");
        }
        return store.at(store.size() - 1);
    } // return the value at the top of the stack, keeping it in the stack
    
    int size() const{return store.size();} // return how many items are in the stack

    bool empty() const{return store.empty();} // return if the stack is empty

    void display(ostream &os) const{
        Dll tempdll = store;
        Stack tempstck;

        if(store.size() > 0){
            for(int i = 0; i < tempdll.size(); i++){
                tempstck.push(tempdll.at(i));
            }

            os << "[ ";
            int tempsize = tempstck.size();

            for(int j = 0; j < tempsize; j++){
                os << tempstck.pop() << " ";
            }
            os << "]";
        }

        else{
            os << "[ ]";
        }
    } // write the contents of the stack to the ostream
};

ostream &operator<<(ostream &os, const Stack &stack){
    stack.display(os);
    return os;
} // write the contents of the stack to the ostream

#endif
