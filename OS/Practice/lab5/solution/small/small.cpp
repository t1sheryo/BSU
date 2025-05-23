#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Small: Invalid arguments\n";
        return 1;
    }

    // Получаем дескрипторы из аргументов командной строки
    HANDLE hReadPipe1 = (HANDLE)std::stoll(argv[1]);  // Читаем из Pipe1
    HANDLE hWritePipe2 = (HANDLE)std::stoll(argv[2]); // Пишем в Pipe2

    // Чтение данных от Server
    int size;
    double N;
    std::vector<double> arr;

    DWORD bytesRead;
    ReadFile(hReadPipe1, &size, sizeof(int), &bytesRead, NULL);
    arr.resize(size);
    ReadFile(hReadPipe1, arr.data(), size * sizeof(double), &bytesRead, NULL);
    ReadFile(hReadPipe1, &N, sizeof(double), &bytesRead, NULL);

    // Вывод полученных данных
    std::cout << "Small: Received from Server:\n";
    std::cout << "Size: " << size << "\nArray: ";
    for (double num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\nN: " << N << "\n";

    // Обработка данных (вычисление корней элементов > N)
    std::vector<double> result;
    for (double num : arr) {
        if (num > N) {
            result.push_back(sqrt(num));
        }
    }

    // Передача результата в Server
    for (double num : result) {
        WriteFile(hWritePipe2, &num, sizeof(double), &bytesRead, NULL);
    }

    // Закрываем дескрипторы
    CloseHandle(hReadPipe1);
    CloseHandle(hWritePipe2);

    return 0;
}