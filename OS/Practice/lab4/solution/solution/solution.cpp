#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <tchar.h>

using namespace std;

const wstring SEMAPHORE_NAME = L"ReaderSemaphore";
const wstring MUTEX_NAME = L"FileMutex";
const wstring WRITE_EVENT_NAME = L"WriteEvent";
const wstring EXIT_EVENT_NAME = L"ExitEvent";
const wstring ADMIN_READY_EVENT_NAME = L"AdminReadyEvent";

string generateRandomString(size_t length) {
    static const string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static mt19937 rg(random_device{}());
    static uniform_int_distribution<size_t> pick(0, chars.size() - 1);

    string s;
    s.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        s += chars[pick(rg)];
    }
    return s;
}

int main() {
    int M, N, K, P;
    wstring filename;

    cout << "Enter the number of Reader processes (M): ";
    cin >> M;
    cout << "Enter the number of active Reader processes (N, N < M): ";
    cin >> N;
    cout << "Enter the number of elements to write to file (K): ";
    cin >> K;
    cout << "Enter the number of elements each Reader reads (P, K >= P*M): ";
    cin >> P;
    cout << "Enter the filename: ";
    wcin >> filename;

    HANDLE hSemaphore = CreateSemaphore(NULL, N, N, SEMAPHORE_NAME.c_str());
    if (hSemaphore == NULL) {
        cerr << "CreateSemaphore error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME.c_str());
    if (hMutex == NULL) {
        cerr << "CreateMutex error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hWriteEvent = CreateEvent(NULL, TRUE, FALSE, WRITE_EVENT_NAME.c_str());
    if (hWriteEvent == NULL) {
        cerr << "CreateEvent (Write) error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hExitEvent = CreateEvent(NULL, TRUE, FALSE, EXIT_EVENT_NAME.c_str());
    if (hExitEvent == NULL) {
        cerr << "CreateEvent (Exit) error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hAdminReadyEvent = CreateEvent(NULL, TRUE, FALSE, ADMIN_READY_EVENT_NAME.c_str());
    if (hAdminReadyEvent == NULL) {
        cerr << "CreateEvent (AdminReady) error: " << GetLastError() << endl;
        return 1;
    }

    vector<PROCESS_INFORMATION> piReaders(M);
    vector<STARTUPINFO> siReaders(M);

    for (int i = 0; i < M; ++i) {
        ZeroMemory(&siReaders[i], sizeof(STARTUPINFO));
        siReaders[i].cb = sizeof(STARTUPINFO);

        wstring cmdLine = L"reader.exe " + to_wstring(P) + L" " + filename;

        if (!CreateProcess(NULL, &cmdLine[0], NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &siReaders[i], &piReaders[i])) {
            cerr << "CreateProcess error: " << GetLastError() << endl;
            return 1;
        }
    }

    SetEvent(hAdminReadyEvent);

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing" << endl;
        return 1;
    }

    for (int i = 0; i < K; ++i) {
        string data = generateRandomString(10);

        DWORD waitResult = WaitForSingleObject(hMutex, INFINITE);
        if (waitResult == WAIT_OBJECT_0) {
            cout << "Administrator: Activ (mutex captured)" << endl;

            file << data << endl;
            cout << "Administrator wrote: " << data << endl;

            if (!ReleaseMutex(hMutex)) {
                cerr << "ReleaseMutex error: " << GetLastError() << endl;
            }
            cout << "Administrator: Inactiv (mutex released)" << endl;
        }

        SetEvent(hWriteEvent);
        Sleep(10);
        ResetEvent(hWriteEvent);
    }

    file.close();
    SetEvent(hExitEvent);

    for (int i = 0; i < M; ++i) {
        for (int i = 0; i < M; ++i) {
            WaitForSingleObject(piReaders[i].hProcess, INFINITE);
            CloseHandle(piReaders[i].hProcess);
            CloseHandle(piReaders[i].hThread);
        }

        CloseHandle(hSemaphore);
        CloseHandle(hMutex);
        CloseHandle(hWriteEvent);
        CloseHandle(hExitEvent);
        CloseHandle(hAdminReadyEvent);

        return 0;
    }
}