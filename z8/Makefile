# Makefile dla programu analizy przybliżeń różnicowych

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = finite_differences
ANALYSIS = analiza
SOURCE = finite_differences.cpp
ANALYSIS_SOURCE = analiza.cpp

.PHONY: all clean run plot help analysis

all: $(TARGET) $(ANALYSIS)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) -lm

$(ANALYSIS): $(ANALYSIS_SOURCE)
	$(CXX) $(CXXFLAGS) -o $(ANALYSIS) $(ANALYSIS_SOURCE) -lm

run: $(TARGET)
	./$(TARGET)

analysis: $(ANALYSIS)
	./$(ANALYSIS)

plot: run
	@if command -v gnuplot >/dev/null 2>&1; then \
		gnuplot plot_convergence.gnu; \
		echo "Wykresy wygenerowane pomyślnie!"; \
	else \
		echo "BŁĄD: gnuplot nie jest zainstalowany."; \
		echo "Zainstaluj gnuplot: brew install gnuplot (macOS) lub apt-get install gnuplot (Linux)"; \
	fi

clean:
	rm -f $(TARGET) $(ANALYSIS) *.dat *.png

help:
	@echo "Dostępne cele:"
	@echo "  make          - kompiluje wszystkie programy"
	@echo "  make run      - uruchamia główny program i generuje dane"
	@echo "  make analysis - uruchamia program szczegółowej analizy"
	@echo "  make plot     - uruchamia program i generuje wykresy"
	@echo "  make clean    - usuwa pliki tymczasowe i wykonywalne"
	@echo "  make help     - wyświetla tę pomoc"
