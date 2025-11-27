# Pytania kontrolne i ćwiczenia dodatkowe

## Pytania teoretyczne

### 1. Podstawy stabilności numerycznej

**Q1.1**: Co to jest stabilność numeryczna metody rozwiązywania równań różniczkowych?

<details>
<summary>Odpowiedź</summary>

Stabilność numeryczna to właściwość metody numerycznej, przy której małe zaburzenia (błędy zaokrągleń, błędy w danych początkowych) nie narastają w sposób niekontrolowany w trakcie obliczeń. Metoda stabilna daje rozwiązania, które pozostają blisko rozwiązania dokładnego.

Rozróżniamy:
- **Stabilność bezwzględną**: błędy nie rosną w wartości bezwzględnej
- **Stabilność względną**: błędy nie rosną szybciej niż rozwiązanie
</details>

---

**Q1.2**: Jaka jest różnica między stabilnością metody a stabilnością problemu?

<details>
<summary>Odpowiedź</summary>

- **Stabilność problemu** (well-conditioning): czy małe zmiany w danych wejściowych prowadzą do małych zmian w rozwiązaniu (właściwość równania różniczkowego)

- **Stabilność metody numerycznej**: czy metoda numeryczna zachowuje się stabilnie dla danego problemu (właściwość algorytmu)

Przykład: równanie $y' = -1000y$ jest dobrze uwarunkowane (stabilne), ale metoda Eulera bezpośrednia będzie niestabilna dla $dt > 0.002$.
</details>

---

### 2. Metody bezpośrednie vs pośrednie

**Q2.1**: Dlaczego metody pośrednie (implicit) są zazwyczaj bardziej stabilne niż bezpośrednie (explicit)?

<details>
<summary>Odpowiedź</summary>

W metodach pośrednich wartość $y_{n+1}$ pojawia się po obu stronach równania:
$$y_{n+1} = y_n + \Delta t \cdot f(t_{n+1}, y_{n+1})$$

Wymaga to rozwiązania równania (często nieliniowego), ale wprowadza naturalny mechanizm "sprzężenia zwrotnego", który tłumi oscylacje i zapobiega narastaniu błędów.

W metodach bezpośrednich:
$$y_{n+1} = y_n + \Delta t \cdot f(t_n, y_n)$$

Wartość następna zależy tylko od wartości obecnej, co może prowadzić do narastania błędów dla dużych kroków.
</details>

---

**Q2.2**: Jaki jest koszt obliczeniowy metod pośrednich w porównaniu do bezpośrednich?

<details>
<summary>Odpowiedź</summary>

Metody pośrednie są **droższe obliczeniowo**, ponieważ:
1. Wymagają rozwiązania równania (często nieliniowego) w każdym kroku
2. Mogą wymagać iteracji (np. metoda Newtona, iteracja punktu stałego)
3. Dla układów równań: rozwiązanie układu równań liniowych

**Trade-off**: Większy koszt na krok, ale możliwość użycia większych kroków czasowych dzięki lepszej stabilności.
</details>

---

### 3. Rząd dokładności

**Q3.1**: Co oznacza, że metoda ma rząd dokładności $p$?

<details>
<summary>Odpowiedź</summary>

Metoda ma rząd dokładności $p$, jeśli błąd lokalny (w jednym kroku) wynosi:
$$\text{Błąd lokalny} = O(\Delta t^{p+1})$$

a błąd globalny (po wielu krokach) wynosi:
$$\text{Błąd globalny} = O(\Delta t^p)$$

Oznacza to, że przy zmniejszeniu kroku dwukrotnie ($\Delta t \to \Delta t/2$):
- Błąd zmniejsza się $2^p$ razy

**Przykłady**:
- Euler: $p=1$ → błąd $\sim \Delta t$
- Trapezów: $p=2$ → błąd $\sim \Delta t^2$
- RK4: $p=4$ → błąd $\sim \Delta t^4$
</details>

---

**Q3.2**: Dlaczego metoda trapezów ma rząd 2, a metody Eulera rząd 1?

<details>
<summary>Odpowiedź</summary>

Wynika to z rozwinięcia Taylora.

**Euler bezpośrednia**:
$$y_{n+1} = y_n + \Delta t \cdot y'(t_n)$$

Rozwinięcie Taylora:
$$y(t_{n+1}) = y(t_n) + \Delta t \cdot y'(t_n) + \frac{\Delta t^2}{2} y''(t_n) + O(\Delta t^3)$$

Błąd lokalny: $O(\Delta t^2)$ → rząd metody: 1

**Metoda trapezów**:
$$y_{n+1} = y_n + \frac{\Delta t}{2}[y'(t_n) + y'(t_{n+1})]$$

Ta metoda uwzględnia średnią z pochodnych w dwóch punktach, co anuluje człon $O(\Delta t^2)$ w rozwinięciu Taylora.

Błąd lokalny: $O(\Delta t^3)$ → rząd metody: 2
</details>

---

