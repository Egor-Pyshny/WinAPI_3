#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <tlhelp32.h>
#include <string>

using namespace std;

DWORD GetProcName(TCHAR* name)
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return NULL;
    }
    cProcesses = cbNeeded / sizeof(DWORD);
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    for (int i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
            if (NULL != hProcess)
            {
                HMODULE hMod;
                DWORD cbNeeded;
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
                {
                    GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
                    if (lstrcmp(name, szProcessName) == 0)
                    {
                        return aProcesses[i];
                    }
                }
            }
            CloseHandle(hProcess);
        }
    }
    return NULL;
}


int main()
{
    TCHAR szProcessName[MAX_PATH] = TEXT("ConsoleApplication5.exe");
    DWORD pid = GetProcName(szProcessName);

    HANDLE hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (hRemoteProcess != NULL)
    {
        cout << "\nPID finded" << endl;

        LPVOID threadFunction = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
        string argument("InjectionDll.dll");

        LPVOID argumentAddress = VirtualAllocEx(hRemoteProcess, NULL, argument.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        WriteProcessMemory(hRemoteProcess, (LPVOID)argumentAddress, argument.c_str(), argument.length() + 1, NULL);

        if (CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)threadFunction, (LPVOID)argumentAddress, 0, NULL))
        {
            Sleep(1000);
            cout << "Creating thread" << endl;
            CloseHandle(hRemoteProcess);
        }
        else
            cout << "Cant create thread" << endl;
    }
    else
        cout << "Cant find PID" << endl;

    return 0;
}

