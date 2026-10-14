#include <iostream>
using namespace std;

// display array elements
void displayArray(int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i < n - 1 ? ", " : "");
    }
    cout << "]";
}

// merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // temporary arrays
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // merge elements in order
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// recursive merge sort
void mergeSort(int arr[], int left, int right) {
    if (left >= right) return; // base case

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);      // sort left half
    mergeSort(arr, mid + 1, right); // sort right half
    merge(arr, left, mid, right);    // merge both halves
}

// run one test case
void runTest(int testNum, int arr[], int n) {
    cout << "Test Case " << testNum << ":" << endl;
    cout << "Input:  ";
    displayArray(arr, n);
    cout << endl;

    if (n > 1) {
        mergeSort(arr, 0, n - 1);
    }

    cout << "Output: ";
    displayArray(arr, n);
    cout << "\n------------------------------------------" << endl;
}

int main() {
    cout << "==========================================" << endl;
    cout << " TASK 3: SORT STUDENT MARKS (MERGE SORT)" << endl;
    cout << "==========================================" << endl;

    int a1[] = {45, 12, 78, 33, 20, 60};
    runTest(1, a1, 6);

    int a2[] = {1, 2, 3, 4};
    runTest(2, a2, 4);

    int a3[] = {9, 7, 5, 3, 1};
    runTest(3, a3, 5);

    int a4[] = {5, 2, 5, 1, 2};
    runTest(4, a4, 5);

    int a5[] = {8};
    runTest(5, a5, 1);

    int* a6 = NULL;
    runTest(6, a6, 0);

    return 0;
}
