#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
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

class stud_set {
private:
	char name;
	multiset<stud_item> values;
	vector<multiset<stud_item>::iterator> sequence;
	
public:
	stud_set () : name('?') { }
	stud_set (char name) : name(name) { }
	stud_set (char name, int n, int mod) : stud_set(name) {
		gen(n, mod);
	}

	void gen(int n, int mod) {
		values.clear();
		sequence.clear();
		for (int i = 0; i < n; ++i) {
			sequence.push_back(values.insert(stud_item(rand()%(1+mod), sequence.size())));
		}
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
	
	friend int stud_and(stud_set& A, stud_set& B, stud_set& C);
	friend int stud_diff(stud_set& A, stud_set& B, stud_set& C);
	friend int stud_union(stud_set& A, stud_set& B, stud_set& C);
	friend int stud_xor(stud_set& A, stud_set& B, stud_set& C);
	friend int stud_concat(stud_set& A, stud_set& B, stud_set& C);
	friend int stud_merge(stud_set& A, stud_set& B, stud_set& C);
	friend int stud_change(stud_set& A, stud_set& B, stud_set& C, int p);
};
