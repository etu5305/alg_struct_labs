#include "hashtable.h"

int main (void){
  Hashtable A('A'), B('B');
  //A.generate_set();
  //B.generate_set();
  A.input_set();
  B.input_set();
  A.print_hashtable();
  B.print_hashtable();
  A.xor_sets(B);
  A.print_hashtable();
}
