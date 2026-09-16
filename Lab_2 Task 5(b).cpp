#include <iostream>
using namespace std;

void swapValues(int **ppa, int **ppb)
{
    int temp;

    temp = **ppa;
    **ppa = **ppb;
    **ppb = temp;
}

int main()
{
    int a = 5, b = 10;

    int *pa = &a;
    int *pb = &b;

    int **ppa = &pa;
    int **ppb = &pb;

    cout << "Before swapping:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swapValues(ppa, ppb);

    cout << "\nAfter swapping:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}