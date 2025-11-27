# Zajęcia nr 11 - Metody rozwiązywania równań różniczkowych cząstkowych

## Zagadnienia do opanowania

Metody rozwiązywania zagadnień z warunkiem początkowym i brzegowym dla równań różniczkowych cząstkowych w przestrzeni jednowymiarowej.

---

## Zadanie 1: Równanie dyfuzji

Dane jest równanie różniczkowe cząstkowe dyfuzji:

$$\frac{\partial u(x,t)}{\partial t} = D \frac{\partial^2 u(x,t)}{\partial x^2}$$

ze współczynnikiem dyfuzji $D = 1$.

### Warunki brzegowe i początkowe

- **Dziedzina przestrzenna:** $x \in [-1, 1]$
- **Warunek początkowy:** $u(x, 0) = x^3$
- **Warunki brzegowe:**
  - $u(-1, t) = -1 - t$
  - $u(1, t) = 1 + t$

### Parametry dyskretyzacji

- **Węzły przestrzenne (jednorodna siatka):** $x_0 = -1$, $x_1 = 0$, $x_2 = 1$
- **Krok przestrzenny:** $\Delta x = 1$
- **Krok czasowy:** $\delta t = 1$
- **Czas docelowy:** $t = 1$

### Polecenia

Wyznacz przybliżone wartości rozwiązania w węzłach przestrzennych dla $t = 1$, stosując następujące metody:

#### a) Metoda klasyczna bezpośrednia (explicit)

Schemat:
$$\frac{u_i^{n+1} - u_i^n}{\delta t} = D \frac{u_{i+1}^n - 2u_i^n + u_{i-1}^n}{(\Delta x)^2}$$

**Zadanie:** Oblicz wartości $u_1^1$ (wartość w $x=0$ w chwili $t=1$) oraz uzasadnij, czy metoda jest numerycznie stabilna dla podanych parametrów.

**Warunek stabilności:** $\lambda = \frac{D \cdot \delta t}{(\Delta x)^2} \leq \frac{1}{2}$

#### b) Metoda Laasonen (fully implicit)

Schemat:
$$\frac{u_i^{n+1} - u_i^n}{\delta t} = D \frac{u_{i+1}^{n+1} - 2u_i^{n+1} + u_{i-1}^{n+1}}{(\Delta x)^2}$$

**Zadanie:** Wyprowadź układ równań liniowych dla warstwy czasowej $n+1$, rozwiąż go i oblicz wartości w węzłach wewnętrznych. Omów stabilność metody.

**Uwaga:** Metoda Laasonen jest bezwarunkowo stabilna.

#### c) Metoda Cranka-Nicolson

Schemat:
$$\frac{u_i^{n+1} - u_i^n}{\delta t} = \frac{D}{2} \left[ \frac{u_{i+1}^{n+1} - 2u_i^{n+1} + u_{i-1}^{n+1}}{(\Delta x)^2} + \frac{u_{i+1}^n - 2u_i^n + u_{i-1}^n}{(\Delta x)^2} \right]$$

**Zadanie:** Wyprowadź układ równań liniowych, rozwiąż go i oblicz wartości w węzłach wewnętrznych. Omów stabilność metody.

**Uwaga:** Metoda Cranka-Nicolson jest bezwarunkowo stabilna i ma dokładność $O(\delta t^2, (\Delta x)^2)$.

### Analiza stabilności

Dla każdej metody:
1. Oblicz parametr stabilności $\lambda = \frac{D \cdot \delta t}{(\Delta x)^2}$
2. Sprawdź warunki stabilności numerycznej
3. Porównaj uzyskane wyniki

---

## Zadanie 2: Uogólnienie dla równania reakcji-dyfuzji

Rozważmy równanie reakcji-dyfuzji:

$$\frac{\partial U(x,t)}{\partial t} = D \frac{\partial^2 U(x,t)}{\partial x^2} - r U(x,t)$$

gdzie $r$ jest stałą szybkości reakcji.

### Warunki brzegowe (Dirichleta)

- $U(0, t) = \alpha(t)$
- $U(L, t) = \beta(t)$

### Polecenia

#### a) Uogólnienie metody Laasonen

Wyprowadź układ algebraicznych równań liniowych dla metody Laasonen zastosowanej do równania reakcji-dyfuzji. Załóż jednorodną siatkę czasowo-przestrzenną:
- Węzły przestrzenne: $x_i = i \cdot \Delta x$, gdzie $i = 0, 1, 2, \ldots, N$ i $\Delta x = L/N$
- Krok czasowy: $\delta t$

**Wskazówka:** Schemat Laasonen dla równania reakcji-dyfuzji ma postać:
$$\frac{U_i^{n+1} - U_i^n}{\delta t} = D \frac{U_{i+1}^{n+1} - 2U_i^{n+1} + U_{i-1}^{n+1}}{(\Delta x)^2} - r U_i^{n+1}$$

Przekształć to do postaci macierzowej $\mathbf{A} \mathbf{U}^{n+1} = \mathbf{b}^n$.

#### b) Uogólnienie metody Cranka-Nicolson

Wyprowadź układ algebraicznych równań liniowych dla metody Cranka-Nicolson zastosowanej do równania reakcji-dyfuzji.

**Wskazówka:** Schemat Cranka-Nicolson dla równania reakcji-dyfuzji:
$$\frac{U_i^{n+1} - U_i^n}{\delta t} = \frac{D}{2} \left[ \frac{U_{i+1}^{n+1} - 2U_i^{n+1} + U_{i-1}^{n+1}}{(\Delta x)^2} + \frac{U_{i+1}^n - 2U_i^n + U_{i-1}^n}{(\Delta x)^2} \right] - \frac{r}{2}(U_i^{n+1} + U_i^n)$$

Przekształć to do postaci macierzowej $\mathbf{A} \mathbf{U}^{n+1} = \mathbf{B} \mathbf{U}^n + \mathbf{b}$.

### Struktura macierzy

Dla obu metod wypisz:
1. Postać macierzy współczynników (macierz trójdiagonalna)
2. Elementy na diagonali głównej i pobocznych
3. Wektor prawej strony z uwzględnieniem warunków brzegowych

---

## Pytania kontrolne

1. Jaka jest różnica między metodami jawnymi (explicit) a niejawnymi (implicit)?
2. Co oznacza bezwarunkowa stabilność metody?
3. Dlaczego metoda Cranka-Nicolson ma wyższą dokładność niż metody Laasonen?
4. Jak obecność członu reakcyjnego ($-rU$) wpływa na stabilność schematów numerycznych?
5. Jakie są zalety i wady stosowania mniejszych kroków czasowych $\delta t$?

---

## Dodatkowe zadania (opcjonalne)

1. Zaimplementuj wszystkie trzy metody z Zadania 1 w programie komputerowym
2. Porównaj wyniki z rozwiązaniem analitycznym (jeśli dostępne)
3. Zbadaj wpływ rozmiaru siatki na dokładność rozwiązania
4. Sprawdź eksperymentalnie warunki stabilności dla metody explicit
