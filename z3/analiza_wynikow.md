# Analiza wyników i wskazówki

## Obserwacje z wykonania programu

### Porównanie szybkości zbieżności

Dla równania **sinh(x) + x/4 - 1 = 0**:

| Metoda | Liczba iteracji | Rząd zbieżności |
|--------|----------------|-----------------|
| Picarda | ~14 | liniowy (q ≈ 0.194) |
| Bisekcji | ~34 | liniowy (q = 0.5) |
| Newtona | ~4 | kwadratowy (q = 2) |
| Siecznych | ~5 | superlineary (q ≈ 1.618) |

### Wnioski

1. **Metoda Newtona** jest najszybsza - zbieżność kwadratowa
   - Wymaga jednak znajomości pochodnej
   - Liczba poprawnych cyfr dziesiętnych podwaja się w każdej iteracji

2. **Metoda siecznych** jest niemal tak szybka jak Newtona
   - Nie wymaga pochodnej
   - Zbieżność superlinearna (złoty podział φ ≈ 1.618)

3. **Metoda Picarda** - szybkość zależy od funkcji g(x)
   - Dla naszych przykładów: całkiem szybka
   - Wymaga odpowiedniego przekształcenia równania
   - Nie zawsze zbieżna!

4. **Metoda bisekcji** - najwolniejsza, ale najbardziej niezawodna
   - Zawsze zbieżna (jeśli f(a)·f(b) < 0)
   - Każda iteracja zmniejsza przedział o połowę
   - Przewidywalna liczba iteracji

## Analiza zbieżności metody Picarda

### Warunek zbieżności: |g'(x)| < 1

#### Równanie a): sinh(x) + x/4 - 1 = 0

Przekształcenie: **x = asinh(1 - x/4)** → **g(x) = asinh(1 - x/4)**

Pochodna:
```
g'(x) = -1/4 · 1/√(1 + (1 - x/4)²)
```

W okolicy pierwiastka x* ≈ 0.7436:
```
|g'(x*)| ≈ 0.194 < 1 ✓ → Metoda ZBIEGA
```

**Oszacowanie tempa zbieżności:**
- Błąd maleje w każdej iteracji około 5 razy (1/0.194 ≈ 5.15)
- Zbieżność liniowa

#### Równanie b): tanh(x) + 2(x - 1) = 0

Przekształcenie: **x = 1 - tanh(x)/2** → **g(x) = 1 - tanh(x)/2**

Pochodna:
```
g'(x) = -1/(2·cosh²(x))
```

W okolicy pierwiastka x* ≈ 0.5:
```
|g'(x*)| ≈ 0.36 < 1 ✓ → Metoda ZBIEGA
```

**Oszacowanie tempa zbieżności:**
- Błąd maleje w każdej iteracji około 2.8 razy (1/0.36 ≈ 2.78)
- Zbieżność liniowa

### Alternatywne przekształcenia (które NIE zbiegają)

❌ **Złe przekształcenie dla a):** x = 4(1 - sinh(x))
```
g'(x) = -4·cosh(x)
|g'(x)| ≥ 4 > 1 → NIE ZBIEGA
```

## Rząd zbieżności - teoria

### Zbieżność liniowa (rząd 1)
```
|ε_{n+1}| ≈ C|ε_n|, gdzie C < 1
```
Przykład: Metoda Picarda, bisekcji

