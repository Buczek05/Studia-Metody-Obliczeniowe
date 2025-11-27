# Zajęcia nr 3 - Metody rozwiązywania nieliniowych równań algebraicznych

## Zagadnienia do opanowania

- Metody rozwiązywania nieliniowych równań algebraicznych: Picarda, bisekcji, regula falsi, Newtona, siecznych
- Zbieżność metod iteracyjnych

---

## Zadania

### Zadanie 1: Ocena zbieżności metody iteracyjnej Picarda

Oceń zbieżność metody iteracyjnej Picarda w zastosowaniu do równań nieliniowych:

**a)** $\sinh(x) + \frac{x}{4} - 1 = 0$

**b)** $\tanh(x) + 2(x - 1) = 0$

#### Metoda Picarda - przypomnienie

Metoda Picarda polega na przekształceniu równania $f(x) = 0$ do postaci $x = g(x)$ i iterowaniu według wzoru:

$$x_{n+1} = g(x_n)$$

#### Warunek zbieżności

Metoda Picarda jest zbieżna w otoczeniu pierwiastka $x^*$, jeśli:

$$|g'(x)| < 1$$

w tym otoczeniu.

#### Rozwiązanie a) $\sinh(x) + \frac{x}{4} - 1 = 0$

Możliwe przekształcenia do postaci $x = g(x)$:

1. $x = 4(1 - \sinh(x))$
   - Wtedy $g(x) = 4(1 - \sinh(x))$
   - $g'(x) = -4\cosh(x)$

2. $x = \sinh^{-1}(1 - \frac{x}{4})$ (o ile $1 - \frac{x}{4} > 0$)
   - Wtedy $g(x) = \sinh^{-1}(1 - \frac{x}{4})$
   - $g'(x) = \frac{-1/4}{\sqrt{1 + (1 - x/4)^2}}$

**Analiza zbieżności:**

Dla pierwszego przekształcenia: $|g'(x)| = 4|\cosh(x)| \geq 4 > 1$ dla każdego $x$, więc metoda **nie jest zbieżna**.

Dla drugiego przekształcenia: $|g'(x)| = \frac{1}{4\sqrt{1 + (1 - x/4)^2}} < \frac{1}{4} < 1$ w otoczeniu pierwiastka, więc metoda **jest zbieżna**.

#### Rozwiązanie b) $\tanh(x) + 2(x - 1) = 0$

Możliwe przekształcenia:

1. $x = 1 - \frac{\tanh(x)}{2}$
   - Wtedy $g(x) = 1 - \frac{\tanh(x)}{2}$
   - $g'(x) = -\frac{1}{2\cosh^2(x)}$

2. $x = \tanh^{-1}(2 - 2x)$ (o ile $|2 - 2x| < 1$)
   - Wtedy $g(x) = \tanh^{-1}(2 - 2x)$
   - $g'(x) = \frac{-2}{1 - (2 - 2x)^2}$

**Analiza zbieżności:**

Dla pierwszego przekształcenia: $|g'(x)| = \frac{1}{2\cosh^2(x)} \leq \frac{1}{2} < 1$ dla każdego $x$, więc metoda **jest zbieżna**.

Dla drugiego przekształcenia: warunek zbieżności zależy od punktu startowego i pierwiastka.

---

### Zadanie 2: Algorytm Herona jako metoda Newtona

Pokaż, że tzw. algorytm Herona, służący do obliczania pierwiastka kwadratowego z liczby rzeczywistej $a$ w oparciu o wzory:

$$\sqrt{a} = \lim_{n \to \infty} x_n \quad \text{gdzie} \quad x_n = \frac{1}{2}\left(x_{n-1} + \frac{a}{x_{n-1}}\right)$$

może być interpretowany jako algorytm Newtona zastosowany do pewnego równania nieliniowego.

#### Rozwiązanie

Szukamy równania $f(x) = 0$, którego rozwiązaniem jest $\sqrt{a}$.

Naturalne równanie to:
$$f(x) = x^2 - a = 0$$

Metoda Newtona ma postać:
$$x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}$$

Dla $f(x) = x^2 - a$:
- $f'(x) = 2x$

Podstawiając:
$$x_{n+1} = x_n - \frac{x_n^2 - a}{2x_n} = x_n - \frac{x_n}{2} + \frac{a}{2x_n} = \frac{x_n}{2} + \frac{a}{2x_n}$$

$$x_{n+1} = \frac{1}{2}\left(x_n + \frac{a}{x_n}\right)$$

**Wniosek:** Algorytm Herona jest dokładnie metodą Newtona zastosowaną do równania $f(x) = x^2 - a = 0$.

---

## Program

Napisz program w języku C++, realizujący metody:

- **(a)** Picarda
- **(b)** Bisekcji
- **(c)** Newtona
- **(d)** Siecznych

rozwiązywania pojedynczych algebraicznych równań nieliniowych.

### Wymagania programu:

1. Zastosuj program do przykładów z zadania 1
2. Zastosuj **trzy niezależne kryteria zakończenia iteracji**:
   - Maksymalna liczba iteracji
   - $|x_{n+1} - x_n| < \varepsilon$ (estymator błędu)
   - $|f(x_n)| < \delta$ (residuum)

3. Wyprowadzaj na konsolę wyniki pośrednie dla każdej iteracji:
   - Numer iteracji
   - Aktualne przybliżenie $x_n$
   - Wartość funkcji $f(x_n)$ (residuum)
   - Estymator błędu $|x_{n+1} - x_n|$

4. Umożliw porównanie:
   - Szybkości zbieżności różnych metod
   - Liczby iteracji potrzebnych do osiągnięcia zadanej dokładności
   - Zachowania estymatora błędu i residuum w trakcie iteracji

### Wskazówki:

- Dla metody Picarda należy odpowiednio przekształcić równanie do postaci $x = g(x)$
- Dla metody bisekcji potrzebne są dwa punkty początkowe $[a, b]$ takie, że $f(a) \cdot f(b) < 0$
- Dla metody Newtona potrzebna jest pochodna funkcji $f'(x)$
- Dla metody siecznych potrzebne są dwa punkty początkowe $x_0$ i $x_1$

### Pytania do analizy wyników:

1. Która metoda zbiega najszybciej dla zadanych równań?
2. Jak zmienia się estymator błędu i residuum w kolejnych iteracjach?
3. Czy metoda Picarda zbiega dla obu równań? Dlaczego?
4. Jaki wpływ ma wybór punktu startowego na zbieżność poszczególnych metod?
