# Zajęcia nr 5 - Zadania

## Zagadnienia do opanowania

- Obliczanie norm wektorów i macierzy
- Wskaźnik uwarunkowania macierzy
- Eliminacja Gaussa
- Dekompozycja LU macierzy pełnej
- Metody bezpośrednie rozwiązywania układów liniowych równań algebraicznych z macierzą pełną

---

## Zadanie 1: Obliczanie norm wektora i macierzy

**Dany jest wektor:**

$$x = \begin{bmatrix} -1 \\ 2 \\ -3 \\ 4 \\ -5 \end{bmatrix}$$

**i macierz:**

$$A = \begin{bmatrix} 1 & -2 \\ -3 & 4 \end{bmatrix}$$

**Oblicz normę pierwszą, normę drugą i normę maksimum.**

### Rozwiązanie:

#### Dla wektora $x$:

**Norma pierwsza (Manhattan):**
$$\|x\|_1 = |{-1}| + |2| + |{-3}| + |4| + |{-5}| = 1 + 2 + 3 + 4 + 5 = 15$$

**Norma druga (euklidesowa):**
$$\|x\|_2 = \sqrt{(-1)^2 + 2^2 + (-3)^2 + 4^2 + (-5)^2} = \sqrt{1 + 4 + 9 + 16 + 25} = \sqrt{55} \approx 7.416$$

**Norma maksimum:**
$$\|x\|_\infty = \max\{|-1|, |2|, |-3|, |4|, |-5|\} = 5$$

#### Dla macierzy $A$:

**Norma pierwsza (maksimum sumy kolumn):**
$$\|A\|_1 = \max\{|1| + |-3|, |-2| + |4|\} = \max\{4, 6\} = 6$$

**Norma nieskończoność (maksimum sumy wierszy):**
$$\|A\|_\infty = \max\{|1| + |-2|, |-3| + |4|\} = \max\{3, 7\} = 7$$

**Norma Frobeniusa:**
$$\|A\|_F = \sqrt{1^2 + (-2)^2 + (-3)^2 + 4^2} = \sqrt{1 + 4 + 9 + 16} = \sqrt{30} \approx 5.477$$

---

## Zadanie 2: Wskaźnik uwarunkowania macierzy

**Dane są macierze:**

$$A = \begin{bmatrix} 10 & 1 \\ 1 & 20 \end{bmatrix}, \quad B = \begin{bmatrix} 1 & 1+\varepsilon \\ 1-\varepsilon & 1 \end{bmatrix}$$

**gdzie $0 < \varepsilon \ll 1$.**

**Oblicz wskaźnik uwarunkowania dla obu macierzy używając normy maksimum. Która macierz zapewnia lepsze uwarunkowanie?**

### Rozwiązanie:

Wskaźnik uwarunkowania: $\text{cond}(M) = \|M\| \cdot \|M^{-1}\|$

#### Dla macierzy $A$:

**Wyznacznik:**
$$\det(A) = 10 \cdot 20 - 1 \cdot 1 = 200 - 1 = 199$$

**Macierz odwrotna:**
$$A^{-1} = \frac{1}{199} \begin{bmatrix} 20 & -1 \\ -1 & 10 \end{bmatrix}$$

**Normy:**
$$\|A\|_\infty = \max\{10 + 1, 1 + 20\} = 21$$
$$\|A^{-1}\|_\infty = \frac{1}{199}\max\{20 + 1, 1 + 10\} = \frac{21}{199} \approx 0.1055$$

**Wskaźnik uwarunkowania:**
$$\text{cond}_\infty(A) = 21 \cdot \frac{21}{199} = \frac{441}{199} \approx 2.216$$

#### Dla macierzy $B$:

**Wyznacznik:**
$$\det(B) = 1 \cdot 1 - (1+\varepsilon)(1-\varepsilon) = 1 - (1 - \varepsilon^2) = \varepsilon^2$$

**Macierz odwrotna:**
$$B^{-1} = \frac{1}{\varepsilon^2} \begin{bmatrix} 1 & -(1+\varepsilon) \\ -(1-\varepsilon) & 1 \end{bmatrix}$$

**Normy:**
$$\|B\|_\infty = \max\{1 + |1+\varepsilon|, |1-\varepsilon| + 1\} = \max\{2 + \varepsilon, 2 - \varepsilon\} = 2 + \varepsilon$$

