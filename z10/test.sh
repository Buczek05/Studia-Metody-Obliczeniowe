#!/bin/bash
# Skrypt testowy dla projektu ODE Solver

echo "========================================"
echo "Test projektu ODE Solver"
echo "========================================"
echo ""

# Kolory
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Test 1: Sprawdzenie kompilatora
echo -n "Test 1: Sprawdzanie g++... "
if command -v g++ &> /dev/null; then
    echo -e "${GREEN}OK${NC}"
    g++ --version | head -n 1
else
    echo -e "${RED}BŁĄD${NC}"
    echo "g++ nie jest zainstalowany!"
    exit 1
fi

echo ""

# Test 2: Sprawdzenie Python
echo -n "Test 2: Sprawdzanie Python... "
if command -v python3 &> /dev/null; then
    echo -e "${GREEN}OK${NC}"
    python3 --version
else
    echo -e "${RED}BŁĄD${NC}"
    echo "Python3 nie jest zainstalowany!"
    exit 1
fi

echo ""

# Test 3: Sprawdzenie bibliotek Python
echo "Test 3: Sprawdzanie bibliotek Python..."

for lib in numpy matplotlib pandas; do
    echo -n "  - $lib... "
    if python3 -c "import $lib" 2>/dev/null; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${YELLOW}BRAK${NC}"
        echo "    Zainstaluj: pip3 install $lib"
    fi
done

echo ""

# Test 4: Kompilacja
echo "Test 4: Kompilacja programu..."
if make clean &> /dev/null && make &> /dev/null; then
    echo -e "${GREEN}✓ Kompilacja pomyślna${NC}"
else
    echo -e "${RED}✗ Błąd kompilacji${NC}"
    exit 1
fi

echo ""

# Test 5: Uruchomienie programu
echo "Test 5: Uruchomienie programu..."
if ./ode_solver &> /dev/null; then
    echo -e "${GREEN}✓ Program wykonany pomyślnie${NC}"
else
    echo -e "${RED}✗ Błąd wykonania${NC}"
    exit 1
fi

echo ""

# Test 6: Sprawdzenie wygenerowanych plików
echo "Test 6: Sprawdzanie wygenerowanych plików CSV..."

expected_files=(
    "euler_explicit_stable.csv"
    "euler_explicit_unstable.csv"
    "euler_explicit_marginal.csv"
    "euler_implicit.csv"
    "trapezoidal.csv"
    "analytical.csv"
    "convergence_analysis.csv"
)

all_ok=true
for file in "${expected_files[@]}"; do
    echo -n "  - $file... "
    if [ -f "$file" ]; then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}BRAK${NC}"
        all_ok=false
    fi
done

if [ "$all_ok" = false ]; then
    echo -e "${RED}Niektóre pliki nie zostały wygenerowane!${NC}"
    exit 1
fi

echo ""

# Test 7: Wizualizacja (opcjonalnie)
echo "Test 7: Generowanie wykresów..."
if python3 visualize.py &> /dev/null; then
    echo -e "${GREEN}✓ Wykresy wygenerowane${NC}"

    echo ""
    echo "Wygenerowane wykresy:"
    ls -lh wykres_*.png 2>/dev/null | awk '{print "  - " $9 " (" $5 ")"}'
else
    echo -e "${YELLOW}! Problem z wizualizacją${NC}"
    echo "  Sprawdź czy wszystkie biblioteki Python są zainstalowane"
fi

echo ""
echo "========================================"
echo -e "${GREEN}Wszystkie testy zakończone pomyślnie!${NC}"
echo "========================================"
echo ""
echo "Aby zobaczyć wyniki:"
echo "  - Pliki CSV: ls *.csv"
echo "  - Wykresy: ls *.png"
echo "  - Pełna analiza: python3 visualize.py"
echo ""
