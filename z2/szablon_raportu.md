# Raport z zajęć - Metody Obliczeniowe (Zajęcia 2)

**Autor:** [Imię i Nazwisko]
**Data:** [Data wykonania]
**Grupa:** [Numer grupy]

---

## 1. Cel ćwiczenia

Celem ćwiczenia było zbadanie:
- Uwarunkowania zadań obliczeniowych
- Błędów maszynowych w arytmetyce zmiennoprzecinkowej
- Zjawiska utraty cyfr znaczących
- Stabilności numerycznej algorytmów

---

## 2. Zadania teoretyczne

### Zadanie 1: Uwarunkowanie iloczynu i ilorazu

#### Obliczenia:

[Tu wpisz swoje obliczenia wskaźnika uwarunkowania]

$$\kappa_{\text{iloczyn}} = \ldots$$

$$\kappa_{\text{iloraz}} = \ldots$$

#### Wnioski:

[Tu opisz swoje wnioski]

---

### Zadanie 2: Algorytmy obliczania $a^2 - b^2$

#### Test numeryczny:

```cpp
// Kod testowy
double a = 1.0000001;
double b = 1.0;

double A1 = a*a - b*b;
double A2 = (a-b)*(a+b);

// Wartość dokładna (obliczona w wyższej precyzji)
double exact = ...;

double error_A1 = abs(A1 - exact) / abs(exact);
double error_A2 = abs(A2 - exact) / abs(exact);
```

#### Wyniki:

| Algorytm | Wynik | Błąd względny |
|----------|-------|---------------|
| A₁ | ... | ... |
| A₂ | ... | ... |

#### Wnioski:

[Który algorytm jest lepszy i dlaczego?]

---

### Zadanie 3: Uwarunkowanie funkcji $(1+x)^{-1}$

#### Wzór na wskaźnik uwarunkowania:

$$\kappa(x) = \ldots$$

#### Analiza:

- Dla $x \to 0$: $\kappa \approx$ ...
- Dla $x \to -1$: $\kappa \approx$ ...
- Dla $|x| \gg 1$: $\kappa \approx$ ...

#### Wykres:

[Tu wklej wykres κ(x) lub opisz jego przebieg]

---

### Zadanie 4: Obliczanie $\ln(x)$ dla $x \approx 1$

#### Kod testowy:

```cpp
#include <cmath>
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::setprecision(17);

    double t1 = 1e-15;
    double t2 = 1e-12;
    double t3 = 1e-10;

    // Metoda 1: log(1+t)
    std::cout << "log(1+" << t1 << ") = " << log(1.0 + t1) << std::endl;

    // Metoda 2: log1p(t)
    std::cout << "log1p(" << t1 << ") = " << log1p(t1) << std::endl;

    // Porównanie
    std::cout << "Dokładna wartość: " << t1 << std::endl;
}
```

#### Wyniki:

| $t$ | `log(1+t)` | `log1p(t)` | Wartość dokładna | Błąd względny `log` | Błąd względny `log1p` |
|-----|------------|------------|------------------|---------------------|----------------------|
| $10^{-15}$ | ... | ... | $10^{-15}$ | ... | ... |
| $10^{-12}$ | ... | ... | $10^{-12}$ | ... | ... |
| $10^{-10}$ | ... | ... | $10^{-10}$ | ... | ... |

#### Wnioski:

[Która metoda jest lepsza i dlaczego?]

---

## 3. Zadanie programistyczne

### Funkcja do analizy:

$$f(x) = \frac{x^3}{6[\sinh(x) - x]}$$

### Implementacja

#### Metoda naiwna:

```cpp
double compute_naive(double x) {
    // Tu wklej swój kod
}
```

#### Metoda alternatywna (szereg Taylora):

```cpp
double compute_taylor(double x) {
    // Tu wklej swój kod
}
```

### Analiza teoretyczna

#### Problem numeryczny:

Dla małych $x$:
$$\sinh(x) \approx x + \frac{x^3}{6} + O(x^5)$$

Zatem:
$$\sinh(x) - x \approx \frac{x^3}{6}$$

co prowadzi do [opisz problem].

#### Rozwiązanie:

[Opisz jak wykorzystałeś szereg Taylora]

