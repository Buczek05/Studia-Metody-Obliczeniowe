# Zajęcia nr 3 - Metody rozwiązywania nieliniowych równań algebraicznych

## Opis

Program implementuje cztery klasyczne metody rozwiązywania nieliniowych równań algebraicznych:
- Metoda Picarda (iteracji prostej)
- Metoda bisekcji (połowienia przedziału)
- Metoda Newtona (stycznych)
- Metoda siecznych

## Struktura projektu

```
z3/
├── zadania.md      # Treść zadań i teoria
├── main.cpp        # Program w C++
├── Makefile        # Plik do kompilacji
└── README.md       # Ten plik
```

## Kompilacja

### Użycie Makefile (zalecane):
```bash
make
```

### Ręczna kompilacja:
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o equations main.cpp
```

## Uruchomienie

```bash
./equations
```

lub z użyciem Makefile:
```bash
make run
```

## Funkcjonalności programu

### Zaimplementowane metody

1. **Metoda Picarda** - metoda iteracji prostej, wymaga przekształcenia równania do postaci x = g(x)
2. **Metoda Bisekcji** - metoda połowienia przedziału, wymaga przedziału [a,b] z f(a)·f(b) < 0
3. **Metoda Newtona** - metoda stycznych, wymaga znajomości pochodnej funkcji
4. **Metoda Siecznych** - podobna do Newtona, ale nie wymaga pochodnej

### Kryteria zatrzymania

Program wykorzystuje **trzy niezależne kryteria zatrzymania**:
1. Maksymalna liczba iteracji (domyślnie: 50)
2. Estymator błędu: |x_{n+1} - x_n| < ε (domyślnie: ε = 10^-10)
3. Residuum: |f(x_n)| < δ (domyślnie: δ = 10^-10)

### Testowane równania

**Zadanie 1a:** `sinh(x) + x/4 - 1 = 0`
- Przekształcenie Picarda: `x = asinh(1 - x/4)`

**Zadanie 1b:** `tanh(x) + 2(x - 1) = 0`
- Przekształcenie Picarda: `x = 1 - tanh(x)/2`

### Format wyjścia

Dla każdej metody program wyprowadza:
- Tabelę z wynikami pośrednimi dla każdej iteracji:
  - Numer iteracji
  - Przybliżenie x_n
  - Wartość funkcji f(x_n) (residuum)
  - Estymator błędu |x_n - x_{n-1}|
- Podsumowanie zawierające:
  - Informację o zbieżności
  - Kryterium stopu, które zostało spełnione
  - Liczbę wykonanych iteracji
  - Znalezione rozwiązanie
  - Końcowe residuum i błąd

### Algorytm Herona (bonus)

Program zawiera również implementację algorytmu Herona (do obliczania pierwiastka kwadratowego),
który demonstruje, że jest on szczególnym przypadkiem metody Newtona zastosowanej do równania f(x) = x² - a = 0.

## Porównanie metod

Na końcu program wyświetla porównanie liczby iteracji potrzebnych przez każdą metodę
do osiągnięcia zadanej dokładności dla obu równań.

## Modyfikacja parametrów

Aby zmienić parametry obliczeń, edytuj następującą linię w funkcji `main()`:

```cpp
Parameters params(1e-10, 1e-10, 50);
//                epsilon delta  max_iter
```

Aby zmienić punkt startowy lub przedział dla poszczególnych metod, modyfikuj zmienne:
- `x0_1a`, `x0_1b` - punkty startowe
- Parametry w wywołaniach funkcji `bisection()` i `secant()`

## Sprzątanie

Usunięcie pliku wykonywalnego:
```bash
make clean
```

## Wymagania

- Kompilator C++ z obsługą C++11 lub nowszym
- Standardowa biblioteka matematyczna
