#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <locale>

bool isPrime(unsigned int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int wmain(int argc, wchar_t* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    if (argc < 2) {
        std::wcerr << L"Ошибка: недостаточно аргументов!" << std::endl;
        std::wcerr << L"Использование: Child.exe <размер_массива> <элемент1> <элемент2> ..." << std::endl;
        return 1;
    }

    int size = std::stoi(argv[1]);
    std::vector<unsigned int> arr;
    for (int i = 2; i < argc && arr.size() < size; ++i) {
        arr.push_back(std::stoul(argv[i]));
    }

    if (arr.size() != size) {
        std::wcerr << L"Ошибка: неверное количество элементов!" << std::endl;
        return 1;
    }

    std::vector<unsigned int> result(size, 0);
    int primeIndex = 0;
    for (const auto& num : arr) {
        if (isPrime(num)) {
            result[primeIndex++] = num;
        }
    }

    std::wcout << L"Обработанный массив: ";
    for (const auto& num : result) {
        std::wcout << num << L" ";
    }
    std::wcout << std::endl;

    std::wcout << L"Нажмите Enter для выхода...";
    std::wcin.ignore();

    return 0;
}