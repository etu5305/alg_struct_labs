#include "hashtable.h"

Hashtable::Hashtable (char name){
  set_name = name;
  power = 0;
}

void Hashtable::diff (Hashtable &table){
  std::list<int>::iterator it;
  for (int i = 0; i < power; i++){
    for (it = hashtable[i].begin(); it != hashtable[i].end(); it++){
      hashtable[i].remove(*it);
    }
  }
}

void Hashtable::product (Hashtable &table){
  std::list<int>::iterator it, found;
  for (int i = 0; i < power; i++){
    for (it = hashtable[i].begin(); it != hashtable[i].end(); it++){
      found = std::find(table.hashtable[i].begin(), table.hashtable[i].end(), *it);
      if (found == table.hashtable[i].end()){
	hashtable[i].remove(*it);
      }
    }
  }
}

void Hashtable::xor_sets (Hashtable &table){

}

void Hashtable::sum (Hashtable &table){

  for (int i = 0; i < power; i++){
    if (hashtable[i].empty() && table.hashtable[i].empty())
      continue;
    hashtable[i].merge(table.hashtable[i]);
    hashtable[i].sort();
    hashtable[i].unique();
  }

  
}

void Hashtable::print_hashtable (Hashtable &table){

}
