#include <iostream>
using namespace std;

// read student ids
void inputIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) cin >> arr[i];
}

// linear search function
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i; // match found
    }
    return -1; // not found
}

// display search result
void displayResult(int index) {
    if (index != -1) cout << "Result: Found at index " << index << endl;
    else cout << "Result: ID is not registered (Not found)" << endl;
}

// print array
void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i < n - 1 ? ", " : "");
    }
    cout << "]";
}

// run one test case
void runTest(int testNum, int arr[], int n, int target) {
    cout << "Test Case " << testNum << ": Input = ";
    printArray(arr, n);
    cout << ", Target = " << target << endl;
    int idx = linearSearch(arr, n, target);
    displayResult(idx);
    cout << "------------------------------------------" << endl;
}

int main() {
    cout << "==========================================" << endl;
    cout << " TASK 1: STUDENT ID LINEAR SEARCH" << endl;
    cout << "==========================================" << endl;

    int a1[] = {10, 20, 30, 40};
    runTest(1, a1, 4, 10);
    runTest(2, a1, 4, 30);
    runTest(3, a1, 4, 50);

    int a2[] = {7};
    runTest(4, a2, 1, 7);

    int* a3 = NULL;
    runTest(5, a3, 0, 5);

    return 0;
}
