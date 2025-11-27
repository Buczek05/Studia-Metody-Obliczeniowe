# Zajęcia nr 5 - Dekompozycja LU i rozwiązywanie układów równań

## Zawartość

### Pliki z rozwiązaniami zadań teoretycznych:
- **zadania.md** - Rozwiązania zadań 1-3 oraz dodatkowego ćwiczenia (teoria)

### Programy w C++:
- **lu_decomposition.cpp** - Program główny implementujący:
  - Obliczanie norm wektorów i macierzy
  - Dekompozycję LU z częściowym wyborem elementu podstawowego
  - Rozwiązywanie układów równań liniowych
  - Weryfikację rozwiązania

- **zadania_test.cpp** - Weryfikacja rozwiązań zadań teoretycznych 1 i 2:
  - Obliczanie wszystkich norm dla wektora i macierzy z zadania 1
  - Obliczanie wskaźników uwarunkowania dla macierzy A i B z zadania 2
  - Porównanie uwarunkowania dla różnych wartości epsilon

- **zadanie3.cpp** - Szczegółowa demonstracja zadania 3:
  - Krok po kroku dekompozycja LU dla macierzy z zadania 3
  - Wyświetlanie wszystkich kroków eliminacji
  - Wizualizacja permutacji wierszy
  - Szczegółowe rozwiązanie układu równań

- **epsilon_test.cpp** - Dodatkowe ćwiczenie (bonus +5.0):
  - Analiza stabilności numerycznej dla różnych wartości epsilon
  - Porównanie rozwiązań numerycznych z analitycznym
  - Obliczanie wskaźnika uwarunkowania
  - Wizualizacja wpływu epsilon na dokładność

### Pliki pomocnicze:
- **Makefile** - Automatyczna kompilacja i uruchamianie
- **README.md** - Ten plik

## Kompilacja i uruchomienie

### Wymagania:
- Kompilator C++ wspierający standard C++11 lub nowszy (g++, clang++)
- make (opcjonalnie)

### Kompilacja wszystkich programów:
```bash
make
```

### Uruchomienie programu głównego:
```bash
make run
# lub bezpośrednio:
./lu_decomposition
```

### Uruchomienie weryfikacji zadań 1-2:
```bash
make run_zadania
# lub bezpośrednio:
./zadania_test
```

### Uruchomienie szczegółowej demonstracji zadania 3:
```bash
make run_zadanie3
# lub bezpośrednio:
./zadanie3
```

### Uruchomienie dodatkowego ćwiczenia:
```bash
make run_bonus
# lub bezpośrednio:
./epsilon_test
```

### Uruchomienie wszystkich testów:
```bash
make test
```

### Kompilacja ręczna (bez Makefile):
```bash
# Program główny
g++ -std=c++11 -O2 -o lu_decomposition lu_decomposition.cpp

# Weryfikacja zadań 1-2
g++ -std=c++11 -O2 -o zadania_test zadania_test.cpp

# Szczegółowa demonstracja zadania 3
g++ -std=c++11 -O2 -o zadanie3 zadanie3.cpp

# Dodatkowe ćwiczenie
g++ -std=c++11 -O2 -o epsilon_test epsilon_test.cpp
```

### Czyszczenie:
```bash
make clean
```

## Opis implementacji

### Program główny (lu_decomposition.cpp)

Program implementuje dekompozycję LU zgodnie z wymaganiami wykładu:

#### Procedura 1: `luDecomposition(A, perm)`
- Operuje **wyłącznie na macierzy A**
- Implementuje eliminację Gaussa z częściowym wyborem elementu podstawowego
- Zwraca:
  - Zmodyfikowaną macierz A zawierającą L (poniżej diagonali) i U (na i powyżej diagonali)
  - Wektor permutacji `perm`

#### Procedura 2: `solveLU(A, b, perm)`
- Operuje **wyłącznie na wektorze b**
- Wykorzystuje wyniki z procedury 1
- Rozwiązuje układ w dwóch krokach:
  1. Ly = Pb (podstawienie w przód)
  2. Ux = y (podstawienie wstecz)

