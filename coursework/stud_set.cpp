#include "stud_set.h"
bool operator<(const stud_item& item1, const stud_item& item2)
{
	return (item1.key < item2.key);
}

bool operator<=(const stud_item& item1, const stud_item& item2)
{
	return (item1.key <= item2.key);
}

ostream& operator<<(ostream& os, const stud_item& item)
{
	os << item.key << "(" << item.number << ")" << "";
	return os;
}
int stud_and(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_intersection(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}

	return C.values.size();
}

int stud_diff(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_difference(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}

	return C.values.size();
}

int stud_union(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_union(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}
	
	return C.values.size();
}

int stud_xor(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_symmetric_difference(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}

	return C.values.size();
}

int stud_concat(stud_set& A, stud_set& B, stud_set& C)
{
	std::vector<stud_item> vec1, vec2, result;
	vector<stud_item>::iterator x1, x2;
	
	C.values.clear();
	C.sequence.clear();

	// Формируем упорядоченный по возрастанию ключей массив из элементов множества A
	for (auto it = A.values.begin(); it != A.values.end(); it++) {
		vec1.push_back(*it);
	}
	
	int p = vec1.size();
	
	// Формируем упорядоченный по возрастанию ключей массив из элементов множества B
	for (auto it = B.values.begin(); it != B.values.end(); it++) {
		vec2.push_back(stud_item((*it).key, (*it).number + p));
	}

	x1 = vec1.begin();
  x2 = vec2.begin();
	// Конкатенация элементов последовательности vec1 и последовательности vec2
  while (x1 != vec1.end() || x2 != vec2.end()) {
    if (x1 != vec1.end() && x2 != vec2.end()) {
      if (*x1 <= *x2) {
				result.push_back(*x1);
				++x1;
      } else {
				result.push_back(*x2);
				++x2;
      }
    } else if(x1 != vec1.end()) { // случай когда второй вектор закончился
      result.push_back(*x1);
      ++x1;
    } else { // случай когда первый вектор закончился
      result.push_back(*x2);
      ++x2;
    }
  }

	C.values.insert(result.begin(), result.end());
	C.sequence.resize(C.values.size());

	for (auto it = C.values.begin(); it != C.values.end(); it++) {
		C.sequence[(*it).number] = it;
	}

	return C.values.size();
}

int stud_merge(stud_set& A, stud_set& B, stud_set& C)
{
	stud_concat(A, B, C);
	
	C.sequence.clear();

	for(auto it = C.values.cbegin(); it != C.values.cend(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}

	return C.values.size();
}

int stud_change(stud_set& A, stud_set& B, stud_set& C, int p)
{
	std::vector<stud_item> vec1,vec2,result_tmp,result;
	vector<stud_item>::iterator x1, x2;
	
	C.values.clear();
	C.sequence.clear();

	p = (A.values.size() < p) ? A.values.size() : p;
	
	// Формируем упорядоченный по возрастанию ключей массив из элементов множества A
	for (auto it = A.values.begin(); it != A.values.end(); it++) {
		vec1.push_back(*it);
	}
	// Формируем упорядоченный по возрастанию ключей массив из элементов множества B
	for (auto it = B.values.begin(); it != B.values.end(); it++) {
		vec2.push_back(stud_item((*it).key, (*it).number + p));
	}

  x1 = vec1.begin();
	// Создаём вектор элементов последовательности от 0 до p-1
  while (x1 != vec1.end()){
    if ((*x1).number < p){
			result_tmp.push_back(*x1);
    }
    ++x1;
  }

	x1 = result_tmp.begin();
  x2 = vec2.begin();
    // Конкатенация первых p элементов последовательности vec1 и всей последовательности vec2
  while (x1 != result_tmp.end() || x2 != vec2.end()) {
    if (x1 != result_tmp.end() && x2 != vec2.end()) {
      if (*x1 <= *x2) {
				result.push_back(*x1);
				++x1;
      } else {
				result.push_back(*x2);
				++x2;
      }
    } else if(x1 != result_tmp.end()) { // случай когда второй вектор закончился
      result.push_back(*x1);
      ++x1;
    } else { // случай когда первый вектор закончился
      result.push_back(*x2);
      ++x2;
    }
  }

	if (vec1.size() > vec2.size() + p) {
		vec2.clear();
		result_tmp.clear();
		
		x1 = vec1.begin();
    // Создаём вектор элементов последовательности vec1 от p+vec2.size() до конца
    while (x1 != vec1.end()) {
      if ((*x1).number >= result.size()) {
				vec2.push_back(*x1);
      }
      ++x1;
		}

		x1 = result.begin();
		x2 = vec2.begin();
		// Конкатенация первых p элементов последовательности vec1 и всей последовательности vec2
		while (x1 != result.end() || x2 != vec2.end()) {
			if (x1 != result.end() && x2 != vec2.end()) {
				if (*x1 <= *x2) {
					result_tmp.push_back(*x1);
					++x1;
				} else {
					result_tmp.push_back(*x2);
					++x2;
				}
			} else if(x1 != result.end()) { // случай когда второй вектор закончился
				result_tmp.push_back(*x1);
				++x1;
			} else { // случай когда первый вектор закончился
				result_tmp.push_back(*x2);
				++x2;
			}
		}

		C.values.insert(result_tmp.begin(), result_tmp.end());
		C.sequence.resize(C.values.size());

		for (auto it = C.values.begin(); it != C.values.end(); it++) {
			C.sequence[(*it).number] = it;
		}
	
	} else {
		C.values.insert(result.begin(), result.end());
		C.sequence.resize(C.values.size());

		for (auto it = C.values.begin(); it != C.values.end(); it++) {
			C.sequence[(*it).number] = it;
		}
	}

	return C.values.size();
}
