#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

int wmain(int argc, wchar_t* argv[])
{
    if (argc != 3) {
        std::wcerr << L"Usage: Small.exe <readHandle> <writeHandle>\n";
        return 1;
    }

    HANDLE pipeRead = reinterpret_cast<HANDLE>(std::wcstoull(argv[1], nullptr, 10));
    HANDLE pipeWrite = reinterpret_cast<HANDLE>(std::wcstoull(argv[2], nullptr, 10));

    std::string data;
    char buf[128];
    DWORD rd = 0;
    while (ReadFile(pipeRead, buf, sizeof(buf) - 1, &rd, nullptr) && rd) {
        buf[rd] = '\0';
        data += buf;
    }
    CloseHandle(pipeRead);

    std::istringstream in(data);
    int size; in >> size;
    std::vector<double> arr(size);
    for (int i = 0; i < size; ++i) in >> arr[i];
    double N; in >> N;

    std::vector<double> roots;
    for (double x : arr) {
        if (std::sqrt(x) > N) roots.push_back(std::sqrt(x));
    }

    std::wcout << L"Small computed roots:\n";
    for (double y : arr) {
        std::wcout << y << L"\n";
    }
    for (double y : roots) {
        std::wcout << y << L"\n";
    }

    std::ostringstream out;
    for (double y : roots) out << y << ' ';
    std::string outStr = out.str();

    DWORD written = 0;
    WriteFile(pipeWrite, outStr.data(), (DWORD)outStr.size(), &written, nullptr);
    CloseHandle(pipeWrite);

	system("pause");

    return 0;
}
