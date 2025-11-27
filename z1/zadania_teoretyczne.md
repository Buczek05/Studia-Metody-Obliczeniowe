# Zadania teoretyczne - Zajęcia nr 1

## Zadanie 1: Błąd obcięcia w rozwinięciu Taylora funkcji ln(z)

### Treść zadania
Oszacuj wielkość błędu obcięcia przy wyznaczaniu przybliżonej wartości `ln(z)` poprzez sumowanie `n` wyrazów rozwinięcia w szereg Taylora wokół `z₀ = 1`. Ile wyrazów należy zsumować, aby otrzymać błąd bezwzględny logarytmu nie większy niż `10⁻⁸` dla `z = 2`?

### Rozwiązanie

#### Szereg Taylora dla ln(z) wokół z₀ = 1

Rozwinięcie funkcji `ln(z)` w szereg Taylora wokół punktu `z₀ = 1`:

$$\ln(z) = \ln(1) + \sum_{k=1}^{\infty} \frac{(-1)^{k+1}}{k}(z-1)^k$$

Ponieważ `ln(1) = 0`, otrzymujemy:

$$\ln(z) = \sum_{k=1}^{\infty} \frac{(-1)^{k+1}}{k}(z-1)^k = (z-1) - \frac{(z-1)^2}{2} + \frac{(z-1)^3}{3} - \frac{(z-1)^4}{4} + \ldots$$

Szereg ten jest zbieżny dla `z ∈ (0, 2]`.

#### Przybliżenie n-wyrazowe

Przybliżając `ln(z)` sumą pierwszych `n` wyrazów:

$$S_n(z) = \sum_{k=1}^{n} \frac{(-1)^{k+1}}{k}(z-1)^k$$

#### Oszacowanie błędu obcięcia

Błąd obcięcia (błąd bezwzględny) wynosi:

$$E_n(z) = \left| \ln(z) - S_n(z) \right| = \left| \sum_{k=n+1}^{\infty} \frac{(-1)^{k+1}}{k}(z-1)^k \right|$$

Dla szeregu naprzemiennego spełniającego warunki twierdzenia Leibniza, błąd jest ograniczony przez pierwszy pominięty wyraz:

$$E_n(z) \leq \left| \frac{(-1)^{n+2}}{n+1}(z-1)^{n+1} \right| = \frac{|z-1|^{n+1}}{n+1}$$

#### Obliczenia dla z = 2

Dla `z = 2` mamy `z - 1 = 1`, zatem:

$$E_n(2) \leq \frac{1^{n+1}}{n+1} = \frac{1}{n+1}$$

Szukamy najmniejszego `n` takiego, że:

$$\frac{1}{n+1} \leq 10^{-8}$$

$$n+1 \geq 10^8$$

$$n \geq 10^8 - 1 = 99\,999\,999$$

### Odpowiedź

**Należy zsumować co najmniej `n = 99 999 999` wyrazów szeregu**, aby błąd bezwzględny był nie większy niż `10⁻⁸` dla `z = 2`.

**Uwaga:** To pokazuje, że rozwinięcie Taylora wokół `z₀ = 1` nie jest efektywną metodą obliczania `ln(2)`. W praktyce stosuje się inne metody, np. rozwinięcie wokół innego punktu lub wykorzystanie tożsamości logarytmicznych.

---

## Zadanie 2: Prosty system reprezentacji zmiennoprzecinkowej

### Treść zadania
Rozważ prosty system reprezentacji zmiennoprzecinkowej:

$$\text{rd}(x) = (-1)^e \cdot m \cdot 2^{z-b}$$

gdzie na mantysę oraz cechę przeznaczono po dwa bity (razem 5 bitów: 1 bit znaku + 2 bity cechy + 2 bity mantysy). Wyznacz zbiór wszystkich możliwych liczb rzeczywistych reprezentowalnych w tym systemie przy założeniu, że `b = 1`. Uwzględnij możliwość liczb znormalizowanych (`m ∈ [1, 2)`) oraz zdenormalizowanych, i określ jakie słowa maszynowe należałoby zarezerwować na `+0`, `-0`, `+INF`, `-INF` oraz reprezentacje `NaN`.

### Rozwiązanie

#### Format słowa maszynowego (5 bitów)

```
[s][ee][mm]
```
- `s` - bit znaku (1 bit): 0 = dodatnia, 1 = ujemna
- `ee` - cecha (2 bity): wartość z ∈ {0, 1, 2, 3}
- `mm` - mantysa (2 bity)

#### Parametry systemu

- Bias: `b = 1`
- Cecha rzeczywista: `E = z - b = z - 1`
- Zakres cechy: `E ∈ {-1, 0, 1, 2}` dla `z ∈ {0, 1, 2, 3}`

#### Konwencje IEEE 754 (zaadaptowane do 5-bitowego systemu)

**Wartości specjalne:**
- `z = 0` (cecha `00`): zero lub liczby zdenormalizowane
- `z = 3` (cecha `11`): nieskończoności i NaN

**Liczby znormalizowane:**
- `z ∈ {1, 2}` (cechy `01`, `10`)
- Mantysa: `m = 1.mm₂` (niejawna jedynka), czyli `m ∈ {1.00, 1.01, 1.10, 1.11}₂ = {1.0, 1.25, 1.5, 1.75}₁₀`

