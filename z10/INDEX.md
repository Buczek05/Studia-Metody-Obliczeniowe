# Zajęcia nr 10 - Przewodnik po projekcie

## 📚 Spis treści dokumentacji

Witaj w projekcie ODE Solver! Ten przewodnik pomoże Ci znaleźć odpowiednie materiały.

---

## 🚀 Szybki start

**Chcesz po prostu uruchomić program?**

👉 **[QUICKSTART.md](QUICKSTART.md)** - Uruchomienie w 3 krokach (2 minuty)

```bash
make run              # Kompilacja i uruchomienie
python3 visualize.py  # Wizualizacja wyników
```

---

## 📖 Dokumentacja główna

### 1. **[README.md](README.md)** - Pełna dokumentacja projektu
- Opis metod numerycznych
- Wymagania i instalacja
- Instrukcja kompilacji i użytkowania
- Struktura projektu
- Analiza teoretyczna stabilności

**Dla kogo**: Wszyscy użytkownicy - czytaj jako pierwszy!

---

### 2. **[zadania.md](zadania.md)** - Zadania z teorią matematyczną
- Treści zadań z zajęć
- Wyprowadzenia matematyczne (LaTeX)
- Analiza warunków stabilności
- Rozwiązania analityczne
- Wymagania dotyczące programu

**Dla kogo**: Studenci rozwiązujący zadania, teoria matematyczna

---

### 3. **[pytania_i_cwiczenia.md](pytania_i_cwiczenia.md)** - Materiały do nauki
- Pytania kontrolne z odpowiedziami
- Zadania rachunkowe
- Ćwiczenia programistyczne
- Pytania otwarte
- Literatura dodatkowa

**Dla kogo**: Nauka teorii, przygotowanie do kolokwium

---

### 4. **[PRZYKŁADOWE_WYNIKI.md](PRZYKŁADOWE_WYNIKI.md)** - Weryfikacja wyników
- Przykładowe wyniki numeryczne
- Analiza błędów
- Weryfikacja rzędu zbieżności
- Tabelaryczne zestawienia
- Wnioski i rekomendacje

**Dla kogo**: Weryfikacja poprawności implementacji

---

## 💻 Kod źródłowy

### Program główny

**[ode_solver.cpp](ode_solver.cpp)** - Program w C++
- Implementacja trzech metod numerycznych
- Generowanie danych do wykresów
- Analiza zbieżności
- Obliczanie błędów

### Wizualizacja

**[visualize.py](visualize.py)** - Skrypt Python
- Generowanie 5 wykresów PNG
- Analiza rzędu zbieżności
- Raport podsumowujący
- Wymagania: numpy, matplotlib, pandas

**[plot_gnuplot.gp](plot_gnuplot.gp)** - Alternatywa gnuplot
- To samo co visualize.py, ale w gnuplot
- Dla użytkowników bez Pythona

### Narzędzia pomocnicze

**[Makefile](Makefile)** - Automatyzacja
```bash
make          # Kompilacja
make run      # Kompilacja + uruchomienie
make visualize # Pełna analiza
make clean    # Czyszczenie
make help     # Pomoc
```

**[test.sh](test.sh)** - Testy automatyczne
- Sprawdzenie środowiska
- Test kompilacji
- Test wykonania
- Weryfikacja plików

---

## 📊 Wyniki

Po uruchomieniu programu otrzymasz:

### Pliki CSV (7 plików)
1. `euler_explicit_stable.csv` - Euler stabilna
2. `euler_explicit_marginal.csv` - Euler graniczna
3. `euler_explicit_unstable.csv` - Euler niestabilna
4. `euler_implicit.csv` - Euler pośrednia
5. `trapezoidal.csv` - Metoda trapezów
6. `analytical.csv` - Rozwiązanie dokładne
7. `convergence_analysis.csv` - Analiza zbieżności

### Wykresy PNG (5 plików)
1. `wykres_1_euler_explicit.png` - 3 przypadki Eulera
2. `wykres_2_euler_implicit.png` - Euler pośrednia
3. `wykres_3_trapezoidal.png` - Trapezów
4. `wykres_4_convergence.png` - Analiza zbieżności
5. `wykres_5_error_comparison.png` - Porównanie błędów

---

## 🎯 Według typu użytkownika

### Student rozwiązujący zajęcia

**Kolejność czytania**:
1. [zadania.md](zadania.md) - Przeczytaj treść zadań
2. [QUICKSTART.md](QUICKSTART.md) - Uruchom program
3. [README.md](README.md) - Zrozum implementację
4. [pytania_i_cwiczenia.md](pytania_i_cwiczenia.md) - Sprawdź wiedzę
5. [PRZYKŁADOWE_WYNIKI.md](PRZYKŁADOWE_WYNIKI.md) - Zweryfikuj wyniki

**Czas**: ~2-3 godziny (czytanie + praktyka)

### Osoba ucząca się teorii ODE

**Kolejność czytania**:
1. [README.md](README.md) - Podstawy teoretyczne
2. [zadania.md](zadania.md) - Analiza matematyczna
3. [pytania_i_cwiczenia.md](pytania_i_cwiczenia.md) - Pogłębienie wiedzy
4. [QUICKSTART.md](QUICKSTART.md) - Praktyczne eksperymenty

**Czas**: ~4-5 godzin

