#include <iostream>

using namespace std;

__declspec(dllimport) int add(int a, int b);
__declspec(dllimport) int sub(int a, int b);

int main()
{
    int resultAdd = add(5, 3);
    int resultSub = sub(8, 4);

    cout << "Addition result: " << resultAdd << ";" << endl;
    cout << "Subtraction result: " << resultSub << ";" << endl;

    return 0;
}