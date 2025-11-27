# Podsumowanie - Projekt Zajęcia nr 8

## Przegląd projektu

Kompletny zestaw materiałów do zajęć z metod obliczeniowych na temat przybliżeń różnicowych pochodnych.

---

## Struktura plików

```
z8/
│
├── 📄 ZADANIA.md                  - Zadania do wykonania (z LaTeX)
├── 📄 README.md                   - Dokumentacja główna
├── 📄 INSTRUKCJE.md              - Przewodnik praktyczny
├── 📄 TEORIA.md                  - Teoria matematyczna
├── 📄 PODSUMOWANIE.md            - Ten plik
│
├── 💻 finite_differences.cpp     - Główny program C++
├── 💻 analiza.cpp                - Program analizy szczegółowej
│
├── 📊 plot_convergence.gnu       - Skrypt gnuplot
├── 🔧 Makefile                   - Automatyzacja kompilacji
├── 📝 .gitignore                 - Git ignore
│
└── 📁 Pliki generowane:
    ├── finite_differences         - Program wykonywalny
    ├── analiza                    - Program wykonywalny
    ├── convergence_*.dat          - Dane liczbowe
    └── *.png                      - Wykresy
```

---

## Zawartość poszczególnych plików

### 1. ZADANIA.md ⭐
**Cel:** Zadania dla studentów z pełnym wyprowadzeniem matematycznym

**Zawartość:**
- Zadanie 1: Dowód rzędu O(h²) dla wzorów trzypunktowych
- Zadanie 2: Dowód rzędu O(h⁴) dla wzorów pięciopunktowych
- Zadanie 3: Specyfikacja programu C++
- Zadanie 4: Analiza błędów maszynowych
- Zadanie 5: Porównanie double vs long double

**Format:** Markdown + LaTeX (gotowy do konwersji na PDF)

### 2. README.md 📚
**Cel:** Główna dokumentacja projektu

**Zawartość:**
- Opis zaimplementowanych schematów różnicowych
- Instrukcje kompilacji i uruchomienia
- Wyjaśnienie plików wyjściowych
- Analiza wyników (zbieżność, błędy maszynowe)
- Przykładowe wyniki
- Teoria - przypomnienie szeregu Taylora

### 3. INSTRUKCJE.md 🔧
**Cel:** Praktyczny przewodnik krok po kroku

**Zawartość:**
- Szybki start (kompilacja, uruchomienie)
- Interpretacja wyników tabelarycznych
- Interpretacja wykresów
- Praktyczne wskazówki (wybór metody, wybór h)
- Typowe błędy i ich unikanie
- Eksperymenty do przeprowadzenia
- Debugging
- Pomysły na rozszerzenia

### 4. TEORIA.md 📖
**Cel:** Kompletne wyprowadzenie matematyczne

**Zawartość:**
- Definicja pochodnej i szereg Taylora
- Szczegółowe wyprowadzenie wszystkich metod:
  - Forward/Backward O(h)
  - Central O(h²)
  - Forward/Backward 3pt O(h²)
  - Central 5pt O(h⁴)
  - Druga pochodna O(h²) i O(h⁴)
- Analiza błędów (obcięcia i zaokrąglenia)
- Wyznaczenie optymalnego h
- Catastrophic cancellation
- Porównanie metod w tabeli
- Wzory referencyjne

### 5. finite_differences.cpp 💻
**Cel:** Główny program implementujący wszystkie metody

**Funkcjonalności:**
- Szablony funkcji (double/long double)
- Implementacja 6 schematów różnicowych:
  - Forward 2pt (O(h))
  - Backward 2pt (O(h))
  - Central 3pt (O(h²))
  - Forward 3pt (O(h²))
  - Backward 3pt (O(h²))
  - Central 5pt (O(h⁴))
- Testowanie dla f(x) = cos(x)
- Analiza w 3 punktach:
  - x = 0 (brzeg początkowy)
  - x = π/4 (środek)
  - x = π/2 (brzeg końcowy)
- Generowanie danych dla wykresów
- Wyznaczanie doświadczalnych rzędów dokładności
- Porównanie double vs long double

**Wyjście:**
- Tabele błędów dla różnych h
- Pliki .dat z danymi do gnuplot
- Rzędy dokładności

