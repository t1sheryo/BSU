#include <iostream>
#include "Bank.h"
#include "MyException.h"

int main() {

    try {
        // конструктор и вывод в поток
        bank b(999, 10, 3.25);
        std::cout << b;

        // оператор присваивания
        bank a(739, 1,0.75);
        b = a;
        std::cout << "a: " << a << "b: " << b ;

        // унарный минус
        std::cout << "-b: " << -b;

        // +, -, +=, -=
        bank c(9, 9, 0);
        bank d;
        d = b + c;
        std::cout << "d: " << d;

        a = d - b;
        std::cout << "\nminus:\nb: " << b << "d:" << d;
        std::cout << "a: " << a;

        a -= b;
        std::cout << "a: " << a;
        a += b;
        std::cout << "a: " << a;

        // ==, < , >
        std::cout << "\n dlya ==, >, < :\na:" << a << "b: " << b << "c: " << c << "d: " << d;
        std::cout << std::boolalpha << "a == b: " << (a == b) << "\na > b: " << (a > b) << "\na < b: " << (a < b) << '\n';
    }
    catch(const MyException& ex){
        std::cerr << ex.what();
    }

    return 0;
}