### 4. Analiza stabilności von Neumanna

**Q4.1**: Co to jest analiza stabilności von Neumanna?

<details>
<summary>Odpowiedź</summary>

Analiza stabilności von Neumanna (test amplifikacji) bada, jak błędy narastają w kolejnych krokach czasowych.

Dla równania testowego $y' = \lambda y$, metoda numeryczna ma postać:
$$y_{n+1} = A(\lambda, \Delta t) \cdot y_n$$

gdzie $A$ to **współczynnik amplifikacji**.

**Warunek stabilności**: $|A(\lambda, \Delta t)| \leq 1$

**Przykłady**:
- Euler explicit: $A = 1 + \lambda \Delta t$ → stabilne gdy $|1 + \lambda \Delta t| \leq 1$
- Euler implicit: $A = \frac{1}{1 - \lambda \Delta t}$ → zawsze stabilne dla $\text{Re}(\lambda) < 0$
</details>

---

## Zadania rachunkowe

### Zadanie 1: Analiza stabilności

Dla równania $y' = -5y$, $y(0) = 1$, zbadaj stabilność metody Eulera bezpośredniej.

a) Znajdź warunek na $\Delta t$ zapewniający stabilność
b) Wykonaj 10 kroków dla $\Delta t = 0.3$ i porównaj z rozwiązaniem analitycznym
c) Powtórz dla $\Delta t = 0.5$

<details>
<summary>Rozwiązanie</summary>

**a) Warunek stabilności**:

Dla $y' = \lambda y$ z $\lambda = -5$:
$$|1 + \lambda \Delta t| \leq 1$$
$$|1 - 5\Delta t| \leq 1$$
$$-1 \leq 1 - 5\Delta t \leq 1$$
$$0 \leq 5\Delta t \leq 2$$
$$\Delta t \leq 0.4$$

**b) $\Delta t = 0.3$ (stabilne)**:
- Współczynnik amplifikacji: $A = 1 - 5 \cdot 0.3 = -0.5$
- Po 10 krokach: $y_{10} = (-0.5)^{10} \approx 0.00098$
- Rozwiązanie dokładne: $y(3) = e^{-15} \approx 3.06 \times 10^{-7}$
- Rozwiązanie oscyluje (zmiana znaku), ale jest ograniczone

**c) $\Delta t = 0.5$ (niestabilne)**:
- Współczynnik amplifikacji: $A = 1 - 5 \cdot 0.5 = -1.5$
- $|A| = 1.5 > 1$ → niestabilne!
- Po 10 krokach: $y_{10} = (-1.5)^{10} \approx 57.7$
- Rozwiązanie rozbieżne (eksploduje)
</details>

---

### Zadanie 2: Porównanie metod

Rozwiąż równanie $y' + 2y = 0$, $y(0) = 3$ na przedziale $[0, 2]$ trzema metodami z krokiem $\Delta t = 0.5$.

a) Metoda Eulera bezpośrednia
b) Metoda Eulera pośrednia
c) Metoda trapezów

Porównaj wyniki z rozwiązaniem analitycznym $y(t) = 3e^{-2t}$.

<details>
<summary>Rozwiązanie</summary>

**Rozwiązanie analityczne**:
- $y(0.5) = 3e^{-1} \approx 1.1036$
- $y(1.0) = 3e^{-2} \approx 0.4060$
- $y(1.5) = 3e^{-3} \approx 0.1494$
- $y(2.0) = 3e^{-4} \approx 0.0550$

**a) Euler bezpośrednia**: $y_{n+1} = y_n - 2\Delta t \cdot y_n = (1 - 2\Delta t) y_n = 0 \cdot y_n$

Dla $\Delta t = 0.5$: $y_{n+1} = 0$ dla wszystkich $n \geq 1$!

Uwaga: Metoda jest na granicy stabilności.

**b) Euler pośrednia**: $y_{n+1} = \frac{y_n}{1 + 2\Delta t} = \frac{y_n}{2}$

- $y_1 = 1.5$
- $y_2 = 0.75$
- $y_3 = 0.375$
- $y_4 = 0.1875$

**c) Trapezów**: $y_{n+1} = \frac{1 - \Delta t}{1 + \Delta t} y_n = \frac{0.5}{1.5} y_n = \frac{1}{3} y_n$

- $y_1 = 1.0$
- $y_2 = 0.333$
- $y_3 = 0.111$
- $y_4 = 0.037$

Najlepsza metoda: **trapezów** (najbliższe wartościom dokładnym).
</details>

---

### Zadanie 3: Równanie z rozwiązaniem oscylacyjnym

Rozważ równanie $y'' + 4y = 0$, $y(0) = 1$, $y'(0) = 0$.

Sprowadź je do układu równań pierwszego rzędu i rozwiąż numerycznie.

<details>
<summary>Rozwiązanie</summary>

**Sprowadzenie do układu**:

