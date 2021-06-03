//////////////////////////////////////
//                                  //
//          AUTO-INJECTOR           //
//           made by COC            //
//////////////////////////////////////

#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <ctype.h>

static int search_process_by_name(std::vector<DWORD>* pids)
{
    std::wstring targetProcessName = L"javaw.exe";
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W entry = { 0 };
    int i = 0;

    std::cerr << "[?] Error code create Tool Help=" << GetLastError() << std::endl;
    entry.dwSize = sizeof(PROCESSENTRY32W);
    if (!Process32FirstW(snap, &entry))
        return (-1);
    do {
        if (std::wstring(entry.szExeFile) == targetProcessName)
            (*pids).emplace_back(entry.th32ProcessID);
    } while (Process32NextW(snap, &entry));
    for (; i < (*pids).size(); ++i) {
        std::cout << "javaw N°" << i + 1 << " PID=" << (*pids)[i] << std::endl;
    }
    CloseHandle(snap);
    if (i == 0)
        return (0);
    i -= 1;
    return (i);
}

static int inject_dll_into_process(DWORD pid)
{
    const char* dllpath = "C:\\Users\\Antoine Gasser\\Desktop\\Repo\\ProjetPerso\\EpyCheat\\EpyCheat\\injected.dll";
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    HANDLE hThread;
    LPVOID loc;
    LPTHREAD_START_ROUTINE addrLoadLibrary;
    DWORD dword;
    int write_mem;

    std::cerr << "[?] Error code Open Process=" << GetLastError() << std::endl;
    std::cout << "PROC ID=" << pid << "(inside inject func.)" << std::endl;
    if (hProc != NULL && hProc != INVALID_HANDLE_VALUE) {
        loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        std::cerr << "[?] Error code Virtual Alloc Ex=" << GetLastError() << std::endl;
        if (loc == NULL) {
            std::cerr << "[!]Fail to allocate memory in Target Process." << std::endl;
            return (0);
        }
        write_mem = WriteProcessMemory(hProc, loc, dllpath, strlen(dllpath) + 1, 0);
        std::cerr << "[?] Error code write Process Memory=" << GetLastError() << std::endl;
        if (!write_mem) {
            std::cerr << "[!]Fail to write in Target Process memory." << std::endl;
            return (0);
        }
        addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary((LPCWSTR)"kernel32"), "LoadLibraryA");
        hThread = CreateRemoteThread(hProc, NULL, 0, addrLoadLibrary, loc, 0, &dword);
        std::cerr << "[?] Error code create Remote Thread=" << GetLastError() << std::endl;
        if (hThread == NULL) {
            std::cerr << "[!]Fail to create Remote Thread" << std::endl;
            return (0);
        }
        else
            CloseHandle(hThread);
    }
    else {
        std::cerr << "[!]Fail to open target process!" << std::endl;
        return (0);
    }
    CloseHandle(hProc);
    return (1);
}

int main(void)
{
    std::vector<DWORD> pids;
    int pid = 0;
    int injection = 0;

    std::cout << "!START!" << std::endl << std::endl;
    std::cout << "Trying to find javaw process..." << std::endl;
    if ((pid = search_process_by_name(&pids)) == -1) {
        std::cerr << "Error: process javaw does not exist !" << std::endl;
        return (84);
    }
    else if (pid == -1) {
        std::cerr << "Error: Process32FirstW !" << std::endl;
        return (84);
    }
    else
        std::cout << "Process javaw found..." << std::endl;
    std::cout << "Nb javaw process=" << pid + 1 << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Trying to inject .dll..." << std::endl;
    if (!(injection = inject_dll_into_process(pids[pid]))) {
        std::cerr << "Error: injection failed (verif .dll exists)" << std::endl;
        return (84);
    }
    else
        std::cout << "Injection of the .dll into javaw done !" << std::endl;
    std::cout << std::endl << "!END!";
    return (0);
}