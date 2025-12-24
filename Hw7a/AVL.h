#pragma once

#include <functional>
#include <algorithm>

template <typename T>
struct Node {
    Node* left;
    Node* right;
    T value;
    int height;

    Node(const T& v) : left(nullptr), right(nullptr), value(v), height(1) {}
};

template <typename T>
void update_height(Node<T>* node) {
    if (!node) return;
    int lh = node->left ? node->left->height : 0;
    int rh = node->right ? node->right->height : 0;
    node->height = 1 + std::max(lh, rh);
}

template <typename T>
Node<T>* promote_left(Node<T>* root) {
    if (!root || !root->right)
        return root;
    Node<T>* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    update_height(root);
    update_height(temp);
    return temp;
}

template <typename T>
Node<T>* promote_right(Node<T>* root) {
    if (!root || !root->left)
        return root;
    Node<T>* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    update_height(root);
    update_height(temp);
    return temp;
}

template <typename T>
void rebalance(Node<T>*& root) {
    if (!root) return;
    update_height(root);
    int left_height = root->left ? root->left->height : 0;
    int right_height = root->right ? root->right->height : 0;
    int balance = left_height - right_height;

    if (balance > 1) {
        int ll = root->left && root->left->left ? root->left->left->height : 0;
        int lr = root->left && root->left->right ? root->left->right->height : 0;
        if (lr > ll) root->left = promote_left(root->left);
        root = promote_right(root);
    } else if (balance < -1) {
        int rl = root->right && root->right->left ? root->right->left->height : 0;
        int rr = root->right && root->right->right ? root->right->right->height : 0;
        if (rl > rr) root->right = promote_right(root->right);
        root = promote_left(root);
    }
    update_height(root);
}

template <typename T>
class AVL {
public:
    AVL() : root_(nullptr), size_(0) {}
    ~AVL() { clear(); }

    const Node<T>* getRootNode() const { return root_; }
    int size() const { return size_; }
    void clear() { clear_helper(root_); root_ = nullptr; size_ = 0; }

    bool contains(const T& item) const { return contains_helper(root_, item); }

    bool insert(const T& item) { return insert_helper(root_, item); }
    bool remove(const T& item) { return remove_helper(root_, item); }
    void inorder_traversal(std::function<void(const T&)> visit) const { inorder_helper(root_, visit); }
    void preorder_traversal(std::function<void(const T&)> visit) const { preorder_helper(root_, visit); }
    void postorder_traversal(std::function<void(const T&)> visit) const { postorder_helper(root_, visit); }

private:
    Node<T>* root_;
    int size_;

    bool insert_helper(Node<T>*& node, const T& item) {
        if (!node) {
            node = new Node<T>(item);
            ++size_;
            return true;
        }
        if (item < node->value) {
            bool inserted = insert_helper(node->left, item);
            rebalance(node);
            return inserted;
        } else if (item > node->value) {
            bool inserted = insert_helper(node->right, item);
            rebalance(node);
            return inserted;
        } else { return false;
        }
    }

    bool remove_helper(Node<T>*& node, const T& item) {
        if (!node) return false;
        if (item < node->value) {
            bool removed = remove_helper(node->left, item);
            rebalance(node);
            return removed;
        } else if (item > node->value) {
            bool removed = remove_helper(node->right, item);
            rebalance(node);
            return removed;
        } else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
                --size_;return true;
            } else if (node->left && !node->right) {
                Node<T>* temp = node;
                node = node->left;
                delete temp;
                --size_;
                return true;
            } else if (!node->left && node->right) {
                Node<T>* temp = node;
                node = node->right;
                delete temp;
                --size_;
                return true;
            } else {
                Node<T>* pred = node->left;
                while (pred->right) pred = pred->right;
                node->value = pred->value;
                bool removed = remove_helper(node->left, pred->value);
                rebalance(node);
                return removed;
            }
        }
    }

    bool contains_helper(Node<T>* node, const T& item) const {
        if (!node) return false;
        if (item < node->value) return contains_helper(node->left, item);
        if (item > node->value) return contains_helper(node->right, item);
        return true;
    }

    void clear_helper(Node<T>* node) {
        if (!node) return;
        clear_helper(node->left);
        clear_helper(node->right);
        delete node;
    }

    void inorder_helper(Node<T>* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        inorder_helper(node->left, visit);
        visit(node->value);
        inorder_helper(node->right, visit);
    }

    void preorder_helper(Node<T>* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        visit(node->value);
        preorder_helper(node->left, visit);
        preorder_helper(node->right, visit);
    }

    void postorder_helper(Node<T>* node, std::function<void(const T&)> visit) const {
        if (!node) return;postorder_helper(node->left, visit);
        postorder_helper(node->right, visit);
        visit(node->value);
    }
};
