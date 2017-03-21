#include "hashtable.h"
int main (void){
  srand(time(0));
  Hashtable A('A'), B('B'), C('C'), D('D'), E('E');
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
  A.print_hashtable();
  B.print_hashtable();
  C.print_hashtable();
  D.print_hashtable();
  E.print_hashtable();

  A.diff(B);
  C.product(D);
  C.xor_sets(E);
  A.sum(C);
  A.set_setname('F');
  cout << "\nResult:\n";
  A.print_hashtable();
}
