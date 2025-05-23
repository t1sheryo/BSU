#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

int main() {
    // Создаем анонимные каналы (pipes)
    HANDLE hWritePipe1, hReadPipe1;  // Server пишет в Pipe1, Small читает из Pipe1
    HANDLE hWritePipe2, hReadPipe2;  // Small пишет в Pipe2, Server читает из Pipe2

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;  // Дескрипторы наследуемые

    // Создаем первый канал (Pipe1)
    if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0)) {
        std::cerr << "Failed to create Pipe1\n";
        return 1;
    }

    // Создаем второй канал (Pipe2)
    if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0)) {
        std::cerr << "Failed to create Pipe2\n";
        CloseHandle(hReadPipe1);
        CloseHandle(hWritePipe1);
        return 1;
    }

    // Запускаем процесс Small
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    // Формируем командную строку для процесса Small (передаем дескрипторы)
    std::wstring cmdLine = L"Small.exe " +
        std::to_wstring((long long)hReadPipe1) + L" " +
        std::to_wstring((long long)hWritePipe2);

    if (!CreateProcess(
        NULL,
        &cmdLine[0],
        NULL,
        NULL,
        TRUE,  // Наследуем дескрипторы
        CREATE_NEW_CONSOLE,  // Новая консоль
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::cerr << "Failed to create Small process\n";
        CloseHandle(hReadPipe1);
        CloseHandle(hWritePipe1);
        CloseHandle(hReadPipe2);
        CloseHandle(hWritePipe2);
        return 1;
    }

    // Закрываем ненужные дескрипторы в Server
    CloseHandle(hReadPipe1);  // Server не читает из Pipe1
    CloseHandle(hWritePipe2); // Server не пишет в Pipe2

    // Ввод данных
    int size;
    double N;
    std::cout << "Server: Enter array size: ";
    std::cin >> size;
    std::vector<double> arr(size);
    std::cout << "Server: Enter array elements:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    std::cout << "Server: Enter N: ";
    std::cin >> N;

    // Передача данных в Small (размер, массив, N)
    DWORD bytesWritten;
    WriteFile(hWritePipe1, &size, sizeof(int), &bytesWritten, NULL);
    WriteFile(hWritePipe1, arr.data(), size * sizeof(double), &bytesWritten, NULL);
    WriteFile(hWritePipe1, &N, sizeof(double), &bytesWritten, NULL);

    // Получение результата от Small
    std::vector<double> result;
    double value;
    while (ReadFile(hReadPipe2, &value, sizeof(double), &bytesWritten, NULL) {
        if (bytesWritten == 0) break;  // Конец передачи
        result.push_back(value);
    }

    // Вывод результата
    std::cout << "Server: Received from Small:\n";
    for (double num : result) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Закрываем оставшиеся дескрипторы
    CloseHandle(hWritePipe1);
    CloseHandle(hReadPipe2);

    // Ожидаем завершения Small
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}