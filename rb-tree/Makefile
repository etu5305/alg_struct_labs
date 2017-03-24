CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=main.cpp bst.cpp rb.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rb-tree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
