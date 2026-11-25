// Lab 11 - Task 2: Quick Sort (last element as pivot, Lomuto partition)
// Name: ____________   Reg No: ____________   Section: BSAI 2A
// Implemented from scratch (no std::sort / std::partition).
#include <iostream>
using namespace std;

long long comparisons = 0;   // counts every test arr[j] <= pivot
bool traceOn = true;         // print each partition step
bool detailOn = false;       // print i, j, swaps inside partition

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) cout << (i ? " " : "") << arr[i];
    cout << "]";
}
void swapInt(int& a, int& b) { int t = a; a = b; b = t; }

int gN = 0;  // full array size, used only for printing

// partition (Lomuto): pivot = arr[high]. Puts pivot at its final index and
// returns it. Elements <= pivot end up on the left, larger ones on the right.
// Time: O(n) for n = high-low+1.  Space: O(1).
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                       // end of the "<= pivot" region
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swapInt(arr[i], arr[j]);
            if (detailOn) {
                cout << "    j=" << j << " arr[j]<=" << pivot << " -> i=" << i
                     << ", swap arr[" << i << "] and arr[" << j << "] -> ";
                printArray(arr, gN); cout << endl;
            }
        } else if (detailOn) {
            cout << "    j=" << j << " arr[j]=" << arr[j] << " > " << pivot
                 << " -> no swap, i=" << i << endl;
        }
    }
    swapInt(arr[i + 1], arr[high]);        // place pivot between the two regions
    if (detailOn) {
        cout << "    swap pivot: arr[" << i + 1 << "] <-> arr[" << high << "] -> ";
        printArray(arr, gN); cout << endl;
    }
    if (traceOn) {
        cout << "  partition [" << low << ".." << high << "] pivot=" << pivot
             << " pi=" << i + 1 << " -> ";
        printArray(arr, gN); cout << endl;
    }
    return i + 1;
}

// quickSort: Time O(n log n) average, O(n^2) worst (sorted/reverse input
// with a last-element pivot).  Space O(log n) average, O(n) worst (stack).
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);       // exclude pi: it is already in place
        quickSort(arr, pi + 1, high);
    }
}

void trace(const char* title, int arr[], int n) {
    comparisons = 0; gN = n;
    cout << "\n=== " << title << " ===" << endl;
    cout << "Before: "; printArray(arr, n); cout << endl;
    quickSort(arr, 0, n - 1);
    cout << "After : "; printArray(arr, n); cout << endl;
    cout << "Total comparisons = " << comparisons << endl;
}

int main() {
    // ---- Part A: step-by-step traces ----
    int t1[] = {2, 1, 5, 4, 6, 3};
    int t2[] = {35, 12, 43, 8, 51, 27, 19};
    trace("Trace {2,1,5,4,6,3}", t1, 6);
    trace("Trace {35,12,43,8,51,27,19}", t2, 7);

    // ---- Part B: hand-trace of the first partition pass of {2,1,5,4,6,3} ----
    cout << "\n=== First partition pass of {2,1,5,4,6,3} (pivot = 3) ===" << endl;
    int h[] = {2, 1, 5, 4, 6, 3};
    gN = 6; detailOn = true; comparisons = 0;
    cout << "  start: "; printArray(h, 6); cout << ", i = -1" << endl;
    int pi = partition(h, 0, 5);
    cout << "  returned pi = " << pi << ", comparisons = " << comparisons << endl;
    detailOn = false;

    // ---- Part C: comparison counts (trace output switched off) ----
    traceOn = false;
    cout << "\n=== Comparison counts ===" << endl;
    int r[]   = {5, 1, 4, 2, 8};
    int s[]   = {1, 2, 4, 5, 8};
    int rv[]  = {8, 5, 4, 2, 1};
    int rep[] = {7, 7, 7, 7, 7};
    int one[] = {9};
    trace("Random order {5,1,4,2,8}", r, 5);
    trace("Already sorted {1,2,4,5,8}", s, 5);
    trace("Reverse sorted {8,5,4,2,1}", rv, 5);
    trace("Repeated values {7,7,7,7,7}", rep, 5);
    trace("Single element n = 1", one, 1);
    trace("Empty array n = 0", nullptr, 0);
    return 0;
}
