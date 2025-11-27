# Zajęcia nr 8 - Przybliżenia różnicowe pochodnych

## Zagadnienia do opanowania

Podstawy przybliżeń różnicowych dla pochodnych funkcji. Wyznaczanie błędów obcięcia przybliżeń.

---

## Zadanie 1: Dowód rzędu dokładności wzorów trzypunktowych

### Polecenie

Udowodnij, że jednostronne przybliżenia trzypunktowe na pierwszą pochodną w początkowym i końcowym węźle sieci jednorodnej $x_0, \ldots, x_n$ o kroku $h$, dane wzorami:

$$\left.\frac{df(x)}{dx}\right|_{x=x_0} \approx \frac{-\frac{3}{2}f(x_0) + 2f(x_1) - \frac{1}{2}f(x_2)}{h}$$

$$\left.\frac{df(x)}{dx}\right|_{x=x_n} \approx \frac{\frac{3}{2}f(x_n) - 2f(x_{n-1}) + \frac{1}{2}f(x_{n-2})}{h}$$

mają **dokładność drugiego rzędu**, tj. błąd obcięcia wynosi $O(h^2)$.

### Wskazówka

Rozwiń funkcje $f(x_1)$ i $f(x_2)$ w szereg Taylora wokół punktu $x_0$:

$$f(x_0 + h) = f(x_0) + h f'(x_0) + \frac{h^2}{2!} f''(x_0) + \frac{h^3}{3!} f'''(x_0) + \frac{h^4}{4!} f^{(4)}(\xi_1)$$

$$f(x_0 + 2h) = f(x_0) + 2h f'(x_0) + \frac{(2h)^2}{2!} f''(x_0) + \frac{(2h)^3}{3!} f'''(x_0) + \frac{(2h)^4}{4!} f^{(4)}(\xi_2)$$

gdzie $\xi_1, \xi_2 \in (x_0, x_2)$.

### Rozwiązanie (szkic)

Podstawiamy rozwinięcia do wzoru:

$$-\frac{3}{2}f(x_0) + 2f(x_1) - \frac{1}{2}f(x_2)$$

$$= -\frac{3}{2}f(x_0) + 2\left[f(x_0) + h f'(x_0) + \frac{h^2}{2} f''(x_0) + \frac{h^3}{6} f'''(x_0) + O(h^4)\right]$$

$$\quad - \frac{1}{2}\left[f(x_0) + 2h f'(x_0) + 2h^2 f''(x_0) + \frac{4h^3}{3} f'''(x_0) + O(h^4)\right]$$

Wyraz z $f(x_0)$:
$$-\frac{3}{2} + 2 - \frac{1}{2} = 0 \quad \checkmark$$

Wyraz z $f'(x_0)$:
$$2h - \frac{1}{2} \cdot 2h = 2h - h = h$$

Wyraz z $f''(x_0)$:
$$2 \cdot \frac{h^2}{2} - \frac{1}{2} \cdot 2h^2 = h^2 - h^2 = 0 \quad \checkmark$$

Wyraz z $f'''(x_0)$:
$$2 \cdot \frac{h^3}{6} - \frac{1}{2} \cdot \frac{4h^3}{3} = \frac{h^3}{3} - \frac{2h^3}{3} = -\frac{h^3}{3}$$

Zatem:

$$-\frac{3}{2}f(x_0) + 2f(x_1) - \frac{1}{2}f(x_2) = h f'(x_0) - \frac{h^3}{3} f'''(x_0) + O(h^4)$$

$$\frac{-\frac{3}{2}f(x_0) + 2f(x_1) - \frac{1}{2}f(x_2)}{h} = f'(x_0) - \frac{h^2}{3} f'''(x_0) + O(h^3)$$

Błąd obcięcia:
$$E = -\frac{h^2}{3} f'''(x_0) + O(h^3) = O(h^2)$$

**Wniosek**: Metoda ma dokładność **drugiego rzędu** $O(h^2)$.

---

## Zadanie 2: Dowód rzędu dokładności wzorów pięciopunktowych

### Polecenie

Udowodnij, że pięciopunktowe przybliżenia różnicowe na pierwszą i drugą pochodną w wewnętrznym węźle sieci jednorodnej $x_0, \ldots, x_n$ o kroku $h$:

**Pierwsza pochodna:**

$$\left.\frac{df(x)}{dx}\right|_{x=x_i} \approx \frac{\frac{1}{12}f(x_{i-2}) - \frac{2}{3}f(x_{i-1}) + \frac{2}{3}f(x_{i+1}) - \frac{1}{12}f(x_{i+2})}{h}$$

**Druga pochodna:**

$$\left.\frac{d^2f(x)}{dx^2}\right|_{x=x_i} \approx \frac{-\frac{1}{12}f(x_{i-2}) + \frac{4}{3}f(x_{i-1}) - \frac{5}{2}f(x_i) + \frac{4}{3}f(x_{i+1}) - \frac{1}{12}f(x_{i+2})}{h^2}$$

mają **dokładność czwartego rzędu**, tj. błąd obcięcia wynosi $O(h^4)$.

### Wskazówka

Rozwiń funkcje w szereg Taylora wokół $x_i$:

$$f(x_i \pm h) = f(x_i) \pm h f'(x_i) + \frac{h^2}{2!} f''(x_i) \pm \frac{h^3}{3!} f'''(x_i) + \frac{h^4}{4!} f^{(4)}(x_i) \pm \frac{h^5}{5!} f^{(5)}(\xi)$$

