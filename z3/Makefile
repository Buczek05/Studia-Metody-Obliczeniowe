# Makefile dla programu rozwiązywania równań nieliniowych

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = equations
SOURCE = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
