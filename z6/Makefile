# Makefile dla zajęć nr 6 - Metody Obliczeniowe

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGETS = thomas example_solver least_squares

# Kompilacja wszystkich programów
all: $(TARGETS)

# Algorytm Thomasa - podstawowa wersja
thomas: thomas_algorithm.cpp
	$(CXX) $(CXXFLAGS) -o thomas thomas_algorithm.cpp

# Przykład z użyciem klasy ThomasSolver
example_solver: example_solver.cpp thomas_solver.h
	$(CXX) $(CXXFLAGS) -o example_solver example_solver.cpp

# Program z metodą najmniejszych kwadratów
least_squares: least_squares.cpp
	$(CXX) $(CXXFLAGS) -o least_squares least_squares.cpp

# Uruchomienie wszystkich programów
run: all
	@echo "=== Algorytm Thomasa ==="
	./thomas
	@echo ""
	@echo "=== Przykład z klasą ThomasSolver ==="
	./example_solver
	@echo ""
	@echo "=== Metoda najmniejszych kwadratów ==="
	./least_squares

# Uruchomienie tylko algorytmu Thomasa
run-thomas: thomas
	./thomas

# Uruchomienie tylko przykładu z klasą
run-example: example_solver
	./example_solver

# Uruchomienie tylko metody najmniejszych kwadratów
run-ls: least_squares
	./least_squares

# Czyszczenie plików wykonywalnych
clean:
	rm -f $(TARGETS)

# Informacje o dostępnych celach
help:
	@echo "Dostępne cele:"
	@echo "  make all          - Kompiluje wszystkie programy"
	@echo "  make thomas       - Kompiluje algorytm Thomasa"
	@echo "  make example_solver - Kompiluje przykład z klasą"
	@echo "  make least_squares - Kompiluje metodę najmniejszych kwadratów"
	@echo "  make run          - Kompiluje i uruchamia wszystkie programy"
	@echo "  make run-thomas   - Uruchamia algorytm Thomasa"
	@echo "  make run-example  - Uruchamia przykład z klasą"
	@echo "  make run-ls       - Uruchamia metodę najmniejszych kwadratów"
	@echo "  make clean        - Usuwa pliki wykonywalne"
	@echo "  make help         - Wyświetla tę pomoc"

.PHONY: all run run-thomas run-example run-ls clean help
