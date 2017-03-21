#ifndef RB_H
#define RB_H

struct Node
{
  int key;
  bool color; // red = 0, black = 1

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

class RB
{
public:
    RB(int *A, int n);
    RB();

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


#endif // RB_H
