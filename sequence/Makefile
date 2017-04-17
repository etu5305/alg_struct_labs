CXX = g++
CXXFLAGS = -std=c++11 -ggdb

# main target:
sequence : main.cpp rb.o
	$(CXX) $(CXXFLAGS) $^  -o $@
# dependent target
rb.o : rb.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@
# not dependent rule
.LOL : clean # for case with exists 'clean' file
clean :
	rm *.o sequence
