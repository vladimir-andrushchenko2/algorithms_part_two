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
    
    int height_of_left = HeightOfTree(root->left);
    
    int height_of_right = HeightOfTree(root->right);
    
    return std::abs(height_of_left - height_of_right) < 2 && Solution(root->left) && Solution(root->right);
}

int main() {
    {
        Node node1({1, nullptr, nullptr});
        Node node2({-5, nullptr, nullptr});
        Node node3({3, &node1, &node2});
        Node node4({10, nullptr, nullptr});
        Node node5({2, &node3, &node4});
        assert(Solution(&node5));
    }
    
    {
        Node node7({1, nullptr, nullptr});
        Node node8({-5, nullptr, nullptr});
        Node node6({10, nullptr, nullptr});
        Node node5({3, nullptr, nullptr});
        Node node4({2, &node7, &node8});
        Node node3({2, &node5, &node6});
        Node node2({2, nullptr, &node4});
        Node node1({2, &node3, nullptr});
        Node node0({2, &node1, &node2});
        assert(!Solution(&node0));
    }
    
    return 0;
}
