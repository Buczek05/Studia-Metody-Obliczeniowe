# Zajęcia nr 4: Rozwiązywanie układów nieliniowych równań algebraicznych

## Zagadnienia do opanowania
- Rozwiązywanie układów nieliniowych równań algebraicznych
- Uogólniona metoda Newtona

---

## Zadania

### Zadanie 1: Wyprowadzenie równań metody Newtona

Napisz równania uogólnionej metody Newtona w zastosowaniu do układu równań nieliniowych:

$$
\begin{cases}
x^2 + y^2 + z^2 = 4 \\
x^2 + \frac{y^2}{2} = 1 \\
xy = \frac{1}{2}
\end{cases}
$$

#### Teoria

Uogólniona metoda Newtona dla układu $n$ równań nieliniowych $\mathbf{F}(\mathbf{x}) = \mathbf{0}$, gdzie:

$$\mathbf{F}(\mathbf{x}) = \begin{bmatrix} F_1(x_1, x_2, \ldots, x_n) \\ F_2(x_1, x_2, \ldots, x_n) \\ \vdots \\ F_n(x_1, x_2, \ldots, x_n) \end{bmatrix} = \mathbf{0}$$

opiera się na schemacie iteracyjnym:

$$\mathbf{x}^{(k+1)} = \mathbf{x}^{(k)} - \mathbf{J}^{-1}(\mathbf{x}^{(k)}) \cdot \mathbf{F}(\mathbf{x}^{(k)})$$

gdzie $\mathbf{J}(\mathbf{x})$ jest macierzą Jacobiego:

$$\mathbf{J}(\mathbf{x}) = \begin{bmatrix}
\frac{\partial F_1}{\partial x_1} & \frac{\partial F_1}{\partial x_2} & \cdots & \frac{\partial F_1}{\partial x_n} \\
\frac{\partial F_2}{\partial x_1} & \frac{\partial F_2}{\partial x_2} & \cdots & \frac{\partial F_2}{\partial x_n} \\
\vdots & \vdots & \ddots & \vdots \\
\frac{\partial F_n}{\partial x_1} & \frac{\partial F_n}{\partial x_2} & \cdots & \frac{\partial F_n}{\partial x_n}
\end{bmatrix}$$

W praktyce zamiast obliczać $\mathbf{J}^{-1}$, rozwiązuje się układ równań liniowych:

$$\mathbf{J}(\mathbf{x}^{(k)}) \cdot \Delta\mathbf{x}^{(k)} = -\mathbf{F}(\mathbf{x}^{(k)})$$

gdzie $\Delta\mathbf{x}^{(k)} = \mathbf{x}^{(k+1)} - \mathbf{x}^{(k)}$

#### Rozwiązanie dla zadanego układu

Przekształcamy układ do postaci $\mathbf{F}(\mathbf{x}) = \mathbf{0}$:

$$\mathbf{F}(x, y, z) = \begin{bmatrix}
F_1(x, y, z) \\
F_2(x, y, z) \\
F_3(x, y, z)
\end{bmatrix} = \begin{bmatrix}
x^2 + y^2 + z^2 - 4 \\
x^2 + \frac{y^2}{2} - 1 \\
xy - \frac{1}{2}
\end{bmatrix} = \begin{bmatrix} 0 \\ 0 \\ 0 \end{bmatrix}$$

**Macierz Jacobiego:**

$$\mathbf{J}(x, y, z) = \begin{bmatrix}
\frac{\partial F_1}{\partial x} & \frac{\partial F_1}{\partial y} & \frac{\partial F_1}{\partial z} \\
\frac{\partial F_2}{\partial x} & \frac{\partial F_2}{\partial y} & \frac{\partial F_2}{\partial z} \\
\frac{\partial F_3}{\partial x} & \frac{\partial F_3}{\partial y} & \frac{\partial F_3}{\partial z}
\end{bmatrix} = \begin{bmatrix}
2x & 2y & 2z \\
2x & y & 0 \\
y & x & 0
\end{bmatrix}$$

**Schemat iteracyjny:**

W każdej iteracji $k$:

1. Oblicz wektor wartości funkcji:
   $$\mathbf{F}(\mathbf{x}^{(k)}) = \begin{bmatrix}
   (x^{(k)})^2 + (y^{(k)})^2 + (z^{(k)})^2 - 4 \\
   (x^{(k)})^2 + \frac{(y^{(k)})^2}{2} - 1 \\
   x^{(k)} y^{(k)} - \frac{1}{2}
   \end{bmatrix}$$

