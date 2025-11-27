# Metody Obliczeniowe - Zajęcia 2
## Analiza błędów numerycznych i stabilność algorytmów

---

## 📋 Zawartość

1. [Opis zadania](#opis-zadania)
2. [Struktura projektu](#struktura-projektu)
3. [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
4. [Analiza teoretyczna](#analiza-teoretyczna)
5. [Wyniki i wnioski](#wyniki-i-wnioski)
6. [Wymagania systemowe](#wymagania-systemowe)

---

## 🎯 Opis zadania

Program analizuje błędy numeryczne w obliczaniu funkcji:

```
f(x) = x³ / (6 * (sinh(x) - x))
```

dla zakresu x ∈ [10⁻¹⁰, 10³].

### Główne cele:

1. **Implementacja różnych algorytmów obliczeniowych**
   - Metoda naiwna (bezpośrednie użycie funkcji `sinh()`)
   - Metoda oparta na szeregu Taylora
   - Metoda hybrydowa (adaptacyjna)

2. **Analiza błędów względnych** w zależności od wielkości argumentu x

3. **Identyfikacja problemów numerycznych**
   - Utrata cyfr znaczących
   - Uwarunkowanie zadania
   - Błędy zaokrągleń

4. **Propozycja rozwiązań** zapewniających dokładność maszynową

---

## 📁 Struktura projektu

```
z2/
├── README.md                 # Ten plik - instrukcje
├── zadania.md               # Zadania teoretyczne
├── main.cpp                 # Główny program analizy
├── generate_exact.cpp       # Generator wartości referencyjnych
├── Makefile                 # Automatyzacja kompilacji
├── plot.gnu                 # Skrypt gnuplot do wizualizacji
├── exact_values.txt         # Wartości referencyjne (generowane)
├── results_naive.txt        # Wyniki metody naiwnej (generowane)
├── results_taylor.txt       # Wyniki szeregu Taylora (generowane)
├── results_hybrid.txt       # Wyniki metody hybrydowej (generowane)
└── *.png                    # Wykresy (generowane)
```

---

## 🔨 Kompilacja i uruchomienie

### Opcja 1: Użycie Makefile (zalecane)

```bash
# Kompilacja, uruchomienie i generowanie wykresów
make run

# Tylko kompilacja
make

# Czyszczenie
make clean
```

### Opcja 2: Kompilacja ręczna

```bash
# Kompilacja generatora wartości dokładnych
g++ -std=c++11 -O2 -o generate_exact generate_exact.cpp -lm

# Kompilacja głównego programu
g++ -std=c++11 -O2 -o main main.cpp -lm

# Uruchomienie
./generate_exact    # Generuje exact_values.txt
./main              # Wykonuje analizę

# Generowanie wykresów
gnuplot plot.gnu
```

### Wyniki

Po uruchomieniu programu zostaną wygenerowane:

- `exact_values.txt` - wartości referencyjne
- `results_naive.txt` - wyniki metody naiwnej
- `results_taylor.txt` - wyniki szeregu Taylora
- `results_hybrid.txt` - wyniki metody hybrydowej
- `error_analysis.png` - wykres błędów (pełny zakres)
- `error_analysis_zoom.png` - wykres błędów (zoom na małe x)
- `function_values.png` - wartości funkcji

---

## 📊 Analiza teoretyczna

### Problem numeryczny

Dla małych wartości x funkcja `sinh(x) - x` jest bliska zeru, co prowadzi do **utraty cyfr znaczących**:

```
sinh(x) ≈ x  (dla x → 0)
sinh(x) - x → 0
```

Dzielenie przez bardzo małą liczbę amplifikuje błędy zaokrągleń.

### Rozwiązanie: Szereg Taylora

Wykorzystujemy rozwinięcie funkcji sinh(x):

```
sinh(x) = x + x³/6 + x⁵/120 + x⁷/5040 + ...
```

Zatem:

```
sinh(x) - x = x³/6 + x⁵/120 + x⁷/5040 + ...
```

Podstawiając do wzoru na f(x):

```
f(x) = x³ / (6 * (x³/6 + x⁵/120 + x⁷/5040 + ...))
     = x³ / (x³ + x⁵/20 + x⁷/840 + ...)
     = 1 / (1 + x²/20 + x⁴/840 + x⁶/37800 + ...)
```

### Wartość graniczna

```
lim(x→0) f(x) = 1
```

### Metoda hybrydowa

Program automatycznie wybiera optymalny algorytm:

- **Dla |x| < 0.1**: Szereg Taylora (unika utraty cyfr znaczących)
- **Dla |x| ≥ 0.1**: Funkcja standardowa sinh() (wystarczająco dokładna)

Próg 0.1 można dostosować eksperymentalnie.

---

## 📈 Wyniki i wnioski

### Obserwacje z wykresów

Po uruchomieniu programu i analizie wykresów można zaobserwować:

1. **Zakres x ∈ [10⁻¹⁰, 10⁻²]** (małe x)
   - Metoda naiwna: **duże błędy** (nawet 10⁰ - 10⁻⁵)
   - Metoda Taylora: błąd na poziomie **dokładności maszynowej** (~10⁻¹⁶)
   - Przyczyna: utrata cyfr znaczących przy odejmowaniu sinh(x) - x

2. **Zakres x ∈ [10⁻¹, 10²]** (średnie x)
   - Obie metody działają dobrze
   - Błędy na poziomie dokładności maszynowej

3. **Zakres x ∈ [10², 10³]** (duże x)
   - Metoda standardowa sinh() może mieć problemy z overflow
   - Dla x > 700: sinh(x) przekracza zakres double
   - Trzeba ostrożnie obsługiwać duże wartości

### Wnioski praktyczne

✅ **Zalecenia:**
- Zawsze analizuj zakres wartości argumentów
- Dla krytycznych obliczeń stosuj metody adaptacyjne
- Testuj algorytmy na skrajnych wartościach
- Porównuj wyniki z wartościami referencyjnymi

⚠️ **Pułapki:**
- Odejmowanie zbliżonych liczb (utrata cyfr znaczących)
- Dzielenie przez bardzo małe liczby
- Overflow/underflow dla funkcji eksponencjalnych
- Założenie że funkcje standardowe są zawsze dokładne

---

## 🔧 Wymagania systemowe

### Kompilator

- **g++** z obsługą C++11 lub nowszego
- Alternatywnie: clang++, MSVC

```bash
# Sprawdź wersję
g++ --version
```

### Biblioteki

Program używa standardowych bibliotek C++:
- `<cmath>` - funkcje matematyczne (sinh, log, exp)
- `<fstream>` - operacje na plikach
- `<iostream>` - wejście/wyjście
- `<vector>` - kontenery

### Narzędzia dodatkowe

**gnuplot** (opcjonalnie, do wizualizacji):

```bash
# macOS
brew install gnuplot

# Linux (Ubuntu/Debian)
sudo apt-get install gnuplot

# Linux (Fedora)
sudo dnf install gnuplot

# Windows
# Pobierz z: http://www.gnuplot.info/
```

### Typ zmiennych

Program używa typu **`double`** (64-bitowa arytmetyka zmiennoprzecinkowa IEEE 754):
- Precyzja: ~15-17 cyfr dziesiętnych
- Zakres: ±10⁻³⁰⁸ do ±10³⁰⁸
- Błąd maszynowy: ε ≈ 2.22 × 10⁻¹⁶

**Dlaczego double, a nie float?**
- `float` (32-bit): precyzja ~7 cyfr, błąd ~10⁻⁷
- `double` (64-bit): precyzja ~15 cyfr, błąd ~10⁻¹⁶
- Dla analizy błędów numerycznych potrzebujemy większej precyzji

**Czy użyć long double?**
- `long double`: precyzja zależy od platformy (80-bit lub 128-bit)
- Na większości systemów: niewiele lepsze niż double
- Wolniejsze obliczenia
- Wniosek: `double` jest optymalnym wyborem

---

## 📚 Materiały dodatkowe

### Literatura

1. **"Numerical Recipes"** - Press, Teukolsky, Vetterling, Flannery
2. **"Accuracy and Stability of Numerical Algorithms"** - Nicholas J. Higham
3. **IEEE 754** - Standard arytmetyki zmiennoprzecinkowej

### Linki

- [IEEE 754 Calculator](https://www.h-schmidt.net/FloatConverter/IEEE754.html)
- [What Every Computer Scientist Should Know About Floating-Point Arithmetic](https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html)
- [Gnuplot documentation](http://www.gnuplot.info/documentation.html)

---

## 🤔 Pytania kontrolne

Po wykonaniu ćwiczenia powinieneś umieć odpowiedzieć na pytania:

1. Co to jest utrata cyfr znaczących i kiedy występuje?
2. Jak obliczyć wskaźnik uwarunkowania zadania?
3. Czym różni się stabilność numeryczna od poprawności numerycznej?
4. Dlaczego szereg Taylora działa lepiej dla małych x?
5. Jak wybrać próg przełączenia w metodzie hybrydowej?
6. Jaki jest błąd maszynowy dla typu double?
7. Czy funkcje biblioteczne (sinh, log, etc.) są zawsze dokładne?

---

## 📝 Zadanie domowe

1. Zmodyfikuj program aby badać funkcję: `g(x) = (e^x - 1) / x` dla x → 0
2. Zaproponuj metodę hybrydową dla tej funkcji
3. Przeanalizuj uwarunkowanie zadania obliczenia `√(x² + 1) - 1` dla małych x

---

## 🐛 Rozwiązywanie problemów

### Program się nie kompiluje

```bash
# Sprawdź czy masz g++
which g++

# Sprawdź wersję C++
g++ -std=c++11 --version
```

### Brak pliku exact_values.txt

```bash
# Wygeneruj plik
./generate_exact
```

### Gnuplot nie działa

```bash
# Sprawdź instalację
which gnuplot
gnuplot --version

# Uruchom ręcznie
gnuplot plot.gnu
```

### Dziwne wyniki

- Sprawdź czy plik `exact_values.txt` został poprawnie wygenerowany
- Upewnij się że używasz typu `double`, nie `float`
- Zweryfikuj przedział x: [10⁻¹⁰, 10³]

---

## ✍️ Autor

Materiały przygotowane dla kursu **Metody Obliczeniowe w Nauce i Technice**.

Data utworzenia: 2025

---

## 📄 Licencja

Materiały edukacyjne - wolne do użytku w celach dydaktycznych.
