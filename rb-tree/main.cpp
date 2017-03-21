#include <iostream>
#include <bst.h>

using namespace std;

int main()
{
    BST tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(10);
    tree.insert(9);
    tree.insert(11);

    tree.remove(7);
    tree.remove(9);

    tree.print();

    return 0;
}

