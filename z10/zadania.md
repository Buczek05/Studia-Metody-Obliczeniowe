# Zajęcia nr 10 - Metody numeryczne rozwiązywania równań różniczkowych zwyczajnych

## Zagadnienia do opanowania

Metody różnicowe rozwiązywania zagadnień z warunkiem początkowym dla równań różniczkowych zwyczajnych pierwszego rzędu. Metody bezpośrednie i pośrednie a kwestia stabilności numerycznej. Metody: bezpośrednia Eulera, pośrednia Eulera, trapezów.

---

## Zadanie 1 - Analiza stabilności metod numerycznych

Dane jest równanie różniczkowe zwyczajne pierwszego rzędu:

$$y'(t) + \frac{100t + 10}{t + 1}(y(t) - 1) = 0$$

określone dla zmiennej $t \geq 0$, z warunkiem początkowym $y(0) = 2$.

### Część a) Określenie typu równania

Przekształćmy równanie do postaci standardowej:

$$y'(t) = -\frac{100t + 10}{t + 1}(y(t) - 1)$$

Niech $p(t) = \frac{100t + 10}{t + 1}$. Dla $t \geq 0$:
- $p(0) = 10$
- $\lim_{t \to \infty} p(t) = 100$
- $p(t) > 0$ dla wszystkich $t \geq 0$

Równanie można zapisać jako:
$$y'(t) = -p(t) \cdot (y - 1)$$

To jest równanie **rozpadu** (decay) z punktem równowagi w $y = 1$. Rozwiązanie dąży asymptotycznie do wartości $y = 1$.

### Część b) Warunki stabilności dla różnych metod

Zbadaj, jakie warunki muszą być spełnione przez krok czasowy $\Delta t$, aby metody były stabilne:

#### (a) Metoda bezpośrednia Eulera

Schemat metody:
$$y_{n+1} = y_n + \Delta t \cdot f(t_n, y_n)$$

Dla naszego równania:
$$y_{n+1} = y_n - \Delta t \cdot p(t_n) \cdot (y_n - 1)$$

**Warunek stabilności**: Metoda Eulera bezpośrednia jest stabilna, gdy:
$$\left|1 - \Delta t \cdot p(t_n)\right| \leq 1$$

Co daje:
$$\Delta t \leq \frac{2}{p(t_n)}$$

Dla $t \to \infty$: $\Delta t \leq \frac{2}{100} = 0.02$

Dla $t = 0$: $\Delta t \leq \frac{2}{10} = 0.2$

**Wniosek**: Metoda jest **warunkowo stabilna** - wymaga $\Delta t \leq 0.02$ dla stabilności w całym przedziale.

#### (b) Metoda pośrednia Eulera

Schemat metody:
$$y_{n+1} = y_n + \Delta t \cdot f(t_{n+1}, y_{n+1})$$

Dla naszego równania:
$$y_{n+1} = y_n - \Delta t \cdot p(t_{n+1}) \cdot (y_{n+1} - 1)$$

Rozwiązując względem $y_{n+1}$:
$$y_{n+1}(1 + \Delta t \cdot p(t_{n+1})) = y_n + \Delta t \cdot p(t_{n+1})$$
$$y_{n+1} = \frac{y_n + \Delta t \cdot p(t_{n+1})}{1 + \Delta t \cdot p(t_{n+1})}$$

**Warunek stabilności**: Współczynnik przy $y_n$ to:
$$\frac{1}{1 + \Delta t \cdot p(t_{n+1})} < 1$$

Ponieważ $p(t) > 0$ i $\Delta t > 0$, metoda jest **bezwarunkowo stabilna** dla $\Delta t > 0$.

#### (c) Metoda trapezów

Schemat metody:
$$y_{n+1} = y_n + \frac{\Delta t}{2}[f(t_n, y_n) + f(t_{n+1}, y_{n+1})]$$

Dla naszego równania:
$$y_{n+1} = y_n - \frac{\Delta t}{2}[p(t_n)(y_n - 1) + p(t_{n+1})(y_{n+1} - 1)]$$

Rozwiązując względem $y_{n+1}$:
$$y_{n+1}\left(1 + \frac{\Delta t}{2}p(t_{n+1})\right) = y_n\left(1 - \frac{\Delta t}{2}p(t_n)\right) + \frac{\Delta t}{2}[p(t_n) + p(t_{n+1})]$$

**Warunek stabilności**: Metoda trapezów jest **bezwarunkowo stabilna** dla równań z $p(t) > 0$.

### Podsumowanie stabilności

