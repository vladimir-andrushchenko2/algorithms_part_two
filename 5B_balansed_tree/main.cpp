#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
  int value;
  const Node* left = nullptr;
  const Node* right = nullptr;
};

int HeightOfTree(const Node* root) {
    if (!root) {
        return 0;
    }
    
    return std::max(HeightOfTree(root->left), HeightOfTree(root->right)) + 1;
}

bool Solution(const Node* root) {
    if (!root) {
        return true;
    }
    
    return std::abs(HeightOfTree(root->left) - HeightOfTree(root->right)) < 2;
}

int main() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    assert(Solution(&node5));
    
    return 0;
}
