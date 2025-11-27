# Zajęcia nr 11 - Metody rozwiązywania równań różniczkowych cząstkowych

## Opis

Ten projekt zawiera implementacje numerycznych metod rozwiązywania równań różniczkowych cząstkowych (PDE) w przestrzeni jednowymiarowej, ze szczególnym uwzględnieniem równań dyfuzji i reakcji-dyfuzji.

## Zawartość

### Pliki zadań
- **`zadania.md`** - Szczegółowe zadania w formacie Markdown z LaTeX

### Programy C++

#### 1. `diffusion_solver.cpp`
Program rozwiązujący równanie dyfuzji:
$$\frac{\partial u}{\partial t} = D \frac{\partial^2 u}{\partial x^2}$$

**Zaimplementowane metody:**
- Metoda klasyczna bezpośrednia (explicit)
- Metoda Laasonen (fully implicit)
- Metoda Cranka-Nicolson

**Funkcjonalności:**
- Analiza stabilności numerycznej każdej metody
- Obliczanie parametru stabilności λ
- Weryfikacja warunków stabilności
- Porównanie wyników wszystkich metod
- Szczegółowe wyniki krok po kroku

#### 2. `reaction_diffusion.cpp`
Program demonstrujący uogólnienie metod dla równania reakcji-dyfuzji:
$$\frac{\partial U}{\partial t} = D \frac{\partial^2 U}{\partial x^2} - r U$$

**Zaimplementowane metody:**
- Metoda Laasonen z członem reakcyjnym
- Metoda Cranka-Nicolson z członem reakcyjnym

**Funkcjonalności:**
- Wyprowadzenie układów równań algebraicznych
- Wizualizacja struktur macierzy trójdiagonalnych
- Wyświetlanie elementów macierzy i wektorów prawej strony
- Analiza wpływu członu reakcyjnego na stabilność
- Szczegółowe objaśnienia matematyczne

### Dodatkowe pliki
- **`Makefile`** - Automatyzacja kompilacji i uruchamiania programów
- **`README.md`** - Ten plik (dokumentacja projektu)

## Wymagania

- Kompilator C++ obsługujący standard C++11 lub nowszy (g++, clang++)
- Make (opcjonalnie, do użycia Makefile)

## Kompilacja

### Używając Makefile (zalecane)

```bash
# Kompilacja wszystkich programów
make

# Lub kompilacja konkretnego programu
make diffusion_solver
make reaction_diffusion
```

### Ręczna kompilacja

```bash
# Program 1: Równanie dyfuzji
g++ -std=c++11 -Wall -O2 -o diffusion_solver diffusion_solver.cpp

# Program 2: Równanie reakcji-dyfuzji
g++ -std=c++11 -Wall -O2 -o reaction_diffusion reaction_diffusion.cpp
```

## Uruchamianie

### Używając Makefile

```bash
# Uruchomienie wszystkich programów
make run

# Uruchomienie tylko programu równania dyfuzji
make run1

# Uruchomienie tylko programu reakcji-dyfuzji
make run2
```

### Bezpośrednie uruchamianie

```bash
# Program 1
./diffusion_solver

# Program 2
./reaction_diffusion
```

## Struktura zadań

### Zadanie 1: Równanie dyfuzji

**Problem:**
- Równanie: ∂u/∂t = D·∂²u/∂x²
- Dziedzina: x ∈ [-1, 1]
- Warunek początkowy: u(x,0) = x³
- Warunki brzegowe: u(-1,t) = -1-t, u(1,t) = 1+t
- Parametry: D=1, Δx=1, δt=1

**Metody do porównania:**
1. **Explicit** - Metoda klasyczna bezpośrednia
   - Warunek stabilności: λ ≤ 0.5
   - Najprostsza implementacja
   - Może być niestabilna dla dużych kroków czasowych

2. **Laasonen** - Metoda fully implicit
   - Bezwarunkowo stabilna
   - Wymaga rozwiązania układu równań
   - Dokładność: O(δt, Δx²)

3. **Crank-Nicolson** - Metoda semi-implicit
   - Bezwarunkowo stabilna
   - Najwyższa dokładność: O(δt², Δx²)
   - Zalecana dla większości zastosowań

### Zadanie 2: Równanie reakcji-dyfuzji

**Problem:**
- Równanie: ∂U/∂t = D·∂²U/∂x² - r·U
- Warunki brzegowe Dirichleta: U(0,t) = α(t), U(L,t) = β(t)