$$\|B^{-1}\|_\infty = \frac{1}{\varepsilon^2}\max\{1 + |1+\varepsilon|, |1-\varepsilon| + 1\} = \frac{2 + \varepsilon}{\varepsilon^2}$$

**Wskaźnik uwarunkowania:**
$$\text{cond}_\infty(B) = (2 + \varepsilon) \cdot \frac{2 + \varepsilon}{\varepsilon^2} = \frac{(2 + \varepsilon)^2}{\varepsilon^2}$$

Dla $\varepsilon \ll 1$:
$$\text{cond}_\infty(B) \approx \frac{4}{\varepsilon^2}$$

**Przykładowo dla $\varepsilon = 0.01$:**
$$\text{cond}_\infty(B) \approx \frac{4}{0.0001} = 40\,000$$

### Wniosek:

**Macierz $A$ zapewnia znacznie lepsze uwarunkowanie** ($\text{cond} \approx 2.2$) niż macierz $B$ ($\text{cond} \approx 40\,000$ dla $\varepsilon = 0.01$). Macierz $B$ jest źle uwarunkowana i może prowadzić do dużych błędów numerycznych przy rozwiązywaniu układów równań.

---

## Zadanie 3: Dekompozycja LU z częściowym wyborem elementu podstawowego

**Dana jest macierz:**

$$A = \begin{bmatrix}
1 & 2 & 2 & 1 \\
2 & 4 & 4 & 1 \\
2 & 2 & 2 & 1 \\
1 & 1 & 2 & 1
\end{bmatrix}$$

**oraz wektor:**

$$b = \begin{bmatrix} 1 \\ 2 \\ 3 \\ 4 \end{bmatrix}$$

**Wykonaj dekompozycję LU z częściowym wyborem elementu podstawowego i rozwiąż układ $Ax = b$.**

### Rozwiązanie:

#### Krok 1: Eliminacja Gaussa z częściowym wyborem elementu podstawowego

**Macierz początkowa:**
$$A^{(0)} = \begin{bmatrix}
1 & 2 & 2 & 1 \\
2 & 4 & 4 & 1 \\
2 & 2 & 2 & 1 \\
1 & 1 & 2 & 1
\end{bmatrix}, \quad b^{(0)} = \begin{bmatrix} 1 \\ 2 \\ 3 \\ 4 \end{bmatrix}$$

**Krok 1.1:** Szukamy maksymalnego elementu w kolumnie 1:
$$\max\{|1|, |2|, |2|, |1|\} = 2$$
Element znajduje się w wierszu 2 (lub 3). Zamieniamy wiersze 1 i 2.

Macierz permutacji: $P_1$ zamienia wiersze 1 i 2.

$$A^{(1)} = \begin{bmatrix}
2 & 4 & 4 & 1 \\
1 & 2 & 2 & 1 \\
2 & 2 & 2 & 1 \\
1 & 1 & 2 & 1
\end{bmatrix}, \quad b^{(1)} = \begin{bmatrix} 2 \\ 1 \\ 3 \\ 4 \end{bmatrix}$$

**Krok 1.2:** Eliminujemy elementy pod pierwszą pozycją:
- $m_{21} = 1/2$
- $m_{31} = 2/2 = 1$
- $m_{41} = 1/2$

$$A^{(2)} = \begin{bmatrix}
2 & 4 & 4 & 1 \\
0 & 0 & 0 & 0.5 \\
0 & -2 & -2 & 0 \\
0 & -1 & 0 & 0.5
\end{bmatrix}, \quad b^{(2)} = \begin{bmatrix} 2 \\ 0 \\ 1 \\ 3 \end{bmatrix}$$

**Krok 2.1:** Szukamy maksymalnego elementu w kolumnie 2 (wiersze 2-4):
$$\max\{|0|, |-2|, |-1|\} = 2$$
Element znajduje się w wierszu 3. Zamieniamy wiersze 2 i 3.

$$A^{(3)} = \begin{bmatrix}
2 & 4 & 4 & 1 \\
0 & -2 & -2 & 0 \\
0 & 0 & 0 & 0.5 \\
0 & -1 & 0 & 0.5
\end{bmatrix}, \quad b^{(3)} = \begin{bmatrix} 2 \\ 1 \\ 0 \\ 3 \end{bmatrix}$$

**Krok 2.2:** Eliminujemy:
- $m_{42} = -1/(-2) = 0.5$

