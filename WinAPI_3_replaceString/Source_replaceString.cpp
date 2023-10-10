#include <iostream>
#include <Windows.h>

using namespace std;

typedef void (*Treplace)(string, string);

int main()
{
    HINSTANCE hDLL = LoadLibrary(L"C:/Users/user/source/repos/Egor-Pyshny/WinAPI_3/x64/Debug/DLL1.dll");

    if (hDLL != NULL)
    {
        Treplace replace = (Treplace)GetProcAddress(hDLL, "replace");
        string str = "Initial string";
        string str_for_replace = "Replaced text";
        if (replace)
        {           
            cout << str << endl;
            replace(str, str_for_replace);
            cout << str << endl;
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