// pch.cpp: файл исходного кода, соответствующий предварительно скомпилированному заголовочному файлу
#include <iostream>
#include "pch.h"
#include <vector>
// MyLibrary.cpp
using namespace std;
// Реализация экспортируемой функции
int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a * b;
}

void printHello()
{
	cout << "\nHELLO\n" << endl;
}

void replace(string initial, string repl)
{
    HANDLE process = GetCurrentProcess();
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    MEMORY_BASIC_INFORMATION info;
    char* p = 0;
    while (p < si.lpMaximumApplicationAddress)
    {
        if (VirtualQueryEx(process, p, &info, sizeof(info)))
        {
            if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE)
            {
                vector<char> chunk(info.RegionSize);
                if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, NULL))
                {
                    for (size_t i = 0; i < (info.RegionSize - initial.length()); ++i)
                    {
                        if (equal(initial.begin(), initial.end(), &chunk[i]))
                        {
                            char* ref = p + i;
                            copy(repl.begin(), repl.end(), ref);
                            ref[repl.length()] = 0;  
                        }
                    }
                }
            }
            p += info.RegionSize;
        }
    }
}
// При использовании предварительно скомпилированных заголовочных файлов необходим следующий файл исходного кода для выполнения сборки.
