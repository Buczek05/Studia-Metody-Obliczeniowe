# Wzory kwadratur numerycznych - Szybki przewodnik

## 1. Kwadratury proste (dla pojedynczego przedziału [a,b])

### Prostokąty - lewy węzeł
```
∫ₐᵇ f(x) dx ≈ (b - a) · f(a)
```
**Błąd**: O(h²), gdzie h = b - a

### Prostokąty - prawy węzeł
```
∫ₐᵇ f(x) dx ≈ (b - a) · f(b)
```
**Błąd**: O(h²)

### Prostokąty - środek
```
∫ₐᵇ f(x) dx ≈ (b - a) · f((a+b)/2)
```
**Błąd**: O(h³)

### Trapezy
```
∫ₐᵇ f(x) dx ≈ (b - a)/2 · [f(a) + f(b)]
```
**Błąd**: O(h³)

### Simpson (parabol)
Wymaga punktu w środku: xₘ = (a+b)/2
```
∫ₐᵇ f(x) dx ≈ (b - a)/6 · [f(a) + 4f(xₘ) + f(b)]
```
**Błąd**: O(h⁵)

---

## 2. Kwadratury złożone (podział na n przedziałów)

Dla przedziału [a,b] podzielonego na n równych części o długości h = (b-a)/n.

### Prostokąty - lewy węzeł
```
∫ₐᵇ f(x) dx ≈ h · Σᵢ₌₀ⁿ⁻¹ f(a + i·h)
```

### Prostokąty - prawy węzeł
```
∫ₐᵇ f(x) dx ≈ h · Σᵢ₌₁ⁿ f(a + i·h)
```

### Prostokąty - środek
```
∫ₐᵇ f(x) dx ≈ h · Σᵢ₌₀ⁿ⁻¹ f(a + (i + 0.5)·h)
```

### Trapezy
```
∫ₐᵇ f(x) dx ≈ h/2 · [f(a) + 2·Σᵢ₌₁ⁿ⁻¹ f(a + i·h) + f(b)]
```

### Simpson (n musi być parzyste!)
```
∫ₐᵇ f(x) dx ≈ h/3 · [f(x₀) + 4·Σ(nieparzyste i) f(xᵢ) + 2·Σ(parzyste i) f(xᵢ) + f(xₙ)]
```

---

## 3. Kwadratura Gaussa

### Dla przedziału [-1, 1]

#### 2 punkty (dokładna dla wielomianów stopnia ≤ 3)
```
Węzły:  x₁ = -1/√3 ≈ -0.5773502692
        x₂ =  1/√3 ≈  0.5773502692
Wagi:   w₁ = w₂ = 1

∫₋₁¹ f(x) dx ≈ w₁·f(x₁) + w₂·f(x₂)
```

#### 3 punkty (dokładna dla wielomianów stopnia ≤ 5)
```
Węzły:  x₁ = -√(3/5) ≈ -0.7745966692
        x₂ = 0
        x₃ =  √(3/5) ≈  0.7745966692
Wagi:   w₁ = w₃ = 5/9 ≈ 0.5555555556
        w₂ = 8/9 ≈ 0.8888888889

∫₋₁¹ f(x) dx ≈ w₁·f(x₁) + w₂·f(x₂) + w₃·f(x₃)
```

### Transformacja do dowolnego przedziału [a, b]

Dla kwadratury Gaussa na przedziale [-1, 1] z węzłami tᵢ i wagami wᵢ:

```
∫ₐᵇ f(x) dx ≈ (b-a)/2 · Σᵢ wᵢ · f((b-a)/2 · tᵢ + (b+a)/2)
```

---

## 4. Metoda Romberga

Ekstrapolacja Richardsona dla metody trapezów.

### Algorytm:

1. **Oblicz R(k,0)** - metoda trapezów z n = 2^k przedziałami:
   ```
   R(0,0) = T₁    (n = 1)
   R(1,0) = T₂    (n = 2)
   R(2,0) = T₄    (n = 4)
   ...
   ```

2. **Ekstrapolacja Richardsona**:
   ```
   R(k,m) = R(k,m-1) + [R(k,m-1) - R(k-1,m-1)] / (4^m - 1)
   ```

3. **Najdokładniejszy wynik**: R(n,n) w prawym dolnym rogu tablicy

### Tablica Romberga (przykład):
```
k  | m=0        m=1        m=2        m=3
---+------------------------------------------
0  | R(0,0)
1  | R(1,0)    R(1,1)
2  | R(2,0)    R(2,1)    R(2,2)
3  | R(3,0)    R(3,1)    R(3,2)    R(3,3)
```

---

## 5. Rzędy dokładności

| Metoda | Rząd błędu | Krok h maleje o połowę → błąd maleje o: |
|--------|------------|----------------------------------------|
| Prostokąty (lewe/prawe) | O(h²) | ~4 razy |
| Prostokąty (środek) | O(h³) | ~8 razy |
| Trapezy | O(h³) | ~8 razy |
| Simpson | O(h⁵) | ~32 razy |

