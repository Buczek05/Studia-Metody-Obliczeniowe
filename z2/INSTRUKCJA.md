# Szybki start - Zajęcia 2

## 📦 Co znajduje się w tym katalogu?

### Materiały do nauki:
- **zadania.md** - Zadania teoretyczne i programistyczne (ZACZNIJ TU!)
- **rozwiazania.md** - Rozwiązania zadań teoretycznych
- **szablon_raportu.md** - Szablon do sporządzenia raportu
- **README.md** - Pełna dokumentacja projektu

### Kod źródłowy:
- **main.cpp** - Główny program analizy błędów
- **generate_exact.cpp** - Generator wartości referencyjnych
- **analyze.cpp** - Program do analizy statystycznej

### Narzędzia:
- **Makefile** - Automatyzacja kompilacji i uruchomienia
- **plot.gnu** - Skrypt gnuplot do wizualizacji wyników
- **.gitignore** - Konfiguracja Git

---

## 🚀 Szybki start (3 kroki)

### Krok 1: Skompiluj programy

```bash
make
```

Lub ręcznie:
```bash
g++ -std=c++11 -O2 -o main main.cpp -lm
g++ -std=c++11 -O2 -o generate_exact generate_exact.cpp -lm
g++ -std=c++11 -O2 -o analyze analyze.cpp -lm
```

### Krok 2: Uruchom analizę

```bash
make run
```

Lub ręcznie:
```bash
./generate_exact    # Generuje exact_values.txt
./main              # Wykonuje analizę, tworzy results_*.txt
./analyze           # Wyświetla statystyki
gnuplot plot.gnu    # Generuje wykresy (wymaga gnuplot)
```

### Krok 3: Sprawdź wyniki

- **exact_values.txt** - Wartości referencyjne
- **results_naive.txt** - Wyniki metody naiwnej
- **results_taylor.txt** - Wyniki szeregu Taylora
- **results_hybrid.txt** - Wyniki metody hybrydowej
- **error_analysis.png** - Wykres błędów (pełny zakres)
- **error_analysis_zoom.png** - Wykres błędów (małe x)
- **function_values.png** - Wartości funkcji

---

## 📋 Kolejność wykonywania zadań

### Część teoretyczna (30-45 min)

1. Przeczytaj **zadania.md** - zapoznaj się z zadaniami
2. Rozwiąż **Zadanie 1** - uwarunkowanie iloczynu i ilorazu
3. Rozwiąż **Zadanie 2** - algorytmy dla $a^2 - b^2$
4. Rozwiąż **Zadanie 3** - uwarunkowanie $(1+x)^{-1}$
5. Rozwiąż **Zadanie 4** - $\ln(x)$ dla $x \approx 1$
6. Sprawdź odpowiedzi w **rozwiazania.md**

### Część programistyczna (60-90 min)

1. **Przeanalizuj kod:**
   - Otwórz `main.cpp` i zrozum co robi
   - Znajdź funkcję `compute_naive()` - co może pójść źle?
   - Znajdź funkcję `compute_taylor()` - dlaczego to działa?

2. **Uruchom programy:**
   ```bash
   make run
   ```

3. **Przeanalizuj wyniki:**
   - Otwórz wygenerowane wykresy
   - Znajdź zakres gdzie metoda naiwna ma duże błędy
   - Zrozum dlaczego metoda hybrydowa działa najlepiej

4. **Eksperymenty (opcjonalnie):**
   - Zmień próg w metodzie hybrydowej (co się stanie?)
   - Dodaj więcej wyrazów w szeregu Taylora
   - Przetestuj dla innych zakresów x

5. **Sporządź raport:**
   - Użyj **szablon_raportu.md** jako wzór
   - Wklej wykresy i wyniki
   - Odpowiedz na wszystkie pytania

---

## 🛠️ Rozwiązywanie problemów

### Problem: "make: command not found"

**Windows:** Zainstaluj MinGW lub użyj WSL
**macOS:** Zainstaluj Xcode Command Line Tools:
```bash
xcode-select --install
```
**Linux:** Zainstaluj build-essential:
```bash
sudo apt-get install build-essential
```

### Problem: "g++: command not found"