**Liczby zdenormalizowane:**
- `z = 0` (cecha `00`), `mm ≠ 00`
- Mantysa: `m = 0.mm₂` (bez niejawnej jedynki)
- Cecha rzeczywista: `E = -0` (aby uniknąć dodatkowego przesunięcia)

#### Rezerwacja słów maszynowych dla wartości specjalnych

| Wartość | Format | Bity |
|---------|--------|------|
| **+0** | `s=0, z=00, m=00` | `0 00 00` |
| **-0** | `s=1, z=00, m=00` | `1 00 00` |
| **+INF** | `s=0, z=11, m=00` | `0 11 00` |
| **-INF** | `s=1, z=11, m=00` | `1 11 00` |
| **NaN** | `s=*, z=11, m≠00` | `* 11 01`, `* 11 10`, `* 11 11` |

#### Liczby zdenormalizowane (z = 0, mm ≠ 00)

Dla `z = 0`, `E = -0 = 0` (specjalnie: używamy `E = 1 - b = 0` dla zdenormalizowanych):

Wartość: $(-1)^s \cdot 0.mm_2 \cdot 2^{1-b} = (-1)^s \cdot 0.mm_2 \cdot 2^0 = (-1)^s \cdot 0.mm_2$

| s | z | mm | Mantysa (dziesiętnie) | Wartość dziesiętna |
|---|---|----|-----------------------|--------------------|
| 0 | 00 | 01 | 0.25 | +0.25 |
| 0 | 00 | 10 | 0.50 | +0.50 |
| 0 | 00 | 11 | 0.75 | +0.75 |
| 1 | 00 | 01 | 0.25 | -0.25 |
| 1 | 00 | 10 | 0.50 | -0.50 |
| 1 | 00 | 11 | 0.75 | -0.75 |

#### Liczby znormalizowane (z = 1)

Dla `z = 1`, `E = 1 - 1 = 0`:

Wartość: $(-1)^s \cdot 1.mm_2 \cdot 2^0 = (-1)^s \cdot 1.mm_2$

| s | z | mm | Mantysa (dziesiętnie) | Wartość dziesiętna |
|---|---|----|-----------------------|--------------------|
| 0 | 01 | 00 | 1.00 | +1.00 |
| 0 | 01 | 01 | 1.25 | +1.25 |
| 0 | 01 | 10 | 1.50 | +1.50 |
| 0 | 01 | 11 | 1.75 | +1.75 |
| 1 | 01 | 00 | 1.00 | -1.00 |
| 1 | 01 | 01 | 1.25 | -1.25 |
| 1 | 01 | 10 | 1.50 | -1.50 |
| 1 | 01 | 11 | 1.75 | -1.75 |

#### Liczby znormalizowane (z = 2)

Dla `z = 2`, `E = 2 - 1 = 1`:

Wartość: $(-1)^s \cdot 1.mm_2 \cdot 2^1 = (-1)^s \cdot 1.mm_2 \cdot 2$

| s | z | mm | Mantysa (dziesiętnie) | Wartość dziesiętna |
|---|---|----|-----------------------|--------------------|
| 0 | 10 | 00 | 1.00 | +2.00 |
| 0 | 10 | 01 | 1.25 | +2.50 |
| 0 | 10 | 10 | 1.50 | +3.00 |
| 0 | 10 | 11 | 1.75 | +3.50 |
| 1 | 10 | 00 | 1.00 | -2.00 |
| 1 | 10 | 01 | 1.25 | -2.50 |
| 1 | 10 | 10 | 1.50 | -3.00 |
| 1 | 10 | 11 | 1.75 | -3.50 |

#### Wartości specjalne (z = 3)

| s | z | mm | Wartość |
|---|---|----|---------|
| 0 | 11 | 00 | +INF |
| 1 | 11 | 00 | -INF |
| 0/1 | 11 | 01 | NaN |
| 0/1 | 11 | 10 | NaN |
| 0/1 | 11 | 11 | NaN |

### Podsumowanie: Pełny zbiór reprezentowalnych liczb

#### Liczby dodatnie (uporządkowane):
```
+0.00, +0.25, +0.50, +0.75, +1.00, +1.25, +1.50, +1.75,
+2.00, +2.50, +3.00, +3.50, +INF
```

#### Liczby ujemne (uporządkowane):
```
-INF, -3.50, -3.00, -2.50, -2.00, -1.75, -1.50, -1.25,
-1.00, -0.75, -0.50, -0.25, -0.00
```

#### Wartości specjalne:
```
+0, -0, +INF, -INF, NaN (6 różnych reprezentacji)
```

### Uwagi

1. **Luka między liczbami zdenormalizowanymi a znormalizowanymi:** Największa liczba zdenormalizowana to 0.75, najmniejsza znormalizowana to 1.00. Jest płynne przejście dzięki zdenormalizowanym.

2. **Precyzja:** Z tylko 2 bitami mantysy, precyzja jest bardzo niska.

3. **Zakres:** Najmniejsza liczba dodatnia różna od zera: 0.25, największa: 3.50.

4. **Epsylon maszynowy:** Dla tego systemu, epsylon maszynowy (najmniejsze ε takie, że `1 + ε > 1`) to 0.25, ponieważ następna reprezentowalna liczba po 1.00 to 1.25.
