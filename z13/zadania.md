# Zajęcia nr 13 - Interpolacja sklejana i kwadratury

## Zagadnienia do opanowania
- Interpolacja funkcjami sklejanymi
- Interpolacja biliniowa funkcji dwóch zmiennych
- Numeryczne obliczanie całek oznaczonych (kwadratury)

---

## Zadanie 1: Funkcja sklejana kubiczna (natural cubic spline)

Określ wartości współczynników $a$, $b$, $c$ i $d$ tak, aby otrzymać naturalną funkcję sklejaną stopnia trzeciego z węzłami 0, 1 i 2:

$$
S(x) = \begin{cases}
3 + x - 9x^3 & x \in [0, 1] \\
a + b(x-1) + c(x-1)^2 + d(x-1)^3 & x \in [1, 2]
\end{cases}
$$

### Warunki naturalnej funkcji sklejanej:
1. Ciągłość funkcji w węzłach wewnętrznych: $S_0(1) = S_1(1)$
2. Ciągłość pierwszej pochodnej: $S_0'(1) = S_1'(1)$
3. Ciągłość drugiej pochodnej: $S_0''(1) = S_1''(1)$
4. Warunki brzegowe (natural spline): $S_0''(0) = 0$ i $S_1''(2) = 0$

### Rozwiązanie:

Obliczamy pochodne pierwszego segmentu $S_0(x) = 3 + x - 9x^3$:
- $S_0'(x) = 1 - 27x^2$
- $S_0''(x) = -54x$

W punkcie $x = 1$:
- $S_0(1) = 3 + 1 - 9 = -5$
- $S_0'(1) = 1 - 27 = -26$
- $S_0''(1) = -54$

Dla drugiego segmentu $S_1(x) = a + b(x-1) + c(x-1)^2 + d(x-1)^3$:
- $S_1'(x) = b + 2c(x-1) + 3d(x-1)^2$
- $S_1''(x) = 2c + 6d(x-1)$

**Warunek 1** - ciągłość w $x=1$:
$$S_1(1) = a = -5$$

**Warunek 2** - ciągłość pierwszej pochodnej w $x=1$:
$$S_1'(1) = b = -26$$

**Warunek 3** - ciągłość drugiej pochodnej w $x=1$:
$$S_1''(1) = 2c = -54 \Rightarrow c = -27$$

**Warunek 4** - warunek brzegowy natural spline w $x=2$:
$$S_1''(2) = 2c + 6d(2-1) = 2c + 6d = 0$$
$$-54 + 6d = 0 \Rightarrow d = 9$$

### Odpowiedź:
$$\boxed{a = -5, \quad b = -26, \quad c = -27, \quad d = 9}$$

---

## Zadanie 2: Interpolacja biliniowa

Dane są węzły i wartości funkcji dwóch zmiennych:
- $(x_i, y_j, f(x_i, y_j))$: $(0, 0, 1)$, $(2, 0, 2)$, $(0, 4, 3)$, $(2, 4, 4)$

Stosując interpolację biliniową, wyznacz przybliżoną wartość funkcji $f(x, y)$ w punkcie $(x, y) = (1, 1)$.

### Rozwiązanie:

Wzór interpolacji biliniowej:
$$f(x,y) \approx \frac{1}{(x_2-x_1)(y_2-y_1)} \begin{bmatrix} x_2-x & x-x_1 \end{bmatrix} \begin{bmatrix} f(x_1,y_1) & f(x_1,y_2) \\ f(x_2,y_1) & f(x_2,y_2) \end{bmatrix} \begin{bmatrix} y_2-y \\ y-y_1 \end{bmatrix}$$

Gdzie:
- $x_1 = 0, x_2 = 2, y_1 = 0, y_2 = 4$
- $f(0,0) = 1, f(2,0) = 2, f(0,4) = 3, f(2,4) = 4$

Dla $(x,y) = (1,1)$:

$$f(1,1) \approx \frac{1}{(2-0)(4-0)} \begin{bmatrix} 2-1 & 1-0 \end{bmatrix} \begin{bmatrix} 1 & 3 \\ 2 & 4 \end{bmatrix} \begin{bmatrix} 4-1 \\ 1-0 \end{bmatrix}$$

$$= \frac{1}{8} \begin{bmatrix} 1 & 1 \end{bmatrix} \begin{bmatrix} 1 & 3 \\ 2 & 4 \end{bmatrix} \begin{bmatrix} 3 \\ 1 \end{bmatrix}$$

$$= \frac{1}{8} \begin{bmatrix} 1 & 1 \end{bmatrix} \begin{bmatrix} 6 \\ 10 \end{bmatrix} = \frac{1}{8} \cdot 16 = 2$$

### Odpowiedź:
$$\boxed{f(1,1) \approx 2}$$

---

## Zadanie 3: Kwadratury złożone