### Programista implementujący metody

**Kolejność**:
1. [README.md](README.md) - Przegląd projektu
2. [ode_solver.cpp](ode_solver.cpp) - Analiza kodu
3. [PRZYKŁADOWE_WYNIKI.md](PRZYKŁADOWE_WYNIKI.md) - Weryfikacja
4. [pytania_i_cwiczenia.md](pytania_i_cwiczenia.md) - Ćwiczenia zaawansowane

**Czas**: ~2-3 godziny

---

## 🔧 Rozwiązywanie problemów

### Nie kompiluje się program

```bash
# Sprawdź wersję kompilatora
g++ --version  # Wymagane: GCC 7+ lub Clang 5+

# Zainstaluj kompilator (Ubuntu)
sudo apt-get install build-essential

# Zainstaluj kompilator (macOS)
xcode-select --install
```

Więcej: Zobacz [README.md](README.md) sekcja "Wymagania"

### Brak bibliotek Python

```bash
# Instalacja
pip3 install numpy matplotlib pandas

# lub
pip3 install -r requirements.txt

# Alternatywa: użyj gnuplot
gnuplot plot_gnuplot.gp
```

### Program nie generuje plików

```bash
# Uruchom testy diagnostyczne
./test.sh

# Sprawdź uprawnienia
ls -la ode_solver
chmod +x ode_solver
```

---

## 📁 Struktura projektu

```
z10/
├── INDEX.md                      # ← TEN PLIK (przewodnik)
├── README.md                     # Główna dokumentacja
├── QUICKSTART.md                 # Szybki start
├── zadania.md                    # Zadania z teorią (LaTeX)
├── pytania_i_cwiczenia.md        # Materiały do nauki
├── PRZYKŁADOWE_WYNIKI.md         # Wyniki referencyjne
│
├── ode_solver.cpp                # Program główny C++
├── visualize.py                  # Wizualizacja Python
├── plot_gnuplot.gp               # Wizualizacja gnuplot
│
├── Makefile                      # Automatyzacja
├── test.sh                       # Testy
├── requirements.txt              # Zależności Python
└── .gitignore                    # Ignorowane pliki
```

---

## 📝 Tematy dodatkowe

### Zadania do samodzielnego rozwiązania

Z pliku [pytania_i_cwiczenia.md](pytania_i_cwiczenia.md):

- ✅ **Zadanie A**: Van der Pol oscillator
- ✅ **Zadanie B**: Równanie logistyczne
- ✅ **Zadanie C**: Układ Lotki-Volterry (drapieżnik-ofiara)

### Rozszerzenia projektu

Pomysły na rozwój (z [README.md](README.md)):

1. Implementacja metody Runge-Kutta 4 (RK4)
2. Adaptacyjny dobór kroku czasowego
3. Rozwiązywanie równań sztywnych
4. Układy równań różniczkowych
5. Równania wyższych rzędów

---

## 🎓 Cele edukacyjne

Po zakończeniu zajęć powinieneś umieć:

- ✅ Implementować metody numeryczne dla ODE
- ✅ Analizować stabilność numeryczną
- ✅ Weryfikować rząd dokładności metod
- ✅ Porównywać efektywność różnych metod
- ✅ Interpretować wyniki numeryczne
- ✅ Rozpoznawać wpływ błędów maszynowych

---

## 📚 Literatura

Podstawowa:
1. Numerical Recipes - Press et al. (Rozdz. 17)
2. Numerical Analysis - Burden & Faires (Rozdz. 5)
3. A First Course in Numerical Methods - Greif & Ascher (Rozdz. 8)

Zaawansowana:
4. Solving ODE I: Nonstiff Problems - Hairer et al.
5. Solving ODE II: Stiff Problems - Hairer & Wanner

Pełna lista: [pytania_i_cwiczenia.md](pytania_i_cwiczenia.md)

---

## 🆘 Pomoc i wsparcie

### Pytania teoretyczne
→ Zobacz [pytania_i_cwiczenia.md](pytania_i_cwiczenia.md)

### Problemy techniczne
→ Zobacz [README.md](README.md) sekcja "Rozwiązywanie problemów"

### Weryfikacja wyników
→ Zobacz [PRZYKŁADOWE_WYNIKI.md](PRZYKŁADOWE_WYNIKI.md)

### Nie wiesz od czego zacząć?
→ Zobacz [QUICKSTART.md](QUICKSTART.md)

---

## ✅ Checklist - czy jestem gotowy?

Przed przystąpieniem do zajęć sprawdź:

- [ ] Przeczytałem [QUICKSTART.md](QUICKSTART.md)
- [ ] Program kompiluje się: `make`
- [ ] Program działa: `./ode_solver`
- [ ] Wygenerowano 7 plików CSV
- [ ] Rozumiem zadania z [zadania.md](zadania.md)
- [ ] Mam zainstalowane Python + biblioteki (opcjonalnie)

Jeśli wszystko OK - jesteś gotowy! 🎉

---

## 📞 Kontakt

Projekt na zajęcia z Metod Obliczeniowych
Zajęcia nr 10 - Metody numeryczne dla równań różniczkowych zwyczajnych

**Materiały edukacyjne** - wolne do użytku w celach dydaktycznych

---

*Ostatnia aktualizacja: 2025-11-23*
*Wersja: 1.0*
