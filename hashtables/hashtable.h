#define SET_SIZE 26
#include <list>
#include <vector>
#include <iostream>
using namespace std;

class Hashtable {
  
 private:
  std::list<int> hashtable[SET_SIZE*2];

  int power;
  char set_name;

  static const int m = SET_SIZE * 2;
  static const int a = m - 1;
  static const int b = 2;

  int hash_function (int key){
    return (a * key + b) % m;
  }

  void add_element (int key){
    power++;
    int hash = hash_function(key);
    hashtable[hash].push_back(key);
  }

 public:
  Hashtable (char name);
  Hashtable& diff (Hashtable &table);
  Hashtable& product (Hashtable &table);
  Hashtable& xor_sets (Hashtable &table);
  Hashtable& sum (Hashtable &table);

  void print_hashtable (Hashtable &table);

  int get_power (void) { return power; }
  int get_setname (void) { return set_name; }
  void set_setname (char name) { set_name = name; }
};
