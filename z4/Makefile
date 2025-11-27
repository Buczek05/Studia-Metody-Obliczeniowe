# Makefile dla programu metody Newtona

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = newton_method
EXPERIMENTS = experiments
SRC = newton_method.cpp
EXP_SRC = experiments.cpp

all: $(TARGET) $(EXPERIMENTS)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(EXPERIMENTS): $(EXP_SRC)
	$(CXX) $(CXXFLAGS) -o $(EXPERIMENTS) $(EXP_SRC)

run: $(TARGET)
	./$(TARGET)

run-experiments: $(EXPERIMENTS)
	./$(EXPERIMENTS)

clean:
	rm -f $(TARGET) $(EXPERIMENTS)

.PHONY: all run run-experiments clean
