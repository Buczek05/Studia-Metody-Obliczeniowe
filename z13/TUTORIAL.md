# Tutorial - Krok po kroku

Ten przewodnik przeprowadzi Cię przez wszystkie programy i zadania z zajęć 13.

---

## Krok 1: Przygotowanie środowiska

### Sprawdź czy masz wymagane narzędzia:

```bash
# Sprawdź kompilator C++
g++ --version

# Sprawdź czy masz gnuplot (opcjonalne, do wykresów)
gnuplot --version
```

Jeśli gnuplot nie jest zainstalowany:
```bash
# macOS
brew install gnuplot

# Linux (Ubuntu/Debian)
sudo apt install gnuplot
```

---

## Krok 2: Kompilacja programów

### Metoda 1: Użycie Makefile (zalecana)

```bash
# Kompiluj wszystkie programy
make

# Lub kompiluj tylko jeden program
make erf_quadratures
make examples
```

### Metoda 2: Ręczna kompilacja

```bash
# Program erf_quadratures
g++ -std=c++17 -Wall -Wextra -O2 -o erf_quadratures erf_quadratures.cpp -lm

# Program examples
g++ -std=c++17 -Wall -Wextra -O2 -o examples examples.cpp -lm
```

---

## Krok 3: Uruchomienie programu examples

Ten program demonstruje rozwiązania zadań 4 i 5.

```bash
# Uruchom program
./examples

# Lub użyj Makefile
make run-examples
```

### Co zobaczysz:

1. **Zadanie 5** - Kwadratura Gaussa dla ∫₋₁¹ (x⁴ + 1) dx
   - Wyniki dla 2, 3 i 4 punktów Gaussa
   - Porównanie z wartością dokładną
   - Wyjaśnienie dokładności

2. **Zadanie 4** - Metoda Romberga
   - Tablica Romberga pokazująca proces ekstrapolacji
   - Wynik końcowy dla ∫₀⁸ f(x) dx

3. **Przykład dodatkowy** - Porównanie metod dla ∫₀^π sin(x) dx
   - Pokazuje różnicę między trapezami a Gaussem

### Przykładowe wyjście:

```
╔════════════════════════════════════════════════════════════════════╗
║  ZADANIE 5: KWADRATURA GAUSSA                                      ║
╚════════════════════════════════════════════════════════════════════╝

Wartość dokładna: 2.400000000000000

                   Metoda               Wynik         Błąd    Błąd wzgl. [%]
----------------------------------------------------------------------
           Gauss 2 punkty   2.222222222222222     1.7778e-01       7.407407
           Gauss 3 punkty   2.400000000000000     0.0000e+00       0.000000
```

---

## Krok 4: Uruchomienie programu erf_quadratures

Ten program oblicza funkcję erf(x) i analizuje dokładność różnych metod kwadratur.

```bash
# Uruchom program
./erf_quadratures

# Lub użyj Makefile
make run
```

### Co się dzieje:

1. **Część 1**: Obliczenia erf(x) dla x = 1.0, 2.0, 3.0
   - Pokazuje wyniki dla różnych liczb przedziałów (n = 10, 50, 100, 500, 1000)
   - Porównuje 5 metod: prostokąty (lewe, prawe, środek), trapezy, Simpson
   - Wyświetla wartość dokładną ze standardowej biblioteki

2. **Część 2**: Analiza błędów dla x = 3.0
   - Szczegółowa analiza dla każdej metody
   - Obliczenia dla wielu wartości n
   - Generowanie plików z danymi

3. **Wygenerowane pliki**:
   - `data_rect_left.txt` - dane dla prostokątów (lewe)
   - `data_rect_right.txt` - dane dla prostokątów (prawe)
   - `data_rect_mid.txt` - dane dla prostokątów (środek)
   - `data_trapezoid.txt` - dane dla trapezów
   - `data_simpson.txt` - dane dla Simpsona
   - `plot_errors.gp` - skrypt gnuplot

### Przykładowe wyjście:

```
╔════════════════════════════════════════════════════════════════════╗
║  x = 1.0000000000                                                  ║
╚════════════════════════════════════════════════════════════════════╝

Wartość dokładna erf(1.0000000000) = 0.842700792949715

         Metoda         n             n=10             n=50            n=100
----------------------------------------------------------------------
      Rect-Left               0.8776723001     0.8498058354     0.8462602328
       Rect-Mid               0.8430469175     0.8427146302     0.8427042522
        Simpson               0.8427017131     0.8427007944     0.8427007930
```

---

## Krok 5: Generowanie wykresów

Jeśli masz zainstalowany gnuplot, możesz wygenerować wykresy błędów.

```bash
# Wygeneruj wykresy automatycznie
make plot

# Lub ręcznie:
./erf_quadratures
gnuplot plot_errors.gp
```

### Wygenerowany wykres:

Plik `error_analysis.png` zawiera:
- Wykres log₁₀(błąd) vs log₁₀(h) dla wszystkich metod
- Dopasowane proste metodą najmniejszych kwadratów
- Nachylenia prostych = doświadczalne rzędy dokładności

### Jak interpretować wykres:

1. **Oś X**: log₁₀(h) - logarytm kroku
2. **Oś Y**: log₁₀(błąd) - logarytm błędu
3. **Nachylenie linii**: rząd dokładności metody

Teoretyczne nachylenia:
- Prostokąty (lewe/prawe): ~2
- Prostokąty (środek): ~3
- Trapezy: ~3
- Simpson: ~5

---

## Krok 6: Analiza wyników

### Sprawdź dokładność metod:

Otwórz plik z danymi i sprawdź błędy:

