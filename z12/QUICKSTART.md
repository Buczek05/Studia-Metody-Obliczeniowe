# Szybki start - Zajęcia nr 12

## 🚀 Uruchomienie w 3 krokach

### 1. Kompilacja

```bash
make
```

### 2. Zadania teoretyczne (1-3)

```bash
make run-algos
```

**Wynik:** Program wyświetli rozwiązania zadań 1, 2 i 3 z pełnymi obliczeniami.

### 3. Zjawisko Rungego

```bash
make run
```

**Parametry do wpisania:**
- `a = 25` (dla wyraźnego efektu)
- `n = 11` (liczba węzłów)

**Wynik:** Pliki `runge_results.csv` i `runge_nodes.csv`

### 4. Wizualizacja (opcjonalnie)

```bash
make plot
```

**Wynik:** Wykres `runge_phenomenon.png`

---

## 📊 Przykładowe uruchomienie

```
$ make run-algos
./algos

╔════════════════════════════════════════════════════════╗
║   ALGORYTMY INTERPOLACJI WIELOMIANOWEJ - ZADANIA 1-3   ║
╚════════════════════════════════════════════════════════╝

========================================
ZADANIE 1: Interpolacja Lagrange'a
========================================
...
```

```
$ make run
./runge
=== Demonstracja zjawiska Rungego ===
Funkcja: f(x) = x / (1 + a*x^4)
Przedział: [-1, 1]

Podaj wartość parametru 'a': 25
Podaj liczbę węzłów interpolacji: 11
...

Węzły równoodległe:
  Maksymalny błąd: 1.234e+02
  Średni błąd: 5.678e+00

Węzły Czebyszewa:
  Maksymalny błąd: 1.234e-01
  Średni błąd: 5.678e-03

Poprawa: 1000.00x
```

---

## 🔧 Przydatne komendy

| Komenda | Opis |
|---------|------|
| `make` | Kompilacja obu programów |
| `make run-algos` | Uruchom zadania 1-3 |
| `make run` | Uruchom zjawisko Rungego |
| `make plot` | Wizualizacja wyników |
| `make full` | Wszystko: kompilacja + runge + plot |
| `make clean` | Usuń pliki |
| `make help` | Pomoc |

---

## 📚 Pliki projektu

```
z12/
├── README.md                      # Pełna dokumentacja
├── QUICKSTART.md                  # Ten plik
├── zadania_rozwiazania.md        # Rozwiązania teoretyczne
│
├── interpolation_algorithms.cpp  # Zadania 1-3
├── runge_phenomenon.cpp          # Zjawisko Rungego
├── plot_runge.py                 # Wizualizacja
│
└── Makefile                      # Automatyzacja
```

---

## ❓ Problemy?

1. **Brak kompilatora:**
   ```bash
   # macOS
   xcode-select --install

   # Ubuntu/Debian
   sudo apt install build-essential
   ```

2. **Brak Pythona:**
   ```bash
   pip3 install matplotlib pandas numpy
   ```

3. **Szczegóły:** Zobacz `README.md`
