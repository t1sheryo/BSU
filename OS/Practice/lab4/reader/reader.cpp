#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <random>

using namespace std;

void sleepShortRandom() {
    Sleep(1 + rand() % 3);
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 3) {
        wcerr << L"Usage: Reader.exe <P> <filename>" << endl;
        return 1;
    }

    int P = _wtoi(argv[1]);
    wstring wfilename = argv[2];

    HANDLE hLimit = OpenSemaphoreW(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, L"Global\\ReaderLimitSemaphore");
    HANDLE hFileMutex = OpenMutexW(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, L"Global\\FileAccessMutex");
    HANDLE hPrintMutex = OpenMutexW(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, L"Global\\PrintMutex");
    HANDLE hEndEvent = OpenEventW(SYNCHRONIZE, FALSE, L"Global\\EndSessionEvent");

    if (!hLimit || !hFileMutex || !hPrintMutex || !hEndEvent) {
        wcerr << L"Failed to open sync objects: " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(hLimit, INFINITE);

    int readCount = 0;
    vector<wstring> readLines;

    mt19937_64 rng(random_device{}());

    while (readCount < P) {
        if (WaitForSingleObject(hEndEvent, 0) == WAIT_OBJECT_0)
            break;

        sleepShortRandom();

        // Читаем все строки из файла
        vector<wstring> lines;
        WaitForSingleObject(hFileMutex, INFINITE);
        wifstream file(wfilename);
        if (file.is_open()) {
            wstring line;
            while (getline(file, line)) {
                if (!line.empty())
                    lines.push_back(line);
            }
            file.close();
        }
        ReleaseMutex(hFileMutex);

        // Если есть строки, выбираем случайную
        if (!lines.empty()) {
            uniform_int_distribution<size_t> dist(0, lines.size() - 1);
            wstring selectedLine = lines[dist(rng)];
            readLines.push_back(selectedLine);
            readCount++;

            WaitForSingleObject(hPrintMutex, INFINITE);
            wcout << L"Reader " << GetCurrentProcessId() << L" read: " << selectedLine << endl;
            ReleaseMutex(hPrintMutex);
        }
    }

    WaitForSingleObject(hPrintMutex, INFINITE);
    wcout << L"Reader " << GetCurrentProcessId() << L": session ended, total read = " << readCount << endl;
    ReleaseMutex(hPrintMutex);

    ReleaseSemaphore(hLimit, 1, NULL);

    CloseHandle(hLimit);
    CloseHandle(hFileMutex);
    CloseHandle(hPrintMutex);
    CloseHandle(hEndEvent);
    int i = 0;
    std::cin >> i;
    return 0;
}