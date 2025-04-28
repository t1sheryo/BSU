#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tchar.h>

using namespace std;

const wstring SEMAPHORE_NAME = L"ReaderSemaphore";
const wstring MUTEX_NAME = L"FileMutex";
const wstring WRITE_EVENT_NAME = L"WriteEvent";
const wstring EXIT_EVENT_NAME = L"ExitEvent";
const wstring ADMIN_READY_EVENT_NAME = L"AdminReadyEvent";

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: Reader.exe <P> <filename>" << endl;
        return 1;
    }

    int P = stoi(argv[1]);
    wstring filename(argv[2], argv[2] + strlen(argv[2]));

    HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, SEMAPHORE_NAME.c_str());
    if (hSemaphore == NULL) {
        cerr << "OpenSemaphore error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hMutex = OpenMutex(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, MUTEX_NAME.c_str());
    if (hMutex == NULL) {
        cerr << "OpenMutex error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hWriteEvent = OpenEvent(SYNCHRONIZE, FALSE, WRITE_EVENT_NAME.c_str());
    if (hWriteEvent == NULL) {
        cerr << "OpenEvent (Write) error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hExitEvent = OpenEvent(SYNCHRONIZE, FALSE, EXIT_EVENT_NAME.c_str());
    if (hExitEvent == NULL) {
        cerr << "OpenEvent (Exit) error: " << GetLastError() << endl;
        return 1;
    }

    HANDLE hAdminReadyEvent = OpenEvent(SYNCHRONIZE, FALSE, ADMIN_READY_EVENT_NAME.c_str());
    if (hAdminReadyEvent == NULL) {
        cerr << "OpenEvent (AdminReady) error: " << GetLastError() << endl;
        return 1;
    }

    WaitForSingleObject(hAdminReadyEvent, INFINITE);

    HANDLE waitHandles[] = { hWriteEvent, hExitEvent };
    int totalRead = 0;
    vector<string> readData;

    while (true) {
        DWORD waitResult = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);

        if (waitResult == WAIT_OBJECT_0 + 1) { // Exit event
            cout << "Reader " << GetCurrentProcessId() << ": Received exit signal. Total read: " << totalRead << endl;
            break;
        }
        else if (waitResult == WAIT_OBJECT_0) { // Write event
            waitResult = WaitForSingleObject(hSemaphore, 0);
            if (waitResult == WAIT_OBJECT_0) {
                cout << "Reader " << GetCurrentProcessId() << ": Activ (semaphore captured)" << endl;

                waitResult = WaitForSingleObject(hMutex, 0);
                if (waitResult == WAIT_OBJECT_0) {
                    cout << "Reader " << GetCurrentProcessId() << ": Activ (mutex captured)" << endl;

                    ifstream file(filename);
                    if (file.is_open()) {
                        string line;
                        int count = 0;

                        while (count < P && getline(file, line)) {
                            readData.push_back(line);
                            count++;
                            totalRead++;
                        }

                        file.close();

                        cout << "Reader " << GetCurrentProcessId() << " read: ";
                        for (const auto& item : readData) {
                            cout << item << " ";
                        }
                        cout << endl;
                        readData.clear();
                    }

                    if (!ReleaseMutex(hMutex)) {
                        cerr << "ReleaseMutex error: " << GetLastError() << endl;
                    }
                    cout << "Reader " << GetCurrentProcessId() << ": Inactiv (mutex released)" << endl;
                }

                if (!ReleaseSemaphore(hSemaphore, 1, NULL)) {
                    cerr << "ReleaseSemaphore error: " << GetLastError() << endl;
                }
                cout << "Reader " << GetCurrentProcessId() << ": Inactiv (semaphore released)" << endl;
            }

            Sleep(1 + rand() % 3); 
        }
    }

    CloseHandle(hSemaphore);
    CloseHandle(hMutex);
    CloseHandle(hWriteEvent);
    CloseHandle(hExitEvent);
    CloseHandle(hAdminReadyEvent);

    return 0;
}