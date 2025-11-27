# Zajęcia nr 7: Metody iteracyjne rozwiązywania układów równań liniowych

## Zagadnienia do opanowania

- Metody iteracyjne rozwiązywania układów liniowych równań algebraicznych
- Metody: Richardsona, Jacobiego, Gaussa-Seidela, SOR
- Kryteria zbieżności metod iteracyjnych

---

## Zadanie 1

Dany jest układ równań liniowych $Ax = b$, gdzie:

$$
A = \begin{bmatrix} 5 & 1 \\ 4 & 10 \end{bmatrix}, \quad
b = \begin{bmatrix} 49 \\ 30 \end{bmatrix}
$$

**Polecenie:** Oceń zbieżność metody iteracyjnej Jacobiego (w normie maksimum) dla tego układu, posługując się twierdzeniem Banacha o kontrakcji.

### Wskazówki:
- Wyznacz macierz iteracji Jacobiego: $T_J = -D^{-1}(L + U)$
- Oblicz normę maksimum macierzy iteracji: $\|T_J\|_\infty$
- Sprawdź warunek zbieżności: $\|T_J\|_\infty < 1$

---

## Zadanie 2

Dany jest układ liniowych równań algebraicznych $Ax = b$, gdzie:

$$
A = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix}, \quad
b = \begin{bmatrix} 1 \\ 2 \end{bmatrix}
$$

**Polecenie:** Zbadaj i oceń, czy metoda iteracyjna Richardsona jest zbieżna dla tych danych.

Następnie, mając dane przybliżenie początkowe:

$$
x_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}
$$

wyznacz kolejne przybliżenie $x_1$ za pomocą tej metody.

### Wskazówki:
- Metoda Richardsona: $x^{(k+1)} = x^{(k)} + \alpha(b - Ax^{(k)})$
- Zbadaj warunki zbieżności dla różnych wartości parametru $\alpha$

---

## Zadanie 3

Dany jest układ liniowych równań algebraicznych $Ax = b$, gdzie:

$$
A = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix}, \quad
b = \begin{bmatrix} 1 \\ 2 \end{bmatrix}
$$

**Polecenie:** Zbadaj i oceń, czy metoda iteracyjna Gaussa-Seidela jest zbieżna dla tych danych.

Następnie, mając dane przybliżenie początkowe:

$$
x_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}
$$

wyznacz kolejne przybliżenie $x_1$ za pomocą tej metody.

### Wskazówki:
- Metoda Gaussa-Seidela: $x_i^{(k+1)} = \frac{1}{a_{ii}}\left(b_i - \sum_{j<i} a_{ij}x_j^{(k+1)} - \sum_{j>i} a_{ij}x_j^{(k)}\right)$
- Macierz iteracji: $T_{GS} = -(D + L)^{-1}U$
- Sprawdź warunek zbieżności

---

## Zadanie 4

Dany jest układ liniowych równań algebraicznych $Ax = b$, gdzie:

$$
A = \begin{bmatrix} 5 & 1 \\ 2 & 4 \end{bmatrix}, \quad
b = \begin{bmatrix} 1 \\ 2 \end{bmatrix}
$$

**Polecenie:** Zbadaj i oceń, czy metoda iteracyjna SOR (z parametrem $\omega = 1/2$) jest zbieżna dla tych danych.

Następnie, mając dane przybliżenie początkowe:

$$
x_0 = \begin{bmatrix} 1 \\ 1 \end{bmatrix}
$$

wyznacz kolejne przybliżenie $x_1$ za pomocą tej metody.

### Wskazówki:
- Metoda SOR (Successive Over-Relaxation):
$$
x_i^{(k+1)} = (1-\omega)x_i^{(k)} + \frac{\omega}{a_{ii}}\left(b_i - \sum_{j<i} a_{ij}x_j^{(k+1)} - \sum_{j>i} a_{ij}x_j^{(k)}\right)
$$
- Dla $\omega = 1/2$ metoda jest niedorelaksowana (underrelaxation)
- Macierz iteracji: $T_{SOR} = (D + \omega L)^{-1}[(1-\omega)D - \omega U]$

---

## Program główny

Napisz program w języku C/C++, rozwiązujący układ pięciu równań liniowych $Ax = b$ metodami iteracyjnymi:
- (a) Jacobiego
- (b) Gaussa-Seidela
- (c) SOR z parametrem $\omega = 1/2$

