# Rozwiązania zadań teoretycznych - Zajęcia 2

## Zadanie 1: Uwarunkowanie iloczynu i ilorazu

### Iloczyn p = x · y

**Wskaźnik uwarunkowania:**

Dla funkcji $f(x, y) = x \cdot y$ obliczamy wskaźnik uwarunkowania względem zmiennej $x$:

$$\kappa_x = \left| \frac{x}{f(x,y)} \cdot \frac{\partial f}{\partial x} \right| = \left| \frac{x}{xy} \cdot y \right| = \left| \frac{x \cdot y}{x \cdot y} \right| = 1$$

Analogicznie dla $y$: $\kappa_y = 1$

**Wniosek:** Obliczanie iloczynu jest **dobrze uwarunkowane** ($\kappa = 1$).

**Oszacowanie błędu względnego:**

Niech $\tilde{p} = \text{fl}(x \cdot y)$ oznacza wynik obliczony w arytmetyce zmiennoprzecinkowej. Wtedy:

$$\tilde{p} = (x \cdot y)(1 + \varepsilon)$$

gdzie $|\varepsilon| \leq \varepsilon_{\text{mach}}$ (błąd maszynowy).

Błąd względny:

$$\delta_p = \frac{|\tilde{p} - p|}{|p|} = |\varepsilon| \leq \varepsilon_{\text{mach}} \approx 2.22 \times 10^{-16}$$

---

### Iloraz d = x / y

**Wskaźnik uwarunkowania:**

Dla funkcji $f(x, y) = x / y$:

$$\kappa_x = \left| \frac{x}{x/y} \cdot \frac{1}{y} \right| = \left| \frac{x \cdot y}{x} \cdot \frac{1}{y} \right| = 1$$

$$\kappa_y = \left| \frac{y}{x/y} \cdot \left(-\frac{x}{y^2}\right) \right| = \left| \frac{y^2}{x} \cdot \left(-\frac{x}{y^2}\right) \right| = 1$$

**Wniosek:** Obliczanie ilorazu jest również **dobrze uwarunkowane** ($\kappa = 1$).

**Oszacowanie błędu względnego:**

$$\tilde{d} = (x / y)(1 + \varepsilon), \quad |\varepsilon| \leq \varepsilon_{\text{mach}}$$

$$\delta_d \leq \varepsilon_{\text{mach}} \approx 2.22 \times 10^{-16}$$

**Uwaga:** Problem pojawia się gdy $y \approx 0$ (dzielenie przez liczbę bliską zeru amplifikuje błędy).

---

## Zadanie 2: Błąd obliczenia $a^2 - b^2$

### Algorytm A₁: $a \cdot a - b \cdot b$

Wykonujemy trzy operacje zmiennoprzecinkowe:
1. $p_1 = \text{fl}(a \cdot a) = a^2(1 + \varepsilon_1)$
2. $p_2 = \text{fl}(b \cdot b) = b^2(1 + \varepsilon_2)$
3. $r_1 = \text{fl}(p_1 - p_2) = (p_1 - p_2)(1 + \varepsilon_3)$

Rozwijając:

$$r_1 = [a^2(1 + \varepsilon_1) - b^2(1 + \varepsilon_2)](1 + \varepsilon_3)$$

$$= (a^2 - b^2)(1 + \varepsilon_3) + a^2\varepsilon_1(1 + \varepsilon_3) - b^2\varepsilon_2(1 + \varepsilon_3)$$

Dla $|\varepsilon_i| \leq \varepsilon_{\text{mach}}$ i pomijając wyrazy rzędu $\varepsilon^2$:

$$|r_1 - (a^2 - b^2)| \leq |a^2 - b^2|\varepsilon_{\text{mach}} + a^2\varepsilon_{\text{mach}} + b^2\varepsilon_{\text{mach}}$$

**Błąd względny:**

$$\delta_1 \approx \varepsilon_{\text{mach}} \left(1 + \frac{a^2 + b^2}{|a^2 - b^2|}\right)$$

**Krytyczny przypadek:** Gdy $a \approx b$, mamy $a^2 - b^2 \approx 0$, więc:

$$\frac{a^2 + b^2}{|a^2 - b^2|} \gg 1$$

co prowadzi do **dużego błędu względnego** (utrata cyfr znaczących).

---

### Algorytm A₂: $(a - b)(a + b)$