$$A^{(4)} = \begin{bmatrix}
2 & 4 & 4 & 1 \\
0 & -2 & -2 & 0 \\
0 & 0 & 0 & 0.5 \\
0 & 0 & 1 & 0.5
\end{bmatrix}, \quad b^{(4)} = \begin{bmatrix} 2 \\ 1 \\ 0 \\ 3.5 \end{bmatrix}$$

**Krok 3.1:** Szukamy maksymalnego elementu w kolumnie 3 (wiersze 3-4):
$$\max\{|0|, |1|\} = 1$$
Element znajduje się w wierszu 4. Zamieniamy wiersze 3 i 4.

$$U = \begin{bmatrix}
2 & 4 & 4 & 1 \\
0 & -2 & -2 & 0 \\
0 & 0 & 1 & 0.5 \\
0 & 0 & 0 & 0.5
\end{bmatrix}, \quad b^{(5)} = \begin{bmatrix} 2 \\ 1 \\ 3.5 \\ 0 \end{bmatrix}$$

#### Dekompozycja PA = LU:

**Macierz L:**
$$L = \begin{bmatrix}
1 & 0 & 0 & 0 \\
0.5 & 1 & 0 & 0 \\
1 & 0 & 1 & 0 \\
0.5 & 0.5 & 0 & 1
\end{bmatrix}$$

**Macierz U:**
$$U = \begin{bmatrix}
2 & 4 & 4 & 1 \\
0 & -2 & -2 & 0 \\
0 & 0 & 1 & 0.5 \\
0 & 0 & 0 & 0.5
\end{bmatrix}$$

#### Rozwiązanie układu:

**Krok 1: Rozwiązanie $Ly = Pb$ (podstawienie w przód):**
$$y_1 = 2$$
$$y_2 = 1 - 0.5 \cdot 2 = 0$$
$$y_3 = 3.5 - 1 \cdot 2 - 0 \cdot 0 = 1.5$$
$$y_4 = 0 - 0.5 \cdot 2 - 0.5 \cdot 0 - 0 \cdot 1.5 = -1$$

$$y = \begin{bmatrix} 2 \\ 0 \\ 1.5 \\ -1 \end{bmatrix}$$

**Krok 2: Rozwiązanie $Ux = y$ (podstawienie wstecz):**
$$x_4 = \frac{-1}{0.5} = -2$$
$$x_3 = 1.5 - 0.5 \cdot (-2) = 2.5$$
$$x_2 = \frac{0 - (-2) \cdot 0 - 1 \cdot 2.5}{-2} = \frac{-2.5}{-2} = 1.25$$
$$x_1 = \frac{2 - 4 \cdot 1.25 - 4 \cdot 2.5 - 1 \cdot (-2)}{2} = \frac{2 - 5 - 10 + 2}{2} = \frac{-11}{2} = -5.5$$

### Rozwiązanie:
$$x = \begin{bmatrix} -5.5 \\ 1.25 \\ 2.5 \\ -2 \end{bmatrix}$$

---

## Dodatkowe ćwiczenie (dla chętnych, +5.0)

**Dany jest układ równań z macierzą:**

$$A = \begin{bmatrix}
1+\varepsilon & 1 & 1 & 1 \\
1 & 1+\varepsilon & 1 & 1 \\
1 & 1 & 1+\varepsilon & 1 \\
1 & 1 & 1 & 1+\varepsilon
\end{bmatrix}$$

**oraz wektorem:**

$$b = \begin{bmatrix} 6+\varepsilon \\ 6+2\varepsilon \\ 6+2\varepsilon \\ 6+\varepsilon \end{bmatrix}$$

### Rozwiązanie analityczne:

Macierz można zapisać jako: $A = (1+\varepsilon)I + (1-\varepsilon)J$, gdzie $J$ to macierz jednostkowa.

Po przekształceniach można pokazać, że rozwiązanie analityczne to:

$$x = \begin{bmatrix} 1 \\ 2 \\ 2 \\ 1 \end{bmatrix}$$

(niezależnie od wartości $\varepsilon$!)

### Zadanie:

1. Znajdź rozwiązanie analityczne
2. Oblicz rozwiązanie numeryczne dla $\varepsilon = 10^{-5}, 10^{-6}, 10^{-7}, ...$
3. Porównaj rozwiązania i wyjaśnij obserwowane różnice w błędach numerycznych

### Wskazówka:

Przy bardzo małych wartościach $\varepsilon$ macierz staje się źle uwarunkowana, co prowadzi do błędów numerycznych w rozwiązaniu. Wskaźnik uwarunkowania rośnie wraz ze zmniejszaniem się $\varepsilon$.
