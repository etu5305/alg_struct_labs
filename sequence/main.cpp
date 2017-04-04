#include <iostream>
#include "rb.h"
using namespace std;
int main(int argc, char *argv[])
{
    srand(time(0));
    RB A('A'), B('B');
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
    
    }else{
      A.generate_set();
      B.generate_set();
    }
    A.print();
    A.print_sequence();
            
    B.print();
    B.print_sequence();

    ans=2;
    do{
      cout << "\nWhat would you like to do with those sequences? (1) - merge it, (2) - concat it, (3) - change it ";
      cin.clear();
      cin.sync();
      cin >> ans;
      if ((ans != 1) && (ans != 2) && (ans != 3)){
	cout << "Please, you must choose between 1, 2 and 3. \n";
      }
	}while ((ans != 1) && (ans != 2) && (ans != 3));
    
    cout << "\n";

    if (ans == 1){
      merge(A, B);
      A.print();
      A.print_sequence();
    }else if (ans == 2){
      concat(A, B);
      A.print();
      A.print_sequence();
    }else{
      ans=0;
      do{
	cout << "\nPlease enter starting position in A for changing: ";
	cin.clear();
	cin.sync();
	cin >> ans;
	if (ans < 0){
	  cout << "It must be >= 0. Try again. \n";
	}
      }while (ans < 0);
      
      cout << "\n";
      RB *C;
      C = change(A, B, ans);
      C->print();
      C->print_sequence();
    }
    
    return 1;
}
