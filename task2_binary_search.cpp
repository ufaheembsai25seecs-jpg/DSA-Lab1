#include <iostream>
using namespace std;

// read sorted registration ids
void inputSortedIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) cin >> arr[i];
}

// verify array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

// iterative binary search
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2; // prevent overflow
        if (arr[mid] == target) return mid; // match found
        else if (arr[mid] < target) low = mid + 1; // right half
        else high = mid - 1; // left half
    }
    return -1; // not found
}

// print array
void printArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) cout << arr[i] << (i < n - 1 ? ", " : "");
    cout << "]";
}

// run one test case
void runTest(int testNum, int arr[], int n, int target) {
    cout << "Test Case " << testNum << ": Array = ";
    printArray(arr, n);
    cout << ", Target = " << target << endl;
    if (!isSorted(arr, n)) {
        cout << "Error: Array is not sorted." << endl;
        return;
    }
    int idx = binarySearch(arr, 0, n - 1, target);
    if (idx != -1) cout << "Result: Found at index " << idx << endl;
    else cout << "Result: Target " << target << " not found" << endl;
    cout << "------------------------------------------" << endl;
}

int main() {
    cout << "==========================================" << endl;
    cout << " TASK 2: BINARY SEARCH ON SORTED IDS" << endl;
    cout << "==========================================" << endl;

    int a1[] = {10, 20, 30, 40, 50};
    runTest(1, a1, 5, 30);
    runTest(2, a1, 5, 10);
    runTest(3, a1, 5, 50);
    runTest(4, a1, 5, 25);

    int a2[] = {7};
    runTest(5, a2, 1, 7);

    int* a3 = NULL;
    runTest(6, a3, 0, 5);

    return 0;
}
