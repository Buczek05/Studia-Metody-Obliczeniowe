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

## Uwarunkowanie i błąd względny obliczenia wartości funkcji \(f(x)=\ln(x)\)

Względny wskaźnik uwarunkowania definiujemy jako:

$$
\kappa(x)=\left|\frac{x f'(x)}{f(x)}\right|.
$$

Dla funkcji \( f(x)=\ln(x) \) mamy:

$$
f'(x)=\frac{1}{x}.
$$

Zatem:

$$
\kappa(x)=\left|\frac{x\cdot \frac{1}{x}}{\ln(x)}\right|
=\frac{1}{|\ln(x)|}.
$$

Zakładając względny błąd reprezentacji danych \(|\delta|\le u\)
(typowo \(u \approx 10^{-16}\) w podwójnej precyzji), względny błąd wyniku spełnia:

$$
\left|\frac{\Delta f}{f}\right|
\lesssim \kappa(x)\,u
= \frac{u}{|\ln(x)|}.
$$

---

## Ocena błędu względnego dla zadanych wartości

### 1. \(x = 1 + 10^{-15}\)

$$
\ln(1+10^{-15}) \approx 10^{-15},
\qquad
\kappa(x) \approx 10^{15},
$$

$$
\left|\frac{\Delta f}{f}\right|
\lesssim 10^{15}\cdot 10^{-16}
= 10^{-1}.
$$

Błąd względny: **≈ \(10^{-1}\)**.

---

### 2. \(x = 1 + 10^{-12}\)

$$
\ln(1+10^{-12}) \approx 10^{-12},
\qquad
\kappa(x) \approx 10^{12},
$$

$$
\left|\frac{\Delta f}{f}\right|
\lesssim 10^{12}\cdot 10^{-16}
= 10^{-4}.
$$

Błąd względny: **≈ \(10^{-4}\)**.

---

### 3. \(x = 1 + 10^{-10}\)

$$
\ln(1+10^{-10}) \approx 10^{-10},
\qquad
\kappa(x) \approx 10^{10},
$$

$$
\left|\frac{\Delta f}{f}\right|
\lesssim 10^{10}\cdot 10^{-16}
= 10^{-6}.
$$

Błąd względny: **≈ \(10^{-6}\)**.

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