Zainstaluj kompilator:
- **Windows:** MinGW-w64 lub Visual Studio
- **macOS:** Xcode Command Line Tools
- **Linux:** `sudo apt-get install g++`

### Problem: "gnuplot: command not found"

Zainstaluj gnuplot:
```bash
# macOS
brew install gnuplot

# Ubuntu/Debian
sudo apt-get install gnuplot

# Fedora
sudo dnf install gnuplot

# Windows
# Pobierz z: http://www.gnuplot.info/
```

Alternatywnie: **Pomiń generowanie wykresów** i analizuj dane numerycznie.

### Problem: Dziwne wyniki / NaN

1. Sprawdź czy `exact_values.txt` został wygenerowany:
   ```bash
   ls -lh exact_values.txt
   ```

2. Sprawdź zawartość:
   ```bash
   head exact_values.txt
   ```

3. Jeśli plik nie istnieje:
   ```bash
   ./generate_exact
   ```

---

## 💡 Wskazówki do rozwiązania

### Zadanie teoretyczne 2

**Hint:** Rozważ przypadek $a = 1.0000001$, $b = 1.0$. Co się stanie przy odejmowaniu $a^2 - b^2$?

### Zadanie teoretyczne 4

**Hint:** Użyj funkcji `log1p()` z biblioteki `<cmath>`. Zobacz:
```cpp
#include <cmath>
double t = 1e-15;
double y = log1p(t);  // Oblicza ln(1+t) precyzyjnie
```

### Zadanie programistyczne

**Kluczowe pytanie:** Dlaczego dla małych x występuje problem?

**Odpowiedź:** Rozwiń $\sinh(x)$ w szereg Taylora:
$$\sinh(x) = x + \frac{x^3}{6} + \frac{x^5}{120} + \ldots$$

Dla małych x:
$$\sinh(x) - x \approx \frac{x^3}{6}$$

Ale komputer oblicza to jako różnicę dwóch prawie równych liczb!

---

## 📚 Materiały dodatkowe

### Polecane artykuły:
- "What Every Computer Scientist Should Know About Floating-Point Arithmetic" (David Goldberg)
- IEEE 754 Standard

### Przydatne linki:
- [C++ cmath reference](https://en.cppreference.com/w/cpp/numeric/math)
- [Gnuplot tutorial](http://www.gnuplot.info/documentation.html)
- [IEEE 754 Calculator](https://www.h-schmidt.net/FloatConverter/IEEE754.html)

### Kalkulator online:
Przetestuj reprezentację zmiennoprzecinkową:
```
https://www.h-schmidt.net/FloatConverter/IEEE754.html
```

---

## ✅ Checklist przed oddaniem

- [ ] Rozwiązałem wszystkie zadania teoretyczne (1-4)
- [ ] Skompilowałem i uruchomiłem programy
- [ ] Wygenerowałem wykresy (lub przeanalizowałem dane numerycznie)
- [ ] Zrozumiałem dlaczego metoda naiwna nie działa dla małych x
- [ ] Zrozumiałem jak działa szereg Taylora
- [ ] Odpowiedziałem na pytanie: "Jaki typ zmiennych zastosować?"
- [ ] Sporządziłem raport (użyłem szablonu)
- [ ] Załączyłem wykresy i kod źródłowy
- [ ] Opisałem wnioski

---

## 🎓 Kryteria oceny

### Zadania teoretyczne (40%)
- Poprawność obliczeń wskaźników uwarunkowania
- Analiza błędów algorytmów
- Jakość rozumowania matematycznego

### Program (40%)
- Poprawność implementacji
- Analiza wykresów błędów
- Identyfikacja problematycznych zakresów
- Jakość kodu (czytelność, komentarze)

### Raport (20%)
- Kompletność dokumentacji
- Jakość wykresów
- Wnioski i interpretacja wyników
- Estetyka i przejrzystość

---

## ❓ Pytania?

Jeśli masz pytania:
1. Przeczytaj **README.md** (pełna dokumentacja)
2. Sprawdź **rozwiazania.md** (rozwiązania teoretyczne)
3. Zobacz **szablon_raportu.md** (wzór raportu)
4. Zadaj pytanie prowadzącemu zajęcia

---

**Powodzenia!** 🚀

_Czas wykonania: ~2-3 godziny (teoria + program + raport)_
