# Zajęcia 9: Metody różnicowe dla równań różniczkowych zwyczajnych drugiego rzędu

## Opis zadania

Program rozwiązuje równanie różniczkowe zwyczajne drugiego rzędu z warunkami brzegowymi:

$$U''(x) + 2U'(x) - 4U(x) + x^{3/2} = 0$$

na przedziale $[0, 1]$ z warunkami brzegowymi:
- $U(0) = 2$
- $U(1) = -2$

## Metody numeryczne

Program implementuje dwie metody rozwiązywania:

### 1. Metoda konwencjonalna (finite difference method)
- Wykorzystuje **centralne różnice skończone** do aproksymacji pochodnych
- Przekształca równanie różniczkowe w układ równań algebraicznych
- Rozwiązuje układ za pomocą **algorytmu Thomasa** (TDMA - TriDiagonal Matrix Algorithm)
- Teoretyczny rząd dokładności: **O(h²)**

**Aproksymacje:**
```
U'(x_i) ≈ (U_{i+1} - U_{i-1}) / (2h)
U''(x_i) ≈ (U_{i-1} - 2U_i + U_{i+1}) / h²
```

### 2. Metoda strzałów (shooting method)
- Przekształca problem brzegowy na problem początkowy
- Używa **metody Runge-Kutta 4. rzędu** (RK4) do całkowania
- Dobiera parametr początkowy za pomocą **metody bisekcji**
- Teoretyczny rząd dokładności: **O(h⁴)**

## Struktura plików

```
z9/
├── zadania.md          # Zadania teoretyczne (z LaTeX)
├── main.cpp            # Program główny (C++)
├── plot_results.py     # Skrypt do wizualizacji (Python)
├── Makefile           # Automatyzacja kompilacji
└── README.md          # Ten plik
```

## Wymagania

- **Kompilator C++** z obsługą C++11 lub nowszego (g++, clang++)
- **Python 3** z bibliotekami:
  - numpy
  - matplotlib
  - pandas

Instalacja bibliotek Python:
```bash
pip install numpy matplotlib pandas
```

## Kompilacja i uruchomienie

### Opcja 1: Użycie Makefile (zalecane)

```bash
# Kompilacja
make

# Kompilacja i uruchomienie
make run

# Generowanie wykresów
make plot

# Wszystko naraz (kompilacja + uruchomienie + wykresy)
make full

# Czyszczenie plików
make clean

# Pomoc
make help
```

### Opcja 2: Manualna kompilacja

```bash
# Kompilacja
g++ -std=c++11 -Wall -Wextra -O2 main.cpp -o main

# Uruchomienie
./main

# Wizualizacja
python3 plot_results.py
```

## Pliki wyjściowe

Program generuje następujące pliki:

1. **results.csv** - szczegółowe wyniki dla n=100 podprzedziałów
   - Kolumny: x, U_conventional, U_shooting, U_analytical, Error_conv, Error_shoot

2. **convergence.csv** - analiza zbieżności dla różnych wartości h
   - Kolumny: n, h, log10_h, Error_conv, log10_Error_conv, Error_shoot, log10_Error_shoot

3. **solutions_comparison.png** - porównanie rozwiązań numerycznych z analitycznym

4. **convergence_analysis.png** - analiza zbieżności (wykresy log-log)

5. **convergence_combined.png** - połączone porównanie zbieżności obu metod

## Algorytm Thomasa (TDMA)

Algorytm Thomasa to wydajny algorytm rozwiązywania układów równań z macierzą **trójdiagonalną**:

```
[b₁ c₁  0  ...  0 ] [x₁]   [d₁]
[a₂ b₂ c₂  ...  0 ] [x₂]   [d₂]
[0  a₃ b₃  ...  0 ] [x₃] = [d₃]
[... ... ... ... cₙ][...] [...]
[0  ...  0  aₙ bₙ] [xₙ]   [dₙ]
```

**Złożoność obliczeniowa:** O(n) - znacznie szybszy niż eliminacja Gaussa O(n³)

### Algorytm:

1. **Forward elimination:**
   ```
   c'ᵢ = cᵢ / (bᵢ - aᵢ·c'ᵢ₋₁)
   d'ᵢ = (dᵢ - aᵢ·d'ᵢ₋₁) / (bᵢ - aᵢ·c'ᵢ₋₁)
   ```

2. **Back substitution:**
   ```
   xₙ = d'ₙ
   xᵢ = d'ᵢ - c'ᵢ·xᵢ₊₁
   ```

## Analiza wyników

### Rząd dokładności

Program empirycznie wyznacza rząd dokładności na podstawie zależności:

$$\text{błąd} \propto h^p$$

gdzie p to rząd dokładności. Na wykresie log-log:

$$\log(\text{błąd}) = p \cdot \log(h) + C$$

Nachylenie prostej na wykresie log₁₀(błąd) vs log₁₀(h) daje empiryczny rząd p.