Niech $y_1 = y$, $y_2 = y'$. Wtedy:
$$\begin{cases}
y_1' = y_2 \\
y_2' = -4y_1
\end{cases}$$

z warunkami $y_1(0) = 1$, $y_2(0) = 0$.

**Rozwiązanie analityczne**:
$$y(t) = \cos(2t)$$

**Metoda Eulera**:
$$\begin{cases}
y_{1,n+1} = y_{1,n} + \Delta t \cdot y_{2,n} \\
y_{2,n+1} = y_{2,n} - 4\Delta t \cdot y_{1,n}
\end{cases}$$

Dla równań oscylacyjnych metoda Eulera jest **niestabilna** dla większości kroków!

Trzeba użyć metod zachowujących energię (symplectic integrators) lub bardzo małych kroków.
</details>

---

## Ćwiczenia programistyczne

### Ćwiczenie 1: Implementacja RK4

Zaimplementuj metodę Runge-Kutty 4-go rzędu (RK4) dla równania z zadania 1 programu.

**Wzory**:
$$\begin{align}
k_1 &= f(t_n, y_n) \\
k_2 &= f(t_n + \Delta t/2, y_n + \Delta t \cdot k_1/2) \\
k_3 &= f(t_n + \Delta t/2, y_n + \Delta t \cdot k_2/2) \\
k_4 &= f(t_n + \Delta t, y_n + \Delta t \cdot k_3) \\
y_{n+1} &= y_n + \frac{\Delta t}{6}(k_1 + 2k_2 + 2k_3 + k_4)
\end{align}$$

Porównaj dokładność z metodą trapezów.

---

### Ćwiczenie 2: Adaptacyjny dobór kroku

Zaimplementuj algorytm adaptacyjnego doboru kroku czasowego oparty na szacowaniu błędu lokalnego.

**Algorytm**:
1. Wykonaj krok z $\Delta t$ metodą rzędu $p$
2. Wykonaj krok z $\Delta t$ metodą rzędu $p+1$
3. Oszacuj błąd: $e = |y^{(p+1)} - y^{(p)}|$
4. Jeśli $e < \text{TOL}$: akceptuj krok, zwiększ $\Delta t$
5. Jeśli $e > \text{TOL}$: odrzuć krok, zmniejsz $\Delta t$

---

### Ćwiczenie 3: Równanie sztywne

Rozwiąż numerycznie równanie sztywne (stiff equation):
$$y' = -1000(y - \cos(t)) - \sin(t), \quad y(0) = 1$$

Rozwiązanie dokładne: $y(t) = \cos(t)$

a) Sprawdź, jak zachowuje się metoda Eulera bezpośrednia
b) Porównaj z metodą Eulera pośrednią
c) Wyjaśnij różnicę w stabilności

---

## Pytania otwarte

1. **Kiedy warto użyć metod pośrednich mimo większego kosztu obliczeniowego?**

2. **Dlaczego dla równań oscylacyjnych (typu $y'' + \omega^2 y = 0$) zwykłe metody są często nieefektywne?**

3. **Co to są równania sztywne (stiff equations) i dlaczego wymagają specjalnych metod?**

4. **Jak błędy maszynowe wpływają na rozwiązania dla bardzo małych kroków czasowych?**

5. **Czy metoda o wyższym rzędzie dokładności jest zawsze lepsza?**

---

## Zadania do samodzielnego rozwiązania

### Zadanie A: Van der Pol oscillator

Rozwiąż numerycznie równanie van der Pola:
$$y'' - \mu(1 - y^2)y' + y = 0$$

dla $\mu = 1$, z warunkami $y(0) = 2$, $y'(0) = 0$.

### Zadanie B: Równanie logistyczne

Rozwiąż równanie logistyczne:
$$y' = r \cdot y(1 - y/K), \quad y(0) = y_0$$

dla $r = 0.5$, $K = 100$, $y_0 = 10$ na przedziale $[0, 20]$.

Porównaj z rozwiązaniem analitycznym.

### Zadanie C: Układ drapieżnik-ofiara

Rozwiąż układ równań Lotki-Volterry:
$$\begin{cases}
x' = ax - bxy \\
y' = -cy + dxy
\end{cases}$$

dla $a=1$, $b=0.1$, $c=1.5$, $d=0.075$, z warunkami $x(0)=10$, $y(0)=5$.

Narysuj trajektorię w przestrzeni fazowej $(x, y)$.

---

## Literatura dodatkowa

1. **Numerical Recipes** - Press et al.
   - Rozdział 17: Integration of Ordinary Differential Equations

2. **Numerical Analysis** - Burden & Faires
   - Rozdział 5: Initial-Value Problems for ODEs

3. **A First Course in Numerical Methods** - Greif & Ascher
   - Rozdział 8: Differential Equations

4. **Solving Ordinary Differential Equations I: Nonstiff Problems** - Hairer, Nørsett, Wanner

5. **Solving Ordinary Differential Equations II: Stiff and Differential-Algebraic Problems** - Hairer & Wanner
