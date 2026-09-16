#include <iostream>
using namespace std;

int main()
{
    int rows, cols;

    // Taking input from the user for number of students and number of subjects
    // And ensuring that the user enters a valid integer value for both 
    cout << "Enter number of students (rows): ";
    cin >> rows;

    cout << "Enter number of subjects (columns): ";
    cin >> cols;

    while (rows <= 0 || cols <= 0)
    {
        cout << "Rows and columns must be greater than 0." << endl;

        cout << "Enter number of students (rows): ";
        cin >> rows;

        cout << "Enter number of subjects (columns): ";
        cin >> cols;
    }

    // Creating an array of pointers where the pointers are pointing to the rows
    int **marks = new int*[rows];

    // Now we are assigning the columns for each of the rows within this array
    for (int r = 0; r < rows; r++)
    {
        *(marks + r) = new int[cols];
    }

    // Input marks
    cout << "\nEnter marks for each student:\n";

    for (int r = 0; r < rows; r++)
    {
        cout << "Student " << r + 1 << ": ";

        for (int c = 0; c < cols; c++)
        {
            cin >> *(*(marks + r) + c);
        }
    }

    // Display matrix
    cout << "\nMarks Matrix:\n";

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << *(*(marks + r) + c) << " ";
        }

        cout << endl;
    }

    // Calculating the first students total in order to make comparisons later
    int bestTotal = 0;

    for (int c = 0; c < cols; c++)
    {
        bestTotal += *(*(marks + 0) + c);
    }

    int bestStudent = 1;

    // Calculate remaining students' totals
    cout << "\nTotals: ";

    for (int r = 0; r < rows; r++)
    {
        int total = 0;

        for (int c = 0; c < cols; c++)
        {
            total += *(*(marks + r) + c);
        }

        cout << total;

        if (r < rows - 1)
            cout << ", ";

        // Comparisons and updating in case the new student has greater marks then the previous student
        if (r > 0 && total > bestTotal)
        {
            bestTotal = total;
            bestStudent = r + 1;
        }
    }

    cout << endl;

    cout << "Top student: " << bestStudent << endl;
    cout << "Highest total: " << bestTotal << endl;

    // Deallocate each row
    for (int r = 0; r < rows; r++)
    {
        delete[] marks[r];
    }

    // Deallocate row-pointer array
    delete[] marks;

    // Set pointer to nullptr
    marks = nullptr;

    return 0;
}