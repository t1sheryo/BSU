#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <tchar.h>

// Функция для создания наследуемых дескрипторов каналов
void CreateInheritablePipes(HANDLE& hReadPipe, HANDLE& hWritePipe, SECURITY_ATTRIBUTES& sa) {
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        std::cerr << "CreatePipe failed: " << GetLastError() << std::endl;
        exit(1);
    }
}

// Процесс Server
void RunServer() {
    SECURITY_ATTRIBUTES sa;
    HANDLE hReadPipe1, hWritePipe1; // Server пишет в Pipe1, Small читает из Pipe1
    HANDLE hReadPipe2, hWritePipe2; // Small пишет в Pipe2, Server читает из Pipe2

    // Создаем два анонимных канала с наследуемыми дескрипторами
    CreateInheritablePipes(hReadPipe1, hWritePipe1, sa);
    CreateInheritablePipes(hReadPipe2, hWritePipe2, sa);

    // Создаем процесс Small
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Получаем путь к текущему исполняемому файлу
    TCHAR currentExePath[MAX_PATH];
    GetModuleFileName(NULL, currentExePath, MAX_PATH);

    // Формируем командную строку для дочернего процесса
    TCHAR cmdLine[MAX_PATH + 10];
    _stprintf_s(cmdLine, _T("\"%s\" Small"), currentExePath);

    // Устанавливаем дескрипторы для наследования
    si.hStdInput = hReadPipe1;  // Small будет читать из Pipe1
    si.hStdOutput = hWritePipe2; // Small будет писать в Pipe2
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Создаем процесс Small
    if (!CreateProcess(
        NULL,           // Имя модуля (используем командную строку)
        cmdLine,        // Командная строка
        NULL,           // Атрибуты безопасности процесса
        NULL,           // Атрибуты безопасности потока
        TRUE,           // Дескрипторы наследуются
        0,              // Флаги создания
        NULL,           // Окружение (используем родительское)
        NULL,           // Текущий каталог (используем родительский)
        &si,            // STARTUPINFO
        &pi))           // PROCESS_INFORMATION
    {
        DWORD err = GetLastError();
        std::cerr << "CreateProcess failed (" << err << "): ";

        if (err == ERROR_FILE_NOT_FOUND) {
            std::cerr << "File not found" << std::endl;
        }
        else {
            std::cerr << "Unknown error" << std::endl;
        }

        CloseHandle(hReadPipe1);
        CloseHandle(hWritePipe1);
        CloseHandle(hReadPipe2);
        CloseHandle(hWritePipe2);
        exit(1);
    }

    // Закрываем ненужные дескрипторы в родительском процессе
    CloseHandle(hReadPipe1); // Server не читает из Pipe1
    CloseHandle(hWritePipe2); // Server не пишет в Pipe2

    // Ввод данных
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    std::vector<double> arr(size);
    std::cout << "Enter array elements: ";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    double N;
    std::cout << "Enter number N: ";
    std::cin >> N;

    // Записываем данные в Pipe1 (для Small)
    DWORD written;
    if (!WriteFile(hWritePipe1, &size, sizeof(size), &written, NULL) || written != sizeof(size)) {
        std::cerr << "Write size failed" << std::endl;
        exit(1);
    }

    if (!WriteFile(hWritePipe1, arr.data(), size * sizeof(double), &written, NULL) ||
        written != size * sizeof(double)) {
        std::cerr << "Write array failed" << std::endl;
        exit(1);
    }

    if (!WriteFile(hWritePipe1, &N, sizeof(N), &written, NULL) || written != sizeof(N)) {
        std::cerr << "Write N failed" << std::endl;
        exit(1);
    }

    // Читаем размер результатов
    int resultSize = 0;
    DWORD read = 0;
    if (!ReadFile(hReadPipe2, &resultSize, sizeof(resultSize), &read, NULL) ||
        read != sizeof(resultSize)) {
        std::cerr << "Read result size failed" << std::endl;
        exit(1);
    }

    // Читаем элементы только если они есть
    std::vector<double> results;
    if (resultSize > 0) {
        results.resize(resultSize);
        if (!ReadFile(hReadPipe2, results.data(), resultSize * sizeof(double), &read, NULL) ||
            read != resultSize * sizeof(double)) {
            std::cerr << "Read results failed" << std::endl;
            exit(1);
        }
    }

    // Выводим результаты (может быть пустым массивом)
    std::cout << "\nServer received " << resultSize << " results:" << std::endl;
    for (double val : results) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    // Закрываем оставшиеся дескрипторы
    CloseHandle(hWritePipe1);
    CloseHandle(hReadPipe2);

    // Ожидаем завершения дочернего процесса
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// Процесс Small
void RunSmall() {
    // Получаем стандартные дескрипторы ввода/вывода (наследованные от родителя)
    HANDLE hReadPipe1 = GetStdHandle(STD_INPUT_HANDLE);   // Читаем из Pipe1 (от Server)
    HANDLE hWritePipe2 = GetStdHandle(STD_OUTPUT_HANDLE); // Пишем в Pipe2 (для Server)

    // Читаем данные от Server
    int size;
    DWORD read;
    if (!ReadFile(hReadPipe1, &size, sizeof(size), &read, NULL) || read != sizeof(size)) {
        std::cerr << "Small: read size failed" << std::endl;
        exit(1);
    }

    std::vector<double> arr(size);
    if (!ReadFile(hReadPipe1, arr.data(), size * sizeof(double), &read, NULL) ||
        read != size * sizeof(double)) {
        std::cerr << "Small: read array failed" << std::endl;
        exit(1);
    }

    double N;
    if (!ReadFile(hReadPipe1, &N, sizeof(N), &read, NULL) || read != sizeof(N)) {
        std::cerr << "Small: read N failed" << std::endl;
        exit(1);
    }

    // Выводим полученные данные
    /*std::cout << "Small received data:" << std::endl;
    std::cout << "Size: " << size << std::endl;
    std::cout << "Array: ";
    for (double val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\nN: " << N << std::endl;*/

    // Обрабатываем данные - находим квадратные корни элементов > 0
    std::vector<double> results;
    for (double val : arr) {
        if (val > 0) {
            results.push_back(sqrt(val));
        }
    }

    // Отправляем результаты Server
    DWORD written = 0;
    int resultSize = static_cast<int>(results.size());
    if (!WriteFile(hWritePipe2, &resultSize, sizeof(resultSize), &written, NULL) ||
        written != sizeof(resultSize)) {
        std::cerr << "Small: write result size failed" << std::endl;
        exit(1);
    }

    // Отправляем элементы только если они есть
    if (resultSize > 0) {
        if (!WriteFile(hWritePipe2, results.data(), resultSize * sizeof(double), &written, NULL) ||
            written != resultSize * sizeof(double)) {
            std::cerr << "Small: write results failed" << std::endl;
            exit(1);
        }
    }

    // Закрываем дескрипторы
    CloseHandle(hReadPipe1);
    CloseHandle(hWritePipe2);
}

int _tmain(int argc, TCHAR* argv[]) {
    if (argc > 1 && _tcscmp(argv[1], _T("Small")) == 0) {
        RunSmall();
    }
    else {
        RunServer();
    }
    return 0;
}