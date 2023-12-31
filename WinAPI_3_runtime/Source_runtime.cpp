#include <iostream>
#include <Windows.h>

using namespace std;

typedef int (*Tadd)(int, int);
typedef int (*Tsub)(int, int);

int main()
{
    HINSTANCE hDLL = LoadLibrary(L"C:/Users/user/source/repos/Egor-Pyshny/WinAPI_3/x64/Debug/DLL1.dll");

    if (hDLL != NULL)
    {
        Tadd add = (Tadd)GetProcAddress(hDLL, "add");
        Tsub sub = (Tsub)GetProcAddress(hDLL, "sub");

        if (add && sub)
        {
            int resultAdd = add(5, 3);
            int resultSub = sub(8, 4);

            cout << "add = " << resultAdd << ";" << endl;
            cout << "sub = " << resultSub << ";" << endl;

        }
        else
        {
            cout << "Failed to get function" << endl;
        }
        FreeLibrary(hDLL);
    }
    else
    {
        cout << "Failed to load DLL" << endl;
    }
    return 0;
}