### Wyniki numeryczne

#### Wykres błędów:

![Wykres błędów](error_analysis.png)

[Lub opisz wykres jeśli nie możesz go wkleić]

#### Obserwacje z wykresu:

1. **Zakres $x \in [10^{-10}, 10^{-2}]$:**
   - Metoda naiwna: błąd rzędu ...
   - Metoda Taylora: błąd rzędu ...
   - Przyczyna: ...

2. **Zakres $x \in [10^{-1}, 10^2]$:**
   - Obie metody: ...

3. **Zakres $x \in [10^2, 10^3]$:**
   - Obserwacje: ...

#### Tabela wybranych wartości:

| $x$ | $\log_{10}(x)$ | Metoda naiwna | Metoda Taylora | Metoda hybrydowa | Błąd naiwny | Błąd Taylor |
|-----|----------------|---------------|----------------|------------------|-------------|-------------|
| $10^{-10}$ | -10 | ... | ... | ... | ... | ... |
| $10^{-5}$ | -5 | ... | ... | ... | ... | ... |
| $10^{-2}$ | -2 | ... | ... | ... | ... | ... |
| $1$ | 0 | ... | ... | ... | ... | ... |
| $10$ | 1 | ... | ... | ... | ... | ... |
| $100$ | 2 | ... | ... | ... | ... | ... |

### Metoda hybrydowa

#### Algorytm decyzyjny:

```cpp
double compute_hybrid(double x) {
    const double threshold = ...; // Wybrany próg

    if (abs(x) < threshold) {
        return compute_taylor(x);
    } else {
        return compute_naive(x);
    }
}
```

#### Uzasadnienie wyboru progu:

[Wyjaśnij dlaczego wybrałeś taki próg przełączenia]

### Analiza błędów

#### Błąd względny:

$$\delta(x) = \frac{|f_{\text{obliczone}}(x) - f_{\text{dokładne}}(x)|}{|f_{\text{dokładne}}(x)|}$$

#### Statystyki:

| Metoda | Min błąd | Max błąd | Średni błąd |
|--------|----------|----------|-------------|
| Naiwna | ... | ... | ... |
| Taylor | ... | ... | ... |
| Hybrydowa | ... | ... | ... |

---

## 4. Odpowiedzi na pytania kontrolne

### Jaki typ zmiennych należy zastosować i dlaczego?

[Twoja odpowiedź: float, double, czy long double?]

**Uzasadnienie:**
- Precyzja: ...
- Zakres: ...
- Wydajność: ...

### W którym zakresie występuje utrata cyfr znaczących?

[Twoja analiza]

### Dlaczego szereg Taylora działa lepiej dla małych x?

[Twoje wyjaśnienie]

---

## 5. Wnioski końcowe

### Wnioski teoretyczne:

1. [Wniosek 1]
2. [Wniosek 2]
3. [Wniosek 3]

### Wnioski praktyczne:

1. [Wniosek praktyczny 1]
2. [Wniosek praktyczny 2]
3. [Wniosek praktyczny 3]

### Napotkane problemy:

[Opisz problemy i jak je rozwiązałeś]

### Możliwe ulepszenia:

[Zaproponuj ulepszenia programu]

---

## 6. Bibliografia

1. Press W.H. et al., "Numerical Recipes in C++", Cambridge University Press
2. Higham N.J., "Accuracy and Stability of Numerical Algorithms"
3. Dokumentacja C++ (cmath): https://en.cppreference.com/w/cpp/numeric/math
4. [Inne źródła]

---

## 7. Załączniki

### Kod źródłowy:

[Link do repozytorium lub załącz pliki .cpp]

### Wykresy:

[Załącz wszystkie wygenerowane wykresy]

### Dane wyjściowe:

[Próbki danych z plików results_*.txt]

---

## Ocena własnej pracy

**Co się udało:**
- [Punkt 1]
- [Punkt 2]

**Co sprawiło trudność:**
- [Punkt 1]
- [Punkt 2]

**Czego się nauczyłem:**
- [Punkt 1]
- [Punkt 2]
- [Punkt 3]

---

**Podpis:** [Twój podpis]
**Data:** [Data oddania]
