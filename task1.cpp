#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* buildTree(const string& expression, int& index) {
    if (index >= (int)expression.length() ||
        expression[index] == ',' ||
        expression[index] == ')') {
        return nullptr;
    }

    Node* root = new Node(expression[index]);
    index++;

    if (index < (int)expression.length() && expression[index] == '(') {
        index++;

        root->left = buildTree(expression, index);

        if (index < (int)expression.length() && expression[index] == ',') {
            index++;
        }

        root->right = buildTree(expression, index);

        if (index < (int)expression.length() && expression[index] == ')') {
            index++;
        }
    }

    return root;
}

void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorderIterative(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout << current->data << " ";
        current = current->right;
    }
}

void postorderIterative(Node* root) {
    if (root == nullptr) {
        return;
    }

    stack<Node*> first;
    stack<Node*> second;
    first.push(root);

    while (!first.empty()) {
        Node* current = first.top();
        first.pop();
        second.push(current);

        if (current->left != nullptr) {
            first.push(current->left);
        }

        if (current->right != nullptr) {
            first.push(current->right);
        }
    }

    while (!second.empty()) {
        cout << second.top()->data << " ";
        second.pop();
    }
}

// Validates the expression without constructing tree nodes.
bool parseNode(const string& s, int& i) {
    if (i >= (int)s.length() ||
        !isalpha(static_cast<unsigned char>(s[i]))) {
        return false;
    }

    i++;

    if (i < (int)s.length() && s[i] == '(') {
        i++;

        if (i < (int)s.length() && s[i] != ',') {
            if (!parseNode(s, i)) {
                return false;
            }
        }

        if (i >= (int)s.length() || s[i] != ',') {
            return false;
        }

        i++;

        if (i < (int)s.length() && s[i] != ')') {
            if (!parseNode(s, i)) {
                return false;
            }
        }

        if (i >= (int)s.length() || s[i] != ')') {
            return false;
        }

        i++;
    }

    return true;
}

bool isValidTreeString(const string& s) {
    if (s.empty()) {
        return false;
    }

    int index = 0;

    if (!parseNode(s, index)) {
        return false;
    }

    return index == (int)s.length();
}

// Height is measured in edges. An empty tree has height -1.
int height(Node* root) {
    if (root == nullptr) {
        return -1;
    }

    return 1 + max(height(root->left), height(root->right));
}

void printDepths(Node* root, int depth) {
    if (root == nullptr) {
        return;
    }

    cout << "Node " << root->data << " has depth " << depth << endl;
    printDepths(root->left, depth + 1);
    printDepths(root->right, depth + 1);
}

void destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

BSTNode* insertBST(BSTNode* root, int value) {
    if (root == nullptr) {
        return new BSTNode(value);
    }

    if (value < root->data) {
        root->left = insertBST(root->left, value);
    } else if (value > root->data) {
        root->right = insertBST(root->right, value);
    }

    return root;
}

void inorderBST(BSTNode* root) {
    if (root == nullptr) {
        return;
    }

    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}

void destroyBST(BSTNode* root) {
    if (root == nullptr) {
        return;
    }

    destroyBST(root->left);
    destroyBST(root->right);
    delete root;
}

int main() {
    string expression = "a(b(d,e),c(,f(g,)))";

    cout << "TASK 1: BINARY TREE OPERATIONS" << endl;
    cout << "Expression: " << expression << endl;

    if (!isValidTreeString(expression)) {
        cout << "Invalid tree expression." << endl;
        return 1;
    }

    cout << "Validation: Valid tree string" << endl;

    int index = 0;
    Node* root = buildTree(expression, index);

    cout << "Preorder (recursive): ";
    preorder(root);
    cout << endl;

    cout << "Inorder (iterative): ";
    inorderIterative(root);
    cout << endl;

    cout << "Postorder (iterative): ";
    postorderIterative(root);
    cout << endl;

    cout << "Tree height (edges): " << height(root) << endl;

    cout << "Node depths:" << endl;
    printDepths(root, 0);

    string invalidExpression = "a(b,c";
    cout << "Validation test for \"" << invalidExpression << "\": "
         << (isValidTreeString(invalidExpression) ? "Valid" : "Invalid")
         << endl;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int size = sizeof(values) / sizeof(values[0]);
    BSTNode* bstRoot = nullptr;

    for (int i = 0; i < size; i++) {
        bstRoot = insertBST(bstRoot, values[i]);
    }

    cout << "BST inorder: ";
    inorderBST(bstRoot);
    cout << endl;

    destroyTree(root);
    destroyBST(bstRoot);

    return 0;
}
