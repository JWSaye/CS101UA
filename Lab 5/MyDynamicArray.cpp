#include <iostream>
using namespace std;
class MyDynamicArray {
    private:
        int size, capacity, error, *a;
    public:
        MyDynamicArray() {
            /* Your code goes here */
            capacity = 2;
            size = 0;
            a = new int[capacity];
        }

        MyDynamicArray(int s) {
            /* Your code goes here */
            capacity = s;
            size = s;
            a = new int[capacity];
            for(int i = 0; i < size; i++){
                a[i] = 0;
            }
        }
        
        ~MyDynamicArray() {
            // Your code goes here
            cout << "In the destructor" << endl;
            delete[] a;
        }

        int& operator[](int i){
            /* Your code goes here */
            if(i >= size){
                error = 0;
                cout << "Out of bounds reference : " << i << endl;
                return error;
            }

            else{
                return a[i];
            }
        }
        void add(int v) {
            /* Your code goes here */
            if(size == capacity){
                int *a_new;
                capacity = capacity * 2;
                cout << "Doubling to : " << capacity << endl;
                a_new = new int[capacity];
                for(int i = 0; i < size; i++){
                    a_new[i] = a[i];
                }
                for(int j = size; j < capacity; j++){
                    a_new[j] = 0;
                }
                delete[] a;
                a = a_new;
                a[size] = v;
                size++;
            }
            else{
                a[size] = v;
                size++;
            }
        }
        void del() {
           /* Your code goes here */
           if(size <= capacity/4){
               int *a_new;
               capacity = capacity/2;
               cout << "Reducing to : " << capacity << endl;
               a_new = new int[capacity];
               for(int i = 0; i < size; i++){
                   a_new[i] = a[i];
               }
               for(int j = size; j < capacity; j++){
                   a_new[j] = 0;
               }
               delete[] a;
               a = a_new;
           }
           a[size] = 0;
           size--;
        }
        int length() { return size;}
        void clear() {
            delete[] a;
            a = new int[capacity=2];
            size = 0;
        }
        
        MyDynamicArray& operator=(const MyDynamicArray& src) {
            cout << "In the copy assignment operator" << endl;
            capacity = src.capacity;
            size = src.size;
            delete[] a;
            a = new int;
            for(int i = 0; i < size; i++){
               a[i] = src.a[i];
            }
            return *this;
        }

        MyDynamicArray(const MyDynamicArray & src) {
            cout << "In the copy constructor" << endl;
            capacity = src.capacity;
            size = src.size;
            a = new int[capacity];
            for(int i = 0; i < size; i++){
                a[i] = src.a[i];
            }
        }
};

