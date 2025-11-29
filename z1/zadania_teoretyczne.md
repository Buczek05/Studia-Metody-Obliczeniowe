# Zadania teoretyczne - Zajęcia nr 1

## Zadanie 1: Błąd obcięcia w rozwinięciu Taylora funkcji ln(z)

### Treść zadania
Oszacuj wielkość błędu obcięcia przy wyznaczaniu przybliżonej wartości `ln(z)` poprzez sumowanie `n` wyrazów rozwinięcia w szereg Taylora wokół `z₀ = 1`. Ile wyrazów należy zsumować, aby otrzymać błąd bezwzględny logarytmu nie większy niż `10⁻⁸` dla `z = 2`?

### Rozwiązanie
# Oszacowanie błędu obcięcia szeregu Taylora dla ln(z)

## Rozwinięcie Taylora logarytmu

Zapisujemy:

$$z = 1 + x \qquad \Rightarrow \qquad x = z - 1.$$

Rozwinięcie:

$$\ln(1+x) = x - \frac{x^2}{2} + \frac{x^3}{3} - \frac{x^4}{4} + \dots$$

Ogólnie:

$$
\ln(z) = \sum_{k=1}^{\infty} (-1)^{k+1}\frac{(z-1)^k}{k}.
$$

---

## Przypadek szczególny: $z = 2$

Wtedy:

$$x = 2 - 1 = 1.$$

Podstawiamy:

$$
\ln 2 = 1 - \frac{1}{2} + \frac{1}{3} - \frac{1}{4} + \dots
$$

Suma n wyrazów:

$$
S_n = \sum_{k=1}^{n} (-1)^{k+1}\frac{1}{k}.
$$

---

## Błąd obcięcia — kryterium Leibniza

Wyrazy szeregu:

$$a_k = \frac{1}{k}.$$

Dla szeregu naprzemiennego:

$$|R_n| \le a_{n+1}.$$

Czyli:

$$|R_n| \le \frac{1}{n+1}.$$

---

## Warunek na dokładność $10^{-8}$

Chcemy:

$$|R_n| \le 10^{-8}.$$

Wystarczy:

$$
\frac{1}{n+1} \le 10^{-8}.
$$

Odwracamy nierówność:

$$
n + 1 \ge 10^8.
$$

Zatem:

$$
n \ge 10^8 - 1.
$$

---

## Odpowiedź końcowa

Aby błąd bezwzględny przybliżenia $\ln 2$ był nie większy niż  
$10^{-8}$, należy zsumować co najmniej:

$$
n = 99\,999\,999.
$$

co odpowiada w przybliżeniu:

$$
10^8\ \text{wyrazów}.
$$

Szereg jest bardzo wolno zbieżny i niepraktyczny dla obliczeń
wysokiej precyzji dla $\ln 2$.

---

## Zadanie 2: Prosty system reprezentacji zmiennoprzecinkowej

### Treść zadania
Rozważ prosty system reprezentacji zmiennoprzecinkowej:

$$\text{rd}(x) = (-1)^e \cdot m \cdot 2^{z-b}$$

gdzie na mantysę oraz cechę przeznaczono po dwa bity (razem 5 bitów: 1 bit znaku + 2 bity cechy + 2 bity mantysy). Wyznacz zbiór wszystkich możliwych liczb rzeczywistych reprezentowalnych w tym systemie przy założeniu, że `b = 1`. Uwzględnij możliwość liczb znormalizowanych (`m ∈ [1, 2)`) oraz zdenormalizowanych, i określ jakie słowa maszynowe należałoby zarezerwować na `+0`, `-0`, `+INF`, `-INF` oraz reprezentacje `NaN`.

### Rozwiązanie
# Prosty system reprezentacji zmiennoprzecinkowej (5 bitów)

Rozważamy system:

$$rd(x) = (-1)^e \, m \, 2^{z-b}$$

gdzie:
- $e$ – bit znaku (0 – plus, 1 – minus),
- $m$ – mantysa,
- $z$ – cecha (wykładnik z przesunięciem),
- $b = 1$ – bias.

Założenia:
- jedno słowo maszynowe ma 5 bitów,
- na mantysę i na cechę przeznaczono po 2 bity,
- rozważamy liczby znormalizowane ($m \in [1,2)$) oraz zdenormalizowane,
- mamy też specjalne reprezentacje $+0$, $-0$, $+\infty$, $-\infty$ oraz NaN.

---

