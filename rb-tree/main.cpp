#include <iostream>
#include "rb.h"
#include "bin_operation.cpp"

using namespace std;

int main()
{
  srand(time(0));
  RB A('A'), B('B'), C('C'), D('D'), E('E');
  int ans=2;
  do{
    cout << "Would you like to enter (1) sets yourself or to generate (2) random sets ? (1/2) ";
    cin.clear();
    cin.sync();
    cin >> ans;
    if ((ans != 1) && (ans != 2)){
      cout << "Please, you must choose between 1 and 2. \n";
    }
  }while ((ans != 1) && (ans != 2));
  
  cout << "\n";

  if (ans == 1){
    A.input_set();
    B.input_set();
    C.input_set();
    D.input_set();
    E.input_set();
    
  }else{
    A.generate_set();
    B.generate_set();
    C.generate_set();
    D.generate_set();
    E.generate_set();
    }
  A.print();
  B.print();
  C.print();
  D.print();
  E.print();

    vector<int> res;
    vector<int>::iterator it;
    
    rb_diff(res,A,B);
    RB* tree_res1 = new RB('F',res);
    res.clear();

    rb_product(res,C,D);
    for (it = res.begin(); it != res.end(); it++){
      cout << *it << endl;
  }
    RB* tree_res2 = new RB('F',res);
    res.clear();

    rb_xor(res,*tree_res2,E);
    delete tree_res2;
    tree_res2 = new RB('F',res);
    res.clear();

    rb_sum(res, *tree_res1, *tree_res2);
    delete tree_res1;
    delete tree_res2;
    tree_res1 = new RB('F',res);
    res.clear();

    cout << "Resulting tree:" << endl;
    tree_res1->pop_clear();
    while (tree_res1->pop()){
      cout << tree_res1->get_current_value() << " ";
    }
cout << endl;
    tree_res1->print();

    cout << endl;
    
    
    return 0;
}