2. Oblicz macierz Jacobiego:
   $$\mathbf{J}(\mathbf{x}^{(k)}) = \begin{bmatrix}
   2x^{(k)} & 2y^{(k)} & 2z^{(k)} \\
   2x^{(k)} & y^{(k)} & 0 \\
   y^{(k)} & x^{(k)} & 0
   \end{bmatrix}$$

3. Rozwiąż układ równań liniowych:
   $$\mathbf{J}(\mathbf{x}^{(k)}) \cdot \begin{bmatrix} \Delta x \\ \Delta y \\ \Delta z \end{bmatrix} = -\mathbf{F}(\mathbf{x}^{(k)})$$

4. Zaktualizuj rozwiązanie:
   $$\begin{bmatrix} x^{(k+1)} \\ y^{(k+1)} \\ z^{(k+1)} \end{bmatrix} = \begin{bmatrix} x^{(k)} \\ y^{(k)} \\ z^{(k)} \end{bmatrix} + \begin{bmatrix} \Delta x \\ \Delta y \\ \Delta z \end{bmatrix}$$

---

### Zadanie 2: Kryteria stopu

Zaproponuj i uzasadnij trzy niezależne kryteria zakończenia iteracji dla metody Newtona.

**Rozwiązanie:**

1. **Kryterium normy poprawki** (błąd bezwzględny):
   $$\|\Delta\mathbf{x}^{(k)}\| = \|\mathbf{x}^{(k+1)} - \mathbf{x}^{(k)}\| < \varepsilon_1$$

   Jeśli zmiana rozwiązania między iteracjami jest mała, można uznać że osiągnięto zbieżność.

2. **Kryterium residuum** (wartość funkcji):
   $$\|\mathbf{F}(\mathbf{x}^{(k)})\| < \varepsilon_2$$

   Jeśli wektor wartości funkcji jest bliski zeru, rozwiązanie spełnia układ równań.

3. **Maksymalna liczba iteracji**:
   $$k \geq k_{\max}$$

   Zabezpieczenie przed nieskończoną pętlą w przypadku braku zbieżności.

Typowe normy używane w kryteriach: norma euklidesowa $\|\mathbf{v}\| = \sqrt{\sum_i v_i^2}$ lub norma maksimum $\|\mathbf{v}\|_\infty = \max_i |v_i|$.

---

### Zadanie 3: Analiza zbieżności

Dla zadanego układu równań:
- Znajdź analitycznie jedno z rozwiązań (jeśli możliwe)
- Zaproponuj dobre przybliżenie początkowe
- Przewidź, czy metoda Newtona będzie zbieżna dla różnych punktów startowych

**Wskazówki:**

Z równania trzeciego: $xy = \frac{1}{2}$, więc $y = \frac{1}{2x}$

Podstawiając do równania drugiego:
$$x^2 + \frac{1}{8x^2} = 1$$
$$8x^4 - 8x^2 + 1 = 0$$

To równanie kwadratowe względem $x^2$:
$$x^2 = \frac{8 \pm \sqrt{64 - 32}}{16} = \frac{8 \pm \sqrt{32}}{16} = \frac{8 \pm 4\sqrt{2}}{16} = \frac{2 \pm \sqrt{2}}{4}$$

Możliwe przybliżenia początkowe do przetestowania:
- $\mathbf{x}_0 = [0.9, 0.6, 1.5]^T$
- $\mathbf{x}_0 = [1.0, 0.5, 1.7]^T$
- $\mathbf{x}_0 = [-0.9, -0.6, 1.5]^T$

---

## Program do implementacji

Napisz program w C++ realizujący uogólnioną metodę Newtona dla układu z Zadania 1. Program powinien:

1. ✓ Implementować funkcje obliczające $\mathbf{F}(\mathbf{x})$ i $\mathbf{J}(\mathbf{x})$
2. ✓ Rozwiązywać układ równań liniowych (eliminacja Gaussa z wyborem elementu głównego)
3. ✓ Stosować wszystkie trzy kryteria stopu
4. ✓ Wyświetlać szczegółowe informacje dla każdej iteracji:
   - Numer iteracji
   - Aktualne przybliżenie $[x, y, z]$
   - Wartości funkcji $\mathbf{F}(\mathbf{x})$
   - Normę residuum $\|\mathbf{F}(\mathbf{x})\|$
   - Poprawkę $\Delta\mathbf{x}$
   - Normę poprawki $\|\Delta\mathbf{x}\|$
5. ✓ Umożliwiać łatwą zmianę przybliżenia początkowego i parametrów tolerancji
