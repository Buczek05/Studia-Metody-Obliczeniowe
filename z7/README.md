# Zajęcia 7 - Metody iteracyjne rozwiązywania układów równań liniowych

## Opis

Ten katalog zawiera materiały do zajęć nr 7 z metod obliczeniowych, dotyczących metod iteracyjnych rozwiązywania układów równań liniowych.

## Zawartość

- **zadania.md** - Zadania teoretyczne i praktyczne z pełnymi poleceniami
- **iteracyjne.cpp** - Program w C++ implementujący metody iteracyjne
- **Makefile** - Plik do kompilacji programu

## Zaimplementowane metody

Program implementuje trzy metody iteracyjne:

1. **Metoda Jacobiego** - najprostsza metoda iteracyjna, wykorzystuje tylko wartości z poprzedniej iteracji
2. **Metoda Gaussa-Seidela** - wykorzystuje już obliczone nowe wartości w tej samej iteracji
3. **Metoda SOR** (Successive Over-Relaxation) - uogólnienie metody Gaussa-Seidela z parametrem relaksacji ω

## Kompilacja i uruchomienie

### Kompilacja z użyciem Makefile:

```bash
make
```

### Kompilacja ręczna:

```bash
g++ -std=c++11 -Wall -Wextra -O2 -o iteracyjne iteracyjne.cpp
```

### Uruchomienie:

```bash
./iteracyjne
```

lub

```bash
make run
```

### Czyszczenie:

```bash
make clean
```

## Funkcjonalności programu

### 1. Sprawdzanie dominacji diagonalnej
Program automatycznie sprawdza, czy macierz ma dominację diagonalną, co jest warunkiem wystarczającym zbieżności metod iteracyjnych.

### 2. Trzy kryteria stopu
- **Maksymalna liczba iteracji** - zapobiega nieskończonym pętlom
- **Kryterium błędu względnego**: ||x^(k+1) - x^(k)|| < ε
- **Kryterium residuum**: ||b - Ax^(k)|| < ε

### 3. Wyniki pośrednie
Dla każdej iteracji program wyświetla:
- Numer iteracji
- Estymator błędu: ||x^(k+1) - x^(k)||
- Residuum: ||b - Ax^(k)||

### 4. Weryfikacja rozwiązania
Po zakończeniu iteracji program:
- Weryfikuje rozwiązanie obliczając Ax i porównując z b
- Wyświetla końcowy estymator błędu i residuum
- Informuje o liczbie iteracji potrzebnej do zbieżności

## Przykładowe dane

Program rozwiązuje układ 5×5:

```
A = [50   5   4   3   2 ]       b = [140]
    [ 1  40   1   2   3 ]           [ 67]
    [ 4   5  30  -5  -4 ]           [ 62]
    [-3  -2  -1  20   0 ]           [ 89]
    [ 1   2   3   4  30 ]           [153]
```

z przybliżeniem początkowym: x₀ = [6, 6, 6, 6, 6]ᵀ

## Parametry programu

Parametry można zmienić w funkcji `main()`:

- `tolerance` - dokładność obliczeń (domyślnie: 1e-6)
- `maxIterations` - maksymalna liczba iteracji (domyślnie: 1000)
- `omega` - parametr relaksacji dla metody SOR (domyślnie: 0.5)

## Modyfikacja programu

### Zmiana danych wejściowych

Aby rozwiązać inny układ równań, zmodyfikuj w funkcji `main()`:

```cpp
Matrix A = {
    {a11, a12, ...},
    {a21, a22, ...},
    ...
};

Vector b = {b1, b2, ...};
Vector x0 = {x0_1, x0_2, ...};
```

### Zmiana poziomu szczegółowości

Parametr `verbose` w funkcji `solveIterative()` kontroluje ilość wyświetlanych informacji:
- `true` - wszystkie wyniki pośrednie
- `false` - tylko wyniki końcowe

## Obserwacje

Program pozwala zaobserwować:

1. **Szybkość zbieżności** - która metoda najszybciej osiąga zadaną dokładność
2. **Zmianę estymatora błędu** - jak szybko maleje różnica między kolejnymi przybliżeniami
3. **Zmianę residuum** - jak dokładnie kolejne przybliżenia spełniają równanie Ax = b
4. **Wpływ dominacji diagonalnej** - czy macierz spełnia warunek zbieżności

## Teoria

### Metoda Jacobiego

Wzór iteracyjny:
```
x_i^(k+1) = (1/a_ii) * [b_i - Σ(j≠i) a_ij * x_j^(k)]
```

### Metoda Gaussa-Seidela

Wzór iteracyjny:
```
x_i^(k+1) = (1/a_ii) * [b_i - Σ(j<i) a_ij * x_j^(k+1) - Σ(j>i) a_ij * x_j^(k)]
```

### Metoda SOR

Wzór iteracyjny:
```
x_i^(k+1) = (1-ω) * x_i^(k) + (ω/a_ii) * [b_i - Σ(j<i) a_ij * x_j^(k+1) - Σ(j>i) a_ij * x_j^(k)]
```

## Wymagania

- Kompilator C++ z obsługą standardu C++11 lub nowszego
- System operacyjny: Linux, macOS, Windows (z MinGW lub WSL)

## Autor

Materiały przygotowane na zajęcia z Metod Obliczeniowych

## Licencja

Materiały edukacyjne - do użytku akademickiego
