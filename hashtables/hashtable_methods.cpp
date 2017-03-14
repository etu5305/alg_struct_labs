#include "hashtable.h"

Hashtable::Hashtable (char name){
  set_name = name;
  power = 0;
}

void Hashtable::diff (Hashtable &table){
  std::list<int>::iterator it;
  for (int i = 0; i < m; i++){
    for (it = table.hashtable[i].begin(); it != table.hashtable[i].end(); it++){
      hashtable[i].remove(*it);
    }
  }
}

void Hashtable::product (Hashtable &table){
  std::list<int>::iterator it, found;
  for (int i = 0; i < m; i++){
    for (it = hashtable[i].begin(); it != hashtable[i].end(); it++){
      found = std::find(table.hashtable[i].begin(), table.hashtable[i].end(), *it);
      if (found == table.hashtable[i].end()){
	hashtable[i].remove(*it);
      }
    }
  }
}

void Hashtable::xor_sets (Hashtable &table){
  Hashtable copy_table('T');
  copy_table = table;

  table.diff(*this);
  this->diff(copy_table);
  this->sum(table);
  
}

void Hashtable::sum (Hashtable &table){

  for (int i = 0; i < m; i++){
    if (hashtable[i].empty() && table.hashtable[i].empty())
      continue;
    hashtable[i].merge(table.hashtable[i]);
    hashtable[i].sort();
    hashtable[i].unique();
  }

  
}

void Hashtable::input_set (void){
  ;
}

Hashtable& Hashtable::operator= (const Hashtable& table) {
	power = table.power;
	for (int i = 0; i < m; ++i)
		hashtable[i] = table.hashtable[i];

	return *this;
}

void Hashtable::print_hashtable (Hashtable &table){

}