Wykonujemy trzy operacje:
1. $s_1 = \text{fl}(a - b) = (a - b)(1 + \varepsilon_1)$
2. $s_2 = \text{fl}(a + b) = (a + b)(1 + \varepsilon_2)$
3. $r_2 = \text{fl}(s_1 \cdot s_2) = (s_1 \cdot s_2)(1 + \varepsilon_3)$

Rozwijając:

$$r_2 = [(a-b)(1+\varepsilon_1)][(a+b)(1+\varepsilon_2)](1+\varepsilon_3)$$

$$\approx (a^2-b^2)(1 + \varepsilon_1 + \varepsilon_2 + \varepsilon_3)$$

**Błąd względny:**

$$\delta_2 \approx 3\varepsilon_{\text{mach}}$$

**Wniosek:** Algorytm A₂ jest **numerycznie stabilny** - błąd względny jest ograniczony przez stałą wielokrotność $\varepsilon_{\text{mach}}$, niezależnie od wartości $a$ i $b$.

---

### Porównanie

| Algorytm | Błąd względny | Uwarunkowanie |
|----------|---------------|---------------|
| A₁: $a \cdot a - b \cdot b$ | $\varepsilon_{\text{mach}}(1 + \frac{a^2+b^2}{\|a^2-b^2\|})$ | Źle uwarunkowany dla $a \approx b$ |
| A₂: $(a-b)(a+b)$ | $3\varepsilon_{\text{mach}}$ | Dobrze uwarunkowany |

**Zalecenie:** Używaj algorytmu A₂!

---

## Zadanie 3: Uwarunkowanie funkcji $(1+x)^{-1}$

Dla funkcji $f(x) = (1+x)^{-1}$ obliczamy wskaźnik uwarunkowania:

$$f'(x) = -(1+x)^{-2}$$

