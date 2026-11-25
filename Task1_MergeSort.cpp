// Lab 11 - Task 1: Merge Sort
// Name: ____________   Reg No: ____________   Section: BSAI 2A
// Implemented from scratch (no std::sort / std::stable_sort / std::inplace_merge).
#include <iostream>
using namespace std;

long long comparisons = 0;   // element comparisons made in merge()
int maxDepth = 0;            // deepest recursion level reached

// Prints the whole array on one line, e.g. [35 12 43 ...]
void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << arr[i];
    cout << "]";
}

// merge: merges sorted arr[low..mid] and sorted arr[mid+1..high].
// Time: O(n) for n = high-low+1.  Extra space: O(n) (temporary arrays L and R).
// Uses <= so equal elements keep their original order (stable).
void merge(int arr[], int low, int mid, int high, int total) {
    int n1 = mid - low + 1;            // size of left half
    int n2 = high - mid;               // size of right half
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];   // <= keeps stability
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];          // leftovers of L
    while (j < n2) arr[k++] = R[j++];          // leftovers of R

    delete[] L;                                // no memory leaks
    delete[] R;

    cout << "  merge [" << low << ".." << high << "] -> ";
    printArray(arr, total);
    cout << endl;
}

// mergeSort: recursively splits arr[low..high] and merges the halves.
// Time: O(n log n) in every case.  Space: O(n) auxiliary + O(log n) stack.
void mergeSortHelper(int arr[], int low, int high, int total, int depth) {
    if (depth > maxDepth) maxDepth = depth;    // deepest call level (root = 0)
    if (low >= high) return;                   // 0 or 1 element: already sorted
    int mid = low + (high - low) / 2;          // overflow-safe midpoint
    mergeSortHelper(arr, low, mid, total, depth + 1);
    mergeSortHelper(arr, mid + 1, high, total, depth + 1);
    merge(arr, low, mid, high, total);
}
void mergeSort(int arr[], int low, int high) {
    mergeSortHelper(arr, low, high, high + 1, 0);
}

// Runs one test case and prints before/after, comparisons and depth.
void runTest(const char* title, int arr[], int n) {
    comparisons = 0; maxDepth = 0;
    cout << "\n=== " << title << " ===" << endl;
    cout << "Before: "; printArray(arr, n); cout << endl;
    mergeSort(arr, 0, n - 1);
    cout << "After : "; printArray(arr, n); cout << endl;
    cout << "Comparisons = " << comparisons
         << ", max recursion depth = " << maxDepth << endl;
}

int main() {
    int a[] = {35, 12, 43, 8, 51, 27, 19};
    runTest("Main test {35,12,43,8,51,27,19}", a, 7);

    int sorted[]  = {1, 2, 4, 5, 8};
    int reverse[] = {8, 5, 4, 2, 1};
    int dup[]     = {5, 2, 5, 1, 2};
    int one[]     = {42};
    runTest("Already sorted", sorted, 5);
    runTest("Reverse sorted", reverse, 5);
    runTest("Repeated values", dup, 5);
    runTest("Single element (n = 1)", one, 1);
    runTest("Empty array (n = 0)", nullptr, 0);
    return 0;
}
