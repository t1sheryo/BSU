#include <iostream>
#include <windows.h>
#include <process.h>
#include <vector>

struct ThreadData {
	int size;
	char* arr;
};

//DWORD WINAPI func(LPVOID data) {
//	ThreadData* tData = (ThreadData*)data;
//
//	int size = tData->size;
//	for (int i = 0; i < size; ++i) {
//		int val = int(tData->arr[i]);
//		if ((val >= 65 && val <= 90) || (val >= 97 && val <= 122)) continue;
//
//		std::cout << tData->arr[i] << " ";
//	}
//
//	delete[] tData->arr;
//	delete tData;
//
//	return 0;
//}

UINT WINAPI func(void* data) {
	ThreadData* tData = (ThreadData*)data;

	int size = tData->size;
	for (int i = 0; i < size; ++i) {
		int val = int(tData->arr[i]);
		if ((val >= 65 && val <= 90) || (val >= 97 && val <= 122)) continue;

		std::cout << tData->arr[i] << " ";
	}

	delete[] tData->arr;
	delete tData;

	return 0;
}

int main()
{
	HANDLE worker;
	DWORD ThreadID;
	UINT IDThread;

	int size = 0;
	std::cout << "Enter an array size: ";
	std::cin >> size;
	
	std::vector<char> vec(size);
	std::cout << "Enter an array: ";
	for (size_t i = 0; i < size; ++i) {
		std::cin >> vec[i];
	}

	unsigned int timeToSleep = 5000;
	ThreadData* obj = new ThreadData;
	obj->size = size;
	obj->arr = new char[size];
	for (size_t i = 0; i < size; ++i) {
		obj->arr[i] = vec[i];
	}

	//worker = CreateThread(NULL, 0, func, obj, CREATE_SUSPENDED, &ThreadID);
	
	worker = (HANDLE)_beginthreadex(NULL, 0, func, obj, CREATE_SUSPENDED, &IDThread);
	
	if (worker == NULL) {
		return GetLastError();
	}

	DWORD stopCount = ResumeThread(worker);

	WaitForSingleObject(worker, INFINITE);
	CloseHandle(worker);

	return 0;
}