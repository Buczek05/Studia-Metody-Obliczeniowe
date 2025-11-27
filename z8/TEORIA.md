# Teoria - Przybliżenia różnicowe pochodnych

## 1. Podstawy

### 1.1 Definicja pochodnej

$$f'(x) = \lim_{h \to 0} \frac{f(x+h) - f(x)}{h}$$

Dla skończonego $h$ otrzymujemy **przybliżenie**:
$$f'(x) \approx \frac{f(x+h) - f(x)}{h}$$

### 1.2 Szereg Taylora

Podstawowe narzędzie do analizy błędów:

$$f(x+h) = f(x) + h f'(x) + \frac{h^2}{2!} f''(x) + \frac{h^3}{3!} f'''(x) + \frac{h^4}{4!} f^{(4)}(x) + \cdots$$

Krócej: $f(x+h) = \sum_{n=0}^{\infty} \frac{h^n}{n!} f^{(n)}(x)$

---

## 2. Przybliżenia pierwszego rzędu - O(h)

### 2.1 Forward difference (różnica do przodu)

**Wzór:**
$$f'(x) \approx \frac{f(x+h) - f(x)}{h}$$

**Wyprowadzenie:**
$$f(x+h) = f(x) + h f'(x) + \frac{h^2}{2} f''(\xi), \quad \xi \in (x, x+h)$$

$$\frac{f(x+h) - f(x)}{h} = f'(x) + \frac{h}{2} f''(\xi)$$

**Błąd:** $E = \frac{h}{2} f''(\xi) = O(h)$

### 2.2 Backward difference (różnica do tyłu)

**Wzór:**
$$f'(x) \approx \frac{f(x) - f(x-h)}{h}$$

**Wyprowadzenie:** Analogicznie jak forward, ale dla $f(x-h)$

**Błąd:** $E = -\frac{h}{2} f''(\xi) = O(h)$

### 2.3 Zastosowania

- Brzegi przedziału (gdy nie ma punktów po obu stronach)
- Szybkie, ale mało dokładne obliczenia
- Problemy z małymi $h$ (błędy maszynowe!)

---

## 3. Przybliżenia drugiego rzędu - O(h²)

### 3.1 Central difference (różnica centralna)

**Wzór:**
$$f'(x) \approx \frac{f(x+h) - f(x-h)}{2h}$$

**Wyprowadzenie:**
$$f(x+h) = f(x) + h f'(x) + \frac{h^2}{2} f''(x) + \frac{h^3}{6} f'''(x) + O(h^4)$$

$$f(x-h) = f(x) - h f'(x) + \frac{h^2}{2} f''(x) - \frac{h^3}{6} f'''(x) + O(h^4)$$

**Odejmowanie:**
$$f(x+h) - f(x-h) = 2h f'(x) + \frac{h^3}{3} f'''(\xi) + O(h^5)$$

$$\frac{f(x+h) - f(x-h)}{2h} = f'(x) + \frac{h^2}{6} f'''(\xi)$$

**Błąd:** $E = \frac{h^2}{6} f'''(\xi) = O(h^2)$

**Uwaga:** Wyrazy parzyste w szeregu Taylora się **redukują**!

### 3.2 Forward difference 3-punktowa

**Wzór:**
$$f'(x) \approx \frac{-3f(x) + 4f(x+h) - f(x+2h)}{2h}$$

**Wyprowadzenie:** Szukamy $\alpha, \beta, \gamma$ takich, że:
$$\alpha f(x) + \beta f(x+h) + \gamma f(x+2h) = 2h f'(x) + O(h^3)$$

Rozwijamy w szereg i dopasowujemy współczynniki:
- $\alpha + \beta + \gamma = 0$ (eliminacja $f(x)$)
- $\beta + 2\gamma = 2$ (współczynnik przy $f'(x)$)
- $\beta + 4\gamma = 0$ (eliminacja $f''(x)$)

Rozwiązanie: $\alpha = -\frac{3}{2}, \beta = 2, \gamma = -\frac{1}{2}$

Po przemnożeniu przez 2:
$$-3f(x) + 4f(x+h) - f(x+2h) = 2h f'(x) + O(h^3)$$

**Błąd:** $E = \frac{h^2}{3} f'''(\xi) = O(h^2)$

### 3.3 Backward difference 3-punktowa

**Wzór:**
$$f'(x) \approx \frac{3f(x) - 4f(x-h) + f(x-2h)}{2h}$$

**Wyprowadzenie:** Analogicznie jak forward, ale w kierunku przeciwnym.

