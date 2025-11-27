#!/bin/bash

# Skrypt pomocniczy do uruchomienia wszystkich programów i analiz
# Zajęcia 13 - Kwadratury i interpolacja

set -e  # Przerwij na błędzie

# Kolory dla outputu
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Funkcja do wyświetlania nagłówków
header() {
    echo -e "\n${BLUE}╔════════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║  $1${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════════════════════════════════╝${NC}\n"
}

# Funkcja do wyświetlania komunikatów
info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Banner
echo -e "${BLUE}"
cat << "EOF"
╔══════════════════════════════════════════════════════════════════════╗
║                                                                      ║
║   ZAJĘCIA 13 - KWADRATURY I INTERPOLACJA                            ║
║   Automatyczny skrypt uruchamiający                                 ║
║                                                                      ║
╚══════════════════════════════════════════════════════════════════════╝
EOF
echo -e "${NC}"

# Sprawdź dostępność narzędzi
header "Sprawdzanie dostępności narzędzi"

if command -v g++ &> /dev/null; then
    info "g++ jest dostępny ($(g++ --version | head -1))"
else
    error "g++ nie jest zainstalowany!"
    exit 1
fi

if command -v gnuplot &> /dev/null; then
    info "gnuplot jest dostępny ($(gnuplot --version))"
    GNUPLOT_AVAILABLE=1
else
    warning "gnuplot nie jest zainstalowany - wykresy nie będą generowane"
    GNUPLOT_AVAILABLE=0
fi

# Kompilacja
header "Kompilacja programów"

info "Czyszczenie starych plików..."
make clean > /dev/null 2>&1 || true

info "Kompilacja wszystkich programów..."
if make all; then
    info "Kompilacja zakończona sukcesem!"
else
    error "Błąd kompilacji!"
    exit 1
fi

# Uruchomienie programu examples
header "Uruchamianie programu 'examples'"
info "Program demonstruje rozwiązania zadań 4 i 5"
sleep 1

./examples

# Uruchomienie programu erf_quadratures
header "Uruchamianie programu 'erf_quadratures'"
info "Program oblicza funkcję erf(x) różnymi metodami"
sleep 1

# Przekieruj część wyjścia do pliku, ale pokaż podsumowanie
./erf_quadratures > erf_output.txt

# Pokaż ostatnie linie (podsumowanie)
tail -30 erf_output.txt

info "Pełne wyjście zapisane w: erf_output.txt"

# Generowanie wykresów
if [ $GNUPLOT_AVAILABLE -eq 1 ]; then
    header "Generowanie wykresów"

    if [ -f "plot_errors.gp" ]; then
        info "Uruchamianie gnuplot..."
        gnuplot plot_errors.gp

        if [ -f "error_analysis.png" ]; then
            info "Wykres wygenerowany: error_analysis.png"

            # Próba otwarcia wykresu
            if command -v open &> /dev/null; then
                info "Otwieranie wykresu..."
                open error_analysis.png
            elif command -v xdg-open &> /dev/null; then
                info "Otwieranie wykresu..."
                xdg-open error_analysis.png
            else
                info "Wykres zapisany, otwórz ręcznie: error_analysis.png"
            fi
        else
            warning "Nie udało się wygenerować wykresu"
        fi
    else
        warning "Nie znaleziono skryptu plot_errors.gp"
    fi
else
    warning "Pomijam generowanie wykresów (brak gnuplot)"
fi

# Podsumowanie plików
header "Wygenerowane pliki"

echo "Pliki z danymi:"
ls -lh data_*.txt 2>/dev/null | awk '{print "  - " $9 " (" $5 ")"}'

if [ -f "error_analysis.png" ]; then
    echo -e "\nWykresy:"
    ls -lh *.png 2>/dev/null | awk '{print "  - " $9 " (" $5 ")"}'
fi

echo -e "\nPliki pomocnicze:"
ls -lh erf_output.txt plot_errors.gp 2>/dev/null | awk '{print "  - " $9 " (" $5 ")"}'

# Analiza rzędów dokładności
header "Analiza rzędów dokładności"

if [ -f "data_simpson.txt" ]; then
    info "Szacowanie rzędów na podstawie danych..."

    cat << 'EOF' | gnuplot 2>/dev/null || warning "Nie można oszacować rzędów"
set fit quiet
set fit logfile '/dev/null'

# Dopasowania
f1(x) = a1*x + b1
f2(x) = a2*x + b2
f3(x) = a3*x + b3

fit f1(x) 'data_trapezoid.txt' using 1:2 via a1, b1
fit f2(x) 'data_simpson.txt' using 1:2 via a2, b2
fit f3(x) 'data_rect_mid.txt' using 1:2 via a3, b3

print sprintf("  Trapezy:           rząd ≈ %.2f (oczekiwano ~3)", a1)
print sprintf("  Simpson:           rząd ≈ %.2f (oczekiwano ~5)", a2)
print sprintf("  Prostokąty (środ): rząd ≈ %.2f (oczekiwano ~3)", a3)
EOF
fi

# Końcowe informacje
header "Zakończono!"

echo -e "${GREEN}✓ Wszystkie programy zostały uruchomione${NC}"
echo -e "${GREEN}✓ Dane zostały wygenerowane${NC}"
if [ $GNUPLOT_AVAILABLE -eq 1 ]; then
    echo -e "${GREEN}✓ Wykresy zostały wygenerowane${NC}"
fi

echo -e "\n${YELLOW}Co dalej?${NC}"
echo "  1. Sprawdź plik erf_output.txt dla pełnych wyników"
echo "  2. Otwórz error_analysis.png aby zobaczyć wykresy błędów"
echo "  3. Przejrzyj pliki data_*.txt dla surowych danych"
echo "  4. Przeczytaj TUTORIAL.md dla szczegółowej instrukcji"
echo "  5. Zobacz zadania.md dla rozwiązań teoretycznych"

echo -e "\n${BLUE}Aby wyczyścić wszystkie pliki:${NC} make clean\n"