Funkcja $f(x)$ przyjmuje wartości: $-1, 3, 7, 8, 6$ odpowiednio dla $x = 0, 1, 2, 4, 6$.

Oblicz przybliżoną wartość całki $\int_0^6 f(x) dx$ posługując się złożonymi kwadraturami.

**Uwaga**: W przypadkach (c) i (e) zastosuj wzory kwadratur prostych do dwóch pod-przedziałów $[0,2]$ i $[2,6]$, a w pozostałych przypadkach do czterech pod-przedziałów.

### a) Prostokąty (lewy węzeł) - 4 podprzedziały

Podprzedziały: $[0,1], [1,2], [2,4], [4,6]$, długości: $h_1=1, h_2=1, h_3=2, h_4=2$

$$I \approx h_1 f(0) + h_2 f(1) + h_3 f(2) + h_4 f(4)$$
$$I \approx 1 \cdot (-1) + 1 \cdot 3 + 2 \cdot 7 + 2 \cdot 8 = -1 + 3 + 14 + 16 = 32$$

### b) Prostokąty (prawy węzeł) - 4 podprzedziały

$$I \approx h_1 f(1) + h_2 f(2) + h_3 f(4) + h_4 f(6)$$
$$I \approx 1 \cdot 3 + 1 \cdot 7 + 2 \cdot 8 + 2 \cdot 6 = 3 + 7 + 16 + 12 = 38$$

### c) Prostokąty (środek) - 2 podprzedziały $[0,2]$ i $[2,6]$

Dla $[0,2]$: środek w $x=1$, $h=2$
Dla $[2,6]$: środek w $x=4$, $h=4$

$$I \approx 2 \cdot f(1) + 4 \cdot f(4) = 2 \cdot 3 + 4 \cdot 8 = 6 + 32 = 38$$

### d) Trapezy - 4 podprzedziały

$$I \approx \frac{h_1}{2}[f(0)+f(1)] + \frac{h_2}{2}[f(1)+f(2)] + \frac{h_3}{2}[f(2)+f(4)] + \frac{h_4}{2}[f(4)+f(6)]$$
$$I \approx \frac{1}{2}[-1+3] + \frac{1}{2}[3+7] + \frac{2}{2}[7+8] + \frac{2}{2}[8+6]$$
$$I \approx 1 + 5 + 15 + 14 = 35$$

### e) Parabol (Simpson) - 2 podprzedziały $[0,2]$ i $[2,6]$

Dla $[0,2]$: węzły w $0, 1, 2$, $h=1$
$$I_1 \approx \frac{1}{3}[f(0) + 4f(1) + f(2)] = \frac{1}{3}[-1 + 12 + 7] = 6$$

Dla $[2,6]$: węzły w $2, 4, 6$, $h=2$
$$I_2 \approx \frac{2}{3}[f(2) + 4f(4) + f(6)] = \frac{2}{3}[7 + 32 + 6] = 30$$

$$I \approx I_1 + I_2 = 6 + 30 = 36$$

### Podsumowanie:
| Metoda | Wynik |
|--------|-------|
| Prostokąty (lewe) | 32 |
| Prostokąty (prawe) | 38 |
| Prostokąty (środek) | 38 |
| Trapezy | 35 |
| Parabol (Simpson) | 36 |

---

## Zadanie 4: Metoda Romberga

Przedział $[0,8]$ podzielono na 8 równoodległych pod-przedziałów ($h=1$).

Wartości funkcji w węzłach: $f(0)=-5, f(1)=-3, f(2)=1, f(3)=2, f(4)=1, f(5)=-1, f(6)=2, f(7)=5, f(8)=4$

Stosując metodę Romberga, oblicz możliwie najdokładniej przybliżoną wartość całki $\int_0^8 f(x) dx$.

### Rozwiązanie:

**Krok 1**: Obliczenia bazowe metodą trapezów

$R(0,0)$ z $h=8$ (2 punkty: $x=0, 8$):
$$R(0,0) = \frac{8}{2}[f(0) + f(8)] = 4[-5 + 4] = -4$$

$R(1,0)$ z $h=4$ (3 punkty: $x=0, 4, 8$):
$$R(1,0) = \frac{4}{2}[f(0) + 2f(4) + f(8)] = 2[-5 + 2 + 4] = 2$$

$R(2,0)$ z $h=2$ (5 punktów: $x=0, 2, 4, 6, 8$):
$$R(2,0) = \frac{2}{2}[f(0) + 2f(2) + 2f(4) + 2f(6) + f(8)]$$
$$= 1[-5 + 2 + 2 + 4 + 4] = 7$$

$R(3,0)$ z $h=1$ (9 punktów):
$$R(3,0) = \frac{1}{2}[f(0) + 2f(1) + 2f(2) + 2f(3) + 2f(4) + 2f(5) + 2f(6) + 2f(7) + f(8)]$$
$$= \frac{1}{2}[-5 - 6 + 2 + 4 + 2 - 2 + 4 + 10 + 4] = \frac{13}{2} = 6.5$$