**Błąd:** $E = -\frac{h^2}{3} f'''(\xi) = O(h^2)$

---

## 4. Przybliżenia czwartego rzędu - O(h⁴)

### 4.1 Central difference 5-punktowa (pierwsza pochodna)

**Wzór:**
$$f'(x) \approx \frac{f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h)}{12h}$$

**Wyprowadzenie:** Szukamy kombinacji:
$$\alpha f(x-2h) + \beta f(x-h) + \gamma f(x+h) + \delta f(x+2h)$$

Warunki (po rozwinięciu w szereg):
1. $\alpha + \beta + \gamma + \delta = 0$
2. $-2\alpha - \beta + \gamma + 2\delta = 1$ (współczynnik przy $f'(x)$, po podzieleniu przez $h$)
3. $4\alpha + \beta + \gamma + 4\delta = 0$
4. $-8\alpha - \beta + \gamma + 8\delta = 0$

Rozwiązanie: $\alpha = \frac{1}{12}, \beta = -\frac{2}{3}, \gamma = \frac{2}{3}, \delta = -\frac{1}{12}$

**Błąd:** $E = -\frac{h^4}{30} f^{(5)}(\xi) = O(h^4)$

### 4.2 Central difference 5-punktowa (druga pochodna)

**Wzór:**
$$f''(x) \approx \frac{-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h)}{12h^2}$$

**Wyprowadzenie:** Podobnie jak dla pierwszej pochodnej, ale dopasowujemy $f''(x)$.

**Błąd:** $E = \frac{h^4}{90} f^{(6)}(\xi) = O(h^4)$

---

## 5. Druga pochodna

### 5.1 Central difference O(h²)

**Wzór:**
$$f''(x) \approx \frac{f(x-h) - 2f(x) + f(x+h)}{h^2}$$

**Wyprowadzenie:**
$$f(x+h) + f(x-h) = 2f(x) + h^2 f''(x) + \frac{h^4}{12} f^{(4)}(\xi)$$

$$\frac{f(x+h) - 2f(x) + f(x-h)}{h^2} = f''(x) + \frac{h^2}{12} f^{(4)}(\xi)$$

**Błąd:** $E = \frac{h^2}{12} f^{(4)}(\xi) = O(h^2)$

---

## 6. Analiza błędów

### 6.1 Błąd obcięcia (truncation error)

Wynika z przybliżenia nieskończonego szeregu skończoną liczbą wyrazów.

**Dla metody rzędu $p$:**
$$E_{trunc} = C h^p$$

gdzie $C$ zależy od pochodnych funkcji.

### 6.2 Błąd zaokrąglenia (roundoff error)

Wynika z ograniczonej precyzji arytmetyki zmiennoprzecinkowej.

**Dla ilorazu różnicowego:**
$$\frac{f(x+h) - f(x)}{h}$$

Jeśli $f \sim O(1)$, to błędy zaokrągleń $\sim \epsilon_{mach}$

**Względny błąd różnicy:**
$$\frac{\epsilon_{mach}}{|f(x+h) - f(x)|} \sim \frac{\epsilon_{mach}}{h |f'(x)|}$$

**Błąd ilorazu:**
$$E_{round} \sim \frac{\epsilon_{mach}}{h}$$

### 6.3 Błąd całkowity

$$E_{total}(h) = E_{trunc}(h) + E_{round}(h) = C_1 h^p + \frac{C_2 \epsilon_{mach}}{h}$$

### 6.4 Optymalny krok

Minimalizujemy błąd całkowity:
$$\frac{d E_{total}}{dh} = p C_1 h^{p-1} - \frac{C_2 \epsilon_{mach}}{h^2} = 0$$

$$h_{opt} = \left(\frac{C_2 \epsilon_{mach}}{p C_1}\right)^{1/(p+1)}$$

**Rzędy wielkości:**

| Metoda | $h_{opt}$ | Dla double ($\epsilon \approx 10^{-16}$) |
|--------|-----------|------------------------------------------|
| O(h) | $\epsilon^{1/2}$ | $\sim 10^{-8}$ |
| O(h²) | $\epsilon^{1/3}$ | $\sim 10^{-5}$ |
| O(h⁴) | $\epsilon^{1/5}$ | $\sim 10^{-3}$ |

**Wnioski:**
- Metody wyższego rzędu mają większe optymalne $h$
- Są mniej wrażliwe na błędy zaokrągleń
- Pozwalają na użycie większych kroków przy tej samej dokładności

---

## 7. Catastrophic cancellation

### 7.1 Problem

Dla bardzo małych $h$:
$$f(x+h) \approx f(x)$$

Odejmowanie bliskich liczb:
$$f(x+h) - f(x) \approx 0$$

**Utrata cyfr znaczących!**

### 7.2 Przykład numeryczny

Niech $f(x) = \cos(x)$, $x = 1$, $h = 10^{-8}$:

```
f(1)        = 0.5403023058681398  (16 cyfr znaczących)
f(1+10⁻⁸)   = 0.5403023058597251  (16 cyfr znaczących)
różnica     = 0.0000000000084147  (tylko 5 cyfr znaczących!)
```

Po podzieleniu przez $h = 10^{-8}$:
```
iloraz = -0.84147... (5 cyfr znaczących zamiast 16!)
```

### 7.3 Rozwiązanie

1. **Nie używaj zbyt małych $h$** - trzymaj się $h \geq h_{opt}$
2. **Użyj metod wyższego rzędu** - pozwalają na większe $h$
3. **Arytmetyka o wyższej precyzji** - long double, quad precision
4. **Różniczkowanie automatyczne** - unika problemu całkowicie

---

## 8. Porównanie metod

| Metoda | Rząd | Punkty | Błąd trunc. | $h_{opt}$ (double) | Zalety | Wady |
|--------|------|--------|-------------|-------------------|--------|------|
| Forward 2pt | O(h) | 2 | $\frac{h}{2}f''$ | $10^{-8}$ | Prosta, brzegi | Mała dokładność |
| Central 3pt | O(h²) | 2 | $\frac{h^2}{6}f'''$ | $10^{-5}$ | Dobra dokładność | Wymaga 2 stron |
| Forward 3pt | O(h²) | 3 | $\frac{h^2}{3}f'''$ | $10^{-5}$ | Brzegi, O(h²) | 3 punkty |
| Central 5pt | O(h⁴) | 4 | $\frac{h^4}{30}f^{(5)}$ | $10^{-3}$ | Najwyższa dokładność | 4 punkty, środek |

---

## 9. Wzory referencyjne

### 9.1 Pierwsza pochodna

**O(h):**
- Forward: $\frac{-f(x) + f(x+h)}{h}$
- Backward: $\frac{f(x) - f(x-h)}{h}$

**O(h²):**
- Central: $\frac{-f(x-h) + f(x+h)}{2h}$
- Forward: $\frac{-3f(x) + 4f(x+h) - f(x+2h)}{2h}$
- Backward: $\frac{f(x-2h) - 4f(x-h) + 3f(x)}{2h}$

**O(h⁴):**
- Central: $\frac{f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h)}{12h}$

### 9.2 Druga pochodna

**O(h²):**
- Central: $\frac{f(x-h) - 2f(x) + f(x+h)}{h^2}$

**O(h⁴):**
- Central: $\frac{-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h)}{12h^2}$

---

## 10. Praktyczne zastosowania

### 10.1 Kiedy używać różnicowania numerycznego?

**Tak:**
- Brak wzoru analitycznego na pochodną
- Funkcja zadana tabelarycznie (pomiary)
- Złożone funkcje (całki, równania różniczkowe)

**Nie:**
- Gdy można obliczyć pochodną analitycznie
- Gdy jest dostępne różniczkowanie automatyczne
- Gdy wymagana bardzo wysoka dokładność

### 10.2 Alternatywy

1. **Różniczkowanie symboliczne** (SymPy, Mathematica)
   - Dokładne symbolicznie
   - Może generować złożone wyrażenia

2. **Różniczkowanie automatyczne** (forward/reverse mode)
   - Dokładność maszynowa (bez błędu obcięcia!)
   - Efektywne obliczeniowo
   - Wymaga specjalnych bibliotek (PyTorch, JAX, CppAD)

3. **Interpolacja + pochodna**
   - Interpoluj dane (splajny)
   - Różniczkuj wielomian interpolacyjny

---

## Literatura

1. **Burden & Faires** - "Numerical Analysis" (rozdz. 4)
2. **Press et al.** - "Numerical Recipes" (rozdz. 5.7)
3. **Stoer & Bulirsch** - "Introduction to Numerical Analysis" (rozdz. 3)
4. **Süli & Mayers** - "An Introduction to Numerical Analysis" (rozdz. 12)

## Podsumowanie kluczowych wzorów

```
Forward O(h):     f'(x) ≈ [f(x+h) - f(x)] / h

Central O(h²):    f'(x) ≈ [f(x+h) - f(x-h)] / (2h)

Central O(h⁴):    f'(x) ≈ [f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h)] / (12h)

Second O(h²):     f''(x) ≈ [f(x-h) - 2f(x) + f(x+h)] / h²

Optimal h:        h_opt ~ ε_mach^(1/(p+1))  gdzie p = rząd metody
```
