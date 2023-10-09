// pch.cpp: файл исходного кода, соответствующий предварительно скомпилированному заголовочному файлу
#include <iostream>
#include "pch.h"
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

void pr()
{
	cout << "\nDLL IS HERE!!!!!!!!!!-_-" << endl;
}

// При использовании предварительно скомпилированных заголовочных файлов необходим следующий файл исходного кода для выполнения сборки.
