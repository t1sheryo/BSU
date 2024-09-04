#include "iterator.h"

int findMax(int a, int b){
    if(a > b) return a;
    return b;
}

SetIterator* Set::createIterator() const {
    return new SetIterator(this);
}

Set& Set::operator=(const Set &a) {
    if(this == &a){
        return *this;
    }
//    if(s != nullptr){
//        delete[] s;
//    }
    index = a.index;
    capacity = a.capacity;
    size = a.size;
    if(size == 0){ s = nullptr; }
    s = new int[size];
    for(size_t i = 0; i < size; ++i){
        s[i] = a.s[i];
    }
    return *this;
}

Set& Set::operator&(const Set &a) {
    if(size == 0 && a.size == 0) { return *new Set();}
    int max_cap = findMax(capacity, a.capacity);
    int cur_size = 0;
    int *arr = new int[max_cap];
    for(size_t i = 0; i < size; ++i){
        for(size_t j = 0; j < a.size; ++j){
            if(s[i] == a.s[j]){
                cur_size++;
                arr[i] = s[i];
            }
        }
    }
    return *new Set(arr, cur_size);
}

Set& Set::operator&=(const Set &a) {
    *this = *this&a;
    return *this;
}

Set& Set::operator|(const Set &a) {
    if(this == &a) return *this;
    if(size == 0 && a.size == 0) { return *new Set();}
    int cur_cap = capacity + a.capacity;
    int cur_size = size;
    int* arr = new int [cur_cap];
    for(size_t i = 0; i < size; ++i){
        arr[i] = s[i];
    }
    for(size_t i = 0; i < a.size; ++i){
        bool flag = false;
        for(size_t j = 0; j < size; ++j){
            if(a.s[i] == s[j]) flag = true;
        }
        if(!flag){
            arr[cur_size++] = a.s[i];
        }
    }
    return *new Set(arr, cur_size);
}

Set& Set::operator|=(const Set &a) {
    *this = *this|a;
    return *this;
}

Set& Set::operator/(const Set &a) {
    if(this == &a) return *new Set();
    int* arr = new int[size];
    int cur_size = 0;
    for(size_t i = 0; i < size; ++i){
        bool flag = false;
        for(size_t j = 0; j < a.size; ++j){
            int fi = s[i];
            int se = a.s[j];
            if(s[i] == a.s[i]) flag = true;
        }
        if(!flag){
            arr[cur_size++] = s[i];
        }
    }
    return *new Set(arr, cur_size);
}
Set& Set::operator/=(const Set &a) {
    *this = *this/a;
    return *this;
}

Set& Set::operator>>(int num) {
    for(size_t i = 0; i < size; ++i){
        if(s[i] == num){
            throw "Not unique element!";
        }
    }
    if(size == capacity){
            if(capacity == 0) capacity = 1;
            capacity *= 2;
            size += 1;
            int* n = new int[capacity];
            for(size_t i = 0; i + 1 < size; ++i){
                n[i] = s[i];
            }
            n[++index] = num;
            if(s != nullptr){
                delete[] s;
            }
            s = new int[capacity];
            for(size_t i = 0; i < size; ++i){
                s[i] = n[i];
            }
            delete[] n;
            return *this;
    }
    else{
        size += 1;
        s[++index] = num;
        return *this;
    }
}

std::ostream& operator<<(std::ostream& out, const Set& a){
    if(a.size == 0){
        std::cout << "--------";
    }
     for(size_t i = 0; i < a.size; ++i){
         //int aboba = a.s[i];
         out << a.s[i] << " ";
     }
     out << '\n';
     return out;
}

int Set::Size() const { return size; }

void Set::Clear() {
    delete[] s;
    size = 0;
    capacity = 0;
}

bool Set::IsEmpty() const { return size == 0; }

bool Set::IsFull() const { return size == capacity; }