### 6. analiza.cpp 🔬
**Cel:** Szczegółowa analiza pojedynczych aspektów

**Funkcjonalności:**
- Wyświetlanie parametrów precyzji (epsilon_mach, cyfry znaczące)
- Demonstracja catastrophic cancellation
- Porównanie metod dla wybranych h
- Automatyczne szukanie optymalnego h
- Analiza dla double i long double

**Zastosowanie:**
- Głębsze zrozumienie zjawisk numerycznych
- Ilustracja teoretycznych koncepcji
- Debugging i eksploracja

### 7. plot_convergence.gnu 📊
**Cel:** Generowanie wykresów w gnuplot

**Generuje:**
- `convergence_analysis.png`: 6 paneli (double i long double, 3 punkty)
- `comparison_double_vs_long_double.png`: Bezpośrednie porównanie

**Wykresy log-log:**
- Oś X: log₁₀(h)
- Oś Y: log₁₀(błąd)
- Linie referencyjne: slope = 1, 2, 4

### 8. Makefile 🔨
**Cele:**
- `make` - kompiluje wszystko
- `make run` - uruchamia główny program
- `make analysis` - uruchamia analizę
- `make plot` - generuje wykresy
- `make clean` - czyści pliki
- `make help` - pomoc

---

## Jak używać materiałów

### Dla wykładowcy 👨‍🏫

1. **Przygotowanie zajęć:**
   - Rozdaj ZADANIA.md studentom
   - Przeprowadź dowody na tablicy (pomocne: TEORIA.md)
   - Pokaż działanie programów

2. **Podczas zajęć:**
   - Demonstracja: `make run && make analysis`
   - Dyskusja wyników (INSTRUKCJE.md)
   - Interpretacja wykresów

3. **Zadanie domowe:**
   - Studenci implementują własne rozwiązanie
   - Lub modyfikują dostarczony kod
   - Porównują wyniki

### Dla studenta 👨‍🎓

1. **Przed zajęciami:**
   - Przeczytaj TEORIA.md (przypomnienie szeregów Taylora)
   - Przejrzyj ZADANIA.md

2. **Podczas zajęć:**
   - Wykonaj zadania teoretyczne (Zadanie 1, 2)
   - Zaimplementuj program (Zadanie 3)
   - Lub uruchom dostarczony kod: `make plot`

3. **Po zajęciach:**
   - Przeprowadź eksperymenty (INSTRUKCJE.md sekcja Eksperymenty)
   - Odpowiedz na pytania analityczne (Zadanie 4, 5)
   - Napisz raport z wynikami

### Dla samodzielnej nauki 📚

1. **Teoria:**
   - TEORIA.md - pełne wyprowadzenia
   - ZADANIA.md - ćwiczenia z rozwiązaniami

2. **Praktyka:**
   - Skompiluj i uruchom programy
   - Przeanalizuj kod (dobrze skomentowany)
   - Eksperymentuj z parametrami

3. **Weryfikacja:**
   - Porównaj swoje wyniki z dostarczonym programem
   - Sprawdź czy rozumiesz wszystkie wykresy

---

## Kluczowe koncepty

### 1. Rzędy dokładności
- O(h): błąd ~ h
- O(h²): błąd ~ h²
- O(h⁴): błąd ~ h⁴

### 2. Kompromis dokładność vs stabilność
- Małe h → mały błąd obcięcia, duży błąd zaokrąglenia
- Duże h → duży błąd obcięcia, mały błąd zaokrąglenia
- Istnieje optymalne h!

### 3. Catastrophic cancellation
- Odejmowanie bliskich liczb
- Utrata cyfr znaczących
- Ograniczenie minimalnego h

### 4. Wybór metody
- Brzegi: metody jednostronne
- Środek: metody centralne (lepsze)
- Wysoka dokładność: metody wyższego rzędu

---

## Wyniki uczenia się

Po wykonaniu zajęć student powinien:

**Wiedzieć:**
- ✓ Jak wyprowadzić wzory różnicowe z szeregu Taylora
- ✓ Czym jest rząd dokładności i jak go wyznaczyć
- ✓ Skąd biorą się błędy maszynowe
- ✓ Jak znaleźć optymalne h

