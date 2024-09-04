#ifndef MATRICES_TEMPLATE_MYEXCEPTION_H
#define MATRICES_TEMPLATE_MYEXCEPTION_H

#include <iostream>
#include <string>

class MyException {
private:
    std::string text;
public:
    MyException(std::string text) {
        text = text;
    }
    std::string what() {
        return text;
    }
};

#endif //MATRICES_TEMPLATE_MYEXCEPTION_H
