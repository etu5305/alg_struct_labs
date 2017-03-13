CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=main.cpp hashtable_methods.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hashtables

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
