#ifndef ITERATOR_TEMPLATE_USER_CLASS_H
#define ITERATOR_TEMPLATE_USER_CLASS_H

#include <iostream>

class myType{
private:
    std::string name;
    int height;
public:
    myType() : name("unknown"), height(-1) {};
    myType(std::string n, int h) : name(n), height(h) {};
    myType& operator=(const myType& oth){
        if(this == &oth){
            return *this;
        }
        name = oth.name;
        height = oth.height;
        return *this;
    }
    bool operator==(const myType& oth){
        if(name == oth.name && height == oth.height){
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<(std::ostream& out, const myType& oth){
        out << "Name:" << oth.name << ", Height:" << oth.height << ";   ";
        return out;
    }
    myType operator+(const myType& oth){
        std::string s = name + oth.name;
        int h = height + oth.height;
        return myType(s, h);
    }

    myType operator+=(const myType& oth){
        return *this + oth;
    }
};

#endif //ITERATOR_TEMPLATE_USER_CLASS_H
