#include <iostream>
#include "rb.h"

int main(int argc, char *argv[])
{
  RB tree1('A');

  for(int i = 0; i < 5; i++) {
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

  concat(tree1, tree2);

  tree1.print();
  tree1.print_sequence();
  
  return 1;
}
