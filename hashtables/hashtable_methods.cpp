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
  /* std::list<int>::iterator it, found;
  for (int i = 0; i < m; i++){
    for (it = hashtable[i].begin(); it != hashtable[i].end(); it++){
      found = std::find(table.hashtable[i].begin(), table.hashtable[i].end(), *it);
      if (found == table.hashtable[i].end()){
	hashtable[i].remove(*it);
      }
    }
    }*/
  Hashtable copy_table('T');
  copy_table = *this;
  copy_table.diff(table);
  this->diff(copy_table);  
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
  int size=0, element;
  
  cout << "Enter set named " << set_name << "\n";

  do {
    cout << "Enter size of set: ";
    cin.clear();
    cin.sync();
    cin >> size;
    if ((size < 0) || (size > SET_SIZE)){
	cout << "Incorrect size of set. It must be natural number in range [0;" << SET_SIZE << "].\n";
      }
  }while ((size < 0) || (size > SET_SIZE));

    cout << "Now enter the elements of set (one-by-one): ";
    for (int i = 0; i < size; i++){
      cin.clear();
      cin.sync();
      cin >> element;

      add_element (element);
    }
}

Hashtable& Hashtable::operator= (const Hashtable& table) {
	power = table.power;
	for (int i = 0; i < m; ++i)
		hashtable[i] = table.hashtable[i];

	return *this;
}

void Hashtable::print_hashtable (void){
  std::list<int>::iterator it, next;
  cout << "Hashtable for a set " << set_name << "\n";
  cout << "index:key(s)\n";
  for (int i = 0; i < m; i++){
    cout << i << ": ";
    if (hashtable[i].empty())
      cout << "empty";
    
    for (it = hashtable[i].begin(); it != hashtable[i].end(); it++){
      cout << *it;
      next = it;
      next++;
      if (next != hashtable[i].end())
	cout << " -> ";
    }
    cout << "\n";
  }
  cout << "\n";
}

void Hashtable::generate_set (void){
  int t;
  std::vector<int> rand_vector;

  for (int i = 0; i < SET_SIZE; i++){
    t = rand() %100;
    rand_vector.push_back(t);
  }

  std::vector<int>::iterator it;
  std::sort (rand_vector.begin(), rand_vector.end());
  it = std::unique (rand_vector.begin(), rand_vector.end());             
  rand_vector.resize( std::distance(rand_vector.begin(),it));

  for (it = rand_vector.begin(); it != rand_vector.end(); it++){
    add_element (*it);
  }
}
