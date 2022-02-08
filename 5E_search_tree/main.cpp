//#include "solution_tree.h"
#include <cassert>
#include <limits>

using namespace std;

struct Node {
  int value;
  const Node* left = nullptr;
  const Node* right = nullptr;
};

bool IsSubtreeSorted(const Node* root, int max, int min) {
    if (!root) {
        return true;
    }

    if (root->value <= min || root->value >= max) {
        return false;
    }

    return IsSubtreeSorted(root->left, root->value, min) && IsSubtreeSorted(root->right, max, root->value);
}

bool Solution(const Node* root) {
    return IsSubtreeSorted(root, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
}

int main() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
    
    return 0;
}
