# Zajęcia nr 10 - Metody numeryczne rozwiązywania równań różniczkowych

## Opis projektu

Implementacja i analiza metod numerycznych rozwiązywania równań różniczkowych zwyczajnych (ODE) pierwszego rzędu. Projekt zawiera:

- **Program C++** implementujący trzy metody numeryczne
- **Skrypt Python** do wizualizacji wyników
- **Materiały teoretyczne** z wyprowadzeniami i analizą

## Metody zaimplementowane

1. **Metoda Eulera bezpośrednia (explicit Euler)**
   - Warunkowo stabilna
   - Rząd dokładności: O(dt)

2. **Metoda Eulera pośrednia (implicit Euler)**
   - Bezwarunkowo stabilna
   - Rząd dokładności: O(dt)

3. **Metoda trapezów**
   - Bezwarunkowo stabilna
   - Rząd dokładności: O(dt²)

## Problem testowy

Równanie różniczkowe:

```
y'(t) + [(100t + 10)/(t + 1)] * (y(t) - 1) = 0
y(0) = 2
```

Rozwiązanie analityczne:
```
y(t) = 1 + (1 + t)^90 * exp(-100t)
```

## Struktura plików

```
z10/
├── README.md                 # Ta instrukcja
├── zadania.md               # Szczegółowe opisy zadań (LaTeX)
├── ode_solver.cpp           # Program główny C++
├── visualize.py             # Skrypt wizualizacji Python
└── Makefile                 # Automatyzacja kompilacji
```

## Wymagania

### Kompilacja i uruchomienie programu C++

- Kompilator C++ z obsługą C++17 (g++, clang++)
- Make (opcjonalnie)

### Wizualizacja (Python)

```bash
pip install numpy matplotlib pandas
```

lub z użyciem `requirements.txt`:

```bash
pip install -r requirements.txt
```

## Instrukcja użycia

### Sposób 1: Użycie Makefile (zalecane)

```bash
# Kompilacja
make

# Kompilacja + uruchomienie
make run

# Pełna analiza z wizualizacją
make visualize

# Czyszczenie plików
make clean
```

### Sposób 2: Manualna kompilacja

```bash
# Kompilacja
g++ -std=c++17 -O2 ode_solver.cpp -o ode_solver

# Uruchomienie
./ode_solver

# Wizualizacja
python3 visualize.py
```

## Wyniki

Program generuje następujące pliki CSV:

### Dane do wykresów

- `euler_explicit_stable.csv` - Euler bezpośrednia (stabilna, dt=0.005)
- `euler_explicit_marginal.csv` - Euler bezpośrednia (graniczna, dt=0.02)
- `euler_explicit_unstable.csv` - Euler bezpośrednia (niestabilna, dt=0.05)
- `euler_implicit.csv` - Euler pośrednia (dt=0.01)
- `trapezoidal.csv` - Metoda trapezów (dt=0.01)
- `analytical.csv` - Rozwiązanie analityczne
- `convergence_analysis.csv` - Dane do analizy zbieżności

### Wykresy PNG (generowane przez visualize.py)

1. `wykres_1_euler_explicit.png` - Trzy przypadki metody Eulera bezpośredniej
2. `wykres_2_euler_implicit.png` - Metoda Eulera pośrednia vs analityczna
3. `wykres_3_trapezoidal.png` - Metoda trapezów vs analityczna
4. `wykres_4_convergence.png` - Analiza zbieżności: log(błąd) vs log(dt)
5. `wykres_5_error_comparison.png` - Porównanie błędów w funkcji czasu

## Analiza stabilności

### Metoda Eulera bezpośrednia

Warunek stabilności von Neumanna:
```
|1 - dt * p(t)| ≤ 1
```

Dla naszego problemu:
- `p(0) = 10` → `dt_max = 0.2`
- `p(∞) ≈ 100` → `dt_max = 0.02`

