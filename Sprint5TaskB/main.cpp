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

auto Find(Node* root, int key) {
    Node* trailing_pointer = nullptr;

    while (root && root->value != key) {
        trailing_pointer = root;
        
        if (root->value < key) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    
    return std::pair{trailing_pointer, root};
}

void Transplant(Node* parent_of_node_to_be_replaced, Node* node_to_be_replaced, Node* replacement) {
    // if replacing root
    if (!parent_of_node_to_be_replaced) {
        node_to_be_replaced = replacement;
        
    } else if (node_to_be_replaced == parent_of_node_to_be_replaced->left) {
        parent_of_node_to_be_replaced->left = replacement;
        
    } else {
        parent_of_node_to_be_replaced->right = replacement;
    }
}

void Delete(Node* parent, Node* node_to_delete) {
    if (!node_to_delete->left) {
        Transplant(parent, node_to_delete, node_to_delete->right);
        
    } else if (!node_to_delete->right) {
        Transplant(parent, node_to_delete, node_to_delete->left);
        
    } else {
        // if both children
        Node* parent_of_max_in_left_subtree = FindParentOfMax(node_to_delete, node_to_delete->left);
        
        decltype(node_to_delete->value) value_of_max_in_left_subtree;
        
        // удаляю узел который буду использовать как затычку
        if (node_to_delete != parent_of_max_in_left_subtree) {
            value_of_max_in_left_subtree = parent_of_max_in_left_subtree->right->value;
            Transplant(parent_of_max_in_left_subtree, parent_of_max_in_left_subtree->right, parent_of_max_in_left_subtree->right->left);
            
        } else {
            value_of_max_in_left_subtree = parent_of_max_in_left_subtree->left->value;
            Transplant(parent_of_max_in_left_subtree, parent_of_max_in_left_subtree->left, parent_of_max_in_left_subtree->left->left);
        }
        
        node_to_delete->value = value_of_max_in_left_subtree;
    }
}

Node* remove(Node* root, int key) {
    auto output = root;
    auto [parent, node_to_delete] = Find(root, key);
    Delete(parent, node_to_delete);
    return output;
}

void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}



int main() {
    test();
    
    return 0;
}
