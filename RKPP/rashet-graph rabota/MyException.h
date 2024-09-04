#ifndef RASHET_GRAPH_RABOTA_MYEXCEPTION_H
#define RASHET_GRAPH_RABOTA_MYEXCEPTION_H

class MyException{
private:
    const char* error;
public:
    MyException(const char* ex){
        error = ex;
    }
    const char* what() const { return error; }
};

#endif //RASHET_GRAPH_RABOTA_MYEXCEPTION_H
