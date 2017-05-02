CXX = g++
CXXFLAGS = -std=c++11 -ggdb

# main target:
stl : main.cpp 
	$(CXX) $(CXXFLAGS) $^  -o $@
# not dependent rule
.PHONY : clean # for case with exists 'clean' file
clean :
	rm *.o stl
