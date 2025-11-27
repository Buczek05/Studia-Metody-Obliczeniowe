# Makefile dla programu analizy błędów numerycznych
# Kompilator
CXX = g++

# Flagi kompilacji
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Flagi linkera (potrzebne dla funkcji matematycznych)
LDFLAGS = -lm

# Cele
TARGETS = main generate_exact analyze test

# Domyślny cel
all: $(TARGETS)

# Kompilacja głównego programu
main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(LDFLAGS)

# Kompilacja generatora wartości dokładnych
generate_exact: generate_exact.cpp
	$(CXX) $(CXXFLAGS) -o generate_exact generate_exact.cpp $(LDFLAGS)

# Kompilacja programu analizy statystycznej
analyze: analyze.cpp
	$(CXX) $(CXXFLAGS) -o analyze analyze.cpp $(LDFLAGS)

# Kompilacja testów jednostkowych
test: test.cpp
	$(CXX) $(CXXFLAGS) -o test test.cpp $(LDFLAGS)

# Uruchomienie testów
test-run: test
	@echo "=== Uruchamianie testów jednostkowych ==="
	./test

# Uruchomienie pełnej analizy
run: all
	@echo "=== Generowanie dokładnych wartości ==="
	./generate_exact
	@echo ""
	@echo "=== Uruchamianie analizy ==="
	./main
	@echo ""
	@echo "=== Analiza statystyczna ==="
	./analyze
	@echo ""
	@echo "=== Generowanie wykresów ==="
	@if command -v gnuplot > /dev/null; then \
		gnuplot plot.gnu; \
		echo "Wykresy wygenerowane pomyślnie!"; \
	else \
		echo "UWAGA: gnuplot nie jest zainstalowany."; \
		echo "Zainstaluj gnuplot aby wygenerować wykresy: brew install gnuplot (macOS)"; \
	fi

# Czyszczenie plików
clean:
	rm -f $(TARGETS) *.o *.txt *.png

# Czyszczenie tylko wyników (nie binarek)
clean-results:
	rm -f results_*.txt exact_values.txt *.png

# Pomoc
help:
	@echo "Dostępne cele:"
	@echo "  make           - kompiluje programy"
	@echo "  make run       - kompiluje i uruchamia pełną analizę z wykresami"
	@echo "  make test-run  - kompiluje i uruchamia testy jednostkowe"
	@echo "  make analyze   - kompiluje tylko program analizy statystycznej"
	@echo "  make clean     - usuwa wszystkie wygenerowane pliki"
	@echo "  make clean-results - usuwa tylko pliki wyników"
	@echo "  make help      - wyświetla tę pomoc"

.PHONY: all run test-run clean clean-results help
