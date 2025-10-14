#ifndef BST_H
#define BST_H

class BSTNode {
public:
    int key;
    int frequency;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int key,int frequency = 1) : key(key), frequency(frequency),left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    void insert(int key, int frequency = 1);
    void inorder() const;
    BSTNode* getRoot() const
    {
        return root;
    }
    void remove(int key);



private:
    BSTNode* root;

    void insertNode(BSTNode*& node, int key, int frequency);

    void inorderTraversal(BSTNode* node) const;
    void deleteTree(BSTNode* node);
    BSTNode* deleteNode(BSTNode* node, int key);

    BSTNode* findMin(BSTNode* node);

};

#endif // BST_H