### Zbieżność kwadratowa (rząd 2)
```
|ε_{n+1}| ≈ C|ε_n|²
```
Przykład: Metoda Newtona (gdy f'(x*) ≠ 0)

### Zbieżność superlinearna
```
1 < p < 2: |ε_{n+1}| ≈ C|ε_n|^p
```
Przykład: Metoda siecznych (p = φ ≈ 1.618)

## Estymator błędu vs Residuum

### Estymator błędu: |x_n - x_{n-1}|
- Mierzy zmianę między kolejnymi iteracjami
- Nie zawsze dobrze odzwierciedla rzeczywisty błąd |x_n - x*|
- Dla wolno zbieżnych metod może być mylące

### Residuum: |f(x_n)|
- Mierzy jak dobrze x_n spełnia równanie
- f(x_n) = 0 oznacza dokładne rozwiązanie
- Może być małe nawet gdy x_n daleko od x* (źle uwarunkowane problemy)

### Przykład obserwacji z programu

Dla metody Newtona (równanie a), iteracja 2:
```
x_n = 0.74363407520
|x_n - x_{n-1}| = 4.68e-05   ← estymator błędu
|f(x_n)| = 8.92e-10           ← residuum
```

Residuum jest **znacznie mniejsze** niż estymator błędu!
- To normalne dla metody Newtona w pobliżu rozwiązania
- Wskazuje na dobrą jakość przybliżenia

## Algorytm Herona jako metoda Newtona

### Równanie: f(x) = x² - a = 0

Rozwiązanie: x* = √a

### Metoda Newtona:
```
x_{n+1} = x_n - f(x_n)/f'(x_n)
        = x_n - (x_n² - a)/(2x_n)
        = x_n - x_n/2 + a/(2x_n)
        = (x_n + a/x_n)/2
```

To jest dokładnie wzór Herona! ✓

### Geometryczna interpretacja
1. Heron (III wiek p.n.e.) - wzór empiryczny
2. Newton (XVII wiek) - ogólna metoda
3. Algorytm Herona to szczególny przypadek metody Newtona

## Praktyczne wskazówki

### Wybór metody w praktyce

**Metoda Newtona** - gdy:
- ✓ Znamy pochodną funkcji
- ✓ Zależy nam na szybkości
- ✓ Mamy dobre przybliżenie początkowe
- ✗ Pochodna może być zerowa
- ✗ Pochodna jest trudna do obliczenia

**Metoda siecznych** - gdy:
- ✓ Nie znamy/nie chcemy liczyć pochodnej
- ✓ Zależy nam na szybkości
- ✓ f(x) jest kosztowna obliczeniowo

**Metoda bisekcji** - gdy:
- ✓ Niezawodność > szybkość
- ✓ Możemy znaleźć przedział [a,b] z f(a)·f(b) < 0
- ✓ Funkcja może być "trudna" (nieróżniczkowalna, itp.)

**Metoda Picarda** - gdy:
- ✓ Naturalne przekształcenie x = g(x) jest oczywiste
- ✓ |g'(x)| < 1 w obszarze zainteresowania
- Rzadko stosowana w praktyce dla pojedynczych równań

### Kryteria stopu

Program używa trzech kryteriów jednocześnie:

1. **Maksymalna liczba iteracji** - bezpieczeństwo
2. **|x_{n+1} - x_n| < ε** - praktyczne kryterium
3. **|f(x_n)| < δ** - teoretycznie najlepsze

**Zalecenie:** Używaj kombinacji 2 i 3, plus zabezpieczenie (1).

## Eksperymenty do wykonania

1. **Zmień punkt startowy** dla metod Picarda, Newtona i siecznych
   - Jak wpływa na liczbę iteracji?
   - Czy metoda nadal zbiega?

2. **Zmień tolerancje** ε i δ
   - Jak zmienia się liczba iteracji?
   - Czy stosunek liczby iteracji między metodami się zmienia?

3. **Przetestuj inne równania:**
   ```
   - cos(x) - x = 0
   - e^x - 2 - x = 0
   - x³ - 2x - 5 = 0
   ```

4. **Sprawdź źle uwarunkowane równanie:**
   ```
   (x - 1)⁴ = 0  (pierwiastek wielokrotny)
   ```
   - Metoda Newtona zbiega wolniej (liniowo zamiast kwadratowo)

## Zadania dodatkowe

1. Zmodyfikuj program, aby liczył dokładny błąd |x_n - x*| dla przypadku, gdy znasz x*

2. Zaimplementuj **metodę regula falsi** (fałszywej pozycji)

3. Dodaj wykres zbieżności (log|błąd| vs iteracja) - określ eksperymentalnie rząd zbieżności

4. Zaimplementuj kryterium stopu Aitkena dla metody Picarda
