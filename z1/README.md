# Metody Obliczeniowe - Zajęcia nr 1

## Temat: Błędy w obliczeniach numerycznych i reprezentacja zmiennoprzecinkowa

Ten projekt zawiera rozwiązania zadań z pierwszych zajęć z przedmiotu Metody Obliczeniowe, dotyczących:
- Rodzajów błędów w obliczeniach numerycznych
- Reprezentacji zmiennoprzecinkowej liczb rzeczywistych
- Standardu IEEE 754
- Eksperymentalnego wyznaczania epsylona maszynowego

---

## 📁 Struktura projektu

```
z1/
├── README.md                    # Ten plik
├── zadania_teoretyczne.md       # Rozwiązania zadań teoretycznych (1 i 2)
├── Makefile                     # System budowania projektu
├── src/
│   └── machine_epsilon.cpp      # Program do wyznaczania epsylona maszynowego
└── bin/
    └── machine_epsilon          # Skompilowany program (po kompilacji)
```

---

## 📝 Zawartość projektu

### 1. Zadania teoretyczne (`zadania_teoretyczne.md`)

Plik zawiera szczegółowe rozwiązania zadań teoretycznych:

#### Zadanie 1: Błąd obcięcia w szeregu Taylora
- Oszacowanie błędu obcięcia dla ln(z) przy sumowaniu n wyrazów szeregu Taylora wokół z₀ = 1
- Obliczenie liczby wyrazów potrzebnych do osiągnięcia błędu ≤ 10⁻⁸ dla z = 2
- Wzory zapisane w formacie LaTeX

#### Zadanie 2: System reprezentacji zmiennoprzecinkowej
- Analiza prostego 5-bitowego systemu zmiennoprzecinkowego
- Wyznaczenie wszystkich reprezentowalnych liczb
- Określenie słów maszynowych dla wartości specjalnych (+0, -0, +INF, -INF, NaN)
- Liczby znormalizowane i zdenormalizowane

### 2. Program C++ (`src/machine_epsilon.cpp`)

Program eksperymentalnie wyznacza:
- **Epsylon maszynowy** - najmniejszą liczbę ε taką, że fl(1 + ε) > 1
- **Liczbę bitów mantysy** dla typów float, double, long double
- **Liczbę cyfr znaczących** w reprezentacji dziesiętnej
- **Weryfikację wyników** poprzez porównanie z wartościami ze standardowej biblioteki C++

Program dodatkowo wyjaśnia związek między epsylonem maszynowym a precyzją arytmetyki zmiennoprzecinkowej.

---

## 🔧 Wymagania

- Kompilator C++ obsługujący standard C++17 lub nowszy (np. g++, clang++)
- System budowania `make`
- System operacyjny: Linux, macOS, Windows (z MinGW/Cygwin)

---

## 🚀 Kompilacja i uruchomienie

### Kompilacja programu

```bash
make
```

Alternatywnie, bezpośrednia kompilacja:
```bash
g++ -std=c++17 -Wall -Wextra -O2 src/machine_epsilon.cpp -o bin/machine_epsilon
```

### Uruchomienie programu

```bash
./bin/machine_epsilon
```

Lub kompilacja i uruchomienie w jednej komendzie:
```bash
make run
```

### Czyszczenie plików

Usunięcie skompilowanych plików:
```bash
make clean
```

Pełne czyszczenie (włącznie z katalogiem bin):
```bash
make distclean
```

### Ponowna kompilacja

```bash
make rebuild
```

### Informacje o projekcie

```bash
make info
```

---

## 📊 Oczekiwane wyniki

Program powinien wyświetlić wyniki zbliżone do:

### Dla typu `float` (IEEE 754 single precision):
- Epsylon maszynowy: ~1.19 × 10⁻⁷
- Liczba bitów mantysy: 24 bity (23 + 1 niejawny)
- Liczba cyfr znaczących: ~7 cyfr dziesiętnych

### Dla typu `double` (IEEE 754 double precision):
- Epsylon maszynowy: ~2.22 × 10⁻¹⁶
- Liczba bitów mantysy: 53 bity (52 + 1 niejawny)
- Liczba cyfr znaczących: ~16 cyfr dziesiętnych

### Dla typu `long double`:
- Wyniki zależą od platformy i kompilatora:
  - Na x86-64 (extended precision): 64 bity mantysy
  - Na niektórych platformach może być równoważny `double`
  - Na niektórych systemach (ARM64): 113 bitów mantysy (quad precision)

---

## 🧮 Teoria: Epsylon maszynowy

### Definicja
Epsylon maszynowy (ε) to najmniejsza liczba taka, że:
```
fl(1 + ε) > 1
```
gdzie `fl()` oznacza reprezentację zmiennoprzecinkową.

### Znaczenie
- Określa precyzję systemu arytmetyki zmiennoprzecinkowej
- Jest bezpośrednio związany z liczbą bitów mantysy: ε = 2⁻ᵖ (gdzie p to liczba bitów)
- Wyznacza minimalną rozróżnialną różnicę między liczbami w okolicy 1.0

### Konsekwencje praktyczne
- Błędy zaokrągleń są rzędu ε
- Względny błąd reprezentacji: |x - fl(x)| / |x| ≤ ε/2
- Nie należy porównywać liczb zmiennoprzecinkowych na równość (a == b)
- Zamiast tego: |a - b| < ε (lub wielokrotność ε)

---

## 📚 Standard IEEE 754

### Format single precision (float - 32 bity):
```
[1 bit znaku][8 bitów cechy][23 bity mantysy]
```
- Zakres cechy: -126 do +127
- Mantysa: 23 bity + 1 bit niejawny = 24 bity efektywnie
- Zakres: ~10⁻³⁸ do ~10³⁸
- Precyzja: ~7 cyfr dziesiętnych

### Format double precision (double - 64 bity):
```
[1 bit znaku][11 bitów cechy][52 bity mantysy]
```
- Zakres cechy: -1022 do +1023
- Mantysa: 52 bity + 1 bit niejawny = 53 bity efektywnie
- Zakres: ~10⁻³⁰⁸ do ~10³⁰⁸
- Precyzja: ~16 cyfr dziesiętnych

---

## 🔍 Algorytm wyznaczania epsylona

```cpp
T epsilon = 1.0;
while (1.0 + epsilon/2.0 > 1.0) {
    epsilon = epsilon / 2.0;
}
return epsilon;
```

**Jak to działa:**
1. Zaczynamy od ε = 1.0
2. Sprawdzamy czy (1 + ε/2) jest rozróżnialne od 1
3. Jeśli tak, dzielimy ε przez 2 i powtarzamy
4. W końcu osiągamy wartość, dla której (1 + ε/2) nie jest już rozróżnialne od 1
5. Wtedy obecna wartość ε to epsylon maszynowy

---

## 👨‍💻 Autor

Projekt wykonany w ramach zajęć z przedmiotu Metody Obliczeniowe.

---

## 📄 Licencja

Projekt edukacyjny - wolne użycie w celach akademickich.
