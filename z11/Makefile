# Makefile dla programów z zajęć nr 11

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Pliki źródłowe
SOURCES = diffusion_solver.cpp reaction_diffusion.cpp

# Pliki wykonywalne
EXECUTABLES = diffusion_solver reaction_diffusion

.PHONY: all clean run run1 run2 help

# Kompilacja wszystkich programów
all: $(EXECUTABLES)

# Kompilacja poszczególnych programów
diffusion_solver: diffusion_solver.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

reaction_diffusion: reaction_diffusion.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Uruchomienie obu programów
run: all
	@echo "=========================================="
	@echo "Uruchamianie: diffusion_solver"
	@echo "=========================================="
	./diffusion_solver
	@echo ""
	@echo "=========================================="
	@echo "Uruchamianie: reaction_diffusion"
	@echo "=========================================="
	./reaction_diffusion

# Uruchomienie pierwszego programu (równanie dyfuzji)
run1: diffusion_solver
	./diffusion_solver

# Uruchomienie drugiego programu (reakcja-dyfuzja)
run2: reaction_diffusion
	./reaction_diffusion

# Czyszczenie plików wykonywalnych
clean:
	rm -f $(EXECUTABLES)

# Pomoc
help:
	@echo "Dostępne komendy:"
	@echo "  make          - kompiluje wszystkie programy"
	@echo "  make all      - kompiluje wszystkie programy"
	@echo "  make run      - kompiluje i uruchamia wszystkie programy"
	@echo "  make run1     - kompiluje i uruchamia diffusion_solver"
	@echo "  make run2     - kompiluje i uruchamia reaction_diffusion"
	@echo "  make clean    - usuwa pliki wykonywalne"
	@echo "  make help     - wyświetla tę pomoc"
