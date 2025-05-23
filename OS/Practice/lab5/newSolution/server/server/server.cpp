#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>

int wmain()
{
    SECURITY_ATTRIBUTES sa = { sizeof(sa), nullptr, TRUE };

    HANDLE srvToChild_Read = nullptr, srvToChild_Write = nullptr;
    HANDLE childToSrv_Read = nullptr, childToSrv_Write = nullptr;

    if (!CreatePipe(&srvToChild_Read, &srvToChild_Write, &sa, 0) ||
        !CreatePipe(&childToSrv_Read, &childToSrv_Write, &sa, 0))
    {
        std::wcerr << L"CreatePipe failed, code=" << GetLastError() << L"\n";
        return 1;
    }

    SetHandleInformation(srvToChild_Write, HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(childToSrv_Read, HANDLE_FLAG_INHERIT, 0);

    std::wostringstream wcmd;
    wcmd << L"Small.exe "
        << reinterpret_cast<uintptr_t>(srvToChild_Read) << L" "
        << reinterpret_cast<uintptr_t>(childToSrv_Write);

    std::wstring cmdLine = wcmd.str();
    wchar_t* cmdBuf = &cmdLine[0];

    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi = {};

    if (!CreateProcessW(
        nullptr,           // запустить Small.exe из PATH или текущей папки
        cmdBuf,            // командная строка (Wide)
        nullptr, nullptr,  // атрибуты безопасности
        TRUE,              // наследовать "наследуемые" дескрипторы
        CREATE_NEW_CONSOLE,
        nullptr, nullptr,
        &si, &pi
    ))
    {
        std::wcerr << L"CreateProcessW failed, code=" << GetLastError() << L"\n";
        return 1;
    }

    CloseHandle(srvToChild_Read);
    CloseHandle(childToSrv_Write);

    std::wcout << L"Enter array size: ";
    int size; std::wcin >> size;
	std::wcout << L"Enter array elements : ";
    std::vector<double> arr(size);
    for (int i = 0; i < size; ++i) {
        std::wcin >> arr[i];
    }
    std::wcout << L"Enter N: ";
    double N; std::wcin >> N;

    std::ostringstream out;
    out << size << ' ';
    for (double x : arr) out << x << ' ';
    out << N << ' ';
    std::string outStr = out.str();

    DWORD written = 0;
    if (!WriteFile(srvToChild_Write, outStr.data(), (DWORD)outStr.size(), &written, nullptr))
    {
        std::wcerr << L"WriteFile failed\n";
    }
    CloseHandle(srvToChild_Write);  // важно — чтобы Small получил EOF

    std::string reply;
    char buffer[128];
    DWORD readBytes = 0;
    while (ReadFile(childToSrv_Read, buffer, sizeof(buffer) - 1, &readBytes, nullptr) && readBytes) {
        buffer[readBytes] = '\0';
        reply += buffer;
    }
    CloseHandle(childToSrv_Read);

    std::istringstream in(reply);
    std::vector<double> roots;
    double r;
    while (in >> r) roots.push_back(r);

    std::wcout << L"Server received roots:\n";
    for (double y : roots) {
        std::wcout << y << L"\n";
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
