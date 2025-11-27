# Zajęcia nr 12 - Interpolacja Wielomianowa

## 📋 Spis treści

- [Opis projektu](#opis-projektu)
- [Zagadnienia teoretyczne](#zagadnienia-teoretyczne)
- [Struktura projektu](#struktura-projektu)
- [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
- [Zadania](#zadania)
- [Program - Zjawisko Rungego](#program---zjawisko-rungego)
- [Wyniki](#wyniki)

## Opis projektu

Projekt implementuje różne metody interpolacji wielomianowej funkcji jednej zmiennej, ze szczególnym uwzględnieniem zjawiska Rungego. Zawiera rozwiązania zadań teoretycznych oraz program demonstracyjny w C++.

## Zagadnienia teoretyczne

### Metody interpolacji

1. **Interpolacja Lagrange'a**
   - Baza potęgowa
   - Baza Lagrange'a (wielomiany bazowe)
   - Baza Newtona (ilorazy różnicowe)

2. **Algorytmy**
   - Algorytm Hornera (efektywne obliczanie wartości wielomianu)
   - Algorytm Neville'a (rekurencyjne obliczanie wartości)

3. **Zjawisko Rungego**
   - Oscylacje wielomianu interpolacyjnego na krańcach przedziału
   - Porównanie węzłów równoodległych vs węzłów Czebyszewa

4. **Interpolacja Hermite'a**
   - Warunki na wartości funkcji i jej pochodnych
   - Uogólnione ilorazy różnicowe

## Struktura projektu

```
z12/
├── README.md                          # Ten plik
├── zadania_rozwiazania.md            # Rozwiązania zadań teoretycznych (1-3)
├── Makefile                          # Automatyzacja kompilacji
│
├── interpolation_algorithms.cpp     # Implementacje algorytmów (Zadania 1-3)
├── runge_phenomenon.cpp             # Program główny - zjawisko Rungego
│
├── plot_runge.py                    # Skrypt do wizualizacji (Python)
│
└── Pliki wyjściowe (generowane):
    ├── runge_results.csv            # Dane do wykresu
    ├── runge_nodes.csv              # Współrzędne węzłów
    └── runge_phenomenon.png         # Wykres zjawiska Rungego
```

## Kompilacja i uruchomienie

### Wymagania

- Kompilator C++ z obsługą C++11 (g++, clang++)
- Python 3 z bibliotekami: matplotlib, pandas, numpy (opcjonalnie, do wizualizacji)
- Make (opcjonalnie)

### Instalacja zależności Python (opcjonalnie)

```bash
pip install matplotlib pandas numpy
```

### Kompilacja

#### Użycie Makefile (zalecane)

```bash
# Kompilacja wszystkich programów
make

# Kompilacja i uruchomienie algorytmów (zadania 1-3)
make algos

# Kompilacja i uruchomienie zjawiska Rungego
make run

# Kompilacja, uruchomienie i wizualizacja
make full

# Tylko wizualizacja (po uruchomieniu programu)
make plot

# Pomoc
make help
```

#### Kompilacja ręczna

```bash
# Algorytmy interpolacji (zadania 1-3)
g++ -std=c++11 -Wall -O2 -o algos interpolation_algorithms.cpp

# Zjawisko Rungego
g++ -std=c++11 -Wall -O2 -o runge runge_phenomenon.cpp
```

### Uruchomienie

```bash
# Zadania 1-3
./algos

# Zjawisko Rungego
./runge
# Podaj wartość parametru 'a' (np. 25)
# Podaj liczbę węzłów (np. 11)

# Wizualizacja wyników
python3 plot_runge.py
```

## Zadania

### Zadanie 1: Wielomian interpolacyjny Lagrange'a

**Treść:** Wyznacz wielomian interpolacyjny Lagrange'a przechodzący przez punkty:
- $(4, 2)$
- $(-6, -8)$
- $(-5, 4)$
- $(1, 10)$

Stosując:
- (a) bazę Lagrange'a
- (b) bazę Newtona

**Rozwiązanie:** Zobacz plik `zadania_rozwiazania.md`

**Program:** `interpolation_algorithms.cpp` (funkcja `example_zadanie_1()`)

### Zadanie 2: Algorytm Neville'a

**Treść:** Stosując algorytm Neville'a, oblicz wartość wielomianu interpolacyjnego Lagrange'a przechodzącego przez punkty:
- $(-1, -1)$
- $(2, 2)$
- $(-3, 3)$

dla wartości zmiennej niezależnej $x = 1$.

**Rozwiązanie:** $P(1) = -0.2$

**Program:** `interpolation_algorithms.cpp` (funkcja `example_zadanie_2()`)

### Zadanie 3: Interpolacja Hermite'a

**Treść:** Posługując się bazą Newtona, wyznacz wielomian interpolacyjny Hermite'a $p(x)$ spełniający warunki:
- $p(0) = 0, \quad p'(0) = 1, \quad p''(0) = 2$
- $p(1) = 3, \quad p'(1) = 4$

**Rozwiązanie:** $p(x) = x + x^2 + 3x^3 - 2x^4$

**Program:** `interpolation_algorithms.cpp` (funkcja `example_zadanie_3()`)

## Program - Zjawisko Rungego

### Opis

Program demonstruje zjawisko Rungego na przykładzie interpolacji funkcji:

$$f(x) = \frac{x}{1 + ax^4}$$

na przedziale $[-1, 1]$.

### Funkcjonalności

1. **Generowanie węzłów interpolacji**
   - Węzły równoodległe
   - Węzły Czebyszewa

2. **Interpolacja w bazie Newtona**
   - Obliczanie ilorazów różnicowych
   - Schemat Hornera dla efektywnego obliczania wartości

3. **Analiza błędów**
   - Maksymalny błąd
   - Średni błąd
   - Błąd RMS

4. **Zapis wyników**
   - Plik CSV z wartościami funkcji i interpolacji
   - Plik CSV ze współrzędnymi węzłów

5. **Wizualizacja (skrypt Python)**
   - Wykresy funkcji i wielomianów interpolacyjnych
   - Wykresy błędów (skala logarytmiczna)
   - Zbliżenia na krańce przedziału

### Parametry

- **Parametr `a`:** Kontroluje "intensywność" zjawiska Rungego
  - `a = 25` - wyraźne zjawisko Rungego
  - `a = 1` - słabsze zjawisko
  - Im większe `a`, tym silniejsze oscylacje

- **Liczba węzłów `n`:** Stopień wielomianu = `n - 1`
  - `n = 7` - mało węzłów
  - `n = 11` - średnia liczba węzłów (zalecane)
  - `n = 21` - dużo węzłów (silniejsze oscylacje!)

### Przykładowe uruchomienie

```bash
$ ./runge
=== Demonstracja zjawiska Rungego ===
Funkcja: f(x) = x / (1 + a*x^4)
Przedział: [-1, 1]

Podaj wartość parametru 'a' (np. 25 dla wyraźnego efektu Rungego): 25
Podaj liczbę węzłów interpolacji (np. 11): 11

--- Rozpoczęcie obliczeń ---

Generowanie węzłów interpolacji...
Obliczanie wartości funkcji w węzłach...
...
```

### Interpretacja wyników

**Zjawisko Rungego:**
- Dla **węzłów równoodległych**: wielomian interpolacyjny oscyluje silnie na krańcach przedziału $[-1, 1]$, szczególnie dla dużej liczby węzłów
- Dla **węzłów Czebyszewa**: oscylacje są znacznie mniejsze, interpolacja jest stabilna

**Wnioski:**
- Zwiększanie liczby węzłów równoodległych **pogarsza** jakość interpolacji!
- Węzły Czebyszewa dają lepszą zbieżność
- Zjawisko Rungego to fundamentalne ograniczenie interpolacji wielomianowej

## Wyniki

### Przykładowe wartości dla `a = 25`, `n = 11`

| Metoda | Maksymalny błąd | Średni błąd |
|--------|-----------------|-------------|
| Węzły równoodległe | ~10² - 10⁴ | ~10⁰ - 10² |
| Węzły Czebyszewa | ~10⁻² - 10⁰ | ~10⁻³ - 10⁻¹ |

*Poprawa: 100x - 1000x*

### Wizualizacja

Po uruchomieniu `python3 plot_runge.py` zostanie wygenerowany plik `runge_phenomenon.png` zawierający:

1. **Wykres główny:** Funkcja oryginalna i wielomiany interpolacyjne
2. **Wykres błędów:** Skala logarytmiczna
3. **Zbliżenie (równoodległe):** Widoczne oscylacje na krańcach
4. **Zbliżenie (Czebyszew):** Stabilna interpolacja

## Dodatkowe informacje

### Algorytm Hornera

Efektywna metoda obliczania wartości wielomianu:
- Złożoność: $O(n)$ mnożeń (zamiast $O(n^2)$)
- Stabilność numeryczna

### Węzły Czebyszewa

Węzły Czebyszewa pierwszego rodzaju:

$$x_i = \cos\left(\frac{2i+1}{2n}\pi\right), \quad i = 0, 1, \ldots, n-1$$

na przedziale $[-1, 1]$.

**Własności:**
- Gęstsze na krańcach przedziału
- Minimalizują błąd interpolacji
- Optymalne dla wielomianów ortogonalnych

### Ilorazy różnicowe

Rekurencyjna formuła:

$$f[x_i, x_{i+1}, \ldots, x_{i+k}] = \frac{f[x_{i+1}, \ldots, x_{i+k}] - f[x_i, \ldots, x_{i+k-1}]}{x_{i+k} - x_i}$$

**Zalety:**
- Łatwe dodawanie nowych punktów
- Stabilność numeryczna
- Naturalna dla bazy Newtona

## Literatura

1. **Kincaid, Cheney** - "Analiza numeryczna"
2. **Björck, Dahlquist** - "Metody numeryczne"
3. **Press et al.** - "Numerical Recipes"

## Autor

Materiały do zajęć nr 12 - Metody Obliczeniowe

---

**Uwaga:** W przypadku problemów z kompilacją lub uruchomieniem, sprawdź:
- Wersję kompilatora: `g++ --version` (wymagane C++11)
- Instalację bibliotek Python: `pip list | grep -E "matplotlib|pandas|numpy"`
