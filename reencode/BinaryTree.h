
#pragma once

#include "Node.h"

#include <vector>
#include <queue>

template <typename T>
class BinaryTree
{
public:

    BinaryTree() : root(nullptr) {}

    BinaryTree(std::vector<T> vec) : root(nullptr)
    {
        for (auto &itr : vec)
        {
            Add(itr);
        }
    }

    ~BinaryTree()
    {
        if (nullptr != root)
        {
            Destroy(root);
        }
    }

    bool operator==(const BinaryTree& rhs)
    {
        return *this == rhs.root;
    }

    bool operator==(Node<T>* rhs)
    {
        std::queue<int> q1;
        std::queue<int> q2;

        QueueMe(q1, root);
        QueueMe(q2, rhs);
        return q1 == q2;
    }

    Node<T>* Add(T value)
    {
        if (nullptr == root)
        {
            root = new Node<T>({value, nullptr, nullptr});
            return root;
        }
        auto parent = FindCloseNode(root, value);
        if (parent->value == value) return nullptr;
        else
        {
            auto newNode = new Node<T>({value, nullptr, nullptr});
            if (parent->value < value)
            {
                parent->right = newNode;
            }
            else
            {
                parent->left = newNode;
            }
            return newNode;
        }
    }

    Node<T>* Find(T value)
    {
        if (nullptr != root)
        {
            auto node = FindCloseNode(root, value);
            if (node->value == value) return node;
        }
        return nullptr;
    }

private:

    Node<T>* FindCloseNode(Node<T>* node, T value)
    {
        if (node->value == value) return node;
        else if (node->value < value)
        {
            if (nullptr == node->right) return node;
            else return FindCloseNode(node->right, value);
        }
        else
        {
            if (nullptr == node->left) return node;
            else return FindCloseNode(root->left, value);
        }
    }

    void QueueMe(std::queue<T>& q, Node<T>* node)
    {
        if (nullptr != node->left)
        {
            QueueMe(q, node->left);
        }
        q.push(node->value);
        if (nullptr != node->right)
        {
            QueueMe(q, node->right);
        }
    }

    void Destroy(Node<T>* node)
    {
        if (nullptr != node->left)
        {
            Destroy(node->left);
        }
        if (nullptr != node->right)
        {
            Destroy(node->right);
        }
        delete node;
    }

    template <typename A>
    friend class DoubleLinkedList;

    Node<T>* root;
};
