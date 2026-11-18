// Name: Unais Bin Faheem | CMS ID: 542343 | Class: BSAI-2A
// CS250 Data Structures and Algorithms - Lab 10
// Task 1: Max Heap Insertion and Heap Sort
// No STL containers are used; the heap lives in a dynamic int array.
//
// Index arithmetic (0-based):  parent(i) = (i - 1) / 2
//                              left(i)   = 2i + 1,  right(i) = 2i + 2

#include <iostream>
using namespace std;

class MaxHeap {
private:
    int* arr;       // dynamic array holding the heap
    int  size;      // number of elements currently stored
    int  capacity;  // number of elements the array can hold

    // Doubles the array when it is full.
    // Time complexity: O(n) for the copy, but O(1) amortised per insertion.
    void grow() {
        capacity *= 2;
        int* bigger = new int[capacity];
        for (int i = 0; i < size; i++) bigger[i] = arr[i];
        delete[] arr;
        arr = bigger;
    }

    // Sifts a[i] down inside the first n elements of array a so the
    // max-heap property holds for the subtree rooted at i.
    // Time complexity: O(log n)
    static void siftDown(int* a, int n, int i) {
        while (true) {
            int left = 2 * i + 1, right = 2 * i + 2, largest = i;
            if (left < n && a[left] > a[largest])   largest = left;
            if (right < n && a[right] > a[largest]) largest = right;
            if (largest == i) return;
            int t = a[i]; a[i] = a[largest]; a[largest] = t;
            i = largest;
        }
    }

public:
    // Creates an empty heap with the given starting capacity.  Time: O(1)
    MaxHeap(int cap = 4) : size(0), capacity(cap) { arr = new int[capacity]; }

    // Releases the dynamic array.  Time: O(1)
    ~MaxHeap() { delete[] arr; }

    // Places value at the end, then sifts it up while it is larger than its
    // parent. Returns the number of swaps. Time: O(log n) worst case.
    int insert(int value) {
        if (size == capacity) grow();
        int i = size++;
        arr[i] = value;
        int swaps = 0;
        while (i > 0 && arr[i] > arr[(i - 1) / 2]) {
            int p = (i - 1) / 2;
            int t = arr[i]; arr[i] = arr[p]; arr[p] = t;
            i = p;
            swaps++;
        }
        return swaps;
    }

    // Prints the heap array in storage order.  Time: O(n)
    void printHeap() const {
        for (int i = 0; i < size; i++) cout << arr[i] << (i + 1 < size ? " " : "");
    }

    // Returns a NEW array holding the heap contents in ascending order, so
    // the original max heap stays intact. Works on a copy: repeatedly swap the
    // root (maximum) with the last element, shrink the range, sift down.
    // Caller must delete[] the result. Time: O(n log n)
    int* heapSort() const {
        int* a = new int[size];
        for (int i = 0; i < size; i++) a[i] = arr[i];
        for (int end = size - 1; end > 0; end--) {
            int t = a[0]; a[0] = a[end]; a[end] = t;
            siftDown(a, end, 0);
        }
        return a;
    }

    // Returns how many elements are stored.  Time: O(1)
    int getSize() const { return size; }
};

int main() {
    int input[] = {25, 40, 15, 60, 35, 10, 70, 50};
    int n = sizeof(input) / sizeof(input[0]);

    MaxHeap heap;
    cout << "=== Task 1: Max Heap Insertion ===\n";
    for (int i = 0; i < n; i++) {
        int swaps = heap.insert(input[i]);
        cout << "Insert " << input[i] << " | Swaps: " << swaps << " | Heap: ";
        heap.printHeap();
        cout << "\n";
    }

    cout << "\nFinal max heap : ";
    heap.printHeap();
    cout << "\n";

    int* sorted = heap.heapSort();
    cout << "Sorted output  : ";
    for (int i = 0; i < heap.getSize(); i++)
        cout << sorted[i] << (i + 1 < heap.getSize() ? " " : "");
    cout << "\n";
    delete[] sorted;

    // ---------------- Answers to the questions ----------------
    // Q1. Worst-case swaps for one insertion into a heap of n elements:
    //     the new value can climb from the last level to the root, so the
    //     swaps equal the tree height = floor(log2 n)  ->  O(log n).
    // Q2. Building the heap by n insertions costs O(n log n) in the worst
    //     case (each insertion is O(log n)).
    //     Heap sort also costs O(n log n): n sift-downs of O(log n) each.
    //     (If the heap is built with the bottom-up method, the build is O(n),
    //     but the total for heap sort is still O(n log n).)
    return 0;
}