**Interpretacja**: Jeśli zmniejszymy krok h dwukrotnie:
- Metoda prostokątów (lewe/prawe): błąd zmniejszy się ~4 razy (2²)
- Trapezy: błąd zmniejszy się ~8 razy (2³)
- Simpson: błąd zmniejszy się ~32 razy (2⁵)

---

## 6. Interpolacja biliniowa

Dla 4 punktów na siatce prostokątnej:
```
(x₁, y₁, f₁₁)  (x₂, y₁, f₂₁)
(x₁, y₂, f₁₂)  (x₂, y₂, f₂₂)
```

Wartość w punkcie (x, y):
```
f(x,y) ≈ 1/[(x₂-x₁)(y₂-y₁)] ·
         [x₂-x  x-x₁] · [f₁₁  f₁₂] · [y₂-y]
                        [f₂₁  f₂₂]   [y-y₁]
```

Lub krok po kroku:
1. Interpolacja w kierunku x dla y = y₁:
   ```
   f(x, y₁) ≈ f₁₁·(x₂-x)/(x₂-x₁) + f₂₁·(x-x₁)/(x₂-x₁)
   ```

2. Interpolacja w kierunku x dla y = y₂:
   ```
   f(x, y₂) ≈ f₁₂·(x₂-x)/(x₂-x₁) + f₂₂·(x-x₁)/(x₂-x₁)
   ```

3. Interpolacja w kierunku y:
   ```
   f(x, y) ≈ f(x,y₁)·(y₂-y)/(y₂-y₁) + f(x,y₂)·(y-y₁)/(y₂-y₁)
   ```

---

## 7. Funkcje sklejane kubiczne (cubic splines)

### Warunki ciągłości:

Dla funkcji sklejanej S(x) składającej się z wielomianów kubicznych Sᵢ(x) na przedziałach [xᵢ, xᵢ₊₁]:

1. **Ciągłość funkcji**: Sᵢ(xᵢ₊₁) = Sᵢ₊₁(xᵢ₊₁)
2. **Ciągłość pierwszej pochodnej**: S'ᵢ(xᵢ₊₁) = S'ᵢ₊₁(xᵢ₊₁)
3. **Ciągłość drugiej pochodnej**: S''ᵢ(xᵢ₊₁) = S''ᵢ₊₁(xᵢ₊₁)

### Natural cubic spline:
Dodatkowe warunki brzegowe:
```
S''(x₀) = 0    (lewy brzeg)
S''(xₙ) = 0    (prawy brzeg)
```

### Postać wielomianu na przedziale [xᵢ, xᵢ₊₁]:
```
Sᵢ(x) = aᵢ + bᵢ(x - xᵢ) + cᵢ(x - xᵢ)² + dᵢ(x - xᵢ)³
```

---

## 8. Funkcja błędu (Error Function)

```
erf(x) = (2/√π) · ∫₀ˣ exp(-t²) dt
```

### Wartości specjalne:
- erf(0) = 0
- erf(∞) = 1
- erf(-x) = -erf(x)
- erf(1) ≈ 0.8427007929
- erf(2) ≈ 0.9953222650
- erf(3) ≈ 0.9999779095

### Zastosowania:
- Rozkład normalny w statystyce
- Teoria prawdopodobieństwa
- Równania dyfuzji w fizyce

---

## 9. Przykładowa implementacja w C++

### Metoda trapezów:
```cpp
double trapezoid(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return h * sum;
}
```

### Metoda Simpsona:
```cpp
double simpson(double (*f)(double), double a, double b, int n) {
    // n musi być parzyste!
    if (n % 2 != 0) n++;

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
    }

    return (h / 3.0) * sum;
}
```

---

## 10. Wskazówki praktyczne

1. **Wybór metody**:
   - Dla gładkich funkcji: **Simpson** (najlepsza dokładność)
   - Dla prostych obliczeń: **Trapezy** (dobry kompromis)
   - Dla funkcji nieciągłych: **Prostokąty** (najbardziej odporne)

2. **Wybór liczby przedziałów n**:
   - Zacznij od małej wartości (np. n=10)
   - Podwajaj n aż wynik się ustabilizuje
   - Monitoruj zbieżność: |I(2n) - I(n)| < ε

3. **Numeryczna stabilność**:
   - Unikaj bardzo małych wartości h (błędy zaokrągleń)
   - Dla bardzo dużych przedziałów: dziel na mniejsze części
   - Sprawdzaj warunki brzegowe

4. **Optymalizacja**:
   - Simpson: najszybsza zbieżność dla gładkich funkcji
   - Gauss: najlepsza dokładność dla danej liczby punktów
   - Romberg: automatyczna adaptacja dokładności

---

**Autor**: Materiały do zajęć 13 - Metody Obliczeniowe
**Data**: 2024
