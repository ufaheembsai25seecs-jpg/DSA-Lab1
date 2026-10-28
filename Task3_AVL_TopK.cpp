// Task 3: Self-balancing AVL tree that maintains / returns / deletes the top-k elements
// Criteria: MAX (k largest), MIN (k smallest), SUM (k largest + their sum, via subtree sums)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum Criterion { MAX, MIN, SUM };

struct Node {
    int key;
    int cnt;            // number of copies of key (duplicates are allowed)
    int height;         // height of the subtree (leaf = 1)
    int size;           // total number of elements in the subtree (counting duplicates)
    long long sum;      // sum of all elements in the subtree
    Node *left, *right;
    Node(int k) : key(k), cnt(1), height(1), size(1), sum(k), left(nullptr), right(nullptr) {}
};

class AVLTree {
    Node* root = nullptr;
    vector<string> log;     // rotations performed during the current operation

    // ---------- helpers ----------
    static int h(Node* n)        { return n ? n->height : 0; }
    static int sz(Node* n)       { return n ? n->size : 0; }
    static long long sm(Node* n) { return n ? n->sum : 0; }
    static int balance(Node* n)  { return n ? h(n->left) - h(n->right) : 0; }

    static void update(Node* n) {
        n->height = 1 + max(h(n->left), h(n->right));
        n->size   = n->cnt + sz(n->left) + sz(n->right);
        n->sum    = (long long)n->key * n->cnt + sm(n->left) + sm(n->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        update(y); update(x);
        return x;
    }
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        update(x); update(y);
        return y;
    }

    // Restore the AVL property at n (self-healing step)
    Node* rebalance(Node* n) {
        update(n);
        int bf = balance(n);
        if (bf > 1) {
            if (balance(n->left) < 0) {            // Left-Right case
                log.push_back("Left-Right (LR) imbalance at " + to_string(n->key) +
                              " -> rotateLeft(" + to_string(n->left->key) +
                              "), rotateRight(" + to_string(n->key) + ")");
                n->left = rotateLeft(n->left);
            } else {
                log.push_back("Left-Left (LL) imbalance at " + to_string(n->key) +
                              " -> rotateRight(" + to_string(n->key) + ")");
            }
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balance(n->right) > 0) {           // Right-Left case
                log.push_back("Right-Left (RL) imbalance at " + to_string(n->key) +
                              " -> rotateRight(" + to_string(n->right->key) +
                              "), rotateLeft(" + to_string(n->key) + ")");
                n->right = rotateRight(n->right);
            } else {
                log.push_back("Right-Right (RR) imbalance at " + to_string(n->key) +
                              " -> rotateLeft(" + to_string(n->key) + ")");
            }
            return rotateLeft(n);
        }
        return n;
    }

    // ---------- insert / delete ----------
    Node* insert(Node* n, int key) {
        if (!n) return new Node(key);
        if (key < n->key)      n->left  = insert(n->left, key);
        else if (key > n->key) n->right = insert(n->right, key);
        else { n->cnt++; }                          // duplicate: just count it
        return rebalance(n);
    }

    Node* minNode(Node* n) { while (n->left) n = n->left; return n; }

    // removes ONE copy of key
    Node* remove(Node* n, int key, bool& found) {
        if (!n) return nullptr;
        if (key < n->key)      n->left  = remove(n->left, key, found);
        else if (key > n->key) n->right = remove(n->right, key, found);
        else {
            found = true;
            if (n->cnt > 1) { n->cnt--; }
            else if (!n->left || !n->right) {
                Node* child = n->left ? n->left : n->right;
                delete n;
                return child;                       // may be nullptr
            } else {
                Node* s = minNode(n->right);        // in-order successor
                n->key = s->key;
                n->cnt = s->cnt;
                // remove the successor's node (all its copies) from the right subtree
                bool f;
                n->right = removeAll(n->right, n->key, f);
            }
        }
        return rebalance(n);
    }

    // removes the whole node holding key (all copies); used when moving successor up
    Node* removeAll(Node* n, int key, bool& found) {
        if (!n) return nullptr;
        if (key < n->key)      n->left  = removeAll(n->left, key, found);
        else if (key > n->key) n->right = removeAll(n->right, key, found);
        else {
            found = true;
            if (!n->left || !n->right) {
                Node* child = n->left ? n->left : n->right;
                delete n;
                return child;
            }
            Node* s = minNode(n->right);
            n->key = s->key;
            n->cnt = s->cnt;
            bool f;
            n->right = removeAll(n->right, s->key, f);
        }
        return rebalance(n);
    }

    // ---------- top-k collection (early-stopping traversals) ----------
    void collectLargest(Node* n, int& k, vector<int>& out) {
        if (!n || k == 0) return;
        collectLargest(n->right, k, out);
        for (int i = 0; i < n->cnt && k > 0; i++) { out.push_back(n->key); k--; }
        collectLargest(n->left, k, out);
    }
    void collectSmallest(Node* n, int& k, vector<int>& out) {
        if (!n || k == 0) return;
        collectSmallest(n->left, k, out);
        for (int i = 0; i < n->cnt && k > 0; i++) { out.push_back(n->key); k--; }
        collectSmallest(n->right, k, out);
    }
    // sum of the k largest elements in O(log n) using subtree sizes/sums
    long long sumLargest(Node* n, int k) {
        if (!n || k <= 0) return 0;
        if (k >= n->size) return n->sum;
        int r = sz(n->right);
        if (k <= r) return sumLargest(n->right, k);
        long long res = sm(n->right);
        k -= r;
        int take = min(k, n->cnt);
        res += (long long)take * n->key;
        k -= take;
        return res + sumLargest(n->left, k);
    }

    void printTree(Node* n, int depth) {
        if (!n) return;
        printTree(n->right, depth + 1);
        cout << string(depth * 6, ' ') << n->key;
        if (n->cnt > 1) cout << "(x" << n->cnt << ")";
        cout << " [h=" << n->height << ",bf=" << balance(n) << "]\n";
        printTree(n->left, depth + 1);
    }
    void destroy(Node* n) { if (!n) return; destroy(n->left); destroy(n->right); delete n; }
    bool isBalanced(Node* n) {
        if (!n) return true;
        return abs(balance(n)) <= 1 && isBalanced(n->left) && isBalanced(n->right);
    }

