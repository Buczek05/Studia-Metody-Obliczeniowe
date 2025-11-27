# Zajęcia nr 8 - Przybliżenia różnicowe pochodnych

## Opis

Program do analizy przybliżeń różnicowych pierwszej pochodnej funkcji **f(x) = cos(x)** na przedziale **[0, π/2]**.

## Zaimplementowane schematy różnicowe

### 1. Dwupunktowe (O(h))
- **Forward difference**: `f'(x) ≈ [f(x+h) - f(x)] / h`
- **Backward difference**: `f'(x) ≈ [f(x) - f(x-h)] / h`

### 2. Trzypunktowe (O(h²))
- **Central difference**: `f'(x) ≈ [f(x+h) - f(x-h)] / (2h)`
- **Forward (brzeg)**: `f'(x₀) ≈ [-3/2·f(x₀) + 2·f(x₁) - 1/2·f(x₂)] / h`
- **Backward (brzeg)**: `f'(xₙ) ≈ [3/2·f(xₙ) - 2·f(xₙ₋₁) + 1/2·f(xₙ₋₂)] / h`

### 3. Pięciopunktowe (O(h⁴))
- **Central difference**: `f'(x) ≈ [1/12·f(x-2h) - 2/3·f(x-h) + 2/3·f(x+h) - 1/12·f(x+2h)] / h`

## Kompilacja i uruchomienie

### Wymagania
- Kompilator C++ z obsługą C++17 (g++, clang++)
- gnuplot (opcjonalnie, do generowania wykresów)

### Kompilacja
```bash
make
```

### Uruchomienie
```bash
# Tylko obliczenia
make run

# Obliczenia + wykresy
make plot
```

### Czyszczenie
```bash
make clean
```

## Pliki wyjściowe

### Dane numeryczne
- `convergence_double_middle.dat` - błędy dla punktu środkowego (double)
- `convergence_double_start.dat` - błędy dla brzegu początkowego (double)
- `convergence_double_end.dat` - błędy dla brzegu końcowego (double)
- `convergence_long_double_*.dat` - analogiczne pliki dla typu long double

### Wykresy
- `convergence_analysis.png` - porównanie wszystkich metod
- `comparison_double_vs_long_double.png` - porównanie precyzji

## Analiza wyników

### Doświadczalny rząd dokładności

Rząd dokładności wyznaczamy ze wzoru:
```
p = [log|E(h₂)| - log|E(h₁)|] / [log(h₂) - log(h₁)]
```

Program automatycznie oblicza i wyświetla doświadczalne rzędy dokładności dla wszystkich metod.

### Obserwacje do analizy

1. **Zbieżność teoretyczna vs praktyczna**
   - Czy nachylenie krzywych na wykresie log-log odpowiada teoretycznemu rzędowi?
   - Dla metody O(h) oczekujemy nachylenia = 1
   - Dla metody O(h²) oczekujemy nachylenia = 2
   - Dla metody O(h⁴) oczekujemy nachylenia = 4

2. **Błędy maszynowe**
   - Dla bardzo małych h błąd zaczyna rosnąć zamiast maleć
   - Wynika to z błędów zaokrągleń w arytmetyce zmiennoprzecinkowej
   - Dla double: ε_mach ≈ 2.22×10⁻¹⁶
   - Dla long double: ε_mach ≈ 1.08×10⁻¹⁹ (na większości systemów)

3. **Optymalna wartość h**
   - Istnieje optymalne h minimalizujące całkowity błąd
   - Dla metody O(h²): h_opt ≈ ε_mach^(1/3)
   - Dla metody O(h⁴): h_opt ≈ ε_mach^(1/5)

4. **Double vs Long Double**
   - Long double oferuje większą precyzję (więcej cyfr znaczących)
   - Pozwala na użycie mniejszych h przed wystąpieniem błędów maszynowych
   - Może nie być dostępny na wszystkich platformach

## Zadania do wykonania

### Zadanie 1: Analiza teoretyczna
Udowodnij, że podane wzory mają deklarowane rzędy dokładności, używając rozwinięcia w szereg Taylora.

### Zadanie 2: Eksperymenty numeryczne
1. Uruchom program dla obu typów zmiennych
2. Porównaj wykresy log₁₀(błąd) vs log₁₀(h)
3. Wyznacz doświadczalne rzędy dokładności
4. Zidentyfikuj wartości h, dla których błędy maszynowe zaczynają dominować

### Zadanie 3: Interpretacja
1. Czy wyniki eksperymentalne zgadzają się z teorią?
2. Które metody są najdokładniejsze?
3. Jakie praktyczne wnioski można wyciągnąć dla wyboru h w realnych obliczeniach?
4. Czy warto używać long double zamiast double?

## Przykładowe wyniki

Program wyświetla tabelę błędów dla różnych wartości h oraz oblicza doświadczalne rzędy dokładności:

```
=== Wyznaczanie doświadczalnego rzędu dokładności ===

Metoda                   Rząd teoretyczny    Rząd doświadczalny
-----------------------------------------------------------------
Forward 2pt                     1                      1.0000
Backward 2pt                    1                      1.0000
Central 3pt                     2                      2.0000
Central 5pt                     4                      4.0000
```

## Teoria - przypomnienie

### Szereg Taylora
```
f(x + h) = f(x) + h·f'(x) + (h²/2!)·f''(x) + (h³/3!)·f'''(x) + O(h⁴)
```

### Wyprowadzenie metody centralnej O(h²)
```
f(x + h) = f(x) + h·f'(x) + (h²/2)·f''(x) + O(h³)
f(x - h) = f(x) - h·f'(x) + (h²/2)·f''(x) + O(h³)

f(x + h) - f(x - h) = 2h·f'(x) + O(h³)

f'(x) = [f(x + h) - f(x - h)] / (2h) + O(h²)
```

## Literatura

1. R. L. Burden, J. D. Faires, "Numerical Analysis"
2. W. H. Press et al., "Numerical Recipes in C++"
3. A. Quarteroni, R. Sacco, F. Saleri, "Numerical Mathematics"

## Uwagi

- Program używa szablonów funkcji (function templates) zgodnie z wymaganiami zadania
- Precyzja long double może się różnić w zależności od platformy (80-bit vs 128-bit)
- Wykresy są generowane w formacie PNG, można zmienić format w skrypcie gnuplot
