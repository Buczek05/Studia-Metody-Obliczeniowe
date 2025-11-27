# Makefile dla projektu ODE Solver
# Zajęcia nr 10 - Metody Obliczeniowe

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = ode_solver
SOURCE = ode_solver.cpp

# Reguły

all: $(TARGET)

$(TARGET): $(SOURCE)
	@echo "Kompilacja programu..."
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)
	@echo "✓ Kompilacja zakończona: $(TARGET)"

run: $(TARGET)
	@echo "Uruchamianie programu..."
	./$(TARGET)
	@echo ""
	@echo "✓ Program zakończony"

visualize: run
	@echo "Generowanie wykresów..."
	python3 visualize.py

clean:
	@echo "Czyszczenie plików..."
	rm -f $(TARGET)
	rm -f *.csv
	rm -f *.png
	@echo "✓ Pliki wyczyszczone"

help:
	@echo "Dostępne komendy:"
	@echo "  make          - kompilacja programu"
	@echo "  make run      - kompilacja i uruchomienie"
	@echo "  make visualize - uruchomienie + wizualizacja wyników"
	@echo "  make clean    - usunięcie plików binarnych i wyników"
	@echo "  make help     - wyświetlenie tej pomocy"

.PHONY: all run visualize clean help