#### Funkcje pomocnicze:
- `vectorNorm1`, `vectorNorm2`, `vectorNormInf` - normy wektora
- `matrixNorm1`, `matrixNormInf`, `matrixNormFrobenius` - normy macierzy
- `extractL`, `extractU` - wyodrębnianie macierzy L i U
- `multiplyMatrixVector` - weryfikacja rozwiązania

### Dodatkowe ćwiczenie (epsilon_test.cpp)

Program analizuje wpływ parametru epsilon na stabilność numeryczną:

- Tworzy macierz A i wektor b dla różnych wartości epsilon
- Rozwiązanie analityczne: **x = [1, 2, 2, 1]^T** (niezależne od epsilon!)
- Oblicza wskaźnik uwarunkowania cond(A)
- Porównuje rozwiązania numeryczne z dokładnym
- Wyświetla tabelę z wynikami dla epsilon = 10^-3, ..., 10^-10

## Wyniki programu głównego

Program rozwiązuje układ równań:

```
A = [ 5   4   3   2   1 ]
    [ 10  8   7   6   5 ]
    [ -1  2  -3   4  -5 ]
    [ 6   5  -4   3  -2 ]
    [ 1   2   3   4   5 ]

b = [37, 99, -9, 12, 53]^T
```

Wyświetla:
1. Normy macierzy A i wektora b
2. Macierze L i U po dekompozycji
3. Wektor permutacji
4. Rozwiązanie x
5. Weryfikację (A*x porównane z b)
6. Błąd numeryczny ||b - Ax||

## Wyniki dodatkowego ćwiczenia

Program pokazuje:
1. Tabelę z wartościami epsilon, wskaźnika uwarunkowania, rozwiązania i błędu
2. Szczegółową analizę dla epsilon = 10^-6
3. Wnioski dotyczące stabilności numerycznej

### Kluczowe obserwacje:
- Dla małych epsilon wskaźnik uwarunkowania rośnie ~ 1/epsilon²
- Macierz staje się źle uwarunkowana
- Błędy numeryczne rosną mimo prostego rozwiązania analitycznego
- Ilustruje znaczenie monitorowania wskaźnika uwarunkowania

## Zadania do samodzielnej pracy

1. Przetestuj program dla własnych macierzy
2. Zaimplementuj obliczanie wyznacznika z dekompozycji LU
3. Porównaj czas wykonania z biblioteką standardową (np. Eigen)
4. Rozszerz o dekompozycję bez wyboru elementu podstawowego i porównaj stabilność
5. Zaimplementuj inne metody iteracyjne (Jacobi, Gauss-Seidel)

## Dodatkowe informacje

### Złożoność obliczeniowa:
- Dekompozycja LU: O(n³)
- Rozwiązanie Ly=b i Ux=y: O(n²)
- Całkowita: O(n³)

### Stabilność numeryczna:
- Częściowy wybór elementu podstawowego zapewnia dobrą stabilność
- Bez wyboru: algorytm może być niestabilny dla pewnych macierzy
- Pełny wybór (nie zaimplementowany): najlepsze, ale droższe O(n³) porównań

### Zastosowania:
- Rozwiązywanie układów równań liniowych
- Obliczanie wyznacznika: det(A) = det(P) * ∏U_ii
- Odwracanie macierzy
- Obliczanie macierzy odwrotnej
- Podstawa dla innych algorytmów (np. rozwiązywania równań różniczkowych)

## Literatura

1. G.H. Golub, C.F. Van Loan, "Matrix Computations"
2. W. Press et al., "Numerical Recipes"
3. A. Björck, "Numerical Methods for Least Squares Problems"
4. Materiały z wykładu: Metody Obliczeniowe

## Kontakt

W razie pytań lub problemów z kompilacją/uruchomieniem programów, skontaktuj się z prowadzącym zajęcia.
