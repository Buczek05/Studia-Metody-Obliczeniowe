# Zajęcia 13 - Interpolacja sklejana i kwadratury numeryczne

## 🚀 Szybki start

**Chcesz od razu zacząć?**
- ⚡ **2 minuty**: Zobacz [QUICKSTART.md](QUICKSTART.md)
- 🎓 **Tutorial**: Zobacz [TUTORIAL.md](TUTORIAL.md) dla szczegółowego przewodnika
- 📝 **Zadania**: Zobacz [zadania.md](zadania.md) dla rozwiązań zadań teoretycznych
- 📐 **Wzory**: Zobacz [wzory_kwadratur.md](wzory_kwadratur.md) dla kompletnej ściągawki
- 🗂️ **Mapa projektu**: Zobacz [INDEX.md](INDEX.md) dla przewodnika po plikach

---

## Zawartość

### 📝 Zadania teoretyczne
- **zadania.md** - Pełne rozwiązania wszystkich zadań z zajęć:
  - Zadanie 1: Funkcja sklejana kubiczna (natural cubic spline)
  - Zadanie 2: Interpolacja biliniowa
  - Zadanie 3: Kwadratury złożone (prostokąty, trapezy, Simpson)
  - Zadanie 4: Metoda Romberga
  - Zadanie 5: Kwadratura Gaussa

### 💻 Program numeryczny
- **erf_quadratures.cpp** - Program w C++ do numerycznego obliczania funkcji erf(x)

## Kompilacja i uruchomienie

### Wymagania
- Kompilator C++ obsługujący C++17 (g++, clang++)
- gnuplot (opcjonalnie, do generowania wykresów)

### Instalacja gnuplot (opcjonalnie)
```bash
# macOS
brew install gnuplot

# Linux (Ubuntu/Debian)
sudo apt install gnuplot

# Linux (Fedora)
sudo dnf install gnuplot
```

### Kompilacja

#### Metoda 1: Użycie Makefile
```bash
# Kompilacja
make

# Kompilacja i uruchomienie
make run

# Kompilacja, uruchomienie i generowanie wykresu
make plot

# Czyszczenie
make clean
```

#### Metoda 2: Ręczna kompilacja
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o erf_quadratures erf_quadratures.cpp -lm
./erf_quadratures
```

## Opis programu

Program oblicza funkcję błędu (error function):

$$\text{erf}(x) = \frac{2}{\sqrt{\pi}} \int_0^x e^{-y^2} dy$$

dla wartości x = 1.0, 2.0, 3.0 używając następujących metod kwadratur:

### Zaimplementowane metody

1. **Prostokąty z węzłem po lewej stronie** - O(h²)
2. **Prostokąty z węzłem po prawej stronie** - O(h²)
3. **Prostokąty z węzłem w środku** - O(h³)
4. **Metoda trapezów** - O(h³)
5. **Metoda Simpsona (parabol)** - O(h⁵)

### Funkcjonalności programu

1. **Obliczanie erf(x)** dla różnych wartości x i liczby przedziałów n
2. **Porównanie z wartością dokładną** (std::erf z biblioteki standardowej C++)
3. **Analiza błędów**:
   - Błąd bezwzględny
   - Błąd względny
4. **Wyznaczanie rzędów dokładności** poprzez regresję liniową na wykresach log-log
5. **Generowanie danych** do wizualizacji

## Wyniki

Po uruchomieniu programu otrzymasz:

### 1. Wyniki numeryczne w terminalu
- Wartości erf(x) dla różnych metod i różnych n
- Wartości dokładne
- Błędy bezwzględne i względne

### 2. Pliki z danymi
- `data_rect_left.txt` - dane dla metody prostokątów (lewe)
- `data_rect_right.txt` - dane dla metody prostokątów (prawe)
- `data_rect_mid.txt` - dane dla metody prostokątów (środek)
- `data_trapezoid.txt` - dane dla metody trapezów
- `data_simpson.txt` - dane dla metody Simpsona
- `plot_errors.gp` - skrypt gnuplot do generowania wykresów

### 3. Wykres (po uruchomieniu gnuplot)
- `error_analysis.png` - wykres zależności log₁₀(błąd) od log₁₀(h)

Format plików z danymi:
```
log10(h)  log10(błąd)
```

## Analiza wyników

### Oczekiwane rzędy dokładności

Z teorii wiemy, że błąd kwadratury złożonej jest proporcjonalny do h^p, gdzie p to rząd metody:

| Metoda | Rząd teoretyczny | Nachylenie na wykresie log-log |
|--------|------------------|--------------------------------|
| Prostokąty (lewe/prawe) | O(h²) | ≈ 2 |
| Prostokąty (środek) | O(h³) | ≈ 3 |
| Trapezy | O(h³) | ≈ 3 |
| Simpson | O(h⁵) | ≈ 5 |

### Interpretacja wykresu

Na wykresie log₁₀(błąd) vs log₁₀(h):
- **Nachylenie prostej** = rząd dokładności metody
- Im większe nachylenie, tym szybciej błąd maleje ze zmniejszaniem h
- Dopasowane proste pozwalają **doświadczalnie wyznaczyć** rzędy dokładności

## Generowanie wykresu ręcznie

Jeśli nie używasz `make plot`, możesz wygenerować wykres ręcznie:

```bash
# Po uruchomieniu programu
./erf_quadratures