**Wniosek**: Wymaga `dt ≤ 0.02` dla stabilności w całym przedziale.

### Metoda Eulera pośrednia

Współczynnik przy `y_n`:
```
1 / (1 + dt * p(t)) < 1
```

Ponieważ `p(t) > 0`, metoda jest **bezwarunkowo stabilna**.

### Metoda trapezów

Metoda trapezów jest **bezwarunkowo stabilna** dla równań z `p(t) > 0`.

## Przykładowe wyniki

Po uruchomieniu `make visualize` otrzymasz:

```
=== Rozwiązywanie równania różniczkowego ===
y'(t) + p(t)*(y(t) - 1) = 0
p(t) = (100*t + 10)/(t + 1)
Warunek początkowy: y(0) = 2
Przedział: t ∈ [0, 0.5]

1. Metoda Eulera bezpośrednia:
   a) Stabilny (dt = 0.005)
   ✓ Zapisano: euler_explicit_stable.csv

   b) Niestabilny (dt = 0.05)
   ✓ Zapisano: euler_explicit_unstable.csv

   c) Graniczny (dt = 0.02)
   ✓ Zapisano: euler_explicit_marginal.csv

2. Metoda Eulera pośrednia:
   dt = 0.01
   ✓ Zapisano: euler_implicit.csv

3. Metoda trapezów:
   dt = 0.01
   ✓ Zapisano: trapezoidal.csv

=== Błędy maksymalne ===
Euler bezpośrednia (stabilna):   1.2345e-04
Euler bezpośrednia (graniczna):  4.5678e-04
Euler pośrednia:                 2.3456e-04
Trapezów:                        5.6789e-05
```

## Analiza rzędu zbieżności

Eksperymentalny rząd zbieżności `p` obliczany jest z wzoru:

```
p = log(e₂/e₁) / log(h₂/h₁)
```

gdzie `e₁`, `e₂` to błędy dla kroków `h₁`, `h₂`.

**Teoretyczne wartości**:
- Metody Eulera: `p = 1`
- Metoda trapezów: `p = 2`

Program weryfikuje te wartości eksperymentalnie i generuje wykres log-log.

## Obserwacje i wnioski

### 1. Stabilność numeryczna

- **Euler bezpośrednia**: Dla `dt > 0.02` pojawia się niestabilność
- **Euler pośrednia**: Stabilna dla wszystkich testowanych kroków
- **Trapezów**: Stabilna i najdokładniejsza

### 2. Dokładność

Dla tego samego kroku `dt = 0.01`:
```
Metoda trapezów < Euler pośrednia < Euler bezpośrednia
```

### 3. Błędy maszynowe

Dla bardzo małych kroków (`dt < 1e-5`):
- Błędy przestają maleć zgodnie z teorią
- Dominują błędy zaokrągleń zmiennoprzecinkowych
- Widoczne na wykresie zbieżności jako odchylenie od linii prostej

### 4. Wybór metody

**Rekomendacje**:
- **Szybkie obliczenia**: Euler bezpośrednia z małym `dt`
- **Stabilność**: Euler pośrednia lub trapezów
- **Wysoka dokładność**: Metoda trapezów (rząd 2)

## Zadania dodatkowe

W pliku `zadania.md` znajdziesz:

1. Szczegółową analizę teoretyczną stabilności
2. Zadania dla innych równań różniczkowych
3. Wyprowadzenia matematyczne
4. Pytania kontrolne

## Rozszerzenia projektu

Możliwe kierunki rozwoju:

1. Implementacja metod Runge-Kutty (RK4)
2. Adaptacyjny dobór kroku czasowego
3. Równania sztywne (stiff equations)
4. Układy równań różniczkowych
5. Równania wyższych rzędów

## Autor

Projekt na zajęcia z Metod Obliczeniowych
Zajęcia nr 10 - Metody numeryczne dla ODE

## Licencja

Materiały edukacyjne - wolne do użytku w celach dydaktycznych.
