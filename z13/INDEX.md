# 📚 Indeks plików - Zajęcia 13

Szybki przewodnik po wszystkich plikach w projekcie.

---

## 📖 Dokumentacja i teoria

### 1. **README.md** ⭐ START TUTAJ
Główny plik z instrukcjami - zacznij od tego!
- Opis projektu
- Instrukcje kompilacji
- Wymagania systemowe
- Krótki opis wszystkich programów

### 2. **TUTORIAL.md** 🎓 PRZEWODNIK KROK PO KROKU
Szczegółowy tutorial dla początkujących
- Krok po kroku przez wszystkie programy
- Przykłady użycia
- Rozwiązywanie problemów
- Eksperymenty do przeprowadzenia

### 3. **zadania.md** ✍️ ROZWIĄZANIA ZADAŃ
Pełne rozwiązania wszystkich zadań teoretycznych
- Zadanie 1: Funkcja sklejana kubiczna
- Zadanie 2: Interpolacja biliniowa
- Zadanie 3: Kwadratury złożone (5 metod)
- Zadanie 4: Metoda Romberga
- Zadanie 5: Kwadratura Gaussa

### 4. **wzory_kwadratur.md** 📐 ŚCIĄGAWKA
Kompletny zbiór wzorów i dokumentacja techniczna
- Wszystkie wzory kwadratur
- Węzły i wagi Gaussa
- Algorytm Romberga
- Interpolacja biliniowa
- Funkcje sklejane
- Przykłady implementacji C++
- Wskazówki praktyczne

### 5. **INDEX.md** (ten plik) 🗂️
Mapa wszystkich plików projektu

---

## 💻 Kod źródłowy

### 6. **erf_quadratures.cpp** 🔬 GŁÓWNY PROGRAM
Program do numerycznego obliczania funkcji erf(x)

**Funkcjonalności:**
- 5 metod kwadratur (prostokąty 3×, trapezy, Simpson)
- Obliczenia dla x = 1.0, 2.0, 3.0
- Analiza błędów i zbieżności
- Generowanie danych do wykresów
- Automatyczne tworzenie skryptu gnuplot

**Wyjście:**
- Wyniki numeryczne w terminalu
- Pliki `data_*.txt` z danymi
- Skrypt `plot_errors.gp`

**Uruchomienie:**
```bash
./erf_quadratures
# lub
make run
```

### 7. **examples.cpp** 📊 PRZYKŁADY ZADAŃ
Program demonstracyjny z rozwiązaniami zadań 4 i 5

**Funkcjonalności:**
- Kwadratura Gaussa (2, 3, 4 punkty)
- Metoda Romberga z tablicą
- Porównanie metod dla sin(x)

**Uruchomienie:**
```bash
./examples
# lub
make run-examples
```

---

## 🔧 Narzędzia budowania

### 8. **Makefile** ⚙️ AUTOMATYZACJA KOMPILACJI
Automatyzuje kompilację i uruchamianie

**Dostępne komendy:**
```bash
make              # Kompiluj wszystkie programy
make run          # Uruchom erf_quadratures
make run-examples # Uruchom examples
make plot         # Uruchom erf_quadratures i wygeneruj wykres
make clean        # Wyczyść pliki
make help         # Pokaż pomoc
```

### 9. **run_all.sh** 🚀 SKRYPT AUTOMATYCZNY
Uruchamia wszystko automatycznie z ładnym formatowaniem

**Co robi:**
- Sprawdza dostępność narzędzi
- Kompiluje programy
- Uruchamia oba programy
- Generuje wykresy (jeśli jest gnuplot)
- Analizuje rzędy dokładności
- Pokazuje podsumowanie

**Uruchomienie:**
```bash
./run_all.sh
```

### 10. **.gitignore** 🙈
Ignoruje pliki tymczasowe w git
- Pliki wykonywalne
- Pliki danych (*.txt)
- Wykresy (*.png)
- Pliki tymczasowe

---

## 📊 Pliki danych (generowane automatycznie)

### 11-15. **data_*.txt** - Dane z analizy błędów
Generowane przez `erf_quadratures`:
- `data_rect_left.txt` - prostokąty (lewy węzeł)
- `data_rect_right.txt` - prostokąty (prawy węzeł)
- `data_rect_mid.txt` - prostokąty (środek)
- `data_trapezoid.txt` - trapezy
- `data_simpson.txt` - Simpson

**Format:** `log10(h)  log10(błąd)`

### 16. **plot_errors.gp** - Skrypt gnuplot
Automatycznie generowany skrypt do tworzenia wykresów
- Dopasowanie liniowe dla każdej metody
- Obliczenie nachyleń (rzędów dokładności)
- Tworzenie wykresu PNG

### 17. **error_analysis.png** - Wykres błędów
Graficzna reprezentacja zbieżności metod
- Log-log plot błędu vs kroku h
- Dopasowane proste regresji
- Rzędy dokładności w legendzie

---

## 📁 Struktura plików

