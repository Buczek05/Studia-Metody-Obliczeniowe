# Przykładowe rozwiązania zadań 1-4

## Zadanie 1 - Analiza zbieżności metody Jacobiego

**Dane:**
$$
A = \begin{bmatrix} 5 & 1 \\ 4 & 10 \end{bmatrix}, \quad
b = \begin{bmatrix} 49 \\ 30 \end{bmatrix}
$$

### Rozwiązanie:

#### Krok 1: Rozkład macierzy A = D + L + U

Macierz diagonalna D:
$$
D = \begin{bmatrix} 5 & 0 \\ 0 & 10 \end{bmatrix}
$$

Macierz dolnotrójkątna L (bez diagonali):
$$
L = \begin{bmatrix} 0 & 0 \\ 4 & 0 \end{bmatrix}
$$

Macierz górnotrójkątna U (bez diagonali):
$$
U = \begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix}
$$

#### Krok 2: Macierz iteracji Jacobiego

$$
T_J = -D^{-1}(L + U)
$$

Odwrotność macierzy D:
$$
D^{-1} = \begin{bmatrix} 1/5 & 0 \\ 0 & 1/10 \end{bmatrix} = \begin{bmatrix} 0.2 & 0 \\ 0 & 0.1 \end{bmatrix}
$$

Suma L + U:
$$
L + U = \begin{bmatrix} 0 & 1 \\ 4 & 0 \end{bmatrix}
$$

Macierz iteracji:
$$
T_J = -\begin{bmatrix} 0.2 & 0 \\ 0 & 0.1 \end{bmatrix} \begin{bmatrix} 0 & 1 \\ 4 & 0 \end{bmatrix} = -\begin{bmatrix} 0 & 0.2 \\ 0.4 & 0 \end{bmatrix} = \begin{bmatrix} 0 & -0.2 \\ -0.4 & 0 \end{bmatrix}
$$

#### Krok 3: Norma maksimum (nieskończoność)

$$
\|T_J\|_\infty = \max_i \sum_j |t_{ij}| = \max\{|0| + |-0.2|, |-0.4| + |0|\} = \max\{0.2, 0.4\} = 0.4
$$

#### Krok 4: Sprawdzenie warunku zbieżności

Ponieważ $\|T_J\|_\infty = 0.4 < 1$, na podstawie **twierdzenia Banacha o kontrakcji** metoda Jacobiego jest **zbieżna** dla tego układu.

#### Krok 5: Sprawdzenie dominacji diagonalnej

Wiersz 1: $|a_{11}| = 5 > |a_{12}| = 1$ ✓

Wiersz 2: $|a_{22}| = 10 > |a_{21}| = 4$ ✓

Macierz ma **silną dominację diagonalną**, więc metoda Jacobiego jest zbieżna.

---

## Zadanie 2 - Metoda Richardsona

**Dane:**
$$
A = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix}, \quad
b = \begin{bmatrix} 1 \\ 2 \end{bmatrix}, \quad
x_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}
$$

### Rozwiązanie:

#### Metoda Richardsona
Wzór iteracyjny:
$$
x^{(k+1)} = x^{(k)} + \alpha(b - Ax^{(k)})
$$

gdzie $\alpha$ jest parametrem metody.

#### Krok 1: Obliczenie $r_0 = b - Ax_0$ (residuum początkowe)

$$
Ax_0 = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix} \begin{bmatrix} 1 \\ 1 \end{bmatrix} = \begin{bmatrix} 6 \\ 6 \end{bmatrix}
$$

$$
r_0 = b - Ax_0 = \begin{bmatrix} 1 \\ 2 \end{bmatrix} - \begin{bmatrix} 6 \\ 6 \end{bmatrix} = \begin{bmatrix} -5 \\ -4 \end{bmatrix}
$$

#### Krok 2: Obliczenie $x_1$ dla różnych wartości $\alpha$

**Dla $\alpha = 0.1$:**
$$
x_1 = x_0 + 0.1 \cdot r_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix} + 0.1 \begin{bmatrix} -5 \\ -4 \end{bmatrix} = \begin{bmatrix} 0.5 \\ 0.6 \end{bmatrix}
$$

