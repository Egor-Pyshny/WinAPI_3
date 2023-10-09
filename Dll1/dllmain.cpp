// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fstream>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        std::ofstream outFile("C:/Users/Пользователь/source/repos/Egor-Pyshny/WinAPI_3/log.txt");

        if (outFile.is_open()) {
            // Записываем строку в файл
            outFile << "Привет, мир!" << std::endl;

            // Закрываем файл
            outFile.close();

            std::cout << "Данные успешно записаны в файл." << std::endl;
        }
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

