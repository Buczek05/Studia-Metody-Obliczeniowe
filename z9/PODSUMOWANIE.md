# Podsumowanie materiałów - Zajęcia 9

## Utworzone pliki

### 📚 Materiały teoretyczne
1. **zadania.md** - Zadania teoretyczne w formacie Markdown z LaTeX
   - Zadanie 1: Rozwiązanie równania różniczkowego metodą różnicową
   - Zadanie 2: Analiza dokładności schematów (konwencjonalny i Numerowa)
   - Rozwiązania przykładowe i notatki dodatkowe

2. **NOTATKI.md** - Uwagi techniczne i dodatkowe informacje
   - Obserwacje dotyczące wyników
   - Możliwe przyczyny rozbieżności
   - Ćwiczenia dla studentów (5 zadań)
   - Pytania kontrolne
   - Problemy do debugowania

### 💻 Programy

3. **main.cpp** - Program główny (11 KB)
   - Rozwiązanie równania: U''(x) + 2U'(x) - 4U(x) + x^(3/2) = 0
   - Metoda konwencjonalna (różnice skończone + algorytm Thomasa)
   - Metoda strzałów (RK4 + bisekcja)
   - Rozwiązanie analityczne
   - Analiza zbieżności dla różnych wartości h
   - Empiryczne wyznaczanie rzędu dokładności
   - Identyfikacja wpływu błędów maszynowych
   - Generowanie plików CSV z wynikami

4. **thomas_demo.cpp** - Program demonstracyjny (8 KB)
   - 3 przykłady ilustrujące algorytm Thomasa:
     * Przykład 1: Prosty układ 4×4
     * Przykład 2: Dyskretyzacja równania u'' = -π²sin(πx)
     * Przykład 3: Porównanie złożoności obliczeniowej
   - Wizualizacja kroków algorytmu (forward elimination + back substitution)
   - Weryfikacja rozwiązań
   - Porównanie z rozwiązaniami analitycznymi

### 🐍 Wizualizacja

5. **plot_results.py** - Skrypt Python do generowania wykresów (9 KB)
   - Porównanie rozwiązań numerycznych z analitycznym
   - Analiza błędów bezwzględnych
   - Wykresy zbieżności log-log
   - Automatyczne obliczanie empirycznego rzędu dokładności
   - Identyfikacja wpływu błędów maszynowych
   - Generuje 3 pliki PNG:
     * solutions_comparison.png
     * convergence_analysis.png
     * convergence_combined.png

### 🔧 Narzędzia

6. **Makefile** - Automatyzacja kompilacji i uruchamiania
   - `make` - kompiluje oba programy
   - `make run` - uruchamia program główny
   - `make demo` - uruchamia program demonstracyjny
   - `make plot` - generuje wykresy
   - `make full` - kompilacja + uruchomienie + wykresy
   - `make clean` - czyszczenie
   - `make help` - pomoc

7. **.gitignore** - Wykluczenie plików binarnych i wynikowych z repozytorium

### 📖 Dokumentacja

8. **README.md** - Pełna dokumentacja projektu (7.5 KB)
   - Opis zadania i metod numerycznych
   - Wymagania i instalacja
   - Instrukcje kompilacji i uruchomienia
   - Opis plików wyjściowych
   - Szczegółowy opis algorytmu Thomasa
   - Interpretacja wykresów
   - Zadania dodatkowe
   - Rozwiązywanie problemów

9. **PODSUMOWANIE.md** - Ten plik

## Statystyki

- **Łączna liczba plików:** 9
- **Łączny rozmiar kodu:** ~30 KB
- **Języki programowania:** C++, Python
- **Linie kodu:** ~700 (C++) + ~200 (Python)
- **Liczba funkcji:** 15+

## Funkcjonalności programu głównego

### Zaimplementowane metody:
1. ✅ Metoda konwencjonalna (różnice skończone)
2. ✅ Algorytm Thomasa (TDMA) - O(n)
3. ✅ Metoda strzałów z RK4
4. ✅ Metoda bisekcji dla parametru strzału
5. ✅ Rozwiązanie analityczne (do porównania)

