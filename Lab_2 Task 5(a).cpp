#include <iostream>
using namespace std;

void swapValues(int *pa, int *pb)
{
    int temp;

    temp = *pa;  // Dereferencing pa and storing the value at that address in temp 
    *pa = *pb; // Storing the value at pb into the variable pa
    *pb = temp; // storing the value of temp in the variable where pb is pointing
}

int main()
{
    int a = 5, b = 10;

    cout << "Before swapping:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swapValues(&a, &b);

    cout << "\nAfter swapping:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}