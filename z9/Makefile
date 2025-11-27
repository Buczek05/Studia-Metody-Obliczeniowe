# Makefile dla programu rozwiązującego równanie różniczkowe

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = main
DEMO = thomas_demo
SOURCES = main.cpp
DEMO_SOURCES = thomas_demo.cpp

.PHONY: all clean run plot demo help

all: $(TARGET) $(DEMO)

$(TARGET): $(SOURCES)
	@echo "Kompilacja programu głównego..."
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Kompilacja zakończona pomyślnie!"

$(DEMO): $(DEMO_SOURCES)
	@echo "Kompilacja programu demonstracyjnego..."
	$(CXX) $(CXXFLAGS) $(DEMO_SOURCES) -o $(DEMO)
	@echo "Program demonstracyjny skompilowany!"

run: $(TARGET)
	@echo "Uruchamianie programu..."
	./$(TARGET)

demo: $(DEMO)
	@echo "Uruchamianie programu demonstracyjnego..."
	./$(DEMO)

plot: results.csv convergence.csv
	@echo "Generowanie wykresów..."
	python3 plot_results.py

results.csv convergence.csv: $(TARGET)
	@echo "Najpierw uruchom program: make run"
	@./$(TARGET)

full: all run plot

clean:
	@echo "Czyszczenie plików..."
	rm -f $(TARGET) $(DEMO) *.csv *.png *.o
	@echo "Pliki usunięte!"

help:
	@echo "Dostępne komendy:"
	@echo "  make          - kompiluje oba programy"
	@echo "  make run      - kompiluje i uruchamia program główny"
	@echo "  make demo     - kompiluje i uruchamia program demonstracyjny (algorytm Thomasa)"
	@echo "  make plot     - generuje wykresy (wymaga wyników z programu)"
	@echo "  make full     - kompiluje, uruchamia program główny i generuje wykresy"
	@echo "  make clean    - usuwa skompilowane pliki i wyniki"
	@echo "  make help     - wyświetla tę pomoc"
