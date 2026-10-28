// Task 2: Merge k sorted linked lists using a Binary (Min) Heap
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

// Binary min-heap of ListNode* ordered by node value
class MinHeap {
    vector<ListNode*> a;
    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[i]->val >= a[p]->val) break;
            swap(a[i], a[p]);
            i = p;
        }
    }
    void siftDown(int i) {
        int n = a.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, m = i;
            if (l < n && a[l]->val < a[m]->val) m = l;
            if (r < n && a[r]->val < a[m]->val) m = r;
            if (m == i) break;
            swap(a[i], a[m]);
            i = m;
        }
    }
public:
    bool empty() const { return a.empty(); }
    void push(ListNode* x) { a.push_back(x); siftUp(a.size() - 1); }
    ListNode* pop() {
        ListNode* top = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) siftDown(0);
        return top;
    }
};

// Merge k sorted lists. Time O(N log k), extra space O(k).
ListNode* mergeKLists(vector<ListNode*>& lists) {
    MinHeap heap;
    for (ListNode* head : lists)
        if (head) heap.push(head);              // only the head of each list

    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!heap.empty()) {
        ListNode* smallest = heap.pop();        // global minimum among all heads
        tail->next = smallest;
        tail = smallest;
        if (smallest->next) heap.push(smallest->next);   // advance that list
    }
    return dummy.next;
}

// ---------- helpers ----------
ListNode* makeList(const vector<int>& v) {
    ListNode dummy(0);
    ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
void printList(ListNode* h) {
    if (!h) { cout << "(empty)"; return; }
    for (; h; h = h->next) cout << h->val << (h->next ? " -> " : "");
}
void freeList(ListNode* h) {
    while (h) { ListNode* n = h->next; delete h; h = n; }
}

void runCase(const vector<vector<int>>& data) {
    vector<ListNode*> lists;
    cout << "Input lists:\n";
    for (size_t i = 0; i < data.size(); i++) {
        lists.push_back(makeList(data[i]));
        cout << "  L" << i + 1 << ": ";
        printList(lists.back());
        cout << "\n";
    }
    ListNode* merged = mergeKLists(lists);
    cout << "Merged: ";
    printList(merged);
    cout << "\n\n";
    freeList(merged);
}

int main() {
    runCase({{1, 4, 5}, {1, 3, 4}, {2, 6}});
    runCase({{}, {7, 8}, {}, {1, 9, 10}});
    runCase({});
    return 0;
}