```
z13/
├── README.md                  # ⭐ START - główny przewodnik
├── TUTORIAL.md                # 🎓 Szczegółowy tutorial
├── INDEX.md                   # 🗂️ Ten plik
├── zadania.md                 # ✍️ Rozwiązania zadań teoretycznych
├── wzory_kwadratur.md         # 📐 Wszystkie wzory
│
├── erf_quadratures.cpp        # 🔬 Główny program
├── examples.cpp               # 📊 Program z przykładami
│
├── Makefile                   # ⚙️ System budowania
├── run_all.sh                 # 🚀 Skrypt automatyczny
├── .gitignore                 # 🙈 Ignorowane pliki
│
└── [generowane]
    ├── erf_quadratures        # Plik wykonawczy
    ├── examples               # Plik wykonawczy
    ├── data_*.txt             # Dane (5 plików)
    ├── plot_errors.gp         # Skrypt gnuplot
    └── error_analysis.png     # Wykres
```

---

## 🎯 Szybki start

### Dla niecierpliwych (5 minut):
```bash
# Uruchom wszystko automatycznie
./run_all.sh
```

### Dla dociekliwych (30 minut):
1. Przeczytaj: `README.md`
2. Przejdź przez: `TUTORIAL.md`
3. Uruchom: `make run-examples`
4. Uruchom: `make plot`
5. Przejrzyj: `zadania.md`

### Dla teoretyków:
1. Studiuj: `wzory_kwadratur.md`
2. Rozwiązuj: `zadania.md`
3. Implementuj: sprawdź kod w `*.cpp`

---

## 📚 Kolejność czytania (zalecana)

### Poziom 1: Podstawy (Dla każdego)
1. **README.md** - Zrozumienie projektu
2. **TUTORIAL.md** - Pierwsze uruchomienie

### Poziom 2: Praktyka (Programowanie)
3. **examples.cpp** - Proste przykłady
4. **erf_quadratures.cpp** - Pełna implementacja

### Poziom 3: Teoria (Matematyka)
5. **zadania.md** - Rozwiązania zadań
6. **wzory_kwadratur.md** - Kompletna dokumentacja matematyczna

---

## 🔍 Szukasz czegoś konkretnego?

### Jak uruchomić programy?
→ **README.md** sekcja "Kompilacja i uruchomienie"
→ **TUTORIAL.md** kroki 2-4

### Jak działa metoda X?
→ **wzory_kwadratur.md** - wszystkie wzory
→ **zadania.md** - przykłady obliczeń

### Jak rozwiązać zadanie Y?
→ **zadania.md** - pełne rozwiązania

### Jak zaimplementować metodę Z?
→ **erf_quadratures.cpp** lub **examples.cpp** - sprawdź kod
→ **wzory_kwadratur.md** sekcja 9 - przykłady C++

### Co oznacza błąd kompilacji?
→ **TUTORIAL.md** sekcja "Rozwiązywanie problemów"

### Jak wygenerować wykresy?
→ **TUTORIAL.md** krok 5
→ **README.md** sekcja "Generowanie wykresu"

---

## 📊 Podsumowanie zawartości

| Typ | Liczba plików | Pliki |
|-----|---------------|-------|
| 📖 Dokumentacja | 5 | README, TUTORIAL, zadania, wzory, INDEX |
| 💻 Kod źródłowy | 2 | erf_quadratures.cpp, examples.cpp |
| 🔧 Narzędzia | 3 | Makefile, run_all.sh, .gitignore |
| 📊 Generowane | 7+ | pliki wykonawalne, data_*.txt, wykresy |

**Razem:** 10 plików podstawowych + generowane

---

## 🎓 Cele edukacyjne - które pliki?

| Cel | Polecane pliki |
|-----|----------------|
| Zrozumieć kwadratury numeryczne | wzory_kwadratur.md, zadania.md |
| Nauczyć się implementacji | erf_quadratures.cpp, examples.cpp |
| Zrobić zadania domowe | zadania.md, examples.cpp |
| Napisać raport | TUTORIAL.md, wykresy PNG, zadania.md |
| Przygotować się do egzaminu | wzory_kwadratur.md |
| Zaimpressionować prowadzącego | run_all.sh, własne modyfikacje kodu |

---

## 💡 Wskazówki

- ⭐ Pliki oznaczone gwiazdką to punkty startowe
- 🎓 Emoji ułatwiają nawigację
- Wszystkie pliki .md można czytać w zwykłym edytorze tekstu
- Pliki .cpp zawierają szczegółowe komentarze
- Skrypty automatyczne (Makefile, run_all.sh) oszczędzają czas

---

## 🆘 Potrzebujesz pomocy?

1. Sprawdź **TUTORIAL.md** → sekcja "Rozwiązywanie problemów"
2. Zobacz komentarze w kodzie źródłowym
3. Uruchom `make help`
4. Przeczytaj dokładnie komunikaty błędów

---

**Ostatnia aktualizacja:** 2024
**Wersja:** 1.0
**Autor:** Materiały do zajęć 13 - Metody Obliczeniowe

**Miłej nauki! 🚀**
