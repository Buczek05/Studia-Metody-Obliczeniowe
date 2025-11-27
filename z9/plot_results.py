#!/usr/bin/env python3
"""
Skrypt do wizualizacji wyników rozwiązywania równania różniczkowego
U''(x) + 2U'(x) - 4U(x) + x^(3/2) = 0
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys

# Ustawienia dla lepszej czytelności wykresów
plt.rcParams['figure.figsize'] = (12, 8)
plt.rcParams['font.size'] = 10
plt.rcParams['lines.linewidth'] = 2

def plot_solutions():
    """Wykres porównania rozwiązań numerycznych z analitycznym"""
    try:
        data = pd.read_csv('results.csv')
    except FileNotFoundError:
        print("Błąd: Nie znaleziono pliku results.csv")
        print("Najpierw uruchom program C++!")
        return

    plt.figure(figsize=(14, 10))

    # Wykres 1: Porównanie rozwiązań
    plt.subplot(2, 2, 1)
    plt.plot(data['x'], data['U_analytical'], 'k-', label='Rozwiązanie analityczne', linewidth=2)
    plt.plot(data['x'], data['U_conventional'], 'b--', label='Metoda konwencjonalna', linewidth=1.5)
    plt.plot(data['x'], data['U_shooting'], 'r:', label='Metoda strzałów', linewidth=1.5)
    plt.xlabel('x')
    plt.ylabel('U(x)')
    plt.title('Porównanie rozwiązań numerycznych z analitycznym')
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Wykres 2: Błędy bezwzględne
    plt.subplot(2, 2, 2)
    plt.semilogy(data['x'], data['Error_conv'], 'b-', label='Metoda konwencjonalna')
    plt.semilogy(data['x'], data['Error_shoot'], 'r-', label='Metoda strzałów')
    plt.xlabel('x')
    plt.ylabel('Błąd bezwzględny')
    plt.title('Błędy bezwzględne rozwiązań')
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Wykres 3: Rozwiązanie analityczne (osobno)
    plt.subplot(2, 2, 3)
    plt.plot(data['x'], data['U_analytical'], 'k-', linewidth=2)
    plt.xlabel('x')
    plt.ylabel('U(x)')
    plt.title('Rozwiązanie analityczne')
    plt.grid(True, alpha=0.3)

    # Wykres 4: Różnica między metodami
    plt.subplot(2, 2, 4)
    diff = np.abs(data['U_conventional'] - data['U_shooting'])
    plt.semilogy(data['x'], diff, 'g-', linewidth=2)
    plt.xlabel('x')
    plt.ylabel('|U_conv - U_shoot|')
    plt.title('Różnica między metodami numerycznymi')
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('solutions_comparison.png', dpi=300, bbox_inches='tight')
    print("Wykres porównania rozwiązań zapisany do: solutions_comparison.png")
    plt.show()

def plot_convergence():
    """Wykres analizy zbieżności (log-log)"""
    try:
        data = pd.read_csv('convergence.csv')
    except FileNotFoundError:
        print("Błąd: Nie znaleziono pliku convergence.csv")
        print("Najpierw uruchom program C++!")
        return

    plt.figure(figsize=(14, 6))

    # Wykres 1: Zbieżność metody konwencjonalnej
    plt.subplot(1, 2, 1)
    plt.plot(data['log10_h'], data['log10_Error_conv'], 'bo-', label='Metoda konwencjonalna', markersize=8)

    # Dopasowanie prostej (regresja liniowa)
    coeffs_conv = np.polyfit(data['log10_h'], data['log10_Error_conv'], 1)
    fit_conv = np.poly1d(coeffs_conv)
    plt.plot(data['log10_h'], fit_conv(data['log10_h']), 'b--',
             label=f'Dopasowanie: nachylenie = {coeffs_conv[0]:.2f}', linewidth=1.5)

    # Linie odniesienia dla różnych rzędów
    h_ref = data['log10_h'].values
    err_ref_base = data['log10_Error_conv'].values[len(data)//2]
    h_ref_base = data['log10_h'].values[len(data)//2]

    plt.plot(h_ref, err_ref_base + 1.0 * (h_ref - h_ref_base), 'k:',
             label='Rząd 1 (odniesienie)', alpha=0.5)
    plt.plot(h_ref, err_ref_base + 2.0 * (h_ref - h_ref_base), 'g:',
             label='Rząd 2 (odniesienie)', alpha=0.5)

    plt.xlabel('log₁₀(h)')
    plt.ylabel('log₁₀(błąd)')
    plt.title(f'Zbieżność: Metoda konwencjonalna\n(Empiryczny rząd: {coeffs_conv[0]:.2f})')
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Wykres 2: Zbieżność metody strzałów
    plt.subplot(1, 2, 2)
    plt.plot(data['log10_h'], data['log10_Error_shoot'], 'ro-', label='Metoda strzałów', markersize=8)

    # Dopasowanie prostej
    coeffs_shoot = np.polyfit(data['log10_h'], data['log10_Error_shoot'], 1)
    fit_shoot = np.poly1d(coeffs_shoot)
    plt.plot(data['log10_h'], fit_shoot(data['log10_h']), 'r--',
             label=f'Dopasowanie: nachylenie = {coeffs_shoot[0]:.2f}', linewidth=1.5)

    # Linie odniesienia
    err_ref_base_shoot = data['log10_Error_shoot'].values[len(data)//2]
    plt.plot(h_ref, err_ref_base_shoot + 2.0 * (h_ref - h_ref_base), 'g:',
             label='Rząd 2 (odniesienie)', alpha=0.5)
    plt.plot(h_ref, err_ref_base_shoot + 4.0 * (h_ref - h_ref_base), 'm:',
             label='Rząd 4 (odniesienie)', alpha=0.5)

    plt.xlabel('log₁₀(h)')
    plt.ylabel('log₁₀(błąd)')
    plt.title(f'Zbieżność: Metoda strzałów (RK4)\n(Empiryczny rząd: {coeffs_shoot[0]:.2f})')
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('convergence_analysis.png', dpi=300, bbox_inches='tight')
    print("Wykres analizy zbieżności zapisany do: convergence_analysis.png")
    plt.show()

    # Wypisanie informacji o rzędzie zbieżności
    print("\n=== Analiza rzędu zbieżności ===")
    print(f"Metoda konwencjonalna: empiryczny rząd = {coeffs_conv[0]:.3f}")
    print(f"  (Teoretyczny rząd: 2 dla centralnych różnic)")
    print(f"\nMetoda strzałów: empiryczny rząd = {coeffs_shoot[0]:.3f}")
    print(f"  (Teoretyczny rząd: 4 dla metody RK4)")

    # Identyfikacja wpływu błędów maszynowych
    print("\n=== Analiza wpływu błędów maszynowych ===")
    for i in range(1, len(data)):
        ratio_conv = data['Error_conv'].values[i-1] / data['Error_conv'].values[i]
        ratio_shoot = data['Error_shoot'].values[i-1] / data['Error_shoot'].values[i]

        h_current = data['h'].values[i]

        if ratio_conv < 3.0 or ratio_shoot < 3.0:  # Oczekiwalibyśmy współczynnika ~4 dla rzędu 2
            print(f"h = {h_current:.6f}:")
            if ratio_conv < 3.0:
                print(f"  - Metoda konwencjonalna: współczynnik redukcji błędu = {ratio_conv:.2f}")
                print(f"    (Wpływ błędów maszynowych widoczny dla h < {h_current:.6f})")
            if ratio_shoot < 3.0:
                print(f"  - Metoda strzałów: współczynnik redukcji błędu = {ratio_shoot:.2f}")
                print(f"    (Wpływ błędów maszynowych widoczny dla h < {h_current:.6f})")

def plot_combined_analysis():
    """Połączony wykres obu metod na jednym układzie współrzędnych"""
    try:
        data = pd.read_csv('convergence.csv')
    except FileNotFoundError:
        print("Błąd: Nie znaleziono pliku convergence.csv")
        return

    plt.figure(figsize=(10, 8))

    # Obie metody na jednym wykresie
    plt.plot(data['log10_h'], data['log10_Error_conv'], 'bo-',
             label='Metoda konwencjonalna', markersize=8, linewidth=2)
    plt.plot(data['log10_h'], data['log10_Error_shoot'], 'ro-',
             label='Metoda strzałów (RK4)', markersize=8, linewidth=2)

    # Dopasowania
    coeffs_conv = np.polyfit(data['log10_h'], data['log10_Error_conv'], 1)
    coeffs_shoot = np.polyfit(data['log10_h'], data['log10_Error_shoot'], 1)

    fit_conv = np.poly1d(coeffs_conv)
    fit_shoot = np.poly1d(coeffs_shoot)

    plt.plot(data['log10_h'], fit_conv(data['log10_h']), 'b--',
             label=f'Dopasowanie conv. (rząd {coeffs_conv[0]:.2f})', linewidth=1.5, alpha=0.7)
    plt.plot(data['log10_h'], fit_shoot(data['log10_h']), 'r--',
             label=f'Dopasowanie shoot. (rząd {coeffs_shoot[0]:.2f})', linewidth=1.5, alpha=0.7)

    plt.xlabel('log₁₀(h)', fontsize=14)
    plt.ylabel('log₁₀(błąd)', fontsize=14)
    plt.title('Porównanie zbieżności obu metod\nlog₁₀(błąd) vs log₁₀(h)', fontsize=16)
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('convergence_combined.png', dpi=300, bbox_inches='tight')
    print("Połączony wykres zbieżności zapisany do: convergence_combined.png")
    plt.show()

def main():
    print("=== Wizualizacja wyników ===\n")

    # Sprawdzenie dostępności plików
    try:
        pd.read_csv('results.csv')
        print("✓ Znaleziono plik results.csv")
    except FileNotFoundError:
        print("✗ Nie znaleziono pliku results.csv")
        print("  Uruchom najpierw program C++: ./main")
        return

    try:
        pd.read_csv('convergence.csv')
        print("✓ Znaleziono plik convergence.csv")
    except FileNotFoundError:
        print("✗ Nie znaleziono pliku convergence.csv")
        print("  Uruchom najpierw program C++: ./main")
        return

    print("\nGenerowanie wykresów...\n")

    # Generowanie wszystkich wykresów
    plot_solutions()
    plot_convergence()
    plot_combined_analysis()

    print("\n=== Wizualizacja zakończona ===")
    print("Wygenerowane pliki:")
    print("  1. solutions_comparison.png - Porównanie rozwiązań")
    print("  2. convergence_analysis.png - Analiza zbieżności (osobno)")
    print("  3. convergence_combined.png - Analiza zbieżności (połączone)")

if __name__ == "__main__":
    main()
