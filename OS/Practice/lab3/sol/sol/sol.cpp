#include <windows.h>
#include <iostream>
#include <vector>
#include <clocale>
#include <ctime>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;

struct WorkData {
    vector<float>* arr;
    HANDLE hMutex;
};

struct CountData {
    const vector<float>* arr;
    CRITICAL_SECTION* cs;
    HANDLE hEvent;
    int* positiveCount;
};

DWORD WINAPI WorkThread(LPVOID lpParam) {
    WorkData* data = (WorkData*)lpParam;


    WaitForSingleObject(data->hMutex, INFINITE);

    std::cout << "mutex was captured by work";
    int sleepTime = 0;
    cout << "Enter rest time interval (ms): ";
    cin >> sleepTime;

    vector<float> tempArr;
    for (float num : *(data->arr)) {
        if (num > 0) {
            tempArr.push_back(floor(num));
        }
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }

    for (float num : *(data->arr)) {
        tempArr.push_back(num);
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }

    *(data->arr) = tempArr;

    ReleaseMutex(data->hMutex);

    return 0;
}

DWORD WINAPI CountThread(LPVOID lpParam) {
    CountData* data = (CountData*)lpParam;

    EnterCriticalSection(data->cs);
    cout << "Count thread started processing." << endl;


    *(data->positiveCount) = 0;
    for (float num : *(data->arr)) {
        if (num > 0) {
            (*data->positiveCount)++;
        }
    }
    LeaveCriticalSection(data->cs);
    SetEvent(data->hEvent);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);

    vector<float> arr;
    int positiveCount = 0;

    int size;
    cout << "Enter array size: ";
    cin >> size;

    arr.resize(size);
    cout << "Enter array elements (1 - manually, 2 - randomly): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        for (int i = 0; i < size; i++) {
            cout << "arr[" << i << "] = ";
            cin >> arr[i];
        }
    }
    else {
        srand(time(NULL));
        for (int i = 0; i < size; i++) {
            arr[i] = (rand() % 200 - 100) / 10.0f;
        }
    }

    cout << "Initial array (" << size << " elements): ";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;

    WorkData workData = { &arr, hMutex };
    HANDLE hWork = CreateThread(NULL, 0, WorkThread, &workData, 0, NULL);
    
    EnterCriticalSection(&cs);
    CountData countData = { &arr, &cs, hEvent, &positiveCount };
    HANDLE hCount = CreateThread(NULL, 0, CountThread, &countData, 0, NULL);
    Sleep(1);

    WaitForSingleObject(hMutex, INFINITE);
    std::cout << "mutex was captured by main";

    cout << "Final array (" << arr.size() << " elements): ";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;
    ReleaseMutex(hMutex);


    cout << "Main thread signaled Count to start." << endl;
    LeaveCriticalSection(&cs);

    WaitForSingleObject(hEvent, INFINITE);
    cout << "Number of positive elements: " << positiveCount / 2 << endl;
    WaitForSingleObject(hCount, INFINITE);
    CloseHandle(hCount);
    CloseHandle(hMutex);
    CloseHandle(hEvent);
    DeleteCriticalSection(&cs);

    return 0;
}