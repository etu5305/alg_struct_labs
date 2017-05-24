#include <iostream>
#include <fstream>
#include <ctime>
#include "stud_set.h"
using namespace std;

__inline__ uint64_t rdtsc() {
  uint32_t a, d;
  asm("rdtsc\n" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	std::ofstream out;
	
	out.open("in.txt");
	
	if (!out.is_open()) return 1;

	int num_of_exper = (rand() % 150) + 100;
	unsigned long t1, t2;
		
	out << num_of_exper << endl;

	stud_set arrayofsets[5];
	for (int tempCount = 0; tempCount < num_of_exper; tempCount++) {
		try {
			int size = 0 , temp , sets = 4;

			for (int i = 0; i < 4; i++) {
				temp = (rand() % 250);
				size += temp;
				arrayofsets[i].gen(temp, rand() % 1000);
			}

			t1 = rdtsc();
			
			size += stud_union(arrayofsets[0], arrayofsets[1], arrayofsets[2]); ++sets;
			size += stud_merge(arrayofsets[2], arrayofsets[1], arrayofsets[3]); ++sets;
			size += stud_concat(arrayofsets[2], arrayofsets[3], arrayofsets[0]); ++sets;
			size += stud_concat(arrayofsets[0], arrayofsets[1], arrayofsets[2]); ++sets;
			size += stud_change(arrayofsets[4], arrayofsets[2], arrayofsets[3], 15); ++sets; 
			size += stud_xor(arrayofsets[1], arrayofsets[3], arrayofsets[1]); ++sets;
			size += stud_diff(arrayofsets[4], arrayofsets[0], arrayofsets[2]); ++sets;
			size += stud_and(arrayofsets[4], arrayofsets[2], arrayofsets[3]); ++sets;

			t2 = rdtsc();
			size /= sets;
			out << size << ' ' << (t2 - t1) << std::endl;
		}
		catch (...) {
			std::cout << "Unknown error occur during one of the experiments, continue." << std::endl;
		}
	}

	out.close();
		
	return 0;
}