public:
    ~AVLTree() { destroy(root); }
    int count() const { return sz(root); }

    void show(const string& title) {
        cout << "  " << title << "\n";
        for (auto& s : log) cout << "    * " << s << "\n";
        if (log.empty()) cout << "    * no rotation needed\n";
        log.clear();
        if (!root) cout << "    (tree is empty)\n";
        else printTree(root, 2);   // tree is drawn sideways: right subtree on top
        cout << "    balanced: " << (isBalanced(root) ? "yes" : "NO") << "\n\n";
    }

    // Insert several elements, rebalancing and printing after each one
    void insertMany(const vector<int>& vals) {
        for (int v : vals) {
            root = insert(root, v);
            show("After inserting " + to_string(v) + ":");
        }
    }

    bool erase(int v, bool print = true) {
        bool found = false;
        root = remove(root, v, found);
        if (print) show(found ? "After deleting " + to_string(v) + ":" : "Delete " + to_string(v) + ": value not found");
        else log.clear();
        return found;
    }

    // Update = delete old value + insert new value
    void update(int oldV, int newV) {
        bool found = false;
        root = remove(root, oldV, found);
        if (!found) {
            cout << "  Update failed: " << oldV << " not found\n\n";
            return;
        }
        root = insert(root, newV);
        show("After updating " + to_string(oldV) + " -> " + to_string(newV) + ":");
    }

    vector<int> topK(int k, Criterion c) {
        vector<int> out;
        int kk = k;
        if (c == MIN) collectSmallest(root, kk, out);
        else          collectLargest(root, kk, out);
        return out;
    }

    void queryTopK(int k, Criterion c) {
        vector<int> r = topK(k, c);
        const char* name = c == MAX ? "MAX" : c == MIN ? "MIN" : "SUM";
        cout << "  Top " << k << " [" << name << "]: ";
        for (size_t i = 0; i < r.size(); i++) cout << r[i] << (i + 1 < r.size() ? ", " : "");
        if (c == SUM) cout << "  -> sum = " << sumLargest(root, k);
        cout << "\n\n";
    }

    // Delete the top-k elements one at a time, rebalancing and printing after each deletion
    void deleteTopK(int k, Criterion c) {
        vector<int> r = topK(k, c);
        cout << "  Deleting top " << k << " elements (criterion "
             << (c == MAX ? "MAX" : c == MIN ? "MIN" : "SUM") << ")\n\n";
        for (int v : r) erase(v, true);
    }
};

int main() {
    AVLTree t;

    cout << "=== 1. Insert multiple elements (rebalance + print after each) ===\n\n";
    t.insertMany({10, 20, 30, 40, 50, 25, 5, 4, 45, 45});

    cout << "=== 2. Query top-k with different criteria ===\n\n";
    t.queryTopK(3, MAX);
    t.queryTopK(3, MIN);
    t.queryTopK(4, SUM);

    cout << "=== 3. Update an element ===\n\n";
    t.update(5, 60);

    cout << "=== 4. Delete a single element ===\n\n";
    t.erase(10);

    cout << "=== 5. Delete top-3 (MAX); rebalance + print after each deletion ===\n\n";
    t.deleteTopK(3, MAX);

    cout << "=== 6. Delete top-3 (MIN); a deletion that triggers a rotation ===\n\n";
    t.deleteTopK(3, MIN);

    cout << "=== 7. Query again after deletions ===\n\n";
    t.queryTopK(3, MAX);
    t.queryTopK(2, MIN);
    t.queryTopK(3, SUM);
    cout << "  Elements remaining: " << t.count() << "\n";
    return 0;
}
