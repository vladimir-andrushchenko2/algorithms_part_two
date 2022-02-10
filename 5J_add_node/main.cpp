//#include "solution.h"
#include <cassert>

struct Node {
  Node* left;
  Node* right;
  int value;
};

void insert_impl(Node* root, int key) {
    if (key < root->value) {
        if (!root->left) {
            root->left = new Node{nullptr, nullptr, key};
        } else {
            insert_impl(root->left, key);
        }
    } else {
        if (!root->right) {
            root->right = new Node{nullptr, nullptr, key};
        } else {
            insert_impl(root->right, key);
        }
    }
}

Node* insert(Node* root, int key) {
    insert_impl(root, key);
    return root;
}

int main() {
    Node node1({nullptr, nullptr, 7});
    Node node2({&node1, nullptr, 8});
    Node node3({nullptr, &node2, 7});
    Node* newHead = insert(&node3, 6);
    assert(newHead->left->value == 6);
    assert(newHead == &node3);
    
    return 0;
}