### Oczekiwane wyniki:

- **Metoda konwencjonalna:** rząd ≈ 2
- **Metoda strzałów (RK4):** rząd ≈ 4

### Błędy maszynowe

Dla bardzo małych wartości h (np. h < 10⁻⁴), wpływ błędów zaokrągleń maszynowych staje się dominujący i obserwujemy:
- Odchylenie od teoretycznego rzędu zbieżności
- Nasycenie błędu (error saturation)
- W niektórych przypadkach nawet wzrost błędu

## Rozwiązanie analityczne

Program porównuje wyniki numeryczne z dokładnym rozwiązaniem analitycznym:

```cpp
U(x) = -((9 - 95 exp((-1 - √5)(-1 + x)) + 55 exp((-1 + √5)x) +
         95 exp(1 + √5 + (-1 + √5)x) - 55 exp(2√5 - (1 + √5)x) +
         2x(6 + x(3 + 2x)) - exp(2√5)(9 + 2x(6 + x(3 + 2x)))) ·
         (-1 + coth(√5))) / 64
```

## Przykładowe wyjście programu

```
=== Metody różnicowe dla równań różniczkowych drugiego rzędu ===
Równanie: U''(x) + 2U'(x) - 4U(x) + x^(3/2) = 0
Warunki brzegowe: U(0) = 2, U(1) = -2
Przedział: [0, 1]

1. Rozwiązanie dla n = 100 podprzedziałów

Rozwiązywanie metodą konwencjonalną...
Maksymalny błąd bezwzględny (metoda konwencjonalna): 1.23456e-05

Rozwiązywanie metodą strzałów...
Maksymalny błąd bezwzględny (metoda strzałów): 3.45678e-09

=== Porównanie rozwiązań w wybranych punktach ===
       x         U_conv        U_shoot   U_analytical       Err_conv      Err_shoot
----------------------------------------------------------------------------------------------
  0.0000  2.00000000e+00  2.00000000e+00  2.00000000e+00  0.00000e+00  0.00000e+00
  0.1000  1.75432100e+00  1.75432098e+00  1.75432098e+00  2.34000e-08  1.23000e-11
  ...
```

## Interpretacja wykresów

### 1. solutions_comparison.png
Pokazuje cztery wykresy:
- Porównanie wszystkich trzech rozwiązań
- Błędy bezwzględne (skala logarytmiczna)
- Rozwiązanie analityczne (pojedynczo)
- Różnica między metodami numerycznymi

### 2. convergence_analysis.png
Dwa wykresy log-log pokazujące:
- Zbieżność metody konwencjonalnej z linią dopasowania
- Zbieżność metody strzałów z linią dopasowania
- Linie odniesienia dla różnych rzędów dokładności

**Jak interpretować:**
- Im bardziej nachylona linia, tym wyższy rząd dokładności
- Nachylenie ≈ 2 → metoda drugiego rzędu
- Nachylenie ≈ 4 → metoda czwartego rzędu
- Odchylenie od linii prostej → wpływ błędów maszynowych

### 3. convergence_combined.png
Porównanie obu metod na jednym wykresie dla bezpośredniej oceny.

## Zadania dodatkowe

1. **Modyfikacja równania:** Zmień równanie różniczkowe i odpowiednio zaktualizuj rozwiązanie analityczne.

2. **Schemat Numerowa:** Zaimplementuj schemat Numerowa (4. rzędu) dla metody konwencjonalnej.

3. **Inne warunki brzegowe:** Przetestuj różne wartości U(0) i U(1).

4. **Metoda Newtona:** Zastąp bisekcję metodą Newtona-Raphsona w metodzie strzałów.

5. **Równania nieliniowe:** Rozszerz program na przypadki nieliniowe.

## Autorzy i licencja

Materiały dydaktyczne do zajęć z Metod Obliczeniowych.

## Referencje

1. **Numerow, B. V.** (1924). "Note on the numerical integration of d²x/dt² = f(x,t)". *Astronomische Nachrichten*.

2. **Press, W. H., et al.** (2007). *Numerical Recipes: The Art of Scientific Computing* (3rd ed.). Cambridge University Press.

3. **Burden, R. L., & Faires, J. D.** (2010). *Numerical Analysis* (9th ed.). Brooks/Cole.

## Pytania i problemy

Jeśli program nie działa poprawnie:

1. Sprawdź czy masz zainstalowane wszystkie wymagane narzędzia
2. Upewnij się, że masz uprawnienia do zapisu w katalogu
3. Sprawdź czy pliki CSV zostały wygenerowane przed uruchomieniem skryptu Python

**Typowe problemy:**
- **Błąd kompilacji:** Sprawdź wersję kompilatora (wymagany C++11+)
- **Brak wykresów:** Sprawdź czy zainstalowane są biblioteki Python
- **Puste pliki CSV:** Program C++ nie został poprawnie wykonany
