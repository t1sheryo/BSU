#ifndef ITERATOR_ITERATOR_H
#define ITERATOR_ITERATOR_H

#include <iostream>

class SetIterator;

class Set{
private:
    int *s;
    int index;
    int capacity;
    int size;

public:
    friend class SetIterator;
    Set() : s(nullptr), index(-1), capacity(0), size(0) {}
    Set(int* arr, int _size): size(_size), index(_size - 1), capacity(_size * 2){
        s = new int[_size * 2];
        for(size_t i = 0; i < _size; ++i){
            s[i] = arr[i];
        }
    }

    Set(const Set& a): index(a.index), size(a.size), capacity(a.capacity){
        s = new int[size];
        for(size_t i = 0; i < size; ++i){
            s[i] = a.s[i];
        }
    }

    Set& operator=(const Set& a);
    Set& operator|(const Set& a);
    Set& operator|=(const Set& a);
    Set& operator&(const Set& a);
    Set& operator&=(const Set& a);
    Set& operator/(const Set& a);
    Set& operator/=(const Set& a);
    Set& operator>>(int num);
    friend std::ostream& operator<<(std::ostream& out, const Set& a);
    int Size() const;
    void Clear();
    bool IsEmpty() const;
    bool IsFull() const;

    SetIterator* createIterator() const;

    ~Set(){
        if(size != 0) delete[] s;
    }

};

class SetIterator{
private:
    const Set* st;
    int iter_index;
public:
    SetIterator(const Set* a){
        st = a;
    }
    int getIterIndex() const { return iter_index; }
    void first(){ iter_index = 0; }
    void next(){ iter_index++; }
    bool isDone(){ return iter_index == st->size; }
    int currentItem(){ return st->s[iter_index]; }
};


#endif //ITERATOR_ITERATOR_H
