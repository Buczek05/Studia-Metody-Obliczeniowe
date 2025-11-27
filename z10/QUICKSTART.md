# Quick Start Guide

Szybki start z projektem ODE Solver - w 3 krokach!

## Krok 1: Kompilacja i uruchomienie

```bash
cd z10
make run
```

To polecenie:
- Skompiluje program C++ (`ode_solver.cpp`)
- Uruchomi go automatycznie
- Wygeneruje 7 plików CSV z wynikami

## Krok 2: Wizualizacja wyników

### Opcja A: Python (zalecane)

```bash
# Jeśli nie masz zainstalowanych bibliotek:
pip3 install numpy matplotlib pandas

# Generowanie wykresów:
python3 visualize.py
```

Otrzymasz:
- 5 wykresów PNG
- Szczegółową analizę rzędu zbieżności
- Raport podsumowujący

### Opcja B: gnuplot (alternatywa)

```bash
gnuplot plot_gnuplot.gp
```

## Krok 3: Analiza wyników

Otwórz wygenerowane wykresy:

```bash
# macOS
open wykres_*.png

# Linux
xdg-open wykres_*.png

# Windows
start wykres_*.png
```

---

## Szybkie testy

### Test automatyczny

```bash
./test.sh
```

Sprawdzi:
- Czy masz zainstalowane wymagane narzędzia
- Czy program kompiluje się poprawnie
- Czy generuje wszystkie wymagane pliki
- Czy wizualizacja działa

### Test ręczny - pojedyncze kroki

```bash
# 1. Kompilacja
g++ -std=c++17 -O2 ode_solver.cpp -o ode_solver

# 2. Uruchomienie
./ode_solver

# 3. Sprawdzenie plików
ls *.csv

# 4. Wizualizacja
python3 visualize.py
```

---

## Co dalej?

### Przeczytaj dokumentację

- `README.md` - pełna dokumentacja projektu
- `zadania.md` - szczegółowe zadania z teorią
- `pytania_i_cwiczenia.md` - pytania kontrolne i ćwiczenia dodatkowe

### Eksperymentuj

Modyfikuj parametry w programie `ode_solver.cpp`:

```cpp
// Zmień przedział czasu
double t_end = 1.0;  // Domyślnie: 0.5

// Zmień kroki czasowe
double dt_stable = 0.001;  // Domyślnie: 0.005
double dt_unstable = 0.1;  // Domyślnie: 0.05
```

Przekompiluj i uruchom ponownie:
```bash
make run
python3 visualize.py
```

### Rozwiązuj dodatkowe równania

W pliku `zadania.md` znajdziesz więcej równań do rozwiązania:

- Równania z Zadania 2
- Równanie logistyczne
- Oscylator van der Pola
- Układ drapieżnik-ofiara

---

## Rozwiązywanie problemów

### Problem: "g++ not found"

```bash
# macOS
xcode-select --install

# Ubuntu/Debian
sudo apt-get install build-essential

# Fedora
sudo dnf install gcc-c++
```

### Problem: "python3 not found"

```bash
# macOS
brew install python3

# Ubuntu/Debian
sudo apt-get install python3 python3-pip

# Fedora
sudo dnf install python3 python3-pip
```

### Problem: "ModuleNotFoundError: No module named 'numpy'"

```bash
pip3 install numpy matplotlib pandas
```

lub:

```bash
pip3 install -r requirements.txt
```

### Problem: Błędy kompilacji

Upewnij się, że masz kompilator obsługujący C++17:

```bash
g++ --version
```

Minimalna wersja: GCC 7+ lub Clang 5+

---

## Jednolinijkowe uruchomienie

### Pełna analiza w jednej komendzie

```bash
make clean && make visualize
```

To:
1. Wyczyści stare pliki
2. Skompiluje program
3. Uruchomi program
4. Wygeneruje wykresy
5. Wyświetli analizę

---

## Pomoc

### Makefile - wszystkie komendy

```bash
make help
```

### Pomoc programu

```bash
./ode_solver --help  # (jeśli zaimplementowano)
```

### Więcej informacji

Zobacz `README.md` dla szczegółowej dokumentacji.

---

**Czas na pierwszy test: ~ 2 minuty**

**Powodzenia!** 🚀
