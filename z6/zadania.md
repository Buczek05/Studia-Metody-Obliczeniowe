# Zajęcia nr 6 - Rozwiązania zadań

## Zadanie 1: Pseudorozwiązanie nad-określonego układu równań

### Treść zadania

Znajdź pseudorozwiązanie nad-określonego układu równań:

$$
\begin{cases}
x + 2y = 1 \\
3x + 4y = 2 \\
5x + 6y = 3
\end{cases}
$$

Posłużyć się metodą najmniejszych kwadratów, poprzez bezpośrednie rozwiązanie układu równań normalnych.

### Rozwiązanie

#### Krok 1: Zapisanie układu w postaci macierzowej

Układ równań można zapisać jako $Ax = b$, gdzie:

$$
A = \begin{bmatrix}
1 & 2 \\
3 & 4 \\
5 & 6
\end{bmatrix}, \quad
x = \begin{bmatrix}
x \\
y
\end{bmatrix}, \quad
b = \begin{bmatrix}
1 \\
2 \\
3
\end{bmatrix}
$$

Mamy 3 równania i 2 niewiadome, więc układ jest nad-określony (więcej równań niż niewiadomych).

#### Krok 2: Metoda najmniejszych kwadratów

Pseudorozwiązanie w sensie najmniejszych kwadratów minimalizuje normę $\|Ax - b\|^2$ i jest dane wzorem:

$$
x = (A^T A)^{-1} A^T b
$$

Układ równań normalnych ma postać:

$$
A^T A x = A^T b
$$

#### Krok 3: Obliczenie $A^T$

$$
A^T = \begin{bmatrix}
1 & 3 & 5 \\
2 & 4 & 6
\end{bmatrix}
$$

#### Krok 4: Obliczenie $A^T A$

$$
A^T A = \begin{bmatrix}
1 & 3 & 5 \\
2 & 4 & 6
\end{bmatrix}
\begin{bmatrix}
1 & 2 \\
3 & 4 \\
5 & 6
\end{bmatrix}
$$

$$
A^T A = \begin{bmatrix}
1 \cdot 1 + 3 \cdot 3 + 5 \cdot 5 & 1 \cdot 2 + 3 \cdot 4 + 5 \cdot 6 \\
2 \cdot 1 + 4 \cdot 3 + 6 \cdot 5 & 2 \cdot 2 + 4 \cdot 4 + 6 \cdot 6
\end{bmatrix}
$$

$$
A^T A = \begin{bmatrix}
1 + 9 + 25 & 2 + 12 + 30 \\
2 + 12 + 30 & 4 + 16 + 36
\end{bmatrix}
= \begin{bmatrix}
35 & 44 \\
44 & 56
\end{bmatrix}
$$

#### Krok 5: Obliczenie $A^T b$

$$
A^T b = \begin{bmatrix}
1 & 3 & 5 \\
2 & 4 & 6
\end{bmatrix}
\begin{bmatrix}
1 \\
2 \\
3
\end{bmatrix}
$$

$$
A^T b = \begin{bmatrix}
1 \cdot 1 + 3 \cdot 2 + 5 \cdot 3 \\
2 \cdot 1 + 4 \cdot 2 + 6 \cdot 3
\end{bmatrix}
= \begin{bmatrix}
1 + 6 + 15 \\
2 + 8 + 18
\end{bmatrix}
= \begin{bmatrix}
22 \\
28
\end{bmatrix}
$$

#### Krok 6: Rozwiązanie układu równań normalnych

Układ równań normalnych:

$$
\begin{bmatrix}
35 & 44 \\
44 & 56
\end{bmatrix}
\begin{bmatrix}
x \\
y
\end{bmatrix}
= \begin{bmatrix}
22 \\
28
\end{bmatrix}
$$

czyli:

$$
\begin{cases}
35x + 44y = 22 \\
44x + 56y = 28
\end{cases}
$$

**Metoda eliminacji Gaussa:**

Z pierwszego równania: $35x + 44y = 22$

Mnożymy pierwsze równanie przez $\frac{44}{35}$:

$$
44x + \frac{44 \cdot 44}{35}y = \frac{44 \cdot 22}{35}
$$

$$
44x + \frac{1936}{35}y = \frac{968}{35}
$$

Odejmujemy od drugiego równania:

$$
56y - \frac{1936}{35}y = 28 - \frac{968}{35}
$$

$$
\frac{1960 - 1936}{35}y = \frac{980 - 968}{35}
$$

$$
\frac{24}{35}y = \frac{12}{35}
$$

$$
y = \frac{12}{24} = \frac{1}{2} = 0.5
$$

Podstawiamy do pierwszego równania:

$$
35x + 44 \cdot 0.5 = 22
$$

$$
35x + 22 = 22
$$

$$
35x = 0
$$

$$
x = 0
$$

#### Odpowiedź

Pseudorozwiązanie układu równań w sensie najmniejszych kwadratów:

$$
\boxed{x = 0, \quad y = 0.5}
$$

#### Weryfikacja

Sprawdźmy, jak nasze rozwiązanie spełnia oryginalne równania:

- Równanie 1: $0 + 2(0.5) = 1$ ✓ (dokładnie)
- Równanie 2: $3(0) + 4(0.5) = 2$ ✓ (dokładnie)
- Równanie 3: $5(0) + 6(0.5) = 3$ ✓ (dokładnie)

W tym przypadku układ faktycznie ma dokładne rozwiązanie!

---

## Dodatkowe informacje

### Interpretacja geometryczna

Metoda najmniejszych kwadratów znajduje punkt $(x, y)$, który minimalizuje sumę kwadratów odległości od wszystkich trzech płaszczyzn określonych przez równania układu.

### Warunek istnienia pseudorozwiązania

Pseudorozwiązanie w sensie najmniejszych kwadratów istnieje wtedy, gdy macierz $A^T A$ jest nieosobliwa (odwracalna). W naszym przypadku:

$$
\det(A^T A) = 35 \cdot 56 - 44 \cdot 44 = 1960 - 1936 = 24 \neq 0
$$

Zatem macierz jest odwracalna i rozwiązanie istnieje i jest jednoznaczne.
