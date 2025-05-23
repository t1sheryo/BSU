#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

using namespace std;

wstring generateRandomString(size_t length) {
    static const wchar_t chars[] = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static mt19937_64 rng(random_device{}());
    static uniform_int_distribution<size_t> pick(0, wcslen(chars) - 1);
    wstring s;
    for (size_t i = 0; i < length; ++i)
        s += chars[pick(rng)];
    return s;
}

int wmain() {
    int M, N, K, P;
    wstring wfilename;

    wcout << L"Enter number of Reader processes (M): "; wcin >> M;
    wcout << L"Enter max concurrent Readers (N < M): "; wcin >> N;
    wcout << L"Enter total elements to write (K): "; wcin >> K;
    wcout << L"Enter elements each Reader reads (P): "; wcin >> P;
    wcout << L"Enter filename: "; wcin >> wfilename;

    if (P * M > K) {
        wcerr << L"Error: K must be >= P * M" << endl;
        return 1;
    }

    SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };

    HANDLE hLimit = CreateSemaphoreW(&sa, N, N, L"Global\\ReaderLimitSemaphore");
    HANDLE hFileMutex = CreateMutexW(&sa, FALSE, L"Global\\FileAccessMutex");
    HANDLE hPrintMutex = CreateMutexW(&sa, FALSE, L"Global\\PrintMutex");
    HANDLE hEndEvent = CreateEventW(&sa, TRUE, FALSE, L"Global\\EndSessionEvent");

    if (!hLimit || !hFileMutex || !hPrintMutex || !hEndEvent) {
        wcerr << L"Failed to create sync objects: " << GetLastError() << endl;
        return 1;
    }

    vector<PROCESS_INFORMATION> readers(M);
    vector<STARTUPINFOW> sinfo(M);

    for (int i = 0; i < M; ++i) {
        ZeroMemory(&sinfo[i], sizeof(sinfo[i]));
        sinfo[i].cb = sizeof(sinfo[i]);

        wstring cmd = L"Reader.exe " + to_wstring(P) + L" " + wfilename;
        if (!CreateProcessW(NULL, &cmd[0], NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &sinfo[i], &readers[i])) {
            wcerr << L"Failed to start Reader process, error: " << GetLastError() << endl;
            return 1;
        }
    }

    wofstream file(wfilename);
    if (!file.is_open()) {
        wcerr << L"Failed to open file: " << wfilename << endl;
        return 1;
    }

    for (int i = 0; i < K; ++i) {
        wstring line = generateRandomString(10);
        WaitForSingleObject(hFileMutex, INFINITE);
        file << line << endl;
        file.flush();
        ReleaseMutex(hFileMutex);

        WaitForSingleObject(hPrintMutex, INFINITE);
        wcout << L"Administrator wrote: " << line << endl;
        ReleaseMutex(hPrintMutex);
    }

    file.close();

    // Ждем завершения всех процессов-читателей
    for (auto& pi : readers) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    // Устанавливаем событие завершения после того, как все читатели закончили
    SetEvent(hEndEvent);

    CloseHandle(hLimit);
    CloseHandle(hFileMutex);
    CloseHandle(hPrintMutex);
    CloseHandle(hEndEvent);
    return 0;
}