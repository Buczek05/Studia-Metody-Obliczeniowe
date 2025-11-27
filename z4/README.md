# Zajęcia nr 4: Rozwiązywanie układów nieliniowych równań algebraicznych

## Opis

Program implementuje **uogólnioną metodę Newtona** do rozwiązywania układu trzech nieliniowych równań algebraicznych:

```
x² + y² + z² = 4
x² + y²/2 = 1
xy = 1/2
```

## Struktura projektu

```
z4/
├── README.md              # Ten plik
├── zadania.md             # Zadania teoretyczne z rozwiązaniami
├── newton_method.cpp      # Program główny - metoda Newtona
├── experiments.cpp        # Program z dodatkowymi eksperymentami
├── Makefile              # Plik do kompilacji
```

## Kompilacja i uruchomienie

### Sposób 1: Użycie Makefile

```bash
# Kompilacja obu programów
make

# Kompilacja i uruchomienie programu głównego
make run

# Kompilacja i uruchomienie eksperymentów
make run-experiments

# Czyszczenie plików binarnych
make clean
```

### Sposób 2: Bezpośrednia kompilacja

```bash
# Kompilacja programu głównego
g++ -std=c++11 -o newton_method newton_method.cpp -Wall

# Kompilacja eksperymentów
g++ -std=c++11 -o experiments experiments.cpp -Wall

# Uruchomienie programu głównego
./newton_method

# Uruchomienie eksperymentów
./experiments
```

## Funkcjonalność programu

Program implementuje:

1. **Uogólnioną metodę Newtona** dla układu 3 równań nieliniowych
2. **Trzy niezależne kryteria stopu:**
   - Norma poprawki: ||Δx|| < ε₁
   - Norma residuum: ||F(x)|| < ε₂
   - Maksymalna liczba iteracji
3. **Szczegółowe wyniki pośrednie** dla każdej iteracji:
   - Numer iteracji
   - Aktualne przybliżenie [x, y, z]
   - Wartości funkcji F(x)
   - Norma residuum ||F(x)||
   - Poprawka Δx
   - Norma poprawki ||Δx||
4. **Weryfikację rozwiązania** - sprawdzenie czy znalezione wartości spełniają układ równań

## Algorytm

Metoda Newtona dla układu równań F(x) = 0 opiera się na schemacie iteracyjnym:

1. Oblicz wartość funkcji F(x⁽ᵏ⁾)
2. Oblicz macierz Jacobiego J(x⁽ᵏ⁾)
3. Rozwiąż układ liniowy: J(x⁽ᵏ⁾) · Δx = -F(x⁽ᵏ⁾)
4. Zaktualizuj rozwiązanie: x⁽ᵏ⁺¹⁾ = x⁽ᵏ⁾ + Δx
5. Sprawdź kryteria stopu

## Przykładowe wyniki

Program testuje trzy różne przybliżenia początkowe:

1. **[1.0, 0.5, 1.7]** → zbieżność do [0.9239, 0.5412, 1.6892]
2. **[0.9, 0.6, 1.5]** → zbieżność do [0.9239, 0.5412, 1.6892]
3. **[-0.9, -0.6, 1.5]** → zbieżność do [-0.9239, -0.5412, 1.6892]

Wszystkie przypadki osiągają zbieżność w około 4-5 iteracjach z dokładnością rzędu 10⁻¹⁶.

## Modyfikacja parametrów

Aby zmienić parametry metody, edytuj funkcję `newtonMethod` w pliku `newton_method.cpp`:

```cpp
Vec3 newtonMethod(Vec3 x0,
                  double tol_delta = 1e-10,      // tolerancja ||Δx||
                  double tol_residual = 1e-10,   // tolerancja ||F(x)||
                  int max_iter = 100,            // max iteracji
                  bool verbose = true)           // szczegółowy output
```

Lub zmień przybliżenie początkowe w funkcji `main()`:

```cpp
Vec3 x0(1.0, 0.5, 1.7);  // [x, y, z]
```

## Cechy implementacji

- **Eliminacja Gaussa z częściowym wyborem elementu głównego** do rozwiązywania układu liniowego
- **Detekcja macierzy osobliwej** - program sprawdza czy macierz Jacobiego jest odwracalna
- **Norma euklidesowa** do obliczania ||Δx|| i ||F(x)||
- **Precyzyjne formatowanie wyników** z użyciem manipulatorów C++
- **Czytelny output** z ramkami i wyrównaniem dla lepszej wizualizacji

## Program eksperymentów (experiments.cpp)

Program `experiments.cpp` zawiera dodatkowe eksperymenty do analizy właściwości metody Newtona:

### Eksperyment 1: Wrażliwość na przybliżenie początkowe
Testuje zbieżność metody dla różnych punktów startowych, pokazując do jakich rozwiązań prowadzą różne przybliżenia początkowe.

### Eksperyment 2: Wpływ tolerancji na wyniki
Analizuje jak różne tolerancje wpływają na dokładność rozwiązania i liczbę iteracji.

### Eksperyment 3: Szczegółowa analiza zbieżności
Pokazuje jak zmienia się norma residuum i norma poprawki w kolejnych iteracjach, demonstrując kwadratową szybkość zbieżności metody Newtona.

### Eksperyment 4: Porównanie różnych norm
Porównuje normę euklidesową (L₂) i normę maksimum (L∞) w kryteriach stopu.

Uruchom eksperymenty komendą:
```bash
make run-experiments
```

## Zadania teoretyczne

Szczegółowe zadania teoretyczne, wyprowadzenia wzorów i teoria znajdują się w pliku `zadania.md`.

## Autor

Program stworzony na potrzeby zajęć z Metod Obliczeniowych.