**Dla $\alpha = 0.2$:**
$$
x_1 = x_0 + 0.2 \cdot r_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix} + 0.2 \begin{bmatrix} -5 \\ -4 \end{bmatrix} = \begin{bmatrix} 0 \\ 0.2 \end{bmatrix}
$$

#### Krok 3: Analiza zbieżności

Warunek zbieżności metody Richardsona:
$$
\rho(I - \alpha A) < 1
$$

gdzie $\rho$ oznacza promień spektralny.

**Wartości własne macierzy A:**

Równanie charakterystyczne:
$$
\det(A - \lambda I) = 0
$$

$$
\det\begin{bmatrix} 5-\lambda & 1 \\ 2 & 4-\lambda \end{bmatrix} = (5-\lambda)(4-\lambda) - 2 = 0
$$

$$
\lambda^2 - 9\lambda + 18 = 0
$$

$$
\lambda_1 = 6, \quad \lambda_2 = 3
$$

Dla zbieżności potrzeba:
$$
|1 - \alpha\lambda_i| < 1 \text{ dla wszystkich } i
$$

Dla $\lambda_1 = 6$: $|1 - 6\alpha| < 1 \Rightarrow 0 < \alpha < 1/3$

Dla $\lambda_2 = 3$: $|1 - 3\alpha| < 1 \Rightarrow 0 < \alpha < 2/3$

**Wniosek:** Metoda Richardsona jest zbieżna dla $0 < \alpha < 1/3 \approx 0.333$

---

## Zadanie 3 - Metoda Gaussa-Seidela

**Dane:**
$$
A = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix}, \quad
b = \begin{bmatrix} 1 \\ 2 \end{bmatrix}, \quad
x_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}
$$

### Rozwiązanie:

#### Wzór iteracyjny Gaussa-Seidela:

$$
x_i^{(k+1)} = \frac{1}{a_{ii}}\left(b_i - \sum_{j<i} a_{ij}x_j^{(k+1)} - \sum_{j>i} a_{ij}x_j^{(k)}\right)
$$

#### Krok 1: Obliczenie $x_1$

Dla $i = 1$:
$$
x_1^{(1)} = \frac{1}{a_{11}}(b_1 - a_{12}x_2^{(0)}) = \frac{1}{5}(1 - 1 \cdot 1) = \frac{0}{5} = 0
$$

Dla $i = 2$ (używamy już zaktualizowanego $x_1^{(1)} = 0$):
$$
x_2^{(1)} = \frac{1}{a_{22}}(b_2 - a_{21}x_1^{(1)}) = \frac{1}{4}(2 - 2 \cdot 0) = \frac{2}{4} = 0.5
$$

**Wynik:**
$$
x_1 = \begin{bmatrix} 0 \\ 0.5 \end{bmatrix}
$$

#### Krok 2: Analiza zbieżności

**Sprawdzenie dominacji diagonalnej:**

Wiersz 1: $|a_{11}| = 5 > |a_{12}| = 1$ ✓

Wiersz 2: $|a_{22}| = 4 > |a_{21}| = 2$ ✓

Macierz ma **silną dominację diagonalną**, więc metoda Gaussa-Seidela jest **zbieżna**.

**Macierz iteracji:**
$$
T_{GS} = -(D + L)^{-1}U
$$

gdzie:
- $D = \begin{bmatrix} 5 & 0 \\ 0 & 4 \end{bmatrix}$
- $L = \begin{bmatrix} 0 & 0 \\ 2 & 0 \end{bmatrix}$
- $U = \begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix}$

$$
D + L = \begin{bmatrix} 5 & 0 \\ 2 & 4 \end{bmatrix}
$$

$$
(D + L)^{-1} = \frac{1}{20}\begin{bmatrix} 4 & 0 \\ -2 & 5 \end{bmatrix} = \begin{bmatrix} 0.2 & 0 \\ -0.1 & 0.25 \end{bmatrix}
$$