### Analiza wyników:
1. ✅ Porównanie w wybranych punktach
2. ✅ Maksymalny błąd bezwzględny
3. ✅ Analiza zbieżności dla 9 różnych wartości h
4. ✅ Empiryczne wyznaczanie rzędu dokładności
5. ✅ Identyfikacja wpływu błędów maszynowych
6. ✅ Export danych do CSV

## Jak korzystać z materiałów?

### Dla prowadzącego:
1. Zacznij od `zadania.md` - omów teorię
2. Użyj `make demo` - zademonstruj algorytm Thomasa
3. Uruchom `make full` - pokaż pełną analizę
4. Omów wykresy i wyniki z `NOTATKI.md`

### Dla studentów:
1. Przeczytaj `README.md` - zrozum problem
2. Przeanalizuj kod w `main.cpp`
3. Uruchom `make run` - zobacz wyniki
4. Wygeneruj wykresy: `make plot`
5. Wykonaj ćwiczenia z `NOTATKI.md`
6. Eksperymentuj z parametrami!

## Główne koncepcje omówione w materiałach

### Numeryczne:
- ✅ Centralne różnice skończone (O(h²))
- ✅ Metoda strzałów dla problemów brzegowych
- ✅ Runge-Kutta 4. rzędu (O(h⁴))
- ✅ Metoda bisekcji
- ✅ Algorytm Thomasa dla macierzy trójdiagonalnych
- ✅ Analiza zbieżności (log-log)
- ✅ Błędy dyskretyzacji vs błędy maszynowe

### Programistyczne:
- ✅ Struktura programu numerycznego
- ✅ Używanie vector<double>
- ✅ Generowanie plików CSV
- ✅ Formatowanie wyjścia (setprecision, scientific)
- ✅ Makefile do automatyzacji
- ✅ Dokumentacja kodu

## Możliwe rozszerzenia

1. **Schemat Numerowa** - implementacja metody 4. rzędu dla różnic skończonych
2. **Metoda Newtona-Raphsona** - szybsza niż bisekcja w metodzie strzałów
3. **Wizualizacja w czasie rzeczywistym** - live plotting podczas obliczeń
4. **Równania nieliniowe** - rozszerzenie na przypadki nieliniowe
5. **Warunki brzegowe mieszane** - Dirichleta, Neumanna, Robina
6. **Równania wyższych rzędów** - rozszerzenie do równań 3. i 4. rzędu
7. **Interfejs graficzny** - GUI do zmiany parametrów
8. **Równoległość** - OpenMP/MPI dla dużych siatek

## Wymagane biblioteki

### C++:
- Kompilator z obsługą C++11+ (g++, clang++)
- Biblioteka standardowa (iostream, vector, cmath, fstream, iomanip)

### Python (dla wizualizacji):
```bash
pip install numpy matplotlib pandas
```

## Testowanie

Program został przetestowany z:
- ✅ Kompilacja bez ostrzeżeń
- ✅ Poprawne spełnienie warunków brzegowych
- ✅ Generowanie plików CSV
- ✅ Spójność wyników między metodami
- ✅ Program demonstracyjny (weryfikacja algorytmu Thomasa)

## Znane problemy

1. **Zbieżność** - Błąd nie maleje znacząco z h (możliwy problem z rozwiązaniem analitycznym)
2. **Matplotlib** - Wymaga instalacji bibliotek Python
3. **Błędy maszynowe** - Dla bardzo małych h mogą dominować

Zobacz `NOTATKI.md` dla szczegółów i sugestii rozwiązań.

## Licencja i użycie

Materiały dydaktyczne do zajęć z Metod Obliczeniowych.
Wolne do użytku edukacyjnego.

## Kontakt i wsparcie

W razie pytań:
- Przeczytaj `README.md` i `NOTATKI.md`
- Sprawdź `make help`
- Wykonaj program demonstracyjny: `make demo`
- Eksperymentuj z parametrami w kodzie

---

**Wygenerowano:** 2025-11-23
**Wersja:** 1.0
**Status:** Gotowe do użycia ✅
