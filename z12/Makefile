# Makefile dla projektu interpolacji - Zjawisko Rungego

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Cele
TARGET_RUNGE = runge
TARGET_ALGOS = algos

# Źródła
SOURCE_RUNGE = runge_phenomenon.cpp
SOURCE_ALGOS = interpolation_algorithms.cpp

.PHONY: all clean run plot help run-algos full

all: $(TARGET_RUNGE) $(TARGET_ALGOS)

$(TARGET_RUNGE): $(SOURCE_RUNGE)
	$(CXX) $(CXXFLAGS) -o $(TARGET_RUNGE) $(SOURCE_RUNGE)
	@echo "Kompilacja zakończona: ./$(TARGET_RUNGE)"

$(TARGET_ALGOS): $(SOURCE_ALGOS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_ALGOS) $(SOURCE_ALGOS)
	@echo "Kompilacja zakończona: ./$(TARGET_ALGOS)"

run-algos: $(TARGET_ALGOS)
	./$(TARGET_ALGOS)

run: $(TARGET_RUNGE)
	./$(TARGET_RUNGE)

plot: runge_results.csv
	python3 plot_runge.py

full: all run plot

clean:
	rm -f $(TARGET_RUNGE) $(TARGET_ALGOS) *.csv *.png
	@echo "Pliki usunięte"

help:
	@echo "Dostępne komendy:"
	@echo "  make          - kompilacja obu programów"
	@echo "  make run-algos - kompilacja i uruchomienie algorytmów (zadania 1-3)"
	@echo "  make run      - kompilacja i uruchomienie zjawiska Rungego"
	@echo "  make plot     - wizualizacja wyników (wymaga Pythona)"
	@echo "  make full     - kompilacja, uruchomienie Rungego i wizualizacja"
	@echo "  make clean    - usunięcie plików"
	@echo "  make help     - ta pomoc"