## Struktura słowa

Słowo ma postać:

$$[e]\,[z_1 z_0]\,[m_1 m_0]$$

- 1 bit na znak $e$,
- 2 bity na cechę $z$ (wartości $0,1,2,3$),
- 2 bity na mantysę.

---

## Wartości cechy

Zależność:

$$E = z - b = z - 1.$$

Zatem:

- $z = 0 \Rightarrow E = -1$,
- $z = 1 \Rightarrow E = 0$,
- $z = 2 \Rightarrow E = 1$,
- $z = 3 \Rightarrow E = 2$.

Przydział:
- $z = 00$ – liczby zdenormalizowane i zera,
- $z = 01, 10$ – liczby znormalizowane,
- $z = 11$ – $\pm\infty$ oraz NaN.

---

## Mantysa

Na mantysę mamy 2 bity. Ułamkowa część ma krok $2^{-2} = \tfrac14$.

### Liczby znormalizowane

Mantysa:

$$m = 1.f_2 = 1 + \frac{m_1}{2} + \frac{m_0}{4}, \quad m \in [1,2).$$

Możliwe wartości:

- $m_1 m_0 = 00 \Rightarrow m = 1{,}00_2 = 1$
- $01 \Rightarrow m = 1{,}01_2 = 1{,}25$
- $10 \Rightarrow m = 1{,}10_2 = 1{,}5$
- $11 \Rightarrow m = 1{,}11_2 = 1{,}75$

### Liczby zdenormalizowane

Mantysa:

$$m = 0.f_2 = \frac{m_1}{2} + \frac{m_0}{4}, \quad m \in [0,1).$$

Możliwe wartości:

- $00 \Rightarrow m = 0$
- $01 \Rightarrow m = 0{,}25$
- $10 \Rightarrow m = 0{,}5$
- $11 \Rightarrow m = 0{,}75$

---

## Liczby znormalizowane

### Przypadek $z = 01$ (czyli $z=1$, $E = 0$)

Mamy:

$$x = (-1)^e \, m \, 2^0 = (-1)^e m.$$

Dla $e = 0$ (plus):

- $+1,\ +1{,}25,\ +1{,}5,\ +1{,}75$

Dla $e = 1$ (minus):

- $-1,\ -1{,}25,\ -1{,}5,\ -1{,}75$

### Przypadek $z = 10$ (czyli $z=2$, $E = 1$)

Mamy:

$$x = (-1)^e \, m \, 2^1 = (-1)^e \cdot 2m.$$

Dla $e = 0$:

- $+2,\ +2{,}5,\ +3,\ +3{,}5$

Dla $e = 1$:

- $-2,\ -2{,}5,\ -3,\ -3{,}5$

Łącznie: **16 znormalizowanych niezerowych liczb**.

---

## Liczby zdenormalizowane i zera ($z = 00$)

Dla $z = 00$:

- $m = 0$ – zera,
- $m > 0$ – liczby zdenormalizowane.

Przyjmujemy efektywny wykładnik $E_{\min} = 0$, więc:

$$x = (-1)^e \, m \, 2^0 = (-1)^e m.$$

### Zera

- $e = 0$, $z=00$, $m=00$ → **$+0$**
- $e = 1$, $z=00$, $m=00$ → **$-0$**

### Zdenormalizowane dodatnie ($e=0$)

- $+0{,}25,\ +0{,}5,\ +0{,}75$

### Zdenormalizowane ujemne ($e=1$)

- $-0{,}25,\ -0{,}5,\ -0{,}75$

---

## Nieskończoności i NaN ($z = 11$)

Dla $z = 11$:

- mantysa $m = 0$ – nieskończoności,
- mantysa $m \ne 0$ – NaN.

Słowa:

- $e = 0$, $z=11$, $m=00$ → **$+\infty$**
- $e = 1$, $z=11$, $m=00$ → **$-\infty$**

Każde słowo z:

- $z = 11$ i $m \ne 00$

reprezentuje **NaN** (6 różnych słów maszynowych).

---

## Podsumowanie liczby słów

- liczby znormalizowane: 16,
- zdenormalizowane: 6,
- zera: 2 ($+0$, $-0$),
- nieskończoności: 2 ($+\infty$, $-\infty$),
- NaN: 6.

Razem:

$$16 + 6 + 2 + 2 + 6 = 32 = 2^5,$$

czyli wszystkie możliwe słowa 5-bitowe są wykorzystane.