$$f(x_i \pm 2h) = f(x_i) \pm 2h f'(x_i) + \frac{4h^2}{2!} f''(x_i) \pm \frac{8h^3}{3!} f'''(x_i) + \frac{16h^4}{4!} f^{(4)}(x_i) \pm \frac{32h^5}{5!} f^{(5)}(\xi)$$

Dobierz współczynniki tak, aby:
- Eliminować wyrazy niepożądane
- Otrzymać pożądaną pochodną z najwyższą dokładnością

### Rozwiązanie dla pierwszej pochodnej (szkic)

Szukamy kombinacji:
$$\alpha f(x_{i-2}) + \beta f(x_{i-1}) + \gamma f(x_{i+1}) + \delta f(x_{i+2})$$

która aproksymuje $h f'(x_i)$ z błędem $O(h^5)$.

**Warunki:**

1. Współczynnik przy $f(x_i)$: $\alpha + \beta + \gamma + \delta = 0$
2. Współczynnik przy $f'(x_i)$: $-2\alpha - \beta + \gamma + 2\delta = 1$ (po podzieleniu przez $h$)
3. Współczynnik przy $f''(x_i)$: $4\alpha + \beta + \gamma + 4\delta = 0$ (eliminacja)
4. Współczynnik przy $f'''(x_i)$: $-8\alpha - \beta + \gamma + 8\delta = 0$ (eliminacja)

Rozwiązując układ równań:
$$\alpha = -\frac{1}{12}, \quad \beta = -\frac{2}{3}, \quad \gamma = \frac{2}{3}, \quad \delta = -\frac{1}{12}$$

Podstawowe wyrazy nieparzyste się redukują, pierwszy niezerowy to $O(h^4)$, więc błąd wynosi $O(h^4)$.

---

## Zadanie 3: Program numeryczny

### Polecenie

Napisz program w języku C++ obliczający przybliżone wartości pierwszych pochodnych funkcji:

$$f(x) = \cos(x)$$

w punktach końcowych i środkowym przedziału $\left[0, \frac{\pi}{2}\right]$ zmiennej $x$.

### Wymagania

1. **Zastosuj wszystkie omawiane przybliżenia różnicowe:**
   - Dwupunktowe do przodu i do tyłu (jednostronne, $O(h)$)
   - Trzypunktowe centralne ($O(h^2)$)
   - Trzypunktowe jednostronne na brzegach ($O(h^2)$)
   - Pięciopunktowe centralne ($O(h^4)$)

2. **Użyj szablonów funkcji** z typem zmiennych jako parametrem:
   ```cpp
   template <typename T>
   T forward_diff(T (*f)(T), T x, T h);
   ```

3. **Wykonaj obliczenia dla różnych kroków sieci** $h$ na sieci jednorodnej.

4. **Wykreśl zależność** $\log_{10}|\text{błąd}|$ od $\log_{10} h$ dla wszystkich metod.

5. **Wyznacz doświadczalnie rzędy dokładności** ze wzoru:
   $$p = \frac{\log|E(h_2)| - \log|E(h_1)|}{\log h_2 - \log h_1}$$

   gdzie $E(h)$ to błąd dla kroku $h$.

6. **Obliczenia wykonaj dla dwóch typów:**
   - `double` (64-bitowe)
   - `long double` (80 lub 128-bitowe, w zależności od platformy)

7. **Porównaj wyniki** obu typów i wyjaśnij różnice.

### Dokładna pochodna

Dla funkcji testowej:
$$f(x) = \cos(x) \implies f'(x) = -\sin(x)$$

### Pytania analityczne

Po wykonaniu obliczeń odpowiedz na następujące pytania:

1. **Czy doświadczalne rzędy dokładności zgadzają się z teoretycznymi?**
   - Dla metod $O(h)$ oczekujemy nachylenia ≈ 1
   - Dla metod $O(h^2)$ oczekujemy nachylenia ≈ 2
   - Dla metod $O(h^4)$ oczekujemy nachylenia ≈ 4

2. **Dla jakich wartości $h$ pojawiają się błędy maszynowe?**
   - Zidentyfikuj wartość $h$, poniżej której błąd zaczyna rosnąć
   - Wyjaśnij mechanizm powstawania błędów maszynowych (catastrophic cancellation)

3. **Jaka jest optymalna wartość $h$?**
   - Dla której wartości $h$ błąd całkowity jest minimalny?
   - Porównaj z teoretyczną wartością: $h_{opt} \sim \epsilon_{mach}^{1/(p+1)}$

4. **Czy `long double` daje lepsze wyniki?**
   - Porównaj dokładność i zakres $h$ dla obu typów
   - Kiedy warto używać `long double`?

5. **Która metoda jest najlepsza?**
   - Przy ustalonym $h$, która metoda daje najmniejszy błąd?
   - Jakie są zalety i wady poszczególnych metod?

### Przykładowe wartości do testowania

Testuj dla kroków:
$$h \in \{10^0, 10^{-1}, 10^{-2}, \ldots, 10^{-14}\}$$

Punkty testowe:
- $x_0 = 0$ (brzeg początkowy)
- $x = \frac{\pi}{4}$ (środek przedziału)
- $x_n = \frac{\pi}{2}$ (brzeg końcowy)

---

## Zadanie 4: Analiza błędów maszynowych

### Polecenie

Na podstawie wykresów i obliczeń numerycznych:

1. **Zidentyfikuj wartość krytyczną** $h_{crit}$, poniżej której błędy maszynowe zaczynają dominować nad błędem obcięcia.

2. **Wyjaśnij zjawisko** wzrostu błędu dla małych $h$.

3. **Wyprowadź teoretyczny wzór** na optymalny krok $h_{opt}$ minimalizujący błąd całkowity.

### Teoria

Całkowity błąd składa się z dwóch części:

$$E_{total}(h) = E_{truncation}(h) + E_{roundoff}(h)$$

**Błąd obcięcia** (maleje wraz z $h$):
$$E_{truncation} \sim C_1 h^p$$

gdzie $p$ to rząd metody.

**Błąd zaokrągleń** (rośnie dla małych $h$):
$$E_{roundoff} \sim \frac{C_2 \epsilon_{mach}}{h}$$

gdzie $\epsilon_{mach}$ to precyzja maszynowa:
- `double`: $\epsilon_{mach} \approx 2.22 \times 10^{-16}$
- `long double`: $\epsilon_{mach} \approx 1.08 \times 10^{-19}$ (80-bit) lub $\approx 1.93 \times 10^{-34}$ (128-bit)

### Zadanie

Znajdź minimum funkcji błędu całkowitego:

$$\frac{d E_{total}}{dh} = 0$$

i wyprowadź wzór na $h_{opt}$.

**Rozwiązanie teoretyczne:**

$$E_{total}(h) = C_1 h^p + \frac{C_2 \epsilon_{mach}}{h}$$

$$\frac{d E_{total}}{dh} = p C_1 h^{p-1} - \frac{C_2 \epsilon_{mach}}{h^2} = 0$$

$$p C_1 h^{p+1} = C_2 \epsilon_{mach}$$

$$h_{opt} = \left(\frac{C_2 \epsilon_{mach}}{p C_1}\right)^{1/(p+1)}$$

**Rzędy wielkości:**

- Dla metody $O(h)$: $h_{opt} \sim \epsilon_{mach}^{1/2} \approx 1.5 \times 10^{-8}$ (double)
- Dla metody $O(h^2)$: $h_{opt} \sim \epsilon_{mach}^{1/3} \approx 6.0 \times 10^{-6}$ (double)
- Dla metody $O(h^4)$: $h_{opt} \sim \epsilon_{mach}^{1/5} \approx 3.0 \times 10^{-4}$ (double)

---

## Zadanie 5: Porównanie typów zmiennych

### Polecenie

Wykonaj wszystkie obliczenia dla obu typów (`double` i `long double`) i porównaj:

1. **Minimalny osiągalny błąd** dla każdej metody
2. **Wartość $h_{crit}$**, poniżej której pojawiają się błędy maszynowe
3. **Zakres użytecznych wartości $h$**
4. **Koszt obliczeniowy** (czas wykonania)

### Tabela do wypełnienia

| Metoda | Typ | $h_{opt}$ | $E_{min}$ | $h_{crit}$ | Czas [ms] |
|--------|-----|-----------|-----------|------------|-----------|
| Forward 2pt | double | | | | |
| Forward 2pt | long double | | | | |
| Central 3pt | double | | | | |
| Central 3pt | long double | | | | |
| Central 5pt | double | | | | |
| Central 5pt | long double | | | | |

### Wnioski

Na podstawie wyników napisz wnioski dotyczące:
- Kiedy warto używać `long double`?
- Czy wyższa dokładność arytmetyki zawsze przekłada się na lepsze wyniki?
- Jakie są ograniczenia praktyczne?

---

## Literatura i materiały dodatkowe

1. **Burden, R. L., Faires, J. D.** - *Numerical Analysis* (rozdział o różnicowaniu numerycznym)
2. **Press, W. H. et al.** - *Numerical Recipes in C++* (rozdział 5: Evaluation of Functions)
3. **Quarteroni, A., Sacco, R., Saleri, F.** - *Numerical Mathematics* (rozdział 11: Numerical Differentiation and Integration)
4. **Kincaid, D., Cheney, W.** - *Numerical Analysis: Mathematics of Scientific Computing*

## Uwagi końcowe

- Przybliżenia różnicowe są wrażliwe na błędy zaokrągleń
- Wybór optymalnego $h$ wymaga kompromisu między dokładnością a stabilnością
- W praktyce często używa się metod automatycznego doboru kroku (adaptive step size)
- Dla złożonych problemów lepsze są metody różniczkowania automatycznego (automatic differentiation)
