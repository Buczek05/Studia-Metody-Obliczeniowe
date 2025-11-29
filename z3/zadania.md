# Zajęcia nr 3 - Metody rozwiązywania nieliniowych równań algebraicznych

## Zagadnienia do opanowania

- Metody rozwiązywania nieliniowych równań algebraicznych: Picarda, bisekcji, regula falsi, Newtona, siecznych
- Zbieżność metod iteracyjnych

---

## Zadania

### Zadanie 1: Ocena zbieżności metody iteracyjnej Picarda
## Ocena zbieżności metody Picarda

Metoda Picarda ma postać
$$
x_{k+1} = \varphi(x_k),
$$
a zbieżność na przedziale \(I\) zapewnia warunek:
- \(\varphi(I)\subset I\),
- istnieje \(q<1\) takie, że \(|\varphi'(x)|\le q\) dla wszystkich \(x\in I\).

---

### a) Równanie $\tanh(x)+2(x-1)=0$

Przekształcamy równanie:
$$
\tanh(x) + 2(x-1)=0
\iff \tanh(x)=2(1-x)
\iff x = 1 - \frac{1}{2}\tanh(x).
$$

Wybieramy
$$
\varphi(x)=1-\frac{1}{2}\tanh(x),
\qquad
x_{k+1} = 1 - \frac{1}{2}\tanh(x_k).
$$

Pochodna:
$$
\varphi'(x) = -\frac{1}{2}\operatorname{sech}^2(x),
$$
gdzie $0<\operatorname{sech}^2(x)\le 1$. Zatem
$$
|\varphi'(x)| = \frac{1}{2}\operatorname{sech}^2(x)\le \frac{1}{2}<1
\quad\text{dla każdego }x\in\mathbb{R}.
$$

Ponieważ $\tanh(x)\in(-1,1)$, to
$$
\varphi(x)=1-\frac{1}{2}\tanh(x)\in(0.5,1.5),
$$
czyli np. \(I=[0.5,1.5]\) jest niezmienniczy: $\varphi(I)\subset I$.

**Wniosek:** iteracja Picarda z tą $\varphi$ jest zbieżna (kontrakcja z $q\le \tfrac12$).

---

### b) Równanie $\sinh(x)+\frac{x}{4}-1=0$

Przekształcamy:
$$
\sinh(x)+\frac{x}{4}-1=0
\iff \sinh(x)=1-\frac{x}{4}
\iff x = \operatorname{arsinh}\!\left(1-\frac{x}{4}\right).
$$

Wybieramy
$$
\varphi(x)=\operatorname{arsinh}\!\left(1-\frac{x}{4}\right),
\qquad
x_{k+1} = \operatorname{arsinh}\!\left(1-\frac{x_k}{4}\right).
$$

Pochodna:
$$
\varphi'(x)
= -\frac{1}{4\sqrt{1+\left(1-\frac{x}{4}\right)^2}}.
$$

Stąd
$$
|\varphi'(x)|
= \frac{1}{4\sqrt{1+\left(1-\frac{x}{4}\right)^2}}
\le \frac{1}{4}<1
\quad\text{dla każdego }x.
$$

**Wniosek:** iteracja Picarda dla tej postaci jest również zbieżna (kontrakcja z $q\le \tfrac14$).

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
