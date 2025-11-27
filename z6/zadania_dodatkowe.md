# Zadania dodatkowe - Zajęcia nr 6

## Zadanie 2: Równanie ciepła 1D

Rozwiąż równanie przewodnictwa ciepła w pręcie:

$$
-\frac{d^2 u}{dx^2} = f(x), \quad x \in (0, 1)
$$

z warunkami brzegowymi:
$$
u(0) = 0, \quad u(1) = 0
$$

gdzie $f(x) = \pi^2 \sin(\pi x)$ (źródło ciepła).

**Dokładne rozwiązanie:** $u(x) = \sin(\pi x)$

### Polecenia:

a) Zdyskretyzuj równanie metodą różnic skończonych z krokiem $h = 0.1$ (9 punktów wewnętrznych)

b) Zapisz dyskretyzację w postaci układu równań z macierzą trójdiagonalną

c) Rozwiąż układ algorytmem Thomasa

d) Porównaj rozwiązanie numeryczne z rozwiązaniem dokładnym

### Wskazówka:

Dyskretyzacja drugiej pochodnej:
$$
-\frac{u_{i-1} - 2u_i + u_{i+1}}{h^2} = f_i
$$

Macierz układu:
$$
\frac{1}{h^2} \begin{bmatrix}
2 & -1 & 0 & \cdots & 0 \\
-1 & 2 & -1 & \cdots & 0 \\
\vdots & \ddots & \ddots & \ddots & \vdots \\
0 & \cdots & -1 & 2 & -1 \\
0 & \cdots & 0 & -1 & 2
\end{bmatrix}
\begin{bmatrix}
u_1 \\ u_2 \\ \vdots \\ u_{n-1}
\end{bmatrix}
=
\begin{bmatrix}
f_1 \\ f_2 \\ \vdots \\ f_{n-1}
\end{bmatrix}
$$

---

## Zadanie 3: Porównanie metod

Dla układu równań:

$$
\begin{bmatrix}
10 & -1 & 0 & 0 \\
-1 & 10 & -2 & 0 \\
0 & -2 & 10 & -1 \\
0 & 0 & -1 & 10
\end{bmatrix}
\begin{bmatrix}
x_1 \\ x_2 \\ x_3 \\ x_4
\end{bmatrix}
=
\begin{bmatrix}
9 \\ 7 \\ 7 \\ 9
\end{bmatrix}
$$

a) Rozwiąż algorytmem Thomasa

b) Rozwiąż metodą Gaussa z pełną macierzą

c) Zmierz czas wykonania obu metod dla dużych macierzy ($n = 1000, 5000, 10000$)

d) Porównaj zużycie pamięci obu metod

---

## Zadanie 4: Aproksymacja wielomianowa

Masz dane pomiarowe $(x_i, y_i)$:

| $x$ | 0 | 1 | 2 | 3 | 4 | 5 |
|-----|---|---|---|---|---|---|
| $y$ | 2.1 | 2.9 | 4.8 | 7.2 | 9.9 | 13.1 |

**Polecenia:**

a) Dopasuj funkcję liniową $y = ax + b$ metodą najmniejszych kwadratów

b) Dopasuj funkcję kwadratową $y = ax^2 + bx + c$ metodą najmniejszych kwadratów

c) Dla obu modeli:
   - Oblicz normę residuum
   - Wyświetl wykres punktów i dopasowanej funkcji (opcjonalnie)
   - Określ, który model lepiej pasuje do danych

### Wskazówka:

Dla funkcji kwadratowej macierz $A$ ma postać:
$$
A = \begin{bmatrix}
x_1^2 & x_1 & 1 \\
x_2^2 & x_2 & 1 \\
\vdots & \vdots & \vdots \\
x_n^2 & x_n & 1
\end{bmatrix}
$$

---

## Zadanie 5: Interpolacja funkcjami sklejanymi

Znajdź naturalną funkcję sklejaną kubiczną (natural cubic spline) dla punktów:

$$
(x_0, y_0) = (0, 0), \quad (x_1, y_1) = (1, 1), \quad (x_2, y_2) = (2, 0)
$$

### Teoria:

Funkcja sklejana kubiczna to funkcja postaci:
$$
S_i(x) = a_i + b_i(x - x_i) + c_i(x - x_i)^2 + d_i(x - x_i)^3
$$

dla $x \in [x_i, x_{i+1}]$.

Warunki:
1. Interpolacja: $S_i(x_i) = y_i$
2. Ciągłość: $S_i(x_{i+1}) = S_{i+1}(x_{i+1})$
3. Gładkość pierwszego rzędu: $S_i'(x_{i+1}) = S_{i+1}'(x_{i+1})$
4. Gładkość drugiego rzędu: $S_i''(x_{i+1}) = S_{i+1}''(x_{i+1})$
5. Warunki brzegowe (naturalne): $S_0''(x_0) = 0, \quad S_{n-1}''(x_n) = 0$

Te warunki prowadzą do **układu równań z macierzą trójdiagonalną** dla współczynników $c_i$!

