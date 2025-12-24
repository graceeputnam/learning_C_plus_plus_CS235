#pragma once
#include <stdlib.h>
#include <functional>

template <typename T>
class BST
{
private:
    struct Node
    {
        T value;
        Node *left;
        Node *right;

        Node(T const &v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node *root = nullptr;
    size_t node_count = 0;

public:
    BST() = default;

    ~BST()
    {
        clear();
    }

    bool insert(T const &value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            ++node_count;
            return true;
        }

        Node *current = root;
        while (true)
        {
            if (value == current->value)
            {
                return false;
            }
            else if (value < current->value)
            {
                if (current->left == nullptr)
                {
                    current->left = new Node(value);
                    ++node_count;
                    return true;
                }
                current = current->left;
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = new Node(value);
                    ++node_count;
                    return true;
                }
                current = current->right;
            }
        }
    }

    bool contains(T const &value)
    {
        Node *current = root;
        while (current != nullptr)
        {
            if (value == current->value)
            {
                return true;
            }
            else if (value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return false;
    }

    bool remove(T const &value)
    {
        return remove_recursive(root, value);
    }

    void inorder_traversal(std::function<void(T)> visit) const
    {
        inorder_recursive(root, visit);
    }

    void preorder_traversal(std::function<void(T)> visit) const
    {
        preorder_recursive(root, visit);
    }

    void postorder_traversal(std::function<void(T)> visit) const
    {
        postorder_recursive(root, visit);
    }

    size_t size() const
    {
        return node_count;
    }

    void clear()
    {
        clear_recursive(root);
        root = nullptr;
        node_count = 0;
    }

private:

    void inorder_recursive(Node *node, std::function<void(T)> visit) const
    {
        if (node == nullptr) return;
        inorder_recursive(node->left, visit);
        visit(node->value);
        inorder_recursive(node->right, visit);
    }

    void preorder_recursive(Node *node, std::function<void(T)> visit) const
    {
        if (node == nullptr) return;
        visit(node->value);
        preorder_recursive(node->left, visit);
        preorder_recursive(node->right, visit);
    }

    void postorder_recursive(Node *node, std::function<void(T)> visit) const
    {
        if (node == nullptr) return;
        postorder_recursive(node->left, visit);
        postorder_recursive(node->right, visit);
        visit(node->value);
    }


    void clear_recursive(Node *node)
    {
        if (node == nullptr) return;
        clear_recursive(node->left);
        clear_recursive(node->right);
        delete node;
    }

    Node *find_max(Node *node) const
    {
        while (node != nullptr && node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    }


    bool remove_recursive(Node *&node, T const &value)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (value < node->value)
        {
            return remove_recursive(node->left, value);
        }
        else if (value > node->value)
        {
            return remove_recursive(node->right, value);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
                --node_count;
                return true;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node;
                node = node->right;
                delete temp;
                --node_count;
                return true;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node;
                node = node->left;
                delete temp;
                --node_count;
                return true;
            }
            else
            {
                Node *pred = find_max(node->left);
                T pred_val = pred->value;
                node->value = pred_val;
                remove_recursive(node->left, pred_val);
                return true;
            }
        }
    }
};
