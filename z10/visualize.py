#!/usr/bin/env python3
"""
Skrypt do wizualizacji wyników numerycznego rozwiązywania równań różniczkowych
Zajęcia nr 10 - Metody Obliczeniowe
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path

# Ustawienia wykresów
plt.rcParams['figure.figsize'] = (12, 8)
plt.rcParams['font.size'] = 10
plt.rcParams['lines.linewidth'] = 2
plt.rcParams['lines.markersize'] = 4

def plot_euler_explicit_cases():
    """
    Wykres 1: Metoda Eulera bezpośrednia - 3 przypadki
    """
    fig, axes = plt.subplots(1, 3, figsize=(18, 5))
    fig.suptitle('Metoda Eulera bezpośrednia - analiza stabilności', fontsize=14, fontweight='bold')

    cases = [
        ('euler_explicit_stable.csv', 'a) Przypadek stabilny (dt = 0.005)', axes[0]),
        ('euler_explicit_marginal.csv', 'b) Przypadek graniczny (dt = 0.02)', axes[1]),
        ('euler_explicit_unstable.csv', 'c) Przypadek niestabilny (dt = 0.05)', axes[2])
    ]

    # Wczytaj rozwiązanie analityczne
    analytical = pd.read_csv('analytical.csv')

    for filename, title, ax in cases:
        if Path(filename).exists():
            data = pd.read_csv(filename)

            # Rozwiązanie analityczne (linia ciągła)
            ax.plot(analytical['t'], analytical['y_analytical'],
                   'b-', label='Rozwiązanie analityczne', linewidth=2)

            # Rozwiązanie numeryczne (punkty)
            ax.plot(data['t'], data['y_numerical'],
                   'ro', label='Rozwiązanie numeryczne', markersize=5,
                   markerfacecolor='none', markeredgewidth=1.5)

            ax.set_xlabel('t')
            ax.set_ylabel('y(t)')
            ax.set_title(title)
            ax.legend()
            ax.grid(True, alpha=0.3)

            # Dla przypadku niestabilnego, dostosuj oś Y
            if 'unstable' in filename and data['y_numerical'].max() > 10:
                ax.set_ylim([data['y_numerical'].min() - 1, min(data['y_numerical'].max(), 20)])
                ax.text(0.5, 0.95, 'Uwaga: Rozwiązanie niestabilne!',
                       transform=ax.transAxes, ha='center', va='top',
                       bbox=dict(boxstyle='round', facecolor='red', alpha=0.3))

    plt.tight_layout()
    plt.savefig('wykres_1_euler_explicit.png', dpi=300, bbox_inches='tight')
    print("✓ Zapisano: wykres_1_euler_explicit.png")
    plt.close()


def plot_euler_implicit():
    """
    Wykres 2: Metoda Eulera pośrednia
    """
    fig, ax = plt.subplots(figsize=(10, 6))

    # Wczytaj dane
    analytical = pd.read_csv('analytical.csv')
    data = pd.read_csv('euler_implicit.csv')

    # Rozwiązanie analityczne (linia ciągła)
    ax.plot(analytical['t'], analytical['y_analytical'],
           'b-', label='Rozwiązanie analityczne', linewidth=2)

    # Rozwiązanie numeryczne (punkty)
    ax.plot(data['t'], data['y_numerical'],
           'ro', label='Rozwiązanie numeryczne (dt = 0.01)',
           markersize=6, markerfacecolor='none', markeredgewidth=1.5)

    ax.set_xlabel('t')
    ax.set_ylabel('y(t)')
    ax.set_title('Metoda Eulera pośrednia (implicit)', fontweight='bold')
    ax.legend()
    ax.grid(True, alpha=0.3)

    # Dodaj informację o błędzie
    max_error = data['error'].max()
    ax.text(0.98, 0.98, f'Błąd maksymalny: {max_error:.2e}',
           transform=ax.transAxes, ha='right', va='top',
           bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))

    plt.tight_layout()
    plt.savefig('wykres_2_euler_implicit.png', dpi=300, bbox_inches='tight')
    print("✓ Zapisano: wykres_2_euler_implicit.png")
    plt.close()


def plot_trapezoidal():
    """
    Wykres 3: Metoda trapezów
    """
    fig, ax = plt.subplots(figsize=(10, 6))

    # Wczytaj dane
    analytical = pd.read_csv('analytical.csv')
    data = pd.read_csv('trapezoidal.csv')

    # Rozwiązanie analityczne (linia ciągła)
    ax.plot(analytical['t'], analytical['y_analytical'],
           'b-', label='Rozwiązanie analityczne', linewidth=2)

    # Rozwiązanie numeryczne (punkty)
    ax.plot(data['t'], data['y_numerical'],
           'go', label='Rozwiązanie numeryczne (dt = 0.01)',
           markersize=6, markerfacecolor='none', markeredgewidth=1.5)

    ax.set_xlabel('t')
    ax.set_ylabel('y(t)')
    ax.set_title('Metoda trapezów', fontweight='bold')
    ax.legend()
    ax.grid(True, alpha=0.3)

    # Dodaj informację o błędzie
    max_error = data['error'].max()
    ax.text(0.98, 0.98, f'Błąd maksymalny: {max_error:.2e}',
           transform=ax.transAxes, ha='right', va='top',
           bbox=dict(boxstyle='round', facecolor='lightgreen', alpha=0.5))

    plt.tight_layout()
    plt.savefig('wykres_3_trapezoidal.png', dpi=300, bbox_inches='tight')
    print("✓ Zapisano: wykres_3_trapezoidal.png")
    plt.close()


def plot_convergence_analysis():
    """
    Wykres 4: Analiza zbieżności - log(błąd) vs log(dt)
    """
    fig, ax = plt.subplots(figsize=(10, 8))

    # Wczytaj dane
    data = pd.read_csv('convergence_analysis.csv')

    # Usuń zerowe błędy (niestabilne przypadki)
    data_filtered = data[data['error_euler_explicit'] > 0].copy()

    # Wykres log-log
    if len(data_filtered) > 0:
        ax.loglog(data_filtered['dt'], data_filtered['error_euler_explicit'],
                 'ro-', label='Euler bezpośrednia', linewidth=2, markersize=6)

    ax.loglog(data['dt'], data['error_euler_implicit'],
             'bs-', label='Euler pośrednia', linewidth=2, markersize=6)

    ax.loglog(data['dt'], data['error_trapezoidal'],
             'g^-', label='Trapezów', linewidth=2, markersize=6)

    # Dodaj linie referencyjne dla rzędów zbieżności
    dt_ref = np.array([1e-4, 1e-2])

    # Rząd 1 (nachylenie 1)
    error_order1 = 1e-2 * dt_ref
    ax.loglog(dt_ref, error_order1, 'k--', linewidth=1.5,
             label='Rząd 1 (nachylenie = 1)', alpha=0.5)

    # Rząd 2 (nachylenie 2)
    error_order2 = 1e0 * dt_ref**2
    ax.loglog(dt_ref, error_order2, 'k:', linewidth=1.5,
             label='Rząd 2 (nachylenie = 2)', alpha=0.5)

    ax.set_xlabel('Krok czasowy Δt', fontsize=12)
    ax.set_ylabel('Maksymalny błąd bezwzględny', fontsize=12)
    ax.set_title('Analiza zbieżności: log₁₀(błąd) vs log₁₀(Δt)', fontsize=14, fontweight='bold')
    ax.legend(loc='upper left', fontsize=10)
    ax.grid(True, which='both', alpha=0.3)

    # Dodaj adnotacje
    ax.text(0.98, 0.05,
           'Metoda trapezów: rząd 2\n'
           'Metody Eulera: rząd 1',
           transform=ax.transAxes, ha='right', va='bottom',
           bbox=dict(boxstyle='round', facecolor='yellow', alpha=0.3),
           fontsize=10)

    plt.tight_layout()
    plt.savefig('wykres_4_convergence.png', dpi=300, bbox_inches='tight')
    print("✓ Zapisano: wykres_4_convergence.png")
    plt.close()


def plot_error_comparison():
    """
    Wykres 5: Porównanie błędów dla trzech metod
    """
    fig, ax = plt.subplots(figsize=(10, 6))

    # Wczytaj dane
    euler_stable = pd.read_csv('euler_explicit_stable.csv')
    euler_implicit = pd.read_csv('euler_implicit.csv')
    trapezoidal = pd.read_csv('trapezoidal.csv')

    # Wykres błędów w funkcji czasu
    ax.semilogy(euler_stable['t'], euler_stable['error'],
               'r-', label='Euler bezpośrednia (dt=0.005)', linewidth=2)

    ax.semilogy(euler_implicit['t'], euler_implicit['error'],
               'b-', label='Euler pośrednia (dt=0.01)', linewidth=2)

    ax.semilogy(trapezoidal['t'], trapezoidal['error'],
               'g-', label='Trapezów (dt=0.01)', linewidth=2)

    ax.set_xlabel('t')
    ax.set_ylabel('Błąd bezwzględny |y_num - y_anal|')
    ax.set_title('Porównanie błędów metod numerycznych w funkcji czasu', fontweight='bold')
    ax.legend()
    ax.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('wykres_5_error_comparison.png', dpi=300, bbox_inches='tight')
    print("✓ Zapisano: wykres_5_error_comparison.png")
    plt.close()


def compute_experimental_order():
    """
    Obliczanie eksperymentalnego rzędu zbieżności
    """
    print("\n" + "="*70)
    print("ANALIZA RZĘDU ZBIEŻNOŚCI")
    print("="*70)

    data = pd.read_csv('convergence_analysis.csv')

    # Filtruj stabilne przypadki
    data_stable = data[data['error_euler_explicit'] > 0].copy()

    methods = {
        'Euler bezpośrednia': data_stable[['dt', 'error_euler_explicit']].values,
        'Euler pośrednia': data[['dt', 'error_euler_implicit']].values,
        'Trapezów': data[['dt', 'error_trapezoidal']].values
    }

    print("\nRząd zbieżności p obliczony z: log(e2/e1) / log(h2/h1)\n")

    for method_name, values in methods.items():
        print(f"\n{method_name}:")
        print("-" * 60)

        if len(values) < 2:
            print("  Zbyt mało punktów do analizy")
            continue

        orders = []
        for i in range(len(values) - 1):
            dt1, error1 = values[i]
            dt2, error2 = values[i + 1]

            if error1 > 0 and error2 > 0:
                order = np.log(error2 / error1) / np.log(dt2 / dt1)
                orders.append(order)
                print(f"  dt={dt1:.2e} → dt={dt2:.2e}: p ≈ {order:.3f}")

        if orders:
            avg_order = np.mean(orders)
            print(f"\n  Średni rząd: {avg_order:.3f}")

            # Porównanie z teorią
            if 'Trapez' in method_name:
                theoretical = 2
            else:
                theoretical = 1

            print(f"  Teoretyczny rząd: {theoretical}")
            print(f"  Różnica: {abs(avg_order - theoretical):.3f}")

    print("\n" + "="*70)


def create_summary_report():
    """
    Tworzenie raportu podsumowującego
    """
    print("\n" + "="*70)
    print("RAPORT PODSUMOWUJĄCY")
    print("="*70)

    methods = [
        ('euler_explicit_stable.csv', 'Euler bezpośrednia (stabilna, dt=0.005)'),
        ('euler_explicit_marginal.csv', 'Euler bezpośrednia (graniczna, dt=0.02)'),
        ('euler_implicit.csv', 'Euler pośrednia (dt=0.01)'),
        ('trapezoidal.csv', 'Trapezów (dt=0.01)')
    ]

    print("\nBŁĘDY MAKSYMALNE:\n")

    for filename, method_name in methods:
        if Path(filename).exists():
            data = pd.read_csv(filename)
            if 'error' in data.columns:
                max_error = data['error'].max()
                mean_error = data['error'].mean()
                print(f"{method_name:45s}: max = {max_error:.6e}, mean = {mean_error:.6e}")
            else:
                print(f"{method_name:45s}: Brak danych o błędzie (niestabilny)")

    print("\n" + "="*70)
    print("\nWNIOSKI:")
    print("-" * 70)
    print("""
