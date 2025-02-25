#include <iostream>
#include <vector>
#include <locale> // Для работы с локалью
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>

int wmain() {
    SetConsoleOutputCP(CP_UTF8);
    // Установка локали для поддержки широких символов
    std::locale::global(std::locale(""));
    
    std::wstring exePath = L"C:\\proga\\BSU\\OS\\Practice\\lab2\\parent\\child\\x64\\Debug\\child.exe ";

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO)); // заполняем все поля si нулями
    si.cb = sizeof(STARTUPINFO);
    si.dwX = 500;
    si.dwFlags = STARTF_USEPOSITION;

    int size = 0;
    std::wcout << L"Enter array size: ";
    std::wcin >> size;

    std::vector<unsigned int> arr(size);
    std::wcout << L"Enter array elements(unsigned integers): ";
    for (int i = 0; i < size; ++i) {
        std::wcin >> arr[i];
    }

    std::wstringstream cmdStream;
    cmdStream << exePath << size << L" ";
    for (const auto& num : arr) {
        cmdStream << num << L" ";
    }
    std::wstring cmdLine = cmdStream.str();
    // т.к. str() возвращает константу, то мы создаем массив wchar_t чтобы передать его, т.к. он не const
    std::vector<wchar_t> cmdLineWorkingCopy(cmdLine.begin(), cmdLine.end());
    cmdLineWorkingCopy.push_back(L'\0'); // добавляем нулевой терминатор как признак конца

    if (!CreateProcessW(
        NULL,
        cmdLineWorkingCopy.data(),
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi)) {
        std::wcerr << L"CreateProcess Error: " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::wcout << L"Child process finished" << std::endl;

    return 0;
}