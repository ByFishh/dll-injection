//////////////////////////////////////
//                                  //
//          AUTO-INJECTOR           //
//                                  //
//////////////////////////////////////

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

static int search_process_by_name(std::vector<DWORD> *pids)
{
    std::wstring targetProcessName = L"javaw.exe";
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W entry;
    int i = 0;

    entry.dwSize = sizeof(entry);
    if (!Process32FirstW(snap, &entry))
        return (-1);
    do {
        if (std::wstring(entry.szExeFile) == targetProcessName)
            (*pids).emplace_back(entry.th32ProcessID);
    } while (Process32NextW(snap, &entry));
    for (; i < (*pids).size(); ++i) {
        std::cout << "javaw N°" << i + 1 << " PID=" << (*pids)[i] << std::endl;
    }
    if (i == 0)
        return (0);
    i -= 1;
    return (i);
}

static int inject_dll_into_process(DWORD pid)
{
    const char* dllpath = "C:\\Users\\Antoine Gasser\\Desktop\\Test_injected_exe\\create_exe_cpp\\injected.dll";
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    HANDLE hThread;
    void* loc;

    std::cout << "PROC ID=" << pid << "(inside inject func.)" << std::endl;
    if (hProc && hProc != INVALID_HANDLE_VALUE) {
        loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProc, loc, dllpath, strlen(dllpath) + 1, 0);
        hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
        if (hThread)
            CloseHandle(hThread);
    } else
        return (0);
    if (hProc) {
        CloseHandle(hProc);
    } else
        return (0);
    return (1);
}

int main(void)
{
    std::vector<DWORD> pids;
    int pid = 0;
    int injection = 0;

    std::cout << "!START!" << std::endl << std::endl;
    std::cout << "Trying to find javaw process..." << std::endl;
    if (!(pid = search_process_by_name(&pids))) {
        std::cout << "Error: process javaw does not exist !" << std::endl;
        return (84);
    } else if (pid == -1) {
        std::cout << "Error: Process32FirstW !" << std::endl;
        return (84);
    } else
        std::cout << "Process javaw found..." << std::endl;
    std::cout << "Nb javaw process=" << pid + 1 << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Trying to inject .dll..." << std::endl;
    if (!(injection = inject_dll_into_process(pids[pid]))) {
        std::cout << "Error: injection failed (verif .dll exists)" << std::endl;
        return (84);
    } else
        std::cout << "Injection of the .dll into javaw done !" << std::endl;
    std::cout << std::endl << "!END!";
    return (0);
}