// Name: Unais Bin Faheem | CMS ID: 542343 | Class: BSAI-2A
// CS250 Data Structures and Algorithms - Lab 10
// Task 2: Hospital ER Wait-Time Monitor
// Two heaps give the running median: a max heap holds the smaller half of the
// waits, a min heap holds the larger half. The two roots sit at the middle of
// the sorted data. No STL containers are used.

#include <iostream>
using namespace std;

// One class serves as both heaps: isMax = true -> max heap, false -> min heap.
class Heap {
private:
    int* a;
    int size, capacity;
    bool isMax;

    // True if x should sit above y in this heap.  Time: O(1)
    bool above(int x, int y) const { return isMax ? x > y : x < y; }

    // Doubles the array when full.  Time: O(n) but O(1) amortised per push.
    void grow() {
        capacity *= 2;
        int* b = new int[capacity];
        for (int i = 0; i < size; i++) b[i] = a[i];
        delete[] a;
        a = b;
    }

public:
    // Creates an empty heap of the chosen type.  Time: O(1)
    Heap(bool max, int cap = 4) : size(0), capacity(cap), isMax(max) { a = new int[capacity]; }

    // Frees the dynamic array.  Time: O(1)
    ~Heap() { delete[] a; }

    // Adds x at the end and sifts it up. Time: O(log n)
    void push(int x) {
        if (size == capacity) grow();
        int i = size++;
        a[i] = x;
        while (i > 0 && above(a[i], a[(i - 1) / 2])) {
            int p = (i - 1) / 2;
            int t = a[i]; a[i] = a[p]; a[p] = t;
            i = p;
        }
    }

    // Removes and returns the root: move the last element to the root, then
    // sift it down. Caller must check isEmpty() first. Time: O(log n)
    int pop() {
        int root = a[0];
        a[0] = a[--size];
        int i = 0;
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, best = i;
            if (l < size && above(a[l], a[best])) best = l;
            if (r < size && above(a[r], a[best])) best = r;
            if (best == i) break;
            int t = a[i]; a[i] = a[best]; a[best] = t;
            i = best;
        }
        return root;
    }

    // Returns the root without removing it. Caller must check isEmpty(). Time: O(1)
    int top() const { return a[0]; }

    // Number of stored elements.  Time: O(1)
    int getSize() const { return size; }

    // True when the heap has no elements.  Time: O(1)
    bool isEmpty() const { return size == 0; }
};

class WaitMonitor {
private:
    Heap lower;   // max heap: smaller half (holds the extra element)
    Heap upper;   // min heap: larger half
    int threshold;

public:
    // Creates the monitor with the alert threshold in minutes.  Time: O(1)
    WaitMonitor(int thr) : lower(true), upper(false), threshold(thr) {}

    // Inserts the wait into the correct heap, then rebalances so the sizes
    // differ by at most one, with the max heap holding the extra element.
    // Time: O(log n)
    void addWait(int x) {
        if (lower.isEmpty() || x <= lower.top()) lower.push(x);
        else                                     upper.push(x);

        if (lower.getSize() > upper.getSize() + 1)      upper.push(lower.pop());
        else if (upper.getSize() > lower.getSize())     lower.push(upper.pop());
    }

    // Returns TWICE the median so that .5 values stay exact integers.
    // Time: O(1)
    int twiceMedian() const {
        if (lower.getSize() > upper.getSize()) return 2 * lower.top();
        return lower.top() + upper.top();
    }

    // Median lookup: max-heap root if it holds one more element, otherwise
    // the average of the two roots. Returned as a double. Time: O(1)
    double getMedian() const { return twiceMedian() / 2.0; }

    // True when the median is above the alert threshold. Time: O(1)
    bool alert() const { return twiceMedian() > 2 * threshold; }

    // Prints one report line for an arrival.  Time: O(1)
    void report(int arrival, int wait) const {
        cout << "Arrival " << arrival << " | Wait: " << wait << " | Max root: " << lower.top()
             << " | Min root: ";
        if (upper.isEmpty()) cout << "none"; else cout << upper.top();
        int t = twiceMedian();
        cout << " | Median: " << t / 2 << (t % 2 ? ".5" : "") << " | "
             << (alert() ? "ALERT: call extra staff" : "Normal") << "\n";
    }
};

int main() {
    int waits[] = {45, 20, 60, 15, 30, 90, 10, 55};
    int n = sizeof(waits) / sizeof(waits[0]);

    WaitMonitor monitor(35);
    cout << "=== Task 2: Hospital ER Wait-Time Monitor (threshold 35 min) ===\n";
    for (int i = 0; i < n; i++) {
        monitor.addWait(waits[i]);
        monitor.report(i + 1, waits[i]);
    }

    // ---------------- Answers to the questions ----------------
    // Q1. At arrival 6 the waits are 45 20 60 15 30 90. The average is 43.3 and
    //     the single 90-minute case lifted it from 34 (at arrival 5) by 9.3
    //     minutes. The median (37.5) depends only on the middle two values
    //     (30 and 45); even if the 90 were 900 the median would stay 37.5
    //     while the average would explode to 178. The median reflects the
    //     typical patient, so one extreme case cannot distort the alert.
    // Q2. The roots only sit at the middle of the sorted data if the heaps are
    //     balanced. If the sizes differ by 2 or more, the roots are no longer
    //     the middle values and the reported median is wrong. Example: if
    //     10 20 30 40 50 all went into the max heap, its root 50 would be
    //     reported although the true median is 30.
    // Q3. Re-sorting after every arrival costs O(k log k) for the k-th patient,
    //     about (n^2 / 2) log n in total = O(n^2 log n). The heap method costs
    //     O(log n) per arrival = O(n log n) in total, and each median lookup is
    //     O(1). For n = 1000 that is roughly 5,000,000 versus 10,000 operations.
    return 0;
}
