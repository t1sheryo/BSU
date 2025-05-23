#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cmath>

using namespace std;

void WorkThread(
    vector<float>& arr,
    int& sleepTime,
    mutex& arrMutex,
    mutex& workMutex,
    condition_variable& workCV,
    bool& workReady)
{
    // 1. Ask user for rest interval
    {
        lock_guard<mutex> lg(arrMutex); 
        cout << "[Work] Enter rest time interval (ms): ";
        cin >> sleepTime;
    }

    // 2. Process
    vector<float> temp;
    temp.reserve(arr.size() * 2);
    for (float num : arr) {
        if (num > 0)
            temp.push_back(floor(num));
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }
    for (float num : arr) {
        temp.push_back(num);
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
    }

    // 3. Write back under lock
    {
        lock_guard<mutex> lg(arrMutex);
        arr = move(temp);
    }

    // 4. Notify main that work is ready
    {
        lock_guard<mutex> lk(workMutex);
        workReady = true;
    }
    workCV.notify_one();
}

void CountThread(
    const vector<float>& arr,
    int& positiveCount,
    mutex& sectionMutex,
    mutex& eventMutex,
    condition_variable& eventCV,
    bool& countReady)
{
    // 1. Wait for main signal (critical section)
    sectionMutex.lock();

    // 2. Count positives
    size_t cnt = 0;
    for (float num : arr) {
        if (num > 0) ++cnt;
    }
    positiveCount = static_cast<int>(cnt);

    // 3. Notify main
    {
        lock_guard<mutex> lk(eventMutex);
        countReady = true;
    }
    eventCV.notify_one();

    sectionMutex.unlock();
}

int main() {
    vector<float> arr;
    int sleepTime = 0;
    int positiveCount = 0;

    mutex arrMutex;         
    mutex workMutex;         
    condition_variable workCV;
    bool workReady = false;

    mutex sectionMutex;       
    mutex eventMutex;         
    condition_variable eventCV;
    bool countReady = false;

    sectionMutex.lock();

    // 2. Input array size and elements
    {
        lock_guard<mutex> lg(arrMutex);
        size_t size;
        cout << "Enter array size: ";
        cin >> size;
        arr.resize(size);
        cout << "Enter array elements: ";
        for (size_t i = 0; i < size; ++i)
            cin >> arr[i];
        cout << "Initial array (" << size << " elements): ";
        for (float num : arr)
            cout << num << ' ';
        cout << "\n";
    }

    // 3. Launch work and count threads
    thread workThread(WorkThread,
        ref(arr),
        ref(sleepTime),
        ref(arrMutex),
        ref(workMutex),
        ref(workCV),
        ref(workReady));

    thread countThread(CountThread,
        cref(arr),
        ref(positiveCount),
        ref(sectionMutex),
        ref(eventMutex),
        ref(eventCV),
        ref(countReady));

    this_thread::sleep_for(chrono::milliseconds(2));

    // 5. Wait for work to finish and then print final array
    {
        unique_lock<mutex> lk(workMutex);
        workCV.wait(lk, [&] { return workReady; });
    }
    {
        lock_guard<mutex> lg(arrMutex);
        cout << "Final array (" << arr.size() << " elements): ";
        for (float num : arr)
            cout << num << ' ';
        cout << "\n";
    }

    // 6. Signal CountThread to start (release critical section)
    sectionMutex.unlock();

    // 7. Wait for count to finish
    {
        unique_lock<mutex> lk(eventMutex);
        eventCV.wait(lk, [&] { return countReady; });
    }

    // 8. Print count result
    cout << "Number of positive elements: " << positiveCount << "\n";

    // 9. Join threads and cleanup
    workThread.join();
    countThread.join();

    return 0;
}
