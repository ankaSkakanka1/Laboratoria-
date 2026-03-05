#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

void insert(Node*& root, int val) {
    if (!root) {
        root = new Node(val);
    } else if (val < root->value) {
        insert(root->left, val);
    } else if (val > root->value) {
        insert(root->right, val);
    }
}

bool find(Node* root, int val) {
    if (!root) return false;
    if (root->value == val) return true;
    if (val < root->value) return find(root->left, val);
    return find(root->right, val);
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->value << " ";
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->value << " ";
    }
}

int main() {
    int T;
    cin >> T;
    Node* root = nullptr;

    while (T--) {
        string command;
        cin >> command;

        if (command == "ADD") {
            int x;
            cin >> x;
            insert(root, x);
        } else if (command == "FIND") {
            int x;
            cin >> x;
            cout << (find(root, x) ? "TAK" : "NIE") << endl;
        } else if (command == "INORDER") {
            inorder(root);
            cout << endl;
        } else if (command == "POSTORDER") {
            postorder(root);
            cout << endl;
        }
    }

    return 0;
}