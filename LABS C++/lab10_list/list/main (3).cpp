#include <iostream>
#include "list.h"

void f(std::string& name, std::string& extension) {
    name = "Default";
    extension = ".noext";
}

void Print(std::string& n, std::string& e) {
    std::cout << n << " " << e << std::endl;
}

int main()
{
    try {
        int count = 0;
        List l1;
        l1.InsertFirst("GoodFile", ".txt");
        l1.InsertFirst("BadFile", ".jpg");
        l1.InsertLast("PhotoFile", ".image");
        std::cout << "List l1:\n";
        l1.Print();
        std::cout << std::boolalpha << "\nList l1 contains GoodFile.txt?\n" << l1.Contains("GoodFile", ".txt", count);
        std::cout << " " << count;
        std::cout << "\n\n\n";
        List l2;
        l2 = l1;
        std::cout << "List l2:\n";
        l2.Print();
        l2.DeleteLast();
        l2.DeleteFirst();
        std::cout << "\n\n\n";
        std::cout << "List l2:\n";
        l2.Print();

        std::cout << "\n\n\n";
        List l3(l2);
        std::cout << "List l3:\n";
        l3.Print();

        std::cout << "\n\n\n";
        l1.Delete("GoodFile", ".txt");
        std::cout << "List l1:\n";
        l1.Print();

        std::cout << "\n\n\n";
        std::cout << "List l2:\n";
        l2.Print();
        std::cout << "\n\n\nForEach():\n";
        l2.ForEach(Print);
        std::cout << "\n";
        std::cout << "List l2:\n";
        l2.Print();

        std::cout << "\n\n\n";
        std::cout << "List l1:\n";
        l1.Print();
        std::cout << "\n\n\nForEach():\n";
        l1.ForEach(f);
        std::cout << "List l1:\n";
        l1.Print();
    }
    catch (char* s) {
        std::cout << s;
    }
    return 0;
}