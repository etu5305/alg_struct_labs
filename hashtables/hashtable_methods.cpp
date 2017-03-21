#include "hashtable.h"

Hashtable::Hashtable (char name){
  set_name = name;
  power = 0;
}

void Hashtable::diff (Hashtable &table){
  ListElement *it, *found;
  for (int i = 0; i < m; i++){
    it = table.hashtable[i].head;
    while (it != NULL){
      found = hashtable[i].search(it->value);
      if (found != NULL)
	hashtable[i].remove(found);
      it = it->next;
    }
  }
}

void Hashtable::product (Hashtable &table){
  Hashtable copy_table(*this);
  copy_table.diff(table);
  this->diff(copy_table);  
}

void Hashtable::xor_sets (Hashtable &table){
  Hashtable copy_table(table);
  
  table.diff(*this);
  this->diff(copy_table);
  this->sum(table);
  
}

void Hashtable::sum (Hashtable &table){

  for (int i = 0; i < m; i++){
    if (hashtable[i].empty() && table.hashtable[i].empty())
      continue;
    ListElement *it, *found;
    it = table.hashtable[i].head;
    while (it != NULL){
      if ((found = hashtable[i].search(it->value)) == NULL)
	hashtable[i].push_back(it->value);
      it = it->next;
    }
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
  ListElement *it;
  cout << "Hashtable for a set " << set_name << "\n";
  cout << "index:key(s)\n";
  for (int i = 0; i < m; i++){
    cout << "[" << i << ": ";
    if (hashtable[i].empty())
      cout << "empty";
    
    it = hashtable[i].head;
    while (it != NULL){
      cout << it->value;
      it = it->next;
      if (it != NULL)
	cout << " -> ";
    }
    
    cout << "] ";
    if (i != 0 && (i % 10) == 0)
      cout << "\n";
  }
  cout << "\n\n";
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
