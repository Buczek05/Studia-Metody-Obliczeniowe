# Zajęcia nr 9: Metody różnicowe dla równań różniczkowych drugiego rzędu

## Zagadnienia do opanowania

Metody różnicowe rozwiązywania zagadnień z warunkami brzegowymi dla równań różniczkowych zwyczajnych 2-go rzędu.

---

## Zadanie 1: Rozwiązanie równania różniczkowego metodą różnicową

Dane jest równanie różniczkowe zwyczajne drugiego rzędu:

$$x^2 u''(x) + (2 - x^2) u'(x) - x u(x) + 4 = 0$$

określone na przedziale $x \in [0,2]$, oraz warunki brzegowe:

$$u(0) = 1, \quad u(2) = 3$$

Mając daną jednorodną siatkę węzłów: $x_0 = 0$, $x_1 = 1$, $x_2 = 2$, **wyznacz przybliżone rozwiązanie równania w punkcie $x = 1$**, przy zastosowaniu centralnych przybliżeń różnicowych na pochodne.

### Wskazówki:

Dla centralnych przybliżeń różnicowych drugiego rzędu dokładności:

$$u'(x_i) \approx \frac{u_{i+1} - u_{i-1}}{2h}$$

$$u''(x_i) \approx \frac{u_{i-1} - 2u_i + u_{i+1}}{h^2}$$

gdzie $h$ jest krokiem siatki.

---

## Zadanie 2: Analiza dokładności schematów różnicowych

Dane jest częściowo nieliniowe równanie różniczkowe zwyczajne drugiego rzędu, o postaci:

$$\frac{d^2U(x)}{dx^2} - F(x, U(x)) = 0$$

### Część (a): Schemat konwencjonalny

Udowodnij, że konwencjonalny schemat różnicowy:

$$\frac{u_{i-1} - 2u_i + u_{i+1}}{h^2} - F(x_i, u_i) = 0$$

**aproksymuje to równanie z dokładnością drugiego rzędu** na sieci jednorodnej o kroku $h$.

**Wskazówka:** Rozwiń $u(x)$ w szereg Taylora wokół punktu $x_i$ i pokaż, że główny człon błędu lokalnej dyskretyzacji jest proporcjonalny do $h^2$.

### Część (b): Schemat Numerowa

Natomiast schemat różnicowy **B. Numerowa**:

$$\frac{u_{i-1} - 2u_i + u_{i+1}}{h^2} - \left[\frac{1}{12}F(x_{i-1}, u_{i-1}) + \frac{10}{12}F(x_i, u_i) + \frac{1}{12}F(x_{i+1}, u_{i+1})\right] = 0$$

**aproksymuje to równanie z dokładnością czwartego rzędu**, mimo że korzysta z tej samej liczby (trzech) węzłów sieci.

**Wyjaśnienie:** „Numerow" to nazwisko rosyjskiego astronoma Borisa Wasiliewicza Numerowa (1891-1941), który opracował ten schemat dla zagadnień astronomicznych.

**Zadanie:** Udowodnij, że schemat Numerowa rzeczywiście ma dokładność czwartego rzędu.

**Wskazówka:** Rozwiń zarówno $u(x)$ jak i $F(x, u(x))$ w szeregi Taylora i pokaż, że człony proporcjonalne do $h^2$ i $h^3$ wzajemnie się znoszą.

---

## Rozwiązania przykładowe

### Zadanie 1 - Rozwiązanie krok po kroku:

Dla siatki o kroku $h = 1$:
- $x_0 = 0$, $u_0 = 1$ (warunek brzegowy)
- $x_1 = 1$, $u_1 = ?$ (do wyznaczenia)
- $x_2 = 2$, $u_2 = 3$ (warunek brzegowy)

Podstawiając centralne przybliżenia różnicowe w punkcie $x_1 = 1$:

$$x_1^2 \cdot \frac{u_0 - 2u_1 + u_2}{h^2} + (2 - x_1^2) \cdot \frac{u_2 - u_0}{2h} - x_1 u_1 + 4 = 0$$

Po podstawieniu wartości:

$$1 \cdot \frac{1 - 2u_1 + 3}{1} + (2 - 1) \cdot \frac{3 - 1}{2} - 1 \cdot u_1 + 4 = 0$$

$$4 - 2u_1 + 1 - u_1 + 4 = 0$$

$$9 - 3u_1 = 0$$

$$u_1 = 3$$

Zatem przybliżone rozwiązanie w punkcie $x = 1$ wynosi $u(1) \approx 3$.

---

## Notatki dodatkowe

### Metoda strzałów (Shooting Method)

Dla równania z warunkami brzegowymi $u(a) = \alpha$, $u(b) = \beta$, metoda strzałów polega na:

1. Przekształceniu problemu brzegowego na problem początkowy
2. Zgadnięciu wartości $u'(a) = s$ (parametr strzału)
3. Rozwiązaniu problemu początkowego metodą numeryczną (np. Runge-Kutta)
4. Dostosowaniu parametru $s$ tak, aby $u(b) = \beta$ (np. metodą bisekcji lub Newton-Raphsona)

### Algorytm Thomasa (TDMA - TriDiagonal Matrix Algorithm)

Dla układu równań z macierzą trójdiagonalną:

$$\begin{bmatrix}
b_1 & c_1 & & & \\
a_2 & b_2 & c_2 & & \\
& \ddots & \ddots & \ddots & \\
& & a_{n-1} & b_{n-1} & c_{n-1} \\
& & & a_n & b_n
\end{bmatrix}
\begin{bmatrix}
x_1 \\ x_2 \\ \vdots \\ x_{n-1} \\ x_n
\end{bmatrix}
=
\begin{bmatrix}
d_1 \\ d_2 \\ \vdots \\ d_{n-1} \\ d_n
\end{bmatrix}$$

Algorytm działa w dwóch krokach:
1. **Forward elimination** - modyfikacja współczynników
2. **Back substitution** - wyznaczenie rozwiązań

Złożoność obliczeniowa: $O(n)$ (bardzo wydajny!)
