#ifndef ITERATOR_ITERATOR_H
#define ITERATOR_ITERATOR_H

#include <iostream>

template<class T>
T findMax(T a, T b){
    if(a > b) return a;
    return b;
}

template<class G>
class SetIterator;

template<class T>
class Set{
private:
    T* s;
    int index;
    int capacity;
    int size;

public:
    friend class SetIterator<T>;
    Set() : s(nullptr), index(-1), capacity(0), size(0) {}
    Set(T* arr, int _size): size(_size), index(_size - 1), capacity(_size * 2){
        s = new T[_size * 2];
        for(size_t i = 0; i < _size; ++i){
            s[i] = arr[i];
        }
    }

    Set(const Set<T>& a): index(a.index), size(a.size), capacity(a.capacity){
        s = new T[size];
        for(size_t i = 0; i < size; ++i){
            s[i] = a.s[i];
        }
    }

    Set<T>& operator=(const Set<T> &a) {
        if(this == &a){
            return *this;
        }
        index = a.index;
        capacity = a.capacity;
        size = a.size;
        if(size == 0){ s = nullptr; }
        s = new T[size];
        for(size_t i = 0; i < size; ++i){
            s[i] = a.s[i];
        }
        return *this;
    }
    Set<T> operator|(const Set<T> &a) {
        if(this == &a) return *this;
        if(size == 0 && a.size == 0) { return *new Set<T>();}
        int cur_cap = capacity + a.capacity;
        int cur_size = size;
        T* arr = new T[cur_cap];
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
        return Set<T>(arr, cur_size);
    }
    Set<T>& operator|=(const Set<T> &a) {
        *this = *this|a;
        return *this;
    }
    Set<T> operator&(const Set<T> &a) {
        if(size == 0 && a.size == 0) { return *new Set<T>();}
        int max_cap = findMax(capacity, a.capacity);
        int cur_size = 0;
        T *arr = new T[max_cap];
        for(size_t i = 0; i < size; ++i){
            for(size_t j = 0; j < a.size; ++j){
                if(s[i] == a.s[j]){
                    cur_size++;
                    arr[i] = s[i];
                }
            }
        }
        return Set<T>(arr, cur_size);
    }
    Set<T>& operator&=(const Set<T> &a) {
        *this = *this&a;
        return *this;
    }
    Set<T> operator/(const Set<T> &a) {
        if(this == &a) return *new Set<T>();
        T* arr = new T[size];
        int cur_size = 0;
        for(size_t i = 0; i < size; ++i){
            bool flag = false;
            for(size_t j = 0; j < a.size; ++j){
                T fi = s[i];
                T se = a.s[j];
                if(s[i] == a.s[i]) flag = true;
            }
            if(!flag){
                arr[cur_size++] = s[i];
            }
        }
        return *new Set<T>(arr, cur_size);
    }
    Set<T>& operator/=(const Set<T> &a) {
        *this = *this/a;
        return *this;
    }
    Set<T>& operator>>(T num) {
        for(size_t i = 0; i < size; ++i){
            if(s[i] == num){
                throw "Not unique element!";
            }
        }
        if(size == capacity){
            if(capacity == 0) capacity = 1;
            capacity *= 2;
            size += 1;
            T* n = new T[capacity];
            for(size_t i = 0; i + 1 < size; ++i){
                n[i] = s[i];
            }
            n[++index] = num;
            if(s != nullptr){
                delete[] s;
            }
            s = new T[capacity];
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
    friend std::ostream& operator<<(std::ostream& out, const Set<T>& a){
        if(a.size == 0){
            std::cout << "--------";
        }
        for(size_t i = 0; i < a.size; ++i){
            out << a.s[i] << " ";
        }
        out << '\n';
        return out;
    }
    int Size() const { return size; }
    void Clear() {
        delete[] s;
        size = 0;
        capacity = 0;
    }
    bool IsEmpty() const { return size == 0; }
    bool IsFull() const { return size == capacity; };

    SetIterator<T>* createIterator() const {
        return new SetIterator(this);
    }

    ~Set(){
        if(size != 0) delete[] s;
    }

};

template<class G>
class SetIterator{
private:
    const Set<G>* st;
    int iter_index;
public:
    SetIterator(const Set<G>* a){
        st = a;
    }
    int getIterIndex() const { return iter_index; }
    void first(){ iter_index = 0; }
    void next(){ iter_index++; }
    bool isDone(){ return iter_index == st->size; }
    G currentItem(){ return st->s[iter_index]; }
};


#endif //ITERATOR_ITERATOR_H
