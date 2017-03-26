#include <iostream>
#include "rb.h"
#include "bin_operation.cpp"

using namespace std;

int main()
{
  RB tree,tree2;
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(10);
    tree.insert(9);
    tree.insert(23);

     tree2.insert(9);
    tree2.insert(23);
    tree2.insert(1);
    tree2.insert(10);
    //tree.print();


    vector<int> res;
    vector<int>::iterator it;
    rb_xor(res,tree,tree2);

    RB tree_res = RB(res);

    while (tree_res.pop()){
      cout << tree_res.get_current_value() << " ";
    }

    tree_res.print();

    cout << endl;
    
    
    return 0;
}

