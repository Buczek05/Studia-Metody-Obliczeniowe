# Instrukcje praktyczne - Zajęcia nr 8

## Szybki start

### 1. Kompilacja
```bash
cd /Users/bukowski/Projects/Studia-Metody-Obliczeniowe/z8
make
```

### 2. Uruchomienie głównego programu
```bash
make run
```

lub bezpośrednio:
```bash
./finite_differences
```

### 3. Uruchomienie programu analitycznego
```bash
make analysis
```

### 4. Generowanie wykresów (wymaga gnuplot)
```bash
# Instalacja gnuplot (macOS)
brew install gnuplot

# Instalacja gnuplot (Linux)
sudo apt-get install gnuplot

# Generowanie wykresów
make plot
```

## Struktura plików

```
z8/
├── finite_differences.cpp    - Główny program analizy
├── analiza.cpp               - Program szczegółowej analizy
├── plot_convergence.gnu      - Skrypt gnuplot do wykresów
├── Makefile                  - Automatyzacja kompilacji
├── README.md                 - Dokumentacja ogólna
├── ZADANIA.md               - Zadania do wykonania z LaTeX
├── INSTRUKCJE.md            - Ten plik
└── convergence_*.dat        - Pliki z danymi (generowane)
```

## Co robi każdy program

### finite_differences
Główny program wykonujący:
- Obliczenia dla funkcji f(x) = cos(x)
- Porównanie wszystkich metod różnicowych
- Analiza dla typów double i long double
- Generowanie plików danych do wykresów
- Wyznaczanie doświadczalnych rzędów dokładności

### analiza
Program pomocniczy pokazujący:
- Parametry precyzji typów zmiennych
- Demonstrację catastrophic cancellation
- Szczegółowe porównanie metod dla wybranych h
- Szukanie optymalnego kroku h

## Interpretacja wyników

### Tabela błędów

```
          h    Forward 2pt   Backward 2pt    Central 3pt    Central 5pt
------------------------------------------------------------------------
 1.0000e+00     2.1296e-01     4.3715e-01     1.1210e-01     2.0922e-02
 1.0000e-01     3.4148e-02     3.6504e-02     1.1779e-03     2.3542e-06
 1.0000e-02     3.5237e-03     3.5473e-03     1.1785e-05     2.3570e-10
```

**Co obserwujemy:**
- Dla h = 0.01, metoda Central 5pt (O(h⁴)) daje błąd ~10⁻¹⁰
- Jest to o 5 rzędów wielkości lepsze niż Central 3pt (O(h²))
- Forward i Backward 2pt mają podobne błędy (~10⁻³)

### Rząd dokładności

```
Metoda                   Rząd teoretyczny    Rząd doświadczalny
-----------------------------------------------------------------
Forward 2pt                     1                  0.9864
Central 3pt                     2                  1.9998
Central 5pt                     4                  3.9995
```

**Interpretacja:**
- Doświadczalny rząd bardzo dobrze zgadza się z teorią
- Dla Central 5pt: 3.9995 ≈ 4 ✓
- Niewielkie odchylenia wynikają z błędów zaokrągleń

### Błędy maszynowe

**Typowe objawy:**
```
 1.0000e-06     3.5355e-07     <- Błąd maleje zgodnie z teorią
 1.0000e-07     3.5247e-08     <- Wciąż OK
 1.0000e-08     1.4152e-08     <- UWAGA: Błąd przestaje maleć!
 1.0000e-09     3.6357e-08     <- Błąd rośnie!
```

**Wyjaśnienie:**
- Dla bardzo małych h różnica f(x+h) - f(x) jest bliska zeru
- Odejmowanie bliskich liczb powoduje utratę cyfr znaczących
- Błędy zaokrągleń zaczynają dominować

## Wykresy

### convergence_analysis.png
Pokazuje 6 paneli:
- 3 dla typu double (środek, brzeg początkowy, brzeg końcowy)
- 3 dla typu long double (analogicznie)

