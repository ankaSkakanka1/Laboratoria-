#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

Node* buildBalancedBST(const vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Node* node = new Node(nums[mid]);
    node->left = buildBalancedBST(nums, start, mid - 1);
    node->right = buildBalancedBST(nums, mid + 1, end);
    return node;
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}
bool find(Node* root, int val) {
    if (!root) return false;
    if (root->value == val) return true;
    if (val < root->value) return find(root->left, val);
    return find(root->right, val);
}


int main() {
    int N;
    string command;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());
    Node* root = buildBalancedBST(nums, 0, N - 1);
    preorder(root);
    cout << endl;
    cin >> command;
    if (command == "FIND") {
        int x;
        cin >> x;
        cout << (find(root, x) ? "TAK" : "NIE") << endl;
    } 

    return 0;
}