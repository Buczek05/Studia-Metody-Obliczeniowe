# Instrukcja dla prowadzącego - Zajęcia nr 5

## Szybki start

### 1. Kompilacja wszystkich programów:
```bash
cd z5
make
```

### 2. Uruchomienie wszystkich testów:
```bash
make test
```

## Struktura materiałów

### Rozwiązania teoretyczne
- **zadania.md** - Pełne rozwiązania zadań 1-3 oraz dodatkowego ćwiczenia

### Programy demonstracyjne

#### 1. Program główny (wymagany)
```bash
make run
```
- Dekompozycja LU z częściowym wyborem elementu podstawowego
- Dane z zadania programowego (macierz 5×5)
- Zgodny z wymaganiami wykładu (2 procedury)

#### 2. Weryfikacja zadań teoretycznych
```bash
make run_zadania
```
- Sprawdza obliczenia z zadań 1 i 2
- Wyświetla normy wektorów i macierzy
- Oblicza wskaźniki uwarunkowania

#### 3. Szczegółowa demonstracja zadania 3
```bash
make run_zadanie3
```
- Krok po kroku dekompozycja macierzy z zadania 3
- Idealne do demonstracji podczas zajęć
- Pokazuje wszystkie kroki algorytmu

#### 4. Dodatkowe ćwiczenie (bonus +5.0)
```bash
make run_bonus
```
- Analiza stabilności numerycznej
- Wpływ epsilon na dokładność
- Porównanie z rozwiązaniem analitycznym

## Kluczowe cechy implementacji

### ✓ Zgodność z wymaganiami wykładu:
1. **Procedura 1** (`luDecomposition`):
   - Operuje WYŁĄCZNIE na macierzy A
   - Zwraca macierz z L i U oraz wektor permutacji

2. **Procedura 2** (`solveLU`):
   - Operuje WYŁĄCZNIE na wektorze b
   - Wykorzystuje wyniki z procedury 1
   - Rozwiązuje Ly=Pb, następnie Ux=y

### ✓ Częściowy wybór elementu podstawowego:
- Szuka maksymalnego elementu w kolumnie
- Zamienia wiersze dla stabilności numerycznej
- Śledzi permutacje w wektorze `perm`

### ✓ Weryfikacja poprawności:
- Wszystkie programy weryfikują rozwiązania
- Obliczają błąd ||b - Ax||
- Wyświetlają komunikaty o poprawności

## Dostępne komendy make

| Komenda | Opis |
|---------|------|
| `make` lub `make all` | Kompiluje wszystkie programy |
| `make run` | Uruchamia program główny |
| `make run_zadania` | Weryfikuje zadania 1-2 |
| `make run_zadanie3` | Demonstracja zadania 3 |
| `make run_bonus` | Dodatkowe ćwiczenie |
| `make test` | Uruchamia wszystkie programy |
| `make clean` | Usuwa pliki wykonywalne |

## Oczekiwane wyniki

### Program główny:
- Rozwiązanie: x ≈ [2, 1, 3, 5, 4]
- Błąd: < 10^-14

### Zadania teoretyczne:
- ||x||_1 = 15
- ||x||_2 ≈ 7.416
- ||x||_∞ = 5
- cond(A) ≈ 2.2 (lepsze niż B)

### Zadanie 3:
- Rozwiązanie: x ≈ [2, -3, 2.5, 0]
- Błąd: 0 (rozwiązanie dokładne)

### Dodatkowe ćwiczenie:
- Rozwiązanie analityczne: x = [1, 2, 2, 1]
- Wzrost błędu dla małych epsilon
- cond(B) ≈ 4/ε²

## Uwagi dla studentów

1. Wszystkie programy zawierają szczegółowe komentarze
2. Kod jest napisany zgodnie z C++11
3. Programy są zoptymalizowane (-O2) ale czytelne
4. Weryfikacja rozwiązań jest automatyczna
5. Możliwość łatwej modyfikacji danych wejściowych

## Materiały dodatkowe

- README.md - Szczegółowa dokumentacja
- zadania.md - Rozwiązania teoretyczne z LaTeX
- Wszystkie pliki źródłowe są dobrze skomentowane

---

**Czas kompilacji:** < 5 sekund
**Czas wykonania testów:** < 2 sekundy
**Wymagania:** g++ z obsługą C++11, make (opcjonalnie)
