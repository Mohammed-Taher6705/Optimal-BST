#include "BST.h"
#include <iostream>

using namespace std;

BST::BST() : root(nullptr) {}

BST::~BST()
{
    deleteTree(root);
}

void BST::insert(int key, int frequency)
{
    insertNode(root, key, frequency);
}


void BST::insertNode(BSTNode*& node, int key, int frequency)
{
    if (node==nullptr)
    {
        node = new BSTNode(key, frequency);
        return;
    }

    if (key < node->key) {
        insertNode(node->left, key, frequency);
    }
    else if (key > node->key)
    {
        insertNode(node->right, key, frequency);
    }
    else
    {
        node->frequency += frequency;         // If the key already exists, just update the frequency

    }
}

void BST::inorder() const
{
    inorderTraversal(root);


    cout << endl;
}

void BST::inorderTraversal(BSTNode* node) const //L N R
{
    if (node == nullptr)
    {
        return ;
    }
    inorderTraversal(node->left);
    cout << node->key << " ";
    inorderTraversal(node->right);
}

void BST::deleteTree(BSTNode* node) {
    if (node == nullptr)
    {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}
void BST::remove(int key)
{
    root = deleteNode(root, key);
}

BSTNode* BST::deleteNode(BSTNode* node, int key)
{
    if (!node)
    {
        return node;
    }

    if (key < node->key)
    {
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    }
    else
    {
        if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;

        }
        else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        BSTNode* temp = findMin(node->right);

        node->key = temp->key;

     node->right = deleteNode(node->right, temp->key);
    }
    return node;
}

BSTNode* BST::findMin(BSTNode* node) {
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}
