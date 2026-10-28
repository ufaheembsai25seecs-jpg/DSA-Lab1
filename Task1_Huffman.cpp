// Task 1: Huffman Tree using a Binary (Min) Heap, codes printed in preorder
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Node of the Huffman tree
struct HNode {
    char ch;          // character (valid only for leaves)
    int freq;         // frequency (sum of children for internal nodes)
    int order;        // creation order, used to break ties deterministically
    HNode *left, *right;
    HNode(char c, int f, int o) : ch(c), freq(f), order(o), left(nullptr), right(nullptr) {}
};

// Binary min-heap of HNode* (array based)
class MinHeap {
    vector<HNode*> a;

    // true if x should come out before y
    bool less(HNode* x, HNode* y) {
        if (x->freq != y->freq) return x->freq < y->freq;
        return x->order < y->order;
    }
    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (!less(a[i], a[p])) break;
            swap(a[i], a[p]);
            i = p;
        }
    }
    void siftDown(int i) {
        int n = a.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, m = i;
            if (l < n && less(a[l], a[m])) m = l;
            if (r < n && less(a[r], a[m])) m = r;
            if (m == i) break;
            swap(a[i], a[m]);
            i = m;
        }
    }
public:
    int size() const { return a.size(); }
    void push(HNode* x) { a.push_back(x); siftUp(a.size() - 1); }
    HNode* pop() {
        HNode* top = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) siftDown(0);
        return top;
    }
};

// Build the Huffman tree from characters and their frequencies
HNode* buildHuffman(const string& S, const vector<int>& f) {
    MinHeap heap;
    int order = 0;
    for (size_t i = 0; i < S.size(); i++) heap.push(new HNode(S[i], f[i], order++));
    while (heap.size() > 1) {
        HNode* x = heap.pop();           // smallest  -> left  (edge 0)
        HNode* y = heap.pop();           // 2nd smallest -> right (edge 1)
        HNode* z = new HNode('#', x->freq + y->freq, order++);
        z->left = x;
        z->right = y;
        heap.push(z);
    }
    return heap.pop();
}

// Preorder traversal: root -> left -> right, printing the code at every leaf
void preorder(HNode* root, string code, vector<pair<char,string>>& out) {
    if (!root) return;
    if (!root->left && !root->right) {
        out.push_back({root->ch, code.empty() ? "0" : code});
        return;
    }
    preorder(root->left, code + "0", out);
    preorder(root->right, code + "1", out);
}

void freeTree(HNode* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    delete r;
}

void runCase(const string& S, const vector<int>& f) {
    cout << "S = \"" << S << "\", f = [";
    for (size_t i = 0; i < f.size(); i++) cout << f[i] << (i + 1 < f.size() ? ", " : "");
    cout << "]\n";
    HNode* root = buildHuffman(S, f);
    vector<pair<char,string>> codes;
    preorder(root, "", codes);
    cout << "Huffman codes (preorder): ";
    for (auto& c : codes) cout << c.second << " ";
    cout << "\n";
    for (auto& c : codes) cout << "   " << c.first << " -> " << c.second << "\n";
    cout << endl;
    freeTree(root);
}

int main() {
    runCase("abcdef", {5, 9, 12, 13, 16, 45});
    runCase("abcd",   {10, 5, 30, 55});
    runCase("x",      {7});
    return 0;
}