```bash
# Zobacz pierwsze 10 linii danych dla metody Simpsona
head data_simpson.txt
```

Format: `log10(h)  log10(błąd)`

### Przykład:
```
-1.0000 -6.5234
-1.1761 -7.3456
-1.3010 -8.1234
```

### Oblicz nachylenie (rząd metody):

Możesz użyć gnuplot do dopasowania:
```bash
gnuplot
> f(x) = a*x + b
> fit f(x) 'data_simpson.txt' using 1:2 via a, b
> print a
```

Wartość `a` to doświadczalny rząd dokładności!

---

## Krok 7: Zadania teoretyczne

Otwórz plik `zadania.md` i przejrzyj rozwiązania:

```bash
# W terminalu (jeśli masz zainstalowany markdown viewer)
mdcat zadania.md

# Lub otwórz w edytorze/przeglądarce
open zadania.md  # macOS
xdg-open zadania.md  # Linux
```

Plik zawiera pełne rozwiązania:
- ✅ Zadanie 1: Funkcja sklejana kubiczna
- ✅ Zadanie 2: Interpolacja biliniowa
- ✅ Zadanie 3: Kwadratury złożone
- ✅ Zadanie 4: Metoda Romberga
- ✅ Zadanie 5: Kwadratura Gaussa

---

## Krok 8: Wzory i dokumentacja

### Szybkie odniesienie do wzorów:

```bash
open wzory_kwadratur.md
```

Zawiera:
- Wszystkie wzory kwadratur (proste i złożone)
- Kwadratura Gaussa (węzły i wagi)
- Metoda Romberga
- Interpolacja biliniowa
- Funkcje sklejane
- Przykłady implementacji w C++
- Wskazówki praktyczne

---

## Krok 9: Eksperymenty

### Eksperyment 1: Zbieżność metod

Zmodyfikuj `erf_quadratures.cpp` aby obliczać dla różnych x:

```cpp
std::vector<double> x_values = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
```

Przebuduj i uruchom:
```bash
make clean
make
./erf_quadratures
```

### Eksperyment 2: Własna funkcja

W `examples.cpp` zmień funkcję:

```cpp
double my_function(double x) {
    return std::cos(x * x);  // Zamiast x^4 + 1
}
```

I zmień w `comparison_example()`:
```cpp
double exact = /* oblicz wartość dokładną */;
```

### Eksperyment 3: Większa liczba punktów Gaussa

Dodaj kwadraturę Gaussa z 5 punktami używając tabel węzłów i wag.

---

## Krok 10: Czyszczenie

Po zakończeniu pracy:

```bash
# Usuń pliki wykonywalne i dane
make clean

# Lub zostaw programy, usuń tylko dane
rm -f *.txt *.png *.gp fit.log
```

---

## Rozwiązywanie problemów

### Problem: Program się nie kompiluje

```bash
# Sprawdź wersję kompilatora
g++ --version

# Upewnij się, że używasz C++17
g++ -std=c++17 --version
```

### Problem: Brak pliku erf_quadratures.cpp

```bash
# Sprawdź czy jesteś w odpowiednim katalogu
pwd
ls -l

# Powinien być katalog z13 z plikami .cpp
```

### Problem: gnuplot nie generuje wykresu

```bash
# Sprawdź czy gnuplot jest zainstalowany
which gnuplot

# Uruchom skrypt ręcznie z diagnostyką
gnuplot -persist plot_errors.gp
```

### Problem: Błędy numeryczne (NaN, Inf)

- Sprawdź czy funkcja nie zawiera dzielenia przez zero
- Upewnij się, że przedział całkowania jest poprawny
- Zmniejsz liczbę przedziałów n jeśli jest za duża

---

## Wskazówki zaawansowane

### 1. Porównanie czasu wykonania

```bash
time ./erf_quadratures
```

### 2. Przekierowanie wyjścia do pliku

```bash
./erf_quadratures > output.txt
```

### 3. Debugowanie z gdb

```bash
# Kompiluj z symbolami debugowania
g++ -std=c++17 -g -o erf_quadratures erf_quadratures.cpp -lm

# Uruchom debugger
gdb ./erf_quadratures
```

### 4. Profilowanie wydajności

```bash
# Kompiluj z profilowaniem
g++ -std=c++17 -pg -o erf_quadratures erf_quadratures.cpp -lm

# Uruchom
./erf_quadratures

# Analiza
gprof erf_quadratures gmon.out > analysis.txt
```

---

## Podsumowanie

Po przejściu tego tutoriala powinieneś:

✅ Umieć kompilować i uruchamiać programy
✅ Rozumieć różnice między metodami kwadratur
✅ Potrafić analizować błędy numeryczne
✅ Znać rzędy dokładności metod
✅ Umieć generować i interpretować wykresy
✅ Rozumieć metodę Romberga i kwadraturę Gaussa

---

## Co dalej?

1. **Przeczytaj dokumentację**: `zadania.md` i `wzory_kwadratur.md`
2. **Eksperymentuj**: Zmień funkcje, parametry, metody
3. **Porównaj**: Który metoda jest najlepsza dla Twojej funkcji?
4. **Zoptymalizuj**: Jak osiągnąć dokładność 10⁻⁸ przy minimalnym n?
5. **Rozszerz**: Implementuj własne metody (Gauss-Kronrod, adaptacyjne kwadratury)

---

**Powodzenia w nauce metod numerycznych! 🚀**

Jeśli masz pytania, sprawdź:
- `README.md` - ogólne informacje
- `zadania.md` - rozwiązania zadań
- `wzory_kwadratur.md` - wszystkie wzory
- Kod źródłowy - komentarze w programach
