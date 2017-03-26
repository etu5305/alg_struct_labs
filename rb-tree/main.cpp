#include <iostream>
#include "rb.h"

using namespace std;

int main()
{
    RB tree;

    tree.insert(5);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(10);
    tree.insert(9);
    tree.insert(11);

    tree.print();

    cout << endl;
    while(tree.pop()){
      cout << tree.get_current_value() << " ";
    }


    cout << endl;
    
    
    return 0;
}

