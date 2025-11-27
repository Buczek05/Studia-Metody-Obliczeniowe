# Metody Obliczeniowe - Zajęcia 2

## Zagadnienia do opanowania

- Własności zadań: uwarunkowanie zadań
- Metody oceny błędów maszynowych
- Zjawisko utraty cyfr znaczących przy odejmowaniu
- Własności algorytmów: numeryczna poprawność, numeryczna stabilność

---

## Zadania teoretyczne

### Zadanie 1: Uwarunkowanie iloczynu i ilorazu

Zbadaj uwarunkowanie (względne) zadania obliczenia:
- iloczynu $p = x \cdot y$
- ilorazu $d = x / y$

dwóch liczb rzeczywistych $x$ i $y$, oraz oszacuj wielkość względnych błędów maszynowych wyników w przypadku numerycznych obliczeń zmiennoprzecinkowych $\tilde{p}$ i $\tilde{d}$.

**Wskazówka:** Oblicz wskaźnik uwarunkowania:
$$\kappa = \left| \frac{x}{f(x)} \cdot f'(x) \right|$$

gdzie $f(x)$ jest rozważaną funkcją.

---

### Zadanie 2: Błędy obliczenia $a^2 - b^2$

Oceń błąd względny obliczenia $a^2 - b^2$ w arytmetyce fl, przy zastosowaniu algorytmów:

$$A_1(a,b) = a \cdot a - b \cdot b$$

$$A_2(a,b) = (a - b) \cdot (a + b)$$

zakładając, że $\text{rd}(a) = \tilde{a}$, $\text{rd}(b) = \tilde{b}$.

**Pytania do rozważenia:**
- Który algorytm jest lepiej uwarunkowany?
- W jakich sytuacjach może wystąpić utrata cyfr znaczących?
- Dla jakich wartości $a$ i $b$ różnica między algorytmami będzie najbardziej widoczna?

---

### Zadanie 3: Uwarunkowanie funkcji $(1+x)^{-1}$

Zbadaj uwarunkowanie (względne) zadania obliczenia wartości funkcji:

$$y = f(x) = (1 + x)^{-1}$$

**Wskazówka:**
- Oblicz $\kappa(x) = \left| \frac{x \cdot f'(x)}{f(x)} \right|$
- Przeanalizuj dla jakich wartości $x$ zadanie jest dobrze/źle uwarunkowane
- Co się dzieje gdy $x \approx -1$?

---

### Zadanie 4: Błąd obliczenia $\ln(x)$ dla $x \approx 1$

Oszacuj błąd względny obliczenia wartości funkcji standardowej $f(x) = \ln(x)$ dla:
- $x = 1 + 10^{-15}$
- $x = 1 + 10^{-12}$
- $x = 1 + 10^{-10}$

**Wskazówka:**
- Rozważ rozwinięcie Taylora: $\ln(1+t) = t - \frac{t^2}{2} + \frac{t^3}{3} - \ldots$ dla małych $t$
- Porównaj wyniki obliczenia bezpośredniego $\ln(x)$ z użyciem funkcji `log1p(t)` dostępnej w C++
- Jaki jest błąd zaokrąglenia przy reprezentacji liczb $x$ w arytmetyce zmiennoprzecinkowej?

---

## Program do realizacji

### Treść zadania programistycznego

Zaimplementuj w języku C++ algorytm obliczający przybliżone wartości funkcji:

$$f(x) = \frac{x^3}{6[\sinh(x) - x]}$$

dla $x \in [10^{-10}, 10^3]$, korzystając z funkcji standardowej `sinh()`.

### Zakres analizy

1. W oparciu o zbiór dokładnych wartości funkcji (udostępniony przez prowadzącego) zbadaj jak zmieniają się błędy względne przybliżenia funkcji w zależności od $x$.

2. Wykonaj rysunek przedstawiający zależność:
   $$\log_{10}(|\text{błąd względny}|) \text{ od } \log_{10}(x)$$

3. Z wykresu odczytaj:
   - Zakres zmiennej $x$, w którym błąd względny pozostaje na poziomie błędu reprezentacji
   - Zakresy zmiennej $x$, w których błąd względny jest większy

4. Wyjaśnij przyczyny obserwowanych zmian błędów.

5. Zaproponuj alternatywny sposób obliczania wartości funkcji $f(x)$ w sytuacjach gdy obserwowany błąd jest duży.

6. Dokonaj stosownej modyfikacji programu, aby uzyskać błąd względny na poziomie błędu reprezentacji (tzw. dokładność maszynową) dla dowolnego $x \in [10^{-10}, 10^3]$.

### Pytania dodatkowe

- Jaki typ zmiennych należy zastosować i dlaczego?
- W którym zakresie $x$ występuje utrata cyfr znaczących?
- Jak można wykorzystać rozwinięcie w szereg Taylora funkcji $\sinh(x)$?

### Narzędzia

Do wykonania rysunku użyj programu **GNUPLOT** (dostępny za darmo z Internetu).

---

## Wskazówki teoretyczne

### Utrata cyfr znaczących

Gdy $x \to 0$:
$$\sinh(x) = x + \frac{x^3}{6} + \frac{x^5}{120} + \frac{x^7}{5040} + \ldots$$

Zatem:
$$\sinh(x) - x \approx \frac{x^3}{6} \text{ dla małych } x$$

Co sugeruje alternatywną formułę obliczeniową.

### Błąd względny

Błąd względny definiujemy jako:
$$\delta = \frac{|f_{\text{obliczone}} - f_{\text{dokładne}}|}{|f_{\text{dokładne}}|}$$

### Wskaźnik uwarunkowania

Dla funkcji jednej zmiennej $y = f(x)$:
$$\kappa(x) = \left| \frac{x \cdot f'(x)}{f(x)} \right|$$

- $\kappa \ll 1$ - zadanie dobrze uwarunkowane
- $\kappa \gg 1$ - zadanie źle uwarunkowane
