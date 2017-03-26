#include <iostream>
#include "rb.h"
#include "bin_operation.cpp"

using namespace std;

int main()
{
  RB tree,tree2;
    tree.insert(2);
    tree.insert(5);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(10);
    tree.insert(9);
    tree.insert(23);

    tree2.insert(22);
    tree2.insert(23);
    tree2.insert(1);
    tree2.insert(10);
    //tree.print();


    vector<int> res;
    vector<int>::iterator it;
    rb_product(res,tree,tree2);

    for(it=res.begin(); it < res.end(); it++) {
      cout << *it << " ";
    }


    cout << endl;
    
    
    return 0;
}

