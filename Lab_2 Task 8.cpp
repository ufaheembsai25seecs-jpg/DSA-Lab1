#include <iostream>
using namespace std;

int main()
{
    int n = 3;

    // Allocate memory for 3 integers
    int* values = new int[n];

    // Fixing error one by making it < and not <=
    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }

    // Display the integers
    cout << "Values: ";

    for (int i = 0; i < n; i++)
    {
        cout << values[i] << " ";
    }

    cout << endl;

    // Using delete[] instead of delete to release the values
    delete[] values;

    // Reset pointer
    values = nullptr;

    return 0; // We are not accessing the array values after it has been deallocated
}