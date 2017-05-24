CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=main.cpp stud_set.cpp
BUILD_DIR=buildir
EXECUTABLE=$(BUILD_DIR)/main
OBJECTS=$(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
