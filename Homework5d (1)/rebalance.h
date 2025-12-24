#pragma once

#include <algorithm>

struct Node {
    Node* left;
    Node* right;
    int value;
    int height;

    Node(int v) : left(nullptr), right(nullptr), value(v), height(1) {}
};

void update_height(Node* node) {
    if (!node) return;
    int lh = node->left ? node->left->height : 0;
    int rh = node->right ? node->right->height : 0;
    node->height = 1 + std::max(lh, rh);
}

Node* promote_left(Node* root) {
    if (!root || !root->right)
        return root;
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    update_height(root);
    update_height(temp);
    return temp;
}

Node* promote_right(Node* root) {
    if (!root || !root->left)
        return root;
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    update_height(root);
    update_height(temp);
    return temp;
}

// For rebalance: you only use pointer assignment here!
// The logic below is correct because root is Node*&, but promote_left/right returns Node*
void rebalance(Node*& root) {
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
_H