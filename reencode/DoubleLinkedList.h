
#pragma once

#include "Node.h"
#include "BinaryTree.h"

#include <vector>

template <typename T>
class DoubleLinkedList
{
public:
    DoubleLinkedList() : root(nullptr) {}

    DoubleLinkedList(std::vector<T> vec) : root(nullptr)
    {
        for (auto &itr : vec)
        {
            Add(itr);
        }
    }

    bool operator==(const DoubleLinkedList& rhs)
    {
        return *this == rhs.root;
    }

    bool operator==(Node<T>* rhs)
    {
        Node<T>* rRoot = rhs;
        Node<T>* rptr = rhs;
        Node<T>* ptr = root;
        if (rRoot == nullptr && root == nullptr) return true;
        else if (rRoot == nullptr) return false;
        else if (root == nullptr) return false;

        while (rptr->right != rRoot && ptr->right != root &&
                rptr->value == ptr->value)
        {
            rptr = rptr->right;
            ptr = ptr->right;
        }
        if (rptr->right == rRoot && ptr->right == root && rptr->value == ptr->value) return true;
        return false;
    }

    ~DoubleLinkedList()
    {
        Destroy(root);
    }

    Node<T>* Add(T value)
    {
        if (nullptr == root)
        {
            root = new Node<T>({value, nullptr, nullptr});
            root->left = root;
            root->right = root;
            return root;
        }

        auto parent = FindCloseNode(root, value);
        if (parent->value == value) return nullptr;
        else
        {
            if (parent->value > value) parent = parent->left;
            auto newNode = new Node<T>({value, nullptr, nullptr});
            parent->right->left = newNode;
            newNode->right = parent->right;
            parent->right = newNode;
            newNode->left = parent;

            if (newNode->value < root->value)
            {
                root = newNode;
            }

            return newNode;
        }
    }

    Node<T>* Find(T value)
    {
        if (nullptr != root)
        {
            auto node = FindCloseNode(root, value);
            if (root->value == value) return root;
        }
        return nullptr;
    }

    template <typename A>
    static DoubleLinkedList<A>* Convert(BinaryTree<A>* input)
    {

        auto newList = new DoubleLinkedList<T>();
        if (input->root == nullptr)
        {
            return newList;
        }
        else
        {
            Node<T>* start = input->root;
            Node<T>* end = input->root;
            while (start->left != nullptr) start = start->left;
            while (end->right != nullptr) end = end->right;
            Node<A>* left = nullptr;
            Node<A>* right = nullptr;
            ConvertRecurse(input->root, &left, &right, &start, &end);
            newList->root = start;
        }

        input = nullptr;
    }

private:

    static void ConvertRecurse(Node<T>* node, Node<T>** left, Node<T>** right, Node<T>** parent, Node<T>** last)
    {
        if (nullptr == node->left)
        {
            node->left = *last;
            *left = node;
        }
        else
        {
            Node<T>* rtemp = nullptr;
            ConvertRecurse(node->left, left, &rtemp, &node, last);
            node->left = rtemp;
        }

        if (nullptr == node->right)
        {
            node->right = *parent;
            *right = node;
        }
        else
        {
            Node<T>* ltemp = nullptr;
            ConvertRecurse(node->right, &ltemp, right, parent, &node);
            node->right = ltemp;
        }
    }

    Node<T>* FindCloseNode(Node<T>* node, T value)
    {
        while (root != node->right && node->right->value < value)
        {
            node = node->right;
        }
        return node;
    }

    void Destroy(Node<T>* node)
    {
        while (node != root)
        {
            auto self = node;
            node = node->right;
            delete self;
        }
    }

    Node<T>* root;
};
