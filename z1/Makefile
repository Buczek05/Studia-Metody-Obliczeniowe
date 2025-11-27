# Makefile dla projektu Metody Obliczeniowe - Zajęcia nr 1
# Program do wyznaczania epsylona maszynowego

# Kompilator i flagi
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS =

# Katalogi
SRC_DIR = src
BIN_DIR = bin

# Pliki
TARGET = $(BIN_DIR)/machine_epsilon
SOURCES = $(SRC_DIR)/machine_epsilon.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Kolor w terminalu (opcjonalnie)
GREEN = \033[0;32m
NC = \033[0m # No Color

# Domyślny cel
.PHONY: all
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(SOURCES) | $(BIN_DIR)
	@echo "$(GREEN)Kompilacja programu...$(NC)"
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)
	@echo "$(GREEN)Kompilacja zakończona pomyślnie!$(NC)"
	@echo "Aby uruchomić program, wpisz: ./$(TARGET)"

# Tworzenie katalogu bin jeśli nie istnieje
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Uruchomienie programu
.PHONY: run
run: $(TARGET)
	@echo "$(GREEN)Uruchamianie programu...$(NC)"
	@echo ""
	./$(TARGET)

# Czyszczenie plików tymczasowych i skompilowanych
.PHONY: clean
clean:
	@echo "Czyszczenie plików..."
	rm -rf $(BIN_DIR)/*.o $(TARGET)
	@echo "Wyczyszczono!"

# Pełne czyszczenie (włącznie z katalogiem bin)
.PHONY: distclean
distclean: clean
	rm -rf $(BIN_DIR)
	@echo "Pełne czyszczenie zakończone!"

# Ponowna kompilacja (clean + build)
.PHONY: rebuild
rebuild: clean all

# Informacje o projekcie
.PHONY: info
info:
	@echo "════════════════════════════════════════════════════════"
	@echo "  Projekt: Metody Obliczeniowe - Zajęcia nr 1"
	@echo "  Program: Epsylon maszynowy"
	@echo "════════════════════════════════════════════════════════"
	@echo "Dostępne komendy:"
	@echo "  make         - kompilacja programu"
	@echo "  make run     - kompilacja i uruchomienie"
	@echo "  make clean   - usunięcie plików skompilowanych"
	@echo "  make rebuild - ponowna kompilacja"
	@echo "  make info    - wyświetlenie tego komunikatu"
	@echo ""
	@echo "Kompilator: $(CXX)"
	@echo "Flagi: $(CXXFLAGS)"
	@echo "Plik źródłowy: $(SOURCES)"
	@echo "Plik docelowy: $(TARGET)"
	@echo "════════════════════════════════════════════════════════"

# Pomoc
.PHONY: help
help: info