| Metoda | Typ stabilności | Warunek |
|--------|----------------|---------|
| Bezpośrednia Eulera | Warunkowo stabilna | $\Delta t \leq 0.02$ |
| Pośrednia Eulera | Bezwarunkowo stabilna | $\Delta t > 0$ dowolne |
| Trapezów | Bezwarunkowo stabilna | $\Delta t > 0$ dowolne |

---

## Zadanie 2 - Analiza dodatkowych równań

Przeprowadź analogiczną analizę dla następujących równań różniczkowych zwyczajnych określonych dla $t \geq 0$:

### Równanie 2a
$$y'(t) + 2t + 3y(t) = 0, \quad y(0) = y_0$$

**Typ**: Równanie z czasowo zmiennym współczynnikiem

**Postać standardowa**: $y'(t) = -3y(t) - 2t$

**Analiza stabilności**:
- Metoda Eulera bezpośrednia: $\Delta t \leq \frac{2}{3}$
- Metody pośrednie: bezwarunkowo stabilne

### Równanie 2b
$$y'(t) + 2t - 3y(t) = 0, \quad y(0) = y_0$$

**Typ**: Równanie wzrostu (współczynnik ujemny przy $y$)

**Postać standardowa**: $y'(t) = 3y(t) - 2t$

**Uwaga**: To równanie jest **niestabilne** - rozwiązania rosną wykładniczo!

**Analiza stabilności**:
- Metoda Eulera bezpośrednia: **niestabilna** dla większości kroków
- Metody pośrednie: lepsze, ale wciąż problematyczne dla równań wzrostu

### Równanie 2c
$$y'(t) - 3(1 + t)y(t) = 0, \quad y(0) = y_0$$

**Typ**: Równanie wzrostu

**Postać standardowa**: $y'(t) = 3(1 + t)y(t)$

**Rozwiązanie analityczne**: $y(t) = y_0 \exp\left(3t + \frac{3t^2}{2}\right)$ - silny wzrost wykładniczy

### Równanie 2d
$$y'(t) + (1 + t^2)y(t) = 0, \quad y(0) = y_0$$

**Typ**: Równanie rozpadu

**Postać standardowa**: $y'(t) = -(1 + t^2)y(t)$

**Rozwiązanie analityczne**: $y(t) = y_0 \exp\left(-t - \frac{t^3}{3}\right)$

**Analiza stabilności**:
- Metoda Eulera bezpośrednia: $\Delta t \leq \frac{2}{1 + t^2}$, więc dla $t = 0$: $\Delta t \leq 2$
- Metody pośrednie: bezwarunkowo stabilne

---

## Rozwiązanie analityczne dla Zadania 1

Równanie:
$$y'(t) = -\frac{100t + 10}{t + 1}(y - 1)$$

Rozwiązanie analityczne podane w zadaniu:
$$y(t) = 1 + (1 + t)^{90} e^{-100t}$$

Weryfikacja warunku początkowego:
$$y(0) = 1 + 1^{90} \cdot e^0 = 1 + 1 = 2 \quad \checkmark$$

---

## Program - wymagania

Napisz program w C++ rozwiązujący równanie z Zadania 1 za pomocą trzech metod:

1. **Metoda bezpośrednia Eulera**
2. **Metoda pośrednia Eulera**
3. **Metoda trapezów**

### Wymagania dotyczące wykresów

#### Dla metody bezpośredniej Eulera (3 wykresy):
1. Warunki **numerycznej stabilności** (mały krok, np. $\Delta t = 0.01$)
2. Warunki **numerycznej niestabilności** (duży krok, np. $\Delta t = 0.05$)
3. Przypadek **pośredni** (krok graniczny, np. $\Delta t = 0.02$)

#### Dla metod pośredniej Eulera i trapezów (po 2 wykresy każda):
1. Rozwiązanie **numeryczne** (punkty)
2. Rozwiązanie **analityczne** (linia ciągła)

Oba wykresy na jednym rysunku dla porównania.

### Analiza błędów

Wykonaj wykres zależności $\log_{10}|\text{błąd}|$ od $\log_{10}(\Delta t)$ dla wszystkich trzech metod.

**Teoretyczne rzędy dokładności**:
- Metoda Eulera bezpośrednia: rząd 1 (nachylenie = 1)
- Metoda Eulera pośrednia: rząd 1 (nachylenie = 1)
- Metoda trapezów: rząd 2 (nachylenie = 2)

Zidentyfikuj wartości kroku, poniżej których widoczny jest wpływ błędów maszynowych (odchylenie od linii prostej).
