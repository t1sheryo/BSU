#include <windows.h>
#include <iostream>
#include <vector>
#include <clocale>
#include <ctime>
#include <chrono>
#include <thread>

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

    int sleepTime = 0;
    cout << "Enter rest time interval (ms): ";
    cin >> sleepTime;

    vector<float> tempArr;
    for (float num : *(data->arr)) {
        if (num > 0) {
            tempArr.push_back(floor(num));
        }
        tempArr.push_back(num);
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
    *(data->arr) = tempArr;

    return 0;
}

DWORD WINAPI CountThread(LPVOID lpParam) {
    CountData* data = (CountData*)lpParam;

    // Ждём сигнала от main (критическая секция)
    EnterCriticalSection(data->cs);
    cout << "Count thread started processing." << endl;
    LeaveCriticalSection(data->cs);

    // Считаем положительные элементы
    *(data->positiveCount) = 0;
    for (float num : *(data->arr)) {
        if (num > 0) {
            (*data->positiveCount)++;
        }
    }

    // Сигнализируем main о завершении
    SetEvent(data->hEvent);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Инициализация синхронизации
    HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);

    vector<float> arr;
    int positiveCount = 0;

    // Ввод массива
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

    // Вывод исходного массива
    cout << "Initial array (" << size << " elements): ";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Запуск потока Work
    WorkData workData = { &arr, hMutex };

    HANDLE hWork = CreateThread(NULL, 0, WorkThread, &workData, 0, NULL);

    // Запуск потока Count
    CountData countData = { &arr, &cs, hEvent, &positiveCount };
    HANDLE hCount = CreateThread(NULL, 0, CountThread, &countData, 0, NULL);

    // Ожидание завершения Work и вывод итогового массива
    WaitForSingleObject(hWork, INFINITE);
    WaitForSingleObject(hMutex, INFINITE);
    cout << "Final array (" << arr.size() << " elements): ";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;
    ReleaseMutex(hMutex);

    // Уведомление Count о начале работы (критическая секция)
    EnterCriticalSection(&cs);
    cout << "Main thread signaled Count to start." << endl;
    LeaveCriticalSection(&cs);

    // Ожидание результата от Count (событие)
    WaitForSingleObject(hEvent, INFINITE);
    cout << "Number of positive elements: " << positiveCount << endl;

    // Освобождение ресурсов
    CloseHandle(hWork);
    CloseHandle(hCount);
    CloseHandle(hMutex);
    CloseHandle(hEvent);
    DeleteCriticalSection(&cs);

    return 0;
}