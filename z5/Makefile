# Makefile dla zajęć nr 5

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Pliki wykonywalne
TARGETS = lu_decomposition epsilon_test zadania_test zadanie3

all: $(TARGETS)

lu_decomposition: lu_decomposition.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

epsilon_test: epsilon_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

zadania_test: zadania_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

zadanie3: zadanie3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Uruchomienie programu głównego
run: lu_decomposition
	./lu_decomposition

# Uruchomienie dodatkowego ćwiczenia
run_bonus: epsilon_test
	./epsilon_test

# Uruchomienie weryfikacji zadań teoretycznych
run_zadania: zadania_test
	./zadania_test

# Uruchomienie szczegółowej demonstracji zadania 3
run_zadanie3: zadanie3
	./zadanie3

# Czyszczenie
clean:
	rm -f $(TARGETS) *.o

# Pełna kompilacja i uruchomienie
test: all
	@echo "=== Weryfikacja zadań teoretycznych (1-2) ==="
	@./zadania_test
	@echo ""
	@echo "=== Uruchamianie programu głównego ==="
	@./lu_decomposition
	@echo ""
	@echo "=== Uruchamianie dodatkowego ćwiczenia ==="
	@./epsilon_test

.PHONY: all run run_bonus run_zadania run_zadanie3 clean test
