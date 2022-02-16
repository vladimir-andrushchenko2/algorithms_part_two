// 65208098

#include <cassert>
#include <utility>

/*
-- ПРИНЦИП РАБОТЫ --
Нужно удалить узел таким образом, чтоб дерево не распалось. То есть нужно позаботиться о связи родительского узла и какого-то узла следующего после удаляемого при сохранении свойств бинарного дерева поиска.
 
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 O(logn) так как в худшем случае для удаления прийдется спуститься в самый низ дерева поиска. Это может произойти при удалении самого дальнего листа от корня или при удалении узла у которого есть оба потомка и для сохранения свойств дерева нужно будет спуститься в самый низ одного из поддеревьев для поиска замены удаляемого узла.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 O(n) для хранения дерева и O(1) для удаления, так как может потребоваться некоторая дополнительная память для восстановления дерева после удаления элемента.
 
*/

struct Node {
    Node* left;
    Node* right;
    int value;
};

// get parent of max node and node
Node* FindParentOfMax(Node* root_parent, Node* root) {
    while (root->right) {
        root_parent = root;
        root = root->right;
    }
    
    return root_parent;
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

Node* CopyNode(Node* parent_of_target, Node* target, Node* source) {
    // if replacing root
    if (!parent_of_target) {
        target = source;
        
    } else if (target == parent_of_target->left) {
        parent_of_target->left = source;
        
    } else {
        parent_of_target->right = source;
    }

    return source;
}

Node* Delete(Node* parent, Node* node_to_delete) {
    if (!node_to_delete->left) {
        return CopyNode(parent, node_to_delete, node_to_delete->right);
        
    } else if (!node_to_delete->right) {
        return CopyNode(parent, node_to_delete, node_to_delete->left);
        
    } else {
        // if both children
        Node* parent_of_max_in_left_subtree = FindParentOfMax(node_to_delete, node_to_delete->left);
        
        Node* max_in_left_subtree;
        
        // delete node that will be used as replacement
        if (node_to_delete != parent_of_max_in_left_subtree) {
            max_in_left_subtree = parent_of_max_in_left_subtree->right;

            CopyNode(parent_of_max_in_left_subtree, parent_of_max_in_left_subtree->right, parent_of_max_in_left_subtree->right->left);
            
        } else {
            // if node_to_delete is parent of max in left subtree
            max_in_left_subtree = parent_of_max_in_left_subtree->left;

            CopyNode(parent_of_max_in_left_subtree, parent_of_max_in_left_subtree->left, parent_of_max_in_left_subtree->left->left);
        }
        
        max_in_left_subtree->left = node_to_delete->left;
        max_in_left_subtree->right = node_to_delete->right;

        return CopyNode(parent, node_to_delete, max_in_left_subtree);
    }
}

Node* remove(Node* root, int key) {
    auto [parent, node_to_delete] = Find(root, key);

    if (!node_to_delete) {
        return root;
    }

    // if deleting root
    if (!parent) {
        return Delete(parent, node_to_delete);

    } else {
        Delete(parent, node_to_delete);
        return root;
    }
}

void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
//    Node* newHead = remove(&node7, 10);
//    assert(newHead->value == 5);
//    assert(newHead->right == &node5);
//    assert(newHead->right->value == 8);

    Node* newHead = remove(&node7, 5234);
    assert(newHead == &node7);

//    Node* newHead = remove(&node7, 5);
//    assert(newHead->value == 3);
//
//    assert(newHead->left == &node3);
//    assert(newHead->left->right == &node1);
//
//    assert(newHead->right->value == 10);
//    assert(newHead->right->left == &node5);
}



int main() {
    test();
    
    return 0;
}
