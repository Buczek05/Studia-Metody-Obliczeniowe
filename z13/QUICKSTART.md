# ⚡ Quick Start - 2 minuty do działających programów

## Wariant 1: Wszystko automatycznie (30 sekund)

```bash
./run_all.sh
```

Gotowe! 🎉

---

## Wariant 2: Krok po kroku (2 minuty)

### Krok 1: Kompiluj
```bash
make
```

### Krok 2: Uruchom przykłady (Zadania 4 i 5)
```bash
./examples
```

### Krok 3: Uruchom główny program (funkcja erf)
```bash
./erf_quadratures
```

### Krok 4: Wygeneruj wykres (opcjonalnie, wymaga gnuplot)
```bash
gnuplot plot_errors.gp
open error_analysis.png  # macOS
# lub
xdg-open error_analysis.png  # Linux
```

Gotowe! 🎉

---

## Wariant 3: Super szybki (z make)

```bash
make plot
```

Kompiluje, uruchamia i generuje wykres w jednej komendzie!

---

## 📚 Gdzie dalej?

- **Podstawy**: Czytaj → `README.md`
- **Tutorial**: Czytaj → `TUTORIAL.md`
- **Zadania**: Czytaj → `zadania.md`
- **Wzory**: Czytaj → `wzory_kwadratur.md`
- **Mapa plików**: Czytaj → `INDEX.md`

---

## 🆘 Coś nie działa?

### Błąd kompilacji?
```bash
g++ --version  # Sprawdź czy masz C++17
make clean && make
```

### Brak gnuplot?
```bash
# macOS
brew install gnuplot

# Linux
sudo apt install gnuplot
```

### Inne problemy?
→ Zobacz `TUTORIAL.md` sekcja "Rozwiązywanie problemów"

---

**Tyle!** Jesteś gotowy do eksperymentowania! 🚀
