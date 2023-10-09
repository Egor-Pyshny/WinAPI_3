#include <iostream>
#include <Windows.h>

using namespace std;

typedef int (*Tadd)(int, int);
typedef int (*Tsub)(int, int);
typedef void (*PrintFunction)(string);
typedef int (*YourFunctionType)(int);

int main()
{
    HINSTANCE hDLL = LoadLibrary(L"C:/Users/Пользователь/source/repos/Egor-Pyshny/WinAPI_3/x64/Debug/DLL1.dll");

    if (hDLL != NULL)
    {
        Tadd add = (Tadd)GetProcAddress(hDLL, "add");
        Tsub sub = (Tsub)GetProcAddress(hDLL, "sub");

        if (add && sub)
        {
            int resultAdd = add(5, 3);
            int resultSub = sub(8, 4);

            cout << "Addition result: " << resultAdd << ";" << endl;
            cout << "Subtraction result: " << resultSub << ";" << endl;

        }
        else
        {
            cout << "Failed to get function pointers!" << endl;
        }
        FreeLibrary(hDLL);
    }
    else
    {
        cout << "Failed to load DLL!" << endl;
    }
    return 0;
}