$$\kappa(x) = \left| \frac{x \cdot f'(x)}{f(x)} \right| = \left| \frac{x \cdot [-(1+x)^{-2}]}{(1+x)^{-1}} \right|$$

$$= \left| \frac{-x}{1+x} \right| = \frac{|x|}{|1+x|}$$

### Analiza:

1. **Dla $|x| \ll 1$:**
   $$\kappa(x) \approx |x| \ll 1$$
   Zadanie **dobrze uwarunkowane**.

2. **Dla $x \approx -1$:**
   $$\kappa(x) = \frac{|x|}{|1+x|} \to \infty$$
   Zadanie **źle uwarunkowane** (dzielenie przez liczbę bliską zeru).

3. **Dla $|x| \gg 1$:**
   $$\kappa(x) \approx \frac{|x|}{|x|} = 1$$
   Zadanie **dobrze uwarunkowane**.

**Wykres wskaźnika uwarunkowania:**

```
κ(x)
  ↑
  |     /|
  |    / |
  |   /  |___________
  |  /
  | /
  |/_________________ x
 -2  -1   0   1   2
```

**Wniosek:** Funkcja $(1+x)^{-1}$ jest źle uwarunkowana w otoczeniu punktu $x = -1$.

---

## Zadanie 4: Błąd obliczenia $\ln(x)$ dla $x \approx 1$

### Problem

Dla $x = 1 + t$ gdzie $t$ jest małe ($t = 10^{-15}, 10^{-12}, 10^{-10}$), obliczenie $\ln(x)$ może być problematyczne.

### Analiza błędu reprezentacji

Liczba $x = 1 + t$ musi być najpierw zaokrąglona do formatu zmiennoprzecinkowego:

$$\tilde{x} = \text{rd}(1 + t) = (1 + t)(1 + \varepsilon), \quad |\varepsilon| \leq \varepsilon_{\text{mach}}$$

Dla małych $t$ ($t < \varepsilon_{\text{mach}}$) może zajść:

$$\tilde{x} = 1$$

co prowadzi do $\ln(\tilde{x}) = \ln(1) = 0$ zamiast $\ln(1+t) \approx t$.

### Rozwinięcie Taylora

$$\ln(1+t) = t - \frac{t^2}{2} + \frac{t^3}{3} - \frac{t^4}{4} + \ldots$$

Dla małych $t$: $\ln(1+t) \approx t$

### Obliczenia numeryczne

#### Przypadek 1: $x = 1 + 10^{-15}$

- Wartość dokładna: $\ln(1 + 10^{-15}) \approx 10^{-15}$
- Problem: $10^{-15} < \varepsilon_{\text{mach}} \approx 2.22 \times 10^{-16}$ (NIE - jest większe!)
- Ale odejmowanie $1$ może prowadzić do utraty cyfr znaczących

**Test w C++:**
```cpp
double x = 1.0 + 1e-15;
double y1 = log(x);        // Może być nieprecyzyjne
double y2 = log1p(1e-15);  // Precyzyjne! (log1p oblicza ln(1+t))
```

#### Przypadek 2: $x = 1 + 10^{-12}$

- Wartość dokładna: $\ln(1 + 10^{-12}) \approx 10^{-12}$
- Błąd względny przy użyciu `log()`:
  $$\delta \approx \frac{\varepsilon_{\text{mach}}}{10^{-12}} \approx \frac{2.22 \times 10^{-16}}{10^{-12}} = 2.22 \times 10^{-4}$$

#### Przypadek 3: $x = 1 + 10^{-10}$

- Wartość dokładna: $\ln(1 + 10^{-10}) \approx 10^{-10}$
- Funkcja standardowa `log()` powinna działać poprawnie

### Rozwiązanie: Funkcja log1p

Biblioteka standardowa C++ oferuje funkcję `log1p(t)`, która oblicza $\ln(1+t)$ z wysoką precyzją dla małych $t$:

```cpp
#include <cmath>

double t = 1e-15;
double exact = log1p(t);  // Precyzyjne obliczenie ln(1+t)
```

### Tabela wyników

| $t$ | $\ln(1+t)$ (dokładnie) | `log(1+t)` (błąd) | `log1p(t)` (precyzja) |
|-----|------------------------|-------------------|----------------------|
| $10^{-15}$ | $10^{-15}$ | ~100% | ~$\varepsilon_{\text{mach}}$ |
| $10^{-12}$ | $10^{-12}$ | ~0.01% | ~$\varepsilon_{\text{mach}}$ |
| $10^{-10}$ | $10^{-10}$ | ~$10^{-6}$ | ~$\varepsilon_{\text{mach}}$ |

### Wnioski

1. ✅ Zawsze używaj `log1p(t)` dla obliczenia $\ln(1+t)$ gdy $|t| < 0.01$
2. ⚠️ Unikaj obliczenia `log(1 + t)` bezpośrednio dla małych $t$
3. 📊 Błąd względny może być **bardzo duży** (nawet 100%) dla $t < \varepsilon_{\text{mach}}$

---

## Podsumowanie

### Kluczowe pojęcia

1. **Wskaźnik uwarunkowania** $\kappa$:
   - $\kappa \approx 1$: zadanie dobrze uwarunkowane
   - $\kappa \gg 1$: zadanie źle uwarunkowane

2. **Utrata cyfr znaczących**:
   - Występuje przy odejmowaniu bliskich liczb
   - Algorytm A₁ vs A₂ dla $a^2 - b^2$

3. **Stabilność numeryczna**:
   - Algorytm stabilny: błąd $\sim O(\varepsilon_{\text{mach}})$
   - Algorytm niestabilny: błąd rośnie z liczbą operacji

4. **Funkcje specjalne**:
   - `log1p(t)` dla $\ln(1+t)$
   - `expm1(x)` dla $e^x - 1$
   - Zawsze sprawdzaj dokumentację biblioteki!

### Praktyczne wskazówki

✅ **Dobre praktyki:**
- Używaj funkcji specjalnych (log1p, expm1, hypot)
- Unikaj odejmowania bliskich liczb
- Przekształcaj wzory algebraicznie
- Testuj na skrajnych wartościach

❌ **Złe praktyki:**
- Zakładanie że wszystkie funkcje są dokładne
- Ignorowanie utraty cyfr znaczących
- Dzielenie przez liczby bliskie zeru
- Brak testów numerycznych

---

## Zadania dodatkowe

1. Zbadaj uwarunkowanie funkcji $g(x) = \sqrt{x^2 + 1} - 1$ dla małych $x$.

   **Wskazówka:** Pomnóż i podziel przez $\sqrt{x^2 + 1} + 1$.

2. Zaproponuj stabilny algorytm obliczania $e^x - 1$ dla małych $x$.

   **Wskazówka:** Użyj szeregu Taylora lub funkcji `expm1()`.

3. Porównaj dokładność obliczeń dla typu `float` vs `double` vs `long double`.
