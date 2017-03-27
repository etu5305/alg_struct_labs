#ifndef RB_H
#define RB_H
#include <vector>
#include <iostream>

/* Свойства Красно-Чёрного Дерева
 1. узел либо красный, либо чёрный
 2. корень - чёрный
 3. все листья - чёрные
 4. оба потомка каждого красного узла - чёрные
 5. всякий простой путь от данного узла до любого листового узла,
   являющегося его потомком, содержит одинаковое число чёрных узлов.
 * */

class RB
{
public:
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

    RB(std::vector<int> &A);
    RB();

    bool find(int key);
    bool insert(int key);
    bool remove(int key);
    void print();
    int get_current_value(); 
    bool pop(); // выбирает следующий элемент за тем, что установлен в current, устанавливает указатель на него в current
    bool is_end(); // проверяет, последний ли current элемент в дереве
    void pop_clear(){ end=0; current=0; }
    

private:
    bool bs_find(Node* &search, int key);
    void printnode(int key, int h);
    void show(Node* t, int h);
    void build(int *A, int m);
    void rotate_left(Node* n);
    void rotate_right(Node* n);
    Node* recur_insert (std::vector<int> &A, Node *par, int start, int end);

    static Node* uncle(Node* node);
    static Node* grandparent(Node* node);
    static Node* sibling(Node* node);
    void fix(Node* node); // балансировка дерева
    bool remove_fix(Node* N);
    Node* current; // устанавливается при вызове pop(), для получения значения в узле используется get_current_value()
    bool end; // флаг, который устанавливается, когда во время вызова pop() был достигнут конец дерева

    Node* root; // корень
    int count; // количество узлов в дереве
};


#endif // RB_H
