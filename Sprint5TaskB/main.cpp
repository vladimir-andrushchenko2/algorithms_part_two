#include <cassert>
#include <utility>

struct Node {
  Node* left;
  Node* right;
  int value;
};

// get parent of max node and node
Node* FindParentOfMax(Node* trailing_pointer, Node* runner) {
    while (runner->right) {
        trailing_pointer = runner;
        runner = runner->right;
    }
    
    return trailing_pointer;
}

Node* remove(Node* root, int key) {
    // Your code
    // “ヽ(´▽｀)ノ”
}

void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    
    FindParentOfMax(<#Node *root#>)
//    Node* newHead = remove(&node7, 10);
//    assert(newHead->value == 5);
//    assert(newHead->right == &node5);
//    assert(newHead->right->value == 8);
}



int main() {
    test();
    
    return 0;
}