**Polecenia:**
1. Wyprowadzenie układu równań dla metody Laasonen
2. Wyprowadzenie układu równań dla metody Cranka-Nicolson
3. Analiza struktur macierzy
4. Wpływ członu reakcyjnego na stabilność

## Wyniki programów

### Program 1 (diffusion_solver)

Program wyświetla:
- Parametry problemu
- Warunki początkowe i brzegowe
- Dla każdej metody:
  - Parametr stabilności λ
  - Ocenę stabilności
  - Wartości rozwiązania w każdym kroku czasowym
  - Rozwiązanie końcowe
- Porównanie wyników wszystkich metod
- Podsumowanie stabilności
- Wnioski i zalecenia

### Program 2 (reaction_diffusion)

Program wyświetla:
- Parametry równania (D, r, λ, μ)
- Schematy numeryczne w postaci matematycznej
- Struktury macierzy trójdiagonalnych:
  - Elementy diagonalne
  - Wektory prawej strony
  - Wpływ warunków brzegowych
- Przykładowy układ równań dla pierwszego kroku
- Iterację w czasie z wartościami w każdym kroku
- Podsumowanie metod i zalecenia

## Analiza stabilności

### Parametr stabilności

Dla równania dyfuzji:
$$\lambda = \frac{D \cdot \delta t}{(\Delta x)^2}$$

### Warunki stabilności

| Metoda | Warunek stabilności | Dokładność |
|--------|---------------------|------------|
| Explicit | λ ≤ 0.5 | O(δt, Δx²) |
| Laasonen | Bezwarunkowo stabilna | O(δt, Δx²) |
| Crank-Nicolson | Bezwarunkowo stabilna | O(δt², Δx²) |

### Wpływ członu reakcyjnego

Dla równania reakcji-dyfuzji z r > 0:
- Człon reakcyjny (-r·U) zwiększa stabilność
- Modyfikuje elementy diagonalne: μ = r·δt
- Dla r > 0: proces zanikania (decay)

## Zalecenia praktyczne

### Wybór metody

1. **Dla małych kroków czasowych (λ ≤ 0.5):**
   - Metoda explicit - najprostsza, najszybsza

2. **Dla dużych kroków czasowych:**
   - Crank-Nicolson - najdokładniejsza
   - Laasonen - prostsze równania

3. **Dla problemów sztywnych:**
   - Metody implicit (Laasonen lub Crank-Nicolson)

### Optymalizacja obliczeń

- Zwiększenie Δx → większe λ → ryzyko niestabilności dla explicit
- Zmniejszenie δt → mniejsze λ → większa stabilność, więcej obliczeń
- Metody implicit: koszt rozwiązania układu vs możliwość większych δt

## Rozszerzenia (opcjonalne)

Możliwe modyfikacje programów:

1. **Różne warunki brzegowe:**
   - Neumann: ∂u/∂x = const
   - Robin: kombinacja Dirichlet i Neumann

2. **Nieliniowości:**
   - Równanie Fishera: ∂u/∂t = D·∂²u/∂x² + r·u(1-u)
   - Równanie Burgersа: ∂u/∂t + u·∂u/∂x = ν·∂²u/∂x²

3. **Zmienne współczynniki:**
   - D = D(x) - niejednorodne medium
   - r = r(x,t) - zmienne w czasie i przestrzeni

4. **Wizualizacja:**
   - Export danych do plików
   - Generowanie wykresów (gnuplot, matplotlib)

## Pytania kontrolne

1. Dlaczego metoda explicit ma ograniczenie na λ?
2. Co oznacza "bezwarunkowa stabilność"?
3. Dlaczego Crank-Nicolson ma wyższą dokładność?
4. Jak człon reakcyjny wpływa na dynamikę rozwiązania?
5. Kiedy warto użyć metod implicit pomimo większej złożoności?

## Dodatkowe materiały

### Teoria

- Von Neumann stability analysis
- Warunek CFL (Courant-Friedrichs-Lewy)
- Algorytm Thomasa dla układów trójdiagonalnych
- Metoda analizy harmonicznej

### Literatura

1. Morton K.W., Mayers D.F. - "Numerical Solution of Partial Differential Equations"
2. Strikwerda J.C. - "Finite Difference Schemes and Partial Differential Equations"
3. LeVeque R.J. - "Finite Difference Methods for Ordinary and Partial Differential Equations"

## Czyszczenie

Aby usunąć skompilowane pliki wykonywalne:

```bash
make clean
```

## Autor

Program przygotowany na potrzeby zajęć z Metod Obliczeniowych - Zajęcia nr 11

## Licencja

Materiały edukacyjne - do swobodnego wykorzystania w celach dydaktycznych.