**Umieć:**
- ✓ Implementować schematy różnicowe w C++
- ✓ Używać szablonów funkcji
- ✓ Analizować zbieżność numeryczną
- ✓ Interpretować wykresy log-log
- ✓ Wyznaczać doświadczalny rząd dokładności

**Rozumieć:**
- ✓ Dlaczego metody centralne są lepsze
- ✓ Dlaczego bardzo małe h daje złe wyniki
- ✓ Kiedy używać której metody
- ✓ Ograniczenia arytmetyki zmiennoprzecinkowej

---

## Przykładowe pytania egzaminacyjne

1. **Teoria:**
   - Wyprowadź wzór na centralną różnicę O(h²)
   - Udowodnij, że ma ona dokładność drugiego rzędu
   - Co to jest catastrophic cancellation?

2. **Praktyka:**
   - Która metoda jest najlepsza dla x = 0?
   - Jak wyznaczasz doświadczalny rząd dokładności?
   - Dla h = 10⁻¹⁰ błąd rośnie zamiast maleć. Dlaczego?

3. **Analiza:**
   - Porównaj wyniki dla double i long double
   - Znajdź optymalne h dla metody O(h²)
   - Wyjaśnij kształt wykresu log₁₀(błąd) vs log₁₀(h)

---

## Rozszerzenia i modyfikacje

### Łatwe:
1. Testuj inne funkcje: sin(x), exp(x), x²
2. Zmień przedział: [0, 2π]
3. Dodaj więcej punktów testowych

### Średnie:
1. Implementuj drugą pochodną
2. Dodaj Richardson extrapolation
3. Zaimplementuj adaptive step size

### Trudne:
1. Porównaj z automatic differentiation
2. Implementuj metody wyższych rzędów (O(h⁶))
3. Rozszerz na funkcje wielu zmiennych (gradient)

---

## Częste problemy i rozwiązania

### Problem 1: "Program się nie kompiluje"
**Rozwiązanie:**
- Sprawdź wersję kompilatora: `g++ --version`
- Potrzebujesz C++17 lub nowszego
- Na starszych systemach: zmień `-std=c++17` na `-std=c++11`

### Problem 2: "Long double = double"
**Wyjaśnienie:**
- Na niektórych platformach (Apple Silicon) long double = double
- To ograniczenie platformy, nie błąd programu
- Na Linuxie x86-64 będzie różnica

### Problem 3: "Brak wykresów"
**Rozwiązanie:**
- Zainstaluj gnuplot: `brew install gnuplot` (macOS)
- Lub: `sudo apt install gnuplot` (Linux)
- Lub: Otwórz pliki .dat w Excel/Python

### Problem 4: "Dziwne wyniki dla małych h"
**To nie błąd!** To właśnie błędy maszynowe, których szukamy!

---

## Podsumowanie techniczne

**Języki/narzędzia:**
- C++17
- gnuplot (opcjonalne)
- make

**Rozmiar:**
- ~500 linii kodu C++
- ~2000 linii dokumentacji
- Czas kompilacji: <5s
- Czas wykonania: <1s

**Testowane na:**
- macOS (Apple Silicon)
- Linux (x86-64)
- Kompilatory: g++, clang++

---

## Contact i źródła

**Repozytorium:** (dodaj link do repo)

**Autorzy:**
- Program: C++ z szablonami
- Dokumentacja: Markdown + LaTeX
- Wykresy: gnuplot

**Licencja:** Open source (do użytku edukacyjnego)

**Data ostatniej aktualizacji:** 2025-11-23

---

## Quick Reference

```bash
# Kompilacja
make

# Uruchomienie
make run          # Główny program
make analysis     # Szczegółowa analiza

# Wykresy
make plot         # Wymaga gnuplot

# Czyszczenie
make clean

# Pomoc
make help
```

**Kluczowe pliki do przeczytania w kolejności:**
1. TEORIA.md - zrozumienie matematyki
2. ZADANIA.md - zadania do wykonania
3. INSTRUKCJE.md - jak uruchomić i interpretować
4. README.md - dokumentacja ogólna

**Najważniejszy wniosek:**
> Istnieje optymalne h minimalizujące błąd całkowity.
> Zbyt małe h powoduje błędy maszynowe!
> Używaj metod wyższego rzędu dla lepszej dokładności.

---

**Powodzenia na zajęciach! 🚀**
