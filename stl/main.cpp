#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <time.h>

using namespace std;

class stud_item {
public:
	int key;
	mutable int number;

	stud_item() { key = 0; number = 0; }
	stud_item(int key, int number) : key(key), number(number) { }
	stud_item(const stud_item& other) { key = other.key; number = other.number; }
	stud_item& operator=(const stud_item& other) {
		key = other.key;
		number = other.number;
		return *this;
	}
	~stud_item() { }
	friend ostream& operator<<(ostream& os, const stud_item& item);
	friend bool operator<(const stud_item& item1, const stud_item& item2);
};

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

class stud_set {
private:
	char name;
	multiset<stud_item> values;
	vector<multiset<stud_item>::iterator> sequence;

	void gen(int n, int mod) {
		for (int i = 0; i < n; ++i) {
			sequence.push_back(values.insert(stud_item(rand()%(1+mod), sequence.size())));
		}
	}
	
public:
	stud_set (char name) : name(name) { }
	stud_set (char name, int n, int mod) : stud_set(name) {
		gen(n, mod);
	}

	void setOut() {
		cout << "values " << name << " = { ";
		for (auto it = values.cbegin(); it != values.cend(); ++it)
			cout << *it << ' ';
		cout << '}' << endl;
	}

	void seqOut() {
		cout << "sequence " << name << " = { ";
		for (auto it = sequence.cbegin(); it != sequence.cend(); ++it)
			cout << *(*it) << ' ';
		cout << '}' << endl;
	}

	friend void stud_and(stud_set& A, stud_set& B, stud_set& C);
	friend void stud_diff(stud_set& A, stud_set& B, stud_set& C);
	friend void stud_union(stud_set& A, stud_set& B, stud_set& C);
	friend void stud_xor(stud_set& A, stud_set& B, stud_set& C);
	friend void stud_concat(stud_set& A, stud_set& B, stud_set& C);
	friend void stud_merge(stud_set& A, stud_set& B, stud_set& C);
	friend void stud_change(stud_set& A, stud_set& B, stud_set& C, int p);
};

void stud_and(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_intersection(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}
}

void stud_diff(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_difference(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}
}

void stud_union(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_union(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}
}

void stud_xor(stud_set& A, stud_set& B, stud_set& C)
{
	C.values.clear();
	C.sequence.clear();
	
	set_symmetric_difference(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	
	for (auto it = C.values.begin(); it != C.values.end(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}
}

void stud_concat(stud_set& A, stud_set& B, stud_set& C)
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
}

void stud_merge(stud_set& A, stud_set& B, stud_set& C)
{
	stud_concat(A, B, C);
	
	C.sequence.clear();

	for(auto it = C.values.cbegin(); it != C.values.cend(); ++it) {
		(*it).number = C.sequence.size();
		C.sequence.push_back(it);
	}
}

void stud_change(stud_set& A, stud_set& B, stud_set& C, int p)
{
	std::vector<stud_item> vec1,vec2,result_tmp,result;
	vector<stud_item>::iterator x1, x2;
	
	C.values.clear();
	C.sequence.clear();
	
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

}

int main(int argc, char** argv)
{
	srand(time(NULL));
	
	stud_set A('A', 5, 6);
	stud_set B('B', 2, 6);
	stud_set C('C');

	A.setOut();
	A.seqOut();
	B.setOut();
	B.seqOut();

	cout << "\nA & B" << endl;
	stud_and(A, B, C);
	C.setOut();
	C.seqOut();

	cout << "\nA / B" << endl;
	stud_diff(A, B, C);
	C.setOut();
	C.seqOut();

	cout << "\nB / A" << endl;
	stud_diff(B, A, C);
	C.setOut();
	C.seqOut();

	cout << "\nA + B" << endl;
	stud_union(A, B, C);
	C.setOut();
	C.seqOut();

	cout << "\nA xor B" << endl;
	stud_xor(A, B, C);
	C.setOut();
	C.seqOut();

	cout << "\nconcat(A, B)" << endl;
	stud_concat(A, B, C);
	C.setOut();
	C.seqOut();

	cout << "\nmerge(A, B)" << endl;
	stud_merge(A, B, C);
	C.setOut();
	C.seqOut();

	cout << "\nchange(A, B, 1)" << endl;
	stud_change(A, B, C, 1);
	C.setOut();
	C.seqOut();
	
	return 0;
}
