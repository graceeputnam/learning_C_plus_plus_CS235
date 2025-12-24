#pragma once
#include <functional>

template<class T>
class BST {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() {
        root = nullptr;
        node_count = 0;
    }

    ~BST() {
        clear();
    }

    const Node* getRootNode() const {
        return root;
    }

    bool insert(T item) {
        bool did_insert = false;
        root = insertHelper(root, item, did_insert);
        if (did_insert) node_count++;
        return did_insert;
    }

    bool remove(T item) {
        bool did_remove = false;
        root = removeHelper(root, item, did_remove);
        if (did_remove) node_count--;
        return did_remove;
    }

    bool contains(T item) const {
        return containsHelper(root, item);
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
        node_count = 0;
    }

    int size() const {
        return node_count;
    }

    void inorder_traversal(std::function<void(T)> visit) const {
        std::function<void(Node*)> go = [&](Node* node) {
            if (!node) return;
            go(node->left);
            visit(node->value);
            go(node->right);
        };
        go(root);
    }

    void preorder_traversal(std::function<void(T)> visit) const {
        std::function<void(Node*)> go = [&](Node* node) {
            if (!node) return;
            visit(node->value);
            go(node->left);
            go(node->right);
        };
        go(root);
    }

    void postorder_traversal(std::function<void(T)> visit) const {
        std::function<void(Node*)> go = [&](Node* node) {
            if (!node) return;
            go(node->left);
            go(node->right);
            visit(node->value);
        };
        go(root);
    }

private:
    Node* root = nullptr;
    int node_count = 0;

    Node* insertHelper(Node* node, T item, bool& did_insert) {
        if (!node) {
            did_insert = true;
            return new Node(item);
        }
        if (item < node->value) node->left = insertHelper(node->left, item, did_insert);
        else if (item > node->value) node->right = insertHelper(node->right, item, did_insert);
        return node;
    }

    Node* removeHelper(Node* node, T item, bool& did_remove) {
        if (!node) return nullptr;
        if (item < node->value) node->left = removeHelper(node->left, item, did_remove);
        else if (item > node->value) node->right = removeHelper(node->right, item, did_remove);
        else {
            did_remove = true;
            // No children
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Only right
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Only left
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Two children
            Node* parent = node;
            Node* pred = node->left;
            while (pred->right) {
                parent = pred;
                pred = pred->right;
            }
            node->value = pred->value;
            if (parent == node)
                node->left = removeHelper(node->left, pred->value, did_remove); // immediate left child
            else
                parent->right = removeHelper(parent->right, pred->value, did_remove); // recursive delete, no leaks!
        }
        return node;
    }

    bool containsHelper(Node* node, T item) const {
        if (!node) return false;
        if (item < node->value) return containsHelper(node->left, item);
        if (item > node->value) return containsHelper(node->right, item);
        return true;
    }

    void clearHelper(Node* node) {
        if (!node) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
};