**Na wykresach log-log:**
- Oś X: log₁₀(h)
- Oś Y: log₁₀(błąd)
- Linie proste o nachyleniu = rząd metody
- Punkt przegięcia = pojawienie się błędów maszynowych

### comparison_double_vs_long_double.png
Bezpośrednie porównanie precyzji:
- Na macOS często double = long double (64-bit)
- Na Linuxie x86-64: long double = 80-bit (extended precision)

## Praktyczne wskazówki

### Wybór metody

| Metoda | Dokładność | Punkty potrzebne | Kiedy używać |
|--------|-----------|------------------|--------------|
| Forward 2pt | O(h) | 2 | Brzegi, szybkie obliczenia |
| Central 3pt | O(h²) | 2 | Uniwersalne zastosowanie |
| Forward/Backward 3pt | O(h²) | 3 | Brzegi z lepszą dokładnością |
| Central 5pt | O(h⁴) | 4 | Wysoka dokładność w środku |

### Wybór kroku h

**Dla double (ε ≈ 2.2×10⁻¹⁶):**

| Metoda | h_opt (teoretyczny) | h_opt (praktyczny) | Uwagi |
|--------|---------------------|-------------------|-------|
| O(h) | ~10⁻⁸ | 10⁻⁸ | Bardzo wrażliwe na błędy |
| O(h²) | ~10⁻⁵ | 10⁻⁶ | Dobry kompromis |
| O(h⁴) | ~10⁻³ | 10⁻³ - 10⁻² | Najmniej wrażliwe |

**Złota zasada:** Nie używaj h mniejszych niż h_opt!

### Typowe błędy

1. **h zbyt małe**
   ```
   h = 1e-15  // ŹLE! Błędy maszynowe dominują
   h = 1e-6   // DOBRZE dla Central O(h²)
   ```

2. **Niewłaściwa metoda na brzegu**
   ```cpp
   // ŹLE: Central różnica wymaga x-h i x+h
   double der = central_diff(f, 0.0, h);  // x-h < 0 !

   // DOBRZE: Użyj metody jednostronnej
   double der = forward_diff_3pt(f, 0.0, h);
   ```

3. **Ignorowanie rzędu metody**
   ```
   // Dla h = 0.01:
   // O(h):  błąd ~ 0.01
   // O(h²): błąd ~ 0.0001
   // O(h⁴): błąd ~ 10⁻⁸
   ```

## Eksperymenty do przeprowadzenia

### Eksperyment 1: Zbieżność
1. Uruchom `./finite_differences`
2. Znajdź w output tabelę dla "Punkt środkowy"
3. Zaobserwuj, jak błąd maleje wraz z h
4. Zidentyfikuj punkt, gdzie błąd przestaje maleć

**Pytania:**
- Dla jakiego h błąd jest minimalny?
- Czy zgadza się z h_opt teoretycznym?

### Eksperyment 2: Catastrophic cancellation
1. Uruchom `./analiza`
2. Przeanalizuj tabelę "catastrophic cancellation"
3. Zobacz, jak błąd względny rośnie dla małych h

**Pytania:**
- Dla h = 10⁻¹⁴ różnica f(x+h)-f(x) ma tylko kilka cyfr znaczących
- Jak to wpływa na dokładność ilorazu różnicowego?

### Eksperyment 3: Porównanie metod
1. Uruchom `./analiza`
2. Porównaj wyniki dla h = 0.01, 0.001, 10⁻⁸

**Pytania:**
- Która metoda jest najdokładniejsza dla h = 0.01?
- Która metoda najlepiej radzi sobie z małymi h?
- Dlaczego metoda O(h⁴) ma problemy dla h = 10⁻⁸?

### Eksperyment 4: Wykresy
1. Zainstaluj gnuplot jeśli potrzeba
2. Uruchom `make plot`
3. Otwórz `convergence_analysis.png`

**Pytania:**
- Czy nachylenie krzywych odpowiada rzędowi metody?
- Gdzie występuje minimum błędu?
- Jak wygląda wykres dla bardzo małych h?

## Analiza matematyczna

