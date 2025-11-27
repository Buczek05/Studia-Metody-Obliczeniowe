# Makefile dla zajęć 13 - Kwadratury i interpolacja

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lm

# Pliki wykonywalne
TARGETS = erf_quadratures examples

# Domyślny cel
all: $(TARGETS)

# Kompilacja programu erf_quadratures
erf_quadratures: erf_quadratures.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

# Kompilacja programu examples
examples: examples.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

# Uruchomienie programu erf_quadratures
run: erf_quadratures
	./erf_quadratures

# Uruchomienie programu examples
run-examples: examples
	./examples

# Generowanie wykresów (wymaga gnuplot)
plot: run
	@if command -v gnuplot >/dev/null 2>&1; then \
		gnuplot plot_errors.gp; \
		echo "Wykres zapisany jako error_analysis.png"; \
	else \
		echo "BŁĄD: gnuplot nie jest zainstalowany."; \
		echo "Zainstaluj gnuplot: brew install gnuplot (macOS) lub apt install gnuplot (Linux)"; \
	fi

# Czyszczenie plików
clean:
	rm -f $(TARGETS)
	rm -f *.txt
	rm -f *.png
	rm -f *.gp
	rm -f fit.log

# Pełne czyszczenie (z plikami tymczasowymi)
distclean: clean
	rm -f *~
	rm -f .*.swp

# Pomoc
help:
	@echo "Dostępne cele:"
	@echo "  make              - kompiluje wszystkie programy"
	@echo "  make run          - kompiluje i uruchamia program erf_quadratures"
	@echo "  make run-examples - kompiluje i uruchamia program examples"
	@echo "  make plot         - kompiluje, uruchamia erf_quadratures i generuje wykres"
	@echo "  make clean        - usuwa pliki wykonywalne i dane"
	@echo "  make help         - wyświetla tę pomoc"

.PHONY: all run run-examples plot clean distclean help
