#include <stdlib.h>
using namespace std;
class ListElement {
 public:
  int value;
  ListElement *next;
  ListElement *prev;
  ListElement(int v);
};

class List{
 public:
  List(void);
  ListElement *head;
  ListElement *end;
  ListElement *it;

  void push_back (int v);
  void remove (ListElement *el);
  bool empty(void);
  ListElement* search (int v);
};