### Dane wejściowe:

Macierz współczynników:

$$
A = \begin{bmatrix}
50 & 5 & 4 & 3 & 2 \\
1 & 40 & 1 & 2 & 3 \\
4 & 5 & 30 & -5 & -4 \\
-3 & -2 & -1 & 20 & 0 \\
1 & 2 & 3 & 4 & 30
\end{bmatrix}
$$

Wektor prawej strony:

$$
b = \begin{bmatrix} 140 \\ 67 \\ 62 \\ 89 \\ 153 \end{bmatrix}
$$

Przybliżenie początkowe:

$$
x_0 = \begin{bmatrix} 6 \\ 6 \\ 6 \\ 6 \\ 6 \end{bmatrix}
$$

### Wymagania programu:

1. **Trzy niezależne kryteria zakończenia iteracji:**
   - Maksymalna liczba iteracji (np. 1000)
   - Kryterium residuum: $\|b - Ax^{(k)}\| < \varepsilon$
   - Kryterium błędu względnego: $\|x^{(k+1)} - x^{(k)}\| < \varepsilon$

2. **Wyświetlanie wyników pośrednich:**
   - Numer iteracji
   - Aktualne przybliżenie $x^{(k)}$
   - Estymator błędu: $\|x^{(k+1)} - x^{(k)}\|$
   - Residuum: $\|b - Ax^{(k)}\|$

3. **Porównanie metod:**
   - Liczba iteracji potrzebna do osiągnięcia zadanej dokładności
   - Szybkość zbieżności
   - Dokładność końcowego rozwiązania

### Obserwacje do wykonania:

- Jak zmienia się estymator błędu w kolejnych iteracjach?
- Jak zmienia się residuum układu w kolejnych iteracjach?
- Która metoda jest najszybsza dla tego problemu?
- Czy wszystkie metody są zbieżne?

---

## Teoria - przypomnienie

### Metoda Jacobiego

Rozkład macierzy: $A = D + L + U$, gdzie:
- $D$ - macierz diagonalna
- $L$ - dolnotrójkątna (bez diagonali)
- $U$ - górnotrójkątna (bez diagonali)

Wzór iteracyjny:
$$
x^{(k+1)} = D^{-1}(b - (L + U)x^{(k)})
$$

lub składnikowo:
$$
x_i^{(k+1)} = \frac{1}{a_{ii}}\left(b_i - \sum_{j \neq i} a_{ij}x_j^{(k)}\right)
$$

### Metoda Gaussa-Seidela

Wzór iteracyjny:
$$
x^{(k+1)} = (D + L)^{-1}(b - Ux^{(k)})
$$

lub składnikowo:
$$
x_i^{(k+1)} = \frac{1}{a_{ii}}\left(b_i - \sum_{j<i} a_{ij}x_j^{(k+1)} - \sum_{j>i} a_{ij}x_j^{(k)}\right)
$$

### Metoda SOR

Wzór iteracyjny z parametrem relaksacji $\omega$:
$$
x_i^{(k+1)} = (1-\omega)x_i^{(k)} + \frac{\omega}{a_{ii}}\left(b_i - \sum_{j<i} a_{ij}x_j^{(k+1)} - \sum_{j>i} a_{ij}x_j^{(k)}\right)
$$

Przypadki szczególne:
- $\omega = 1$ → metoda Gaussa-Seidela
- $0 < \omega < 1$ → niedorelaksacja (underrelaxation)
- $1 < \omega < 2$ → nadrelaksacja (overrelaxation)

### Warunki zbieżności

1. **Warunek wystarczający (ogólny):** Promień spektralny macierzy iteracji $\rho(T) < 1$

2. **Kryterium dominacji diagonalnej:**
   - Silna dominacja wierszowa: $|a_{ii}| > \sum_{j \neq i} |a_{ij}|$ dla każdego $i$
   - Silna dominacja kolumnowa: $|a_{jj}| > \sum_{i \neq j} |a_{ij}|$ dla każdego $j$

3. **Dla macierzy dodatnio określonych i symetrycznych:**
   - Metoda Gaussa-Seidela jest zbieżna
   - Metoda SOR jest zbieżna dla $0 < \omega < 2$
