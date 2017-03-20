#include "list.h"
List::List (void){
  head = NULL;
  end = NULL;
  it = NULL;
}

void List::push_back (int v){
  ListElement *el = new ListElement (v);

  if (head != NULL && end != NULL){
    end->next = el;
    el->prev = end;
    end = el;
  }else if (head == NULL){
    head = el;
    end = head;
  }
}

void List::remove (ListElement *el){
  if (el == head){
    if (head->next != NULL){
      (head->next)->prev = NULL;
      head = head->next;
    }else{
      head = NULL;
      end = NULL;
    }     
  }else if (el == end){
    if (end->prev != NULL){
      (end->prev)->next = NULL;
    }
    end = end->prev;
  }else{
   (el->prev)->next = el->next;
   (el->next)->prev = (el->prev);
  //delete el;
  }
}

bool List::empty (void){
  if (head == NULL)
    return true;
  else
    return false;
}

ListElement* List::search (int v){
  ListElement *i = head;
  while (i != NULL){
    if (i->value == v)
      return i;
    i = i->next;
  }
  return NULL;
}

ListElement::ListElement (int v){
  value = v;
  next = NULL;
  prev = NULL;
}
