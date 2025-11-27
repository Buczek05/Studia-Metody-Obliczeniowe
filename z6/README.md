# Zajęcia nr 6: Metody rozwiązywania układów równań z macierzami rzadkimi

## Zagadnienia

1. **Metody bezpośrednie rozwiązywania układów liniowych równań algebraicznych z macierzami rzadkimi**
2. **Algorytm Thomasa** - efektywna metoda dla macierzy trójdiagonalnych
3. **Metody rozwiązywania nad-określonych układów liniowych równań algebraicznych**

## Zawartość

- `zadania.md` - Rozwiązanie zadania 1 (pseudorozwiązanie metodą najmniejszych kwadratów)
- `thomas_algorithm.cpp` - Implementacja algorytmu Thomasa w C++

## Kompilacja i uruchomienie

```bash
# Kompilacja
g++ -std=c++11 -o thomas thomas_algorithm.cpp

# Uruchomienie
./thomas
```

## Algorytm Thomasa - Opis teoretyczny

### Co to jest macierz trójdiagonalna?

Macierz trójdiagonalna to macierz kwadratowa, która ma niezerowe elementy tylko na trzech diagonalach:
- **Diagonala główna** - elementy $a_{ii}$
- **Naddiagonala** - elementy $a_{i,i+1}$ (powyżej głównej)
- **Poddiagonala** - elementy $a_{i,i-1}$ (poniżej głównej)

Przykład macierzy trójdiagonalnej 5×5:

$$
A = \begin{bmatrix}
b_0 & c_0 & 0 & 0 & 0 \\
a_1 & b_1 & c_1 & 0 & 0 \\
0 & a_2 & b_2 & c_2 & 0 \\
0 & 0 & a_3 & b_3 & c_3 \\
0 & 0 & 0 & a_4 & b_4
\end{bmatrix}
$$

### Dlaczego algorytm Thomasa?

- **Standardowa eliminacja Gaussa**: złożoność $O(n^3)$
- **Algorytm Thomasa dla macierzy trójdiagonalnej**: złożoność $O(n)$
- **Użycie pamięci**: zamiast $O(n^2)$ potrzebujemy tylko $O(n)$ (trzy wektory)

### Algorytm

Algorytm Thomasa składa się z dwóch faz:

#### Faza 1: Forward Elimination (Eliminacja w przód)

Modyfikujemy współczynniki macierzy:

$$
\begin{aligned}
b'_0 &= b_0 \\
b'_i &= b_i - \frac{a_i \cdot c_{i-1}}{b'_{i-1}}, \quad i = 1, 2, \ldots, n-1
\end{aligned}
$$

#### Faza 2: Modyfikacja wektora prawych stron i podstawianie wstecz

Modyfikacja wektora $d$:

$$
\begin{aligned}
d'_0 &= d_0 \\
d'_i &= d_i - \frac{a_i \cdot d'_{i-1}}{b'_{i-1}}, \quad i = 1, 2, \ldots, n-1
\end{aligned}
$$

Podstawianie wstecz (Back Substitution):

$$
\begin{aligned}
x_{n-1} &= \frac{d'_{n-1}}{b'_{n-1}} \\
x_i &= \frac{d'_i - c_i \cdot x_{i+1}}{b'_i}, \quad i = n-2, n-3, \ldots, 0
\end{aligned}
$$

### Struktura programu

Program składa się z dwóch głównych procedur zgodnie z wymaganiami zadania:

1. **`thomas_forward_elimination(a, b, c, n)`**
   - Operuje wyłącznie na macierzy A (wektorach a, b, c)
   - Wykonuje eliminację w przód
   - Modyfikuje wektor b (diagonalę główną)

2. **`thomas_solve(a, b, c, d, n)`**
   - Operuje wyłącznie na wektorze d
   - Wykorzystuje zmodyfikowane współczynniki z pierwszej procedury
   - Wykonuje forward elimination dla wektora d oraz back substitution
   - Wynik zapisywany jest w wektorze d

### Reprezentacja macierzy trójdiagonalnej

**Ważne:** Zgodnie z instrukcją zadania, **NIE NALEŻY** używać tablic kwadratowych do reprezentacji macierzy trójdiagonalnej. Zamiast tego używamy trzech wektorów:

```cpp
vector<double> a;  // poddiagonala (n elementów, a[0] nie jest używane)
vector<double> b;  // diagonala główna (n elementów)
vector<double> c;  // naddiagonala (n elementów, c[n-1] nie jest używane)
```

To podejście:
- Oszczędza pamięć: $3n$ zamiast $n^2$ elementów
- Jest bardziej efektywne dla pamięci podręcznej
- Odzwierciedla rzeczywistą strukturę rzadką macierzy

## Metoda najmniejszych kwadratów

### Problem

Dla nad-określonego układu równań (więcej równań niż niewiadomych):

$$
Ax = b
$$

gdzie $A \in \mathbb{R}^{m \times n}$ i $m > n$

### Rozwiązanie

Pseudorozwiązanie minimalizujące $\|Ax - b\|^2$ znajdujemy rozwiązując **układ równań normalnych**:

$$
A^T A x = A^T b
$$

Rozwiązanie:

$$
x = (A^T A)^{-1} A^T b
$$

### Własności

- Rozwiązanie istnieje i jest jednoznaczne, gdy $\text{rank}(A) = n$
- Macierz $A^T A$ jest symetryczna i dodatnio określona
- Można użyć efektywnych metod numerycznych (np. rozkład Choleskiego)

## Wyniki

### Przykład z zadania

Dla układu równań z macierzą:

$$
A = \begin{bmatrix}
100 & -1 & 0 & 0 & 0 \\
2 & 200 & -3 & 0 & 0 \\
0 & 4 & 300 & 5 & 0 \\
0 & 0 & -6 & 200 & -7 \\
0 & 0 & 0 & -8 & 100
\end{bmatrix}, \quad
b = \begin{bmatrix}
199 \\ 195 \\ 929 \\ 954 \\ 360
\end{bmatrix}
$$

**Rozwiązanie:**
$$
x = \begin{bmatrix}
2 \\ 1 \\ 3 \\ 5 \\ 4
\end{bmatrix}
$$

**Weryfikacja:** $Ax = b$ z dokładnością do błędu maszynowego ($< 10^{-15}$)

### Przykład testowy

Dla prostego układu:
$$
\begin{cases}
2x_1 - x_2 = 1 \\
-x_1 + 2x_2 - x_3 = 0 \\
-x_2 + 2x_3 = 1
\end{cases}
$$

**Rozwiązanie:** $x_1 = x_2 = x_3 = 1$

## Zastosowania

Macierze trójdiagonalne występują w:
- Metodach różnic skończonych dla równań różniczkowych
- Interpolacji funkcjami sklejanymi (spline)
- Mechanice (układy mas połączonych sprężynami)
- Finansach (modele wyceny opcji)
- Przetwarzaniu sygnałów (filtry cyfrowe)

## Literatura

1. Numerical Recipes in C++
2. Gene H. Golub, Charles F. Van Loan - "Matrix Computations"
3. Kincaid, Cheney - "Numerical Analysis"