# Generowanie wykresu
gnuplot plot_errors.gp

# Wyświetlenie wykresu
open error_analysis.png    # macOS
xdg-open error_analysis.png  # Linux
```

## Struktura kodu

```cpp
// Główne funkcje kwadratur
double rectangleLeft(...)   // Prostokąty - lewy węzeł
double rectangleRight(...)  // Prostokąty - prawy węzeł
double rectangleMid(...)    // Prostokąty - środek
double trapezoid(...)       // Trapezy
double simpson(...)         // Simpson (parabol)

// Obliczanie erf(x)
double erf_numerical(...)   // Ogólna funkcja do obliczania erf

// Analiza
void analyzeMethod(...)     // Analiza błędów dla danej metody
```

## Dodatkowe informacje

### Pakiet CALERF
W programie używamy funkcji `std::erf()` z biblioteki standardowej C++ (`<cmath>`) jako wartości referencyjnej. Funkcja ta wykorzystuje bardzo dokładne algorytmy (często oparte na aproksymacjach racjonalnych lub szeregach), które dają dokładność bliską maszynowej (εmach ≈ 2.22×10⁻¹⁶ dla double).

### Wartości referencyjne erf(x)
- erf(1.0) ≈ 0.842700792949715
- erf(2.0) ≈ 0.995322265018953
- erf(3.0) ≈ 0.999977909503001

### Dlaczego to ważne?
Funkcja erf(x) jest fundamentalna w:
- Statystyce (rozkład normalny)
- Teorii prawdopodobieństwa
- Fizyce (równanie dyfuzji)
- Przetwarzaniu sygnałów

## Zadania do wykonania

1. ✅ Uruchom program i przeanalizuj wyniki dla różnych wartości x
2. ✅ Wygeneruj wykres i sprawdź, czy rzędy dokładności są zgodne z teorią
3. ✅ Porównaj dokładność różnych metod dla tej samej liczby przedziałów n
4. 📝 Odpowiedz na pytanie: Która metoda jest najbardziej efektywna (najlepsza dokładność dla danego n)?
5. 📝 Wyjaśnij, dlaczego metoda Simpsona jest znacznie dokładniejsza niż pozostałe

## Pomoc

```bash
# Wyświetl dostępne komendy make
make help

# Wyczyść wszystkie wygenerowane pliki
make clean
```

## Kontakt i feedback

Jeśli znajdziesz błędy lub masz sugestie dotyczące programu, zgłoś je prowadzącemu zajęcia.

---

**Powodzenia w obliczeniach numerycznych! 🚀**
