// функции для осуществления бинарных операций над множествами в виде чёрно-красных деревьев
#include <vector>

void rb_sum (std::vector<int> &result, RB &first, RB &second){
  first.pop_clear();// начинаем просматривать с начала
  second.pop_clear();
  first.pop();
  second.pop(); // получаем первые элементы деревьев
  int key1,key2;
  while (!(first.is_end() && second.is_end())){ // пока не достигнут конец обоих деревьев
    key1 = first.get_current_value();
    key2 = second.get_current_value();
    if (first.is_end()){ // первое дерево закончилось, просто добавляем в результат все элементы из второго
      result.push_back(key2);
      second.pop();
      continue;
    }else if (second.is_end()){ // второе дерево закончилось, просто добавляем в результат все элементы из первого
      result.push_back(key1);
      first.pop();
      continue;
    }
    
    if (key1 < key2){
      result.push_back(key1);
      first.pop();
    }else if(key1 > key2){
      result.push_back(key2);
      second.pop();
    }else{ // key1 == key2
      result.push_back(key1);
      first.pop();
      second.pop();
    }
  }
}

void rb_product (std::vector<int> &result, RB &first, RB &second){
  first.pop_clear();// начинаем просматривать с начала
  second.pop_clear();
  first.pop();
  second.pop(); // получаем первые элементы деревьев
  int key1,key2;
  while (!(first.is_end() || second.is_end())){ // пока не достигнут конец одного из деревьев
    key1 = first.get_current_value();
    key2 = second.get_current_value();
    
    if (key1 < key2){
      first.pop();
    }else if(key1 > key2){
      second.pop();
    }else{ // key1 == key2
      result.push_back(key1);
      first.pop();
      second.pop();
    }
  }
}

void rb_diff (std::vector<int> &result, RB &first, RB &second){
  first.pop_clear();// начинаем просматривать с начала
  second.pop_clear();
  first.pop();
  second.pop(); // получаем первые элементы деревьев
  int key1,key2;
  while (!(first.is_end() && second.is_end())){ // пока не достигнут конец обоих деревьев
    key1 = first.get_current_value();
    key2 = second.get_current_value();
    if (first.is_end()){ // первое дерево закончилось, выходим из цикла
      break;
    }else if (second.is_end()){ // второе дерево закончилось, просто добавляем в результат все элементы из первого
      result.push_back(key1);
      first.pop();
      continue;
    }
    
    if (key1 < key2){
      result.push_back(key1);
      first.pop();
    }else if(key1 > key2){
      second.pop();
    }else{ // key1 == key2
      first.pop();
      second.pop();
    }
  }
}

void rb_xor (){
  ;
}
