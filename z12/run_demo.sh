#!/bin/bash

# Skrypt demonstracyjny dla zajęć nr 12
# Uruchamia automatycznie program zjawiska Rungego z domyślnymi parametrami

echo "=========================================="
echo "  Zajęcia nr 12 - Zjawisko Rungego"
echo "  Automatyczny tryb demonstracyjny"
echo "=========================================="
echo

# Kompilacja
echo "Kompilacja programów..."
make clean > /dev/null 2>&1
make all

if [ $? -ne 0 ]; then
    echo "Błąd kompilacji!"
    exit 1
fi

echo
echo "=========================================="
echo "CZĘŚĆ 1: Algorytmy interpolacji (Zadania 1-3)"
echo "=========================================="
echo
./algos

echo
echo
echo "=========================================="
echo "CZĘŚĆ 2: Zjawisko Rungego"
echo "=========================================="
echo

# Uruchomienie z domyślnymi parametrami
# a = 25 (wyraźne zjawisko Rungego)
# n = 11 (rozsądna liczba węzłów)
echo "Parametry demonstracyjne: a=25, n=11"
echo

# Użycie heredoc do przekazania parametrów
./runge <<EOF
25
11
EOF

echo
echo "=========================================="
echo "CZĘŚĆ 3: Wizualizacja"
echo "=========================================="
echo

# Sprawdzenie czy Python jest dostępny
if command -v python3 &> /dev/null; then
    if python3 -c "import matplotlib, pandas, numpy" 2> /dev/null; then
        echo "Tworzenie wykresów..."
        python3 plot_runge.py
    else
        echo "Ostrzeżenie: Brak wymaganych bibliotek Python (matplotlib, pandas, numpy)"
        echo "Instalacja: pip3 install matplotlib pandas numpy"
        echo "Pliki CSV zostały wygenerowane: runge_results.csv, runge_nodes.csv"
    fi
else
    echo "Ostrzeżenie: Python3 nie jest zainstalowany"
    echo "Pliki CSV zostały wygenerowane: runge_results.csv, runge_nodes.csv"
fi

echo
echo "=========================================="
echo "  Demonstracja zakończona!"
echo "=========================================="
echo
echo "Wygenerowane pliki:"
ls -lh *.csv *.png 2>/dev/null | awk '{print "  - " $9 " (" $5 ")"}'
echo