1. Metoda Eulera bezpośrednia:
   - Warunkowo stabilna: wymaga dt ≤ 0.02
   - Dla dt = 0.05: rozwiązanie niestabilne (oscylacje, rozbieżność)
   - Rząd zbieżności: 1

2. Metoda Eulera pośrednia:
   - Bezwarunkowo stabilna dla równań rozpadu
   - Stabilna dla dowolnego dt > 0
   - Rząd zbieżności: 1

3. Metoda trapezów:
   - Bezwarunkowo stabilna
   - Najlepsza dokładność spośród trzech metod
   - Rząd zbieżności: 2 (dwukrotnie lepszy niż Euler!)

4. Dla bardzo małych kroków (dt < 1e-5):
   - Błędy maszynowe zaczynają dominować
   - Odchylenie od teoretycznego rzędu zbieżności
    """)
    print("="*70)


def main():
    """
    Główna funkcja uruchamiająca wszystkie wizualizacje
    """
    print("="*70)
    print("WIZUALIZACJA WYNIKÓW - METODY NUMERYCZNE DLA ODE")
    print("="*70)

    # Sprawdź czy pliki istnieją
    required_files = [
        'euler_explicit_stable.csv',
        'euler_implicit.csv',
        'trapezoidal.csv',
        'analytical.csv',
        'convergence_analysis.csv'
    ]

    missing_files = [f for f in required_files if not Path(f).exists()]

    if missing_files:
        print("\n⚠ UWAGA: Brakujące pliki:")
        for f in missing_files:
            print(f"  - {f}")
        print("\nUruchom najpierw program C++: ./ode_solver")
        return

    print("\nGenerowanie wykresów...\n")

    # Generuj wykresy
    plot_euler_explicit_cases()
    plot_euler_implicit()
    plot_trapezoidal()
    plot_convergence_analysis()
    plot_error_comparison()

    # Analiza numeryczna
    compute_experimental_order()

    # Raport podsumowujący
    create_summary_report()

    print("\n" + "="*70)
    print("WIZUALIZACJA ZAKOŃCZONA POMYŚLNIE")
    print("="*70)
    print("\nWygenerowane pliki:")
    print("  - wykres_1_euler_explicit.png  (3 przypadki)")
    print("  - wykres_2_euler_implicit.png")
    print("  - wykres_3_trapezoidal.png")
    print("  - wykres_4_convergence.png     (analiza zbieżności)")
    print("  - wykres_5_error_comparison.png")
    print("="*70)


if __name__ == '__main__':
    main()
