#include <iostream>
#include "rb.h"

int main(int argc, char *argv[])
{
  RB tree1('A');

  for(int i = 6; i > 1; i--) {
        tree1.insert(i);
  }

  tree1.print();
  tree1.print_sequence();

  RB tree2('B');

  for(int i = 0; i < 7; i++) {
        tree2.insert(i);
  }

  tree2.print();
  tree2.print_sequence();

  RB *tree3;
  
  change(&tree3, tree2, tree1, 2);

  tree3->print();
  tree3->print_sequence();
  
  return 1;
}
