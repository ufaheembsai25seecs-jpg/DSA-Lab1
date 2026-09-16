#include <iostream>
using namespace std;

int main()
{
    int n;

    // Take input from the user for the value of n(the marks from 1 to 10) and validate the value
    do
    {
        cout << "Enter number of marks (1-10): ";
        cin >> n;
    } while (n < 1 || n > 10);

    // Allocate original block
    int *marks = new int[n];

    // Input the original marks
    cout << "Enter " << n << " marks: ";

    for (int i = 0; i < n; i++)
    {
        cin >> *(marks + i);
    }

    // Allocate new block with one extra position
    int *newMarks = new int[n + 1];

    // Copy original marks using pointer notation
    for (int i = 0; i < n; i++)
    {
        *(newMarks + i) = *(marks + i);
    }

    // Read new student's mark into final position
    cout << "Enter new mark: ";
    cin >> *(newMarks + n);

    // Release old block
    delete[] marks;

    // Make original pointer refer to new block
    marks = newMarks;

    // Update size
    n = n + 1;

    // Display the marks on the screen
    cout << "Marks: ";

    for (int i = 0; i < n; i++)
    {
        cout << *(marks + i) << " ";
    }

    cout << endl;

    // Release final block once and only once
    delete[] marks;

    marks = nullptr;

    return 0;
}