**Krok 2**: Ekstrapolacja Richardsona

$$R(k,m) = R(k,m-1) + \frac{R(k,m-1) - R(k-1,m-1)}{4^m - 1}$$

$R(1,1) = R(1,0) + \frac{R(1,0) - R(0,0)}{3} = 2 + \frac{2-(-4)}{3} = 2 + 2 = 4$

$R(2,1) = R(2,0) + \frac{R(2,0) - R(1,0)}{3} = 7 + \frac{7-2}{3} = 7 + \frac{5}{3} = \frac{26}{3} \approx 8.667$

$R(3,1) = R(3,0) + \frac{R(3,0) - R(2,0)}{3} = 6.5 + \frac{6.5-7}{3} = 6.5 - \frac{1}{6} = \frac{19}{3} \approx 6.333$

$R(2,2) = R(2,1) + \frac{R(2,1) - R(1,1)}{15} = \frac{26}{3} + \frac{\frac{26}{3}-4}{15} = \frac{26}{3} + \frac{14}{45} = \frac{404}{45} \approx 8.978$

$R(3,2) = R(3,1) + \frac{R(3,1) - R(2,1)}{15} = \frac{19}{3} + \frac{\frac{19}{3}-\frac{26}{3}}{15} = \frac{19}{3} - \frac{7}{45} = \frac{278}{45} \approx 6.178$

$R(3,3) = R(3,2) + \frac{R(3,2) - R(2,2)}{63} = \frac{278}{45} + \frac{\frac{278}{45}-\frac{404}{45}}{63} = \frac{278}{45} - \frac{2}{45} = \frac{276}{45} = \frac{92}{15} \approx 6.133$

### Tablica Romberga:
| | m=0 | m=1 | m=2 | m=3 |
|---|------|------|------|------|
| k=0 | -4.000 | | | |
| k=1 | 2.000 | 4.000 | | |
| k=2 | 7.000 | 8.667 | 8.978 | |
| k=3 | 6.500 | 6.333 | 6.178 | 6.133 |

### Odpowiedź:
$$\boxed{\int_0^8 f(x) dx \approx 6.133}$$

---

## Zadanie 5: Kwadratura Gaussa

Oblicz przybliżoną wartość całki $\int_{-1}^{1} (x^4 + 1) dx$ za pomocą kwadratury Gaussa z dwoma punktami węzłowymi.

### Rozwiązanie:

Wzór kwadratury Gaussa z 2 punktami:
$$\int_{-1}^{1} f(x) dx \approx w_1 f(x_1) + w_2 f(x_2)$$

Węzły i wagi dla $n=2$:
- $x_1 = -\frac{1}{\sqrt{3}} \approx -0.5773502692$
- $x_2 = \frac{1}{\sqrt{3}} \approx 0.5773502692$
- $w_1 = w_2 = 1$

Funkcja: $f(x) = x^4 + 1$

$$f(x_1) = \left(-\frac{1}{\sqrt{3}}\right)^4 + 1 = \frac{1}{9} + 1 = \frac{10}{9}$$

$$f(x_2) = \left(\frac{1}{\sqrt{3}}\right)^4 + 1 = \frac{1}{9} + 1 = \frac{10}{9}$$

$$I \approx 1 \cdot \frac{10}{9} + 1 \cdot \frac{10}{9} = \frac{20}{9} \approx 2.222222$$

### Wartość dokładna:

$$\int_{-1}^{1} (x^4 + 1) dx = \left[\frac{x^5}{5} + x\right]_{-1}^{1} = \left(\frac{1}{5} + 1\right) - \left(-\frac{1}{5} - 1\right) = \frac{2}{5} + 2 = \frac{12}{5} = 2.4$$

### Błąd:
$$\text{Błąd} = \left|2.4 - 2.222222\right| = 0.177778$$

$$\text{Błąd względny} = \frac{0.177778}{2.4} \times 100\% \approx 7.4\%$$

### Odpowiedź:
- **Kwadratura Gaussa**: $\boxed{2.222}$
- **Wartość dokładna**: $\boxed{2.4}$
- **Błąd względny**: $\boxed{7.4\%}$

---

## Dodatkowe informacje

### Rzędy dokładności metod:
- **Prostokąty (lewe/prawe)**: $O(h^2)$
- **Prostokąty (środek)**: $O(h^3)$
- **Trapezy**: $O(h^3)$
- **Simpson (parabol)**: $O(h^5)$
- **Metoda Romberga**: automatyczna ekstrapolacja poprawiająca rząd dokładności
- **Kwadratura Gaussa (n punktów)**: dokładna dla wielomianów stopnia $\leq 2n-1$