**Polecenie:** Wyprowadź układ równań dla współczynników $c_i$ i rozwiąż go algorytmem Thomasa.

---

## Zadanie 6: Analiza stabilności

Dla algorytmu Thomasa zbadaj:

a) Co się dzieje, gdy element diagonalny jest bardzo mały ($|b_i| < \epsilon$)?

b) Zaimplementuj wersję z pivotingiem (jeśli to możliwe dla macierzy trójdiagonalnej)

c) Sprawdź numeryczną stabilność dla układu:

$$
\begin{bmatrix}
10^{-10} & -1 & 0 \\
-1 & 10^{-10} & -1 \\
0 & -1 & 10^{-10}
\end{bmatrix}
\begin{bmatrix}
x_1 \\ x_2 \\ x_3
\end{bmatrix}
=
\begin{bmatrix}
1 \\ 1 \\ 1
\end{bmatrix}
$$

---

## Zadanie 7: Optymalizacja algorytmu

a) Zmodyfikuj implementację algorytmu Thomasa tak, aby operował "in-place" (bez alokacji dodatkowej pamięci)

b) Zmierz czas wykonania dla różnych rozmiarów macierzy

c) Porównaj wydajność z biblioteką LAPACK (jeśli dostępna)

---

## Zadanie 8: Macierz pentadiagonalna

Uogólnij algorytm Thomasa na macierz **pentadiagonalną** (5 diagonali):

$$
\begin{bmatrix}
b_0 & c_0 & d_0 & 0 & \cdots \\
a_1 & b_1 & c_1 & d_1 & \cdots \\
e_2 & a_2 & b_2 & c_2 & \cdots \\
0 & e_3 & a_3 & b_3 & \cdots \\
\vdots & \ddots & \ddots & \ddots & \ddots
\end{bmatrix}
$$

gdzie:
- $e_i$ - podpoddiagonala
- $a_i$ - poddiagonala
- $b_i$ - diagonala główna
- $c_i$ - naddiagonala
- $d_i$ - nadnaddiagonala

**Wskazówka:** Metoda ma złożoność $O(n)$, ale więcej operacji na element niż algorytm Thomasa.

---

## Zadanie 9: Równanie dyfuzji-reakcji

Rozwiąż stacjonarne równanie dyfuzji-reakcji:

$$
-D\frac{d^2 u}{dx^2} + ku = f(x)
$$

gdzie:
- $D = 0.1$ (współczynnik dyfuzji)
- $k = 1$ (współczynnik reakcji)
- $f(x) = \sin(\pi x)$
- $u(0) = 0, u(1) = 0$

Dyskretyzacja prowadzi do układu z macierzą trójdiagonalną:
$$
\frac{-D}{h^2}(u_{i-1} - 2u_i + u_{i+1}) + ku_i = f_i
$$

---

## Zadanie 10: QR faktorizacja dla najmniejszych kwadratów

Zaimplementuj rozwiązanie nad-określonego układu równań używając rozkładu QR zamiast równań normalnych:

$$
A = QR
$$

Rozwiązanie:
$$
x = R^{-1}Q^T b
$$

**Zalety:**
- Lepsza stabilność numeryczna niż równania normalne
- Unikamy formowania $A^T A$ (może zwiększyć błąd numeryczny)

**Polecenie:** Zaimplementuj metodę Grama-Schmidta do obliczenia rozkładu QR i porównaj wyniki z metodą równań normalnych.

---

## Zadanie 11: Wielokrotne wektory prawych stron

Rozwiąż układ równań $AX = B$, gdzie:

$$
A = \begin{bmatrix}
4 & -1 & 0 & 0 \\
-1 & 4 & -1 & 0 \\
0 & -1 & 4 & -1 \\
0 & 0 & -1 & 4
\end{bmatrix}, \quad
B = \begin{bmatrix}
1 & 0 & 1 \\
0 & 1 & 1 \\
0 & 1 & 2 \\
1 & 0 & 1
\end{bmatrix}
$$

**Wskazówka:** Faktoryzacja macierzy $A$ wykonywana jest **raz**, a następnie rozwiązujemy dla każdej kolumny $B$ osobno.

---

## Zadania programistyczne

### P1: Klasa macierzy rzadkiej

Zaprojektuj i zaimplementuj klasę `SparseMatrix` do reprezentacji macierzy rzadkich w formacie:
- COO (Coordinate format)
- CSR (Compressed Sparse Row)
- Trójdiagonalnym

Zaimplementuj operacje:
- Mnożenie macierz-wektor
- Dodawanie macierzy
- Transpozycja

### P2: Generator układów równań

Napisz program generujący układy równań z macierzą trójdiagonalną o zadanych własnościach:
- Diagonalnie dominująca
- Symetryczna dodatnio określona
- O zadanym wskaźniku uwarunkowania

### P3: Wizualizacja

Napisz program (używając biblioteki graficznej lub generujący pliki dla gnuplot) wizualizujący:
- Strukturę macierzy rzadkiej
- Proces eliminacji w algorytmie Thomasa
- Dopasowanie krzywej metodą najmniejszych kwadratów