### Przykład: Central O(h²)

**Szereg Taylora:**
```
f(x+h) = f(x) + h·f'(x) + (h²/2)·f''(x) + (h³/6)·f'''(ξ₁)
f(x-h) = f(x) - h·f'(x) + (h²/2)·f''(x) - (h³/6)·f'''(ξ₂)
```

**Odejmowanie:**
```
f(x+h) - f(x-h) = 2h·f'(x) + (h³/6)·[f'''(ξ₁) + f'''(ξ₂)]
                = 2h·f'(x) + O(h³)
```

**Przybliżenie:**
```
f'(x) ≈ [f(x+h) - f(x-h)] / (2h)
```

**Błąd obcięcia:**
```
E_trunc = (h²/6)·[f'''(ξ₁) + f'''(ξ₂)] / 2 = O(h²)
```

**Błąd zaokrąglenia:**
Jeśli |f| ~ 1, to błędy zaokrąglenia ~ ε_mach
```
E_round = ε_mach / h
```

**Błąd całkowity:**
```
E_total = C₁·h² + C₂·ε_mach/h
```

**Minimum:**
```
dE/dh = 2C₁·h - C₂·ε_mach/h² = 0
h_opt = (C₂·ε_mach / 2C₁)^(1/3)
h_opt ~ ε_mach^(1/3)
```

Dla double: h_opt ~ (2.2×10⁻¹⁶)^(1/3) ≈ 6×10⁻⁶

## Debugging

### Problem: Program się nie kompiluje
```bash
# Sprawdź wersję kompilatora
g++ --version  # Potrzebne C++17

# Jeśli błąd z M_PI
# Dodaj na początku pliku:
#define _USE_MATH_DEFINES
```

### Problem: Brak wykresów
```bash
# Sprawdź czy gnuplot jest zainstalowany
which gnuplot

# Zainstaluj jeśli trzeba
brew install gnuplot  # macOS
sudo apt install gnuplot  # Linux
```

### Problem: Dziwne wyniki dla long double
```bash
# Sprawdź rozmiar long double
./analiza | grep "Rozmiar"

# Na macOS często long double = double (8 bajtów)
# Na Linuxie x86-64: long double = 16 bajtów (80-bit + padding)
```

## Rozszerzenia projektu

### 1. Inne funkcje
Przetestuj dla:
- f(x) = sin(x)
- f(x) = exp(x)
- f(x) = x²
- f(x) = 1/(1+x²)

### 2. Druga pochodna
Zaimplementuj przybliżenia dla f''(x):
```cpp
// O(h²)
f''(x) ≈ [f(x-h) - 2f(x) + f(x+h)] / h²

// O(h⁴)
f''(x) ≈ [-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h)] / (12h²)
```

### 3. Adaptive step size
Zaimplementuj automatyczny dobór h:
```cpp
template <typename T>
T adaptive_derivative(T (*f)(T), T x, T tol) {
    T h = 0.1;
    T prev = central_diff(f, x, h);

    while (h > 1e-10) {
        h /= 2;
        T curr = central_diff(f, x, h);
        if (std::abs(curr - prev) < tol) return curr;
        prev = curr;
    }
    return prev;
}
```

### 4. Richardson extrapolation
Popraw dokładność przez ekstrapolację:
```cpp
template <typename T>
T richardson(T (*f)(T), T x, T h) {
    T D1 = central_diff(f, x, h);
    T D2 = central_diff(f, x, h/2);
    return (4*D2 - D1) / 3;  // O(h⁴)
}
```

## Literatura uzupełniająca

1. **Numerical Recipes** - Rozdział 5.7: Numerical Derivatives
2. **Burden & Faires** - Rozdział 4: Numerical Differentiation
3. **Wikipedia**: Finite difference coefficient
4. **Wolfram MathWorld**: Finite Difference

## Kontakt i pytania

W przypadku problemów:
1. Sprawdź sekcję Debugging powyżej
2. Przejrzyj README.md i ZADANIA.md
3. Uruchom `make help` dla listy dostępnych poleceń
