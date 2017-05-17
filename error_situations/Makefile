CC=g++
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=Screen0.cpp
BUILD_DIR=build
EXECUTABLE=$(BUILD_DIR)/error_situations
OBJECTS=$(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
