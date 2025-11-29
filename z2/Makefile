# Makefile dla programu analizy błędów numerycznych
# Kompilator
CXX = g++

# Flagi kompilacji
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Flagi linkera (potrzebne dla funkcji matematycznych)
LDFLAGS = -lm

# Cele
TARGETS = main

# Domyślny cel
all: $(TARGETS)

# Kompilacja głównego programu
main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(LDFLAGS)


# Uruchomienie testów
test-run: test
	@echo "=== Uruchamianie testów jednostkowych ==="
	./test

# Uruchomienie pełnej analizy
run: all
	@echo "=== Uruchamianie analizy ==="
	./main
	@echo ""
	@echo "=== Generowanie wykresów ==="
	@if command -v gnuplot > /dev/null; then \
		gnuplot plot.gnu; \
		echo "Wykresy wygenerowane pomyślnie!"; \
	else \
		echo "UWAGA: gnuplot nie jest zainstalowany."; \
		echo "Zainstaluj gnuplot aby wygenerować wykresy: brew install gnuplot (macOS)"; \
	fi



# Pomoc
help:
	@echo "Dostępne cele:"
	@echo "  make           - kompiluje programy"
	@echo "  make run       - kompiluje i uruchamia pełną analizę z wykresami"
	@echo "  make help      - wyświetla tę pomoc"

.PHONY: all run test-run clean clean-results help
