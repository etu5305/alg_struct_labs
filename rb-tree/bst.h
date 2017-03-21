#ifndef BST_H
#define BST_H

#include <iostream>

struct Node
{
  int key;

  Node* left;
  Node* right;
  Node* parent;

  Node(int key, Node* parent = 0)
  {
    this->key = key;
    left = 0;
    right = 0;
    this->parent = parent;
  }

  Node() : Node(0) { }
};

class BST
{
public:
    BST(int *A, int n);
    BST();

    bool find(int key);
    bool insert(int key);
    bool remove(int key);
    void print();

private:
    bool bs_find(Node* &search, int key);
    void printnode(int key, int h);
    void show(Node* t, int h);
    void build(int *A, int m);

    Node* root; // корень
    int count; // количество узлов в дереве
};

#endif // BST_H