$$
T_{GS} = -\begin{bmatrix} 0.2 & 0 \\ -0.1 & 0.25 \end{bmatrix}\begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix} = -\begin{bmatrix} 0 & 0.2 \\ 0 & -0.1 \end{bmatrix} = \begin{bmatrix} 0 & -0.2 \\ 0 & 0.1 \end{bmatrix}
$$

Promień spektralny: $\rho(T_{GS}) = \max\{0, 0.1\} = 0.1 < 1$ ✓

**Metoda jest zbieżna.**

---

## Zadanie 4 - Metoda SOR z ω = 1/2

**Dane:**
$$
A = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix}, \quad
b = \begin{bmatrix} 1 \\ 2 \end{bmatrix}, \quad
x_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}, \quad
\omega = \frac{1}{2}
$$

### Rozwiązanie:

#### Wzór iteracyjny SOR:

$$
x_i^{(k+1)} = (1-\omega)x_i^{(k)} + \frac{\omega}{a_{ii}}\left(b_i - \sum_{j<i} a_{ij}x_j^{(k+1)} - \sum_{j>i} a_{ij}x_j^{(k)}\right)
$$

#### Krok 1: Obliczenie $x_1$

Dla $i = 1$:
$$
x_1^{(1)} = (1-0.5) \cdot 1 + \frac{0.5}{5}(1 - 1 \cdot 1)
$$
$$
x_1^{(1)} = 0.5 + \frac{0.5}{5} \cdot 0 = 0.5
$$

Dla $i = 2$ (używamy $x_1^{(1)} = 0.5$):
$$
x_2^{(1)} = (1-0.5) \cdot 1 + \frac{0.5}{4}(2 - 2 \cdot 0.5)
$$
$$
x_2^{(1)} = 0.5 + \frac{0.5}{4} \cdot 1 = 0.5 + 0.125 = 0.625
$$

**Wynik:**
$$
x_1 = \begin{bmatrix} 0.5 \\ 0.625 \end{bmatrix}
$$

#### Krok 2: Analiza zbieżności

Dla $\omega = 1/2 < 1$ mamy metodę **niedorelaksowaną** (underrelaxation).

Warunek konieczny zbieżności: $0 < \omega < 2$

Ponieważ $\omega = 0.5$ spełnia ten warunek oraz macierz A ma dominację diagonalną, metoda SOR jest **zbieżna**.

#### Krok 3: Porównanie z metodą Gaussa-Seidela

Dla $\omega = 1$ metoda SOR redukuje się do metody Gaussa-Seidela:
$$
x_{GS} = \begin{bmatrix} 0 \\ 0.5 \end{bmatrix}
$$

Dla $\omega = 0.5$ (niedorelaksacja):
$$
x_{SOR} = \begin{bmatrix} 0.5 \\ 0.625 \end{bmatrix}
$$

Niedorelaksacja ($\omega < 1$) powoduje **wolniejszą** zbieżność, ale może poprawić **stabilność** dla źle uwarunkowanych układów.

---

## Rozwiązanie dokładne układu

Dla układu:
$$
\begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix} \begin{bmatrix} x_1 \\ x_2 \end{bmatrix} = \begin{bmatrix} 1 \\ 2 \end{bmatrix}
$$

Metodą eliminacji:
- Z pierwszego równania: $5x_1 + x_2 = 1 \Rightarrow x_2 = 1 - 5x_1$
- Podstawienie do drugiego: $2x_1 + 4(1 - 5x_1) = 2$
- $2x_1 + 4 - 20x_1 = 2$
- $-18x_1 = -2$
- $x_1 = \frac{1}{9}$
- $x_2 = 1 - 5 \cdot \frac{1}{9} = \frac{4}{9}$

**Rozwiązanie dokładne:**
$$
x = \begin{bmatrix} 1/9 \\ 4/9 \end{bmatrix} = \begin{bmatrix} 0.1111... \\ 0.4444... \end{bmatrix}
$$

Porównując z wynikami po jednej iteracji, widzimy, że metody iteracyjne zbiegają do tego rozwiązania.
