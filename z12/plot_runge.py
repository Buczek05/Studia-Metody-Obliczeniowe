#!/usr/bin/env python3
"""
Skrypt do wizualizacji wyników zjawiska Rungego
Wymaga: matplotlib, pandas, numpy
Instalacja: pip install matplotlib pandas numpy
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

def plot_runge_phenomenon():
    """Tworzy wykres demonstrujący zjawisko Rungego"""

    # Wczytanie danych
    try:
        df = pd.read_csv('runge_results.csv')
        nodes = pd.read_csv('runge_nodes.csv')
    except FileNotFoundError as e:
        print(f"Błąd: Nie znaleziono pliku CSV. Uruchom najpierw program C++.")
        print(f"Szczegóły: {e}")
        sys.exit(1)

    # Utworzenie figury z wykresami
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle('Zjawisko Rungego - Porównanie węzłów równoodległych i Czebyszewa',
                 fontsize=14, fontweight='bold')

    # Wykres 1: Funkcja i interpolacje
    ax1 = axes[0, 0]
    ax1.plot(df['x'], df['f(x)'], 'k-', linewidth=2, label='f(x) - funkcja oryginalna')
    ax1.plot(df['x'], df['P_equidistant(x)'], 'r--', linewidth=1.5, label='P(x) - węzły równoodległe')
    ax1.plot(df['x'], df['P_chebyshev(x)'], 'b--', linewidth=1.5, label='P(x) - węzły Czebyszewa')

    # Dodanie węzłów
    ax1.plot(nodes['x_equi'], nodes['y_equi'], 'ro', markersize=6, label='Węzły równoodległe')
    ax1.plot(nodes['x_cheb'], nodes['y_cheb'], 'bs', markersize=6, label='Węzły Czebyszewa')

    ax1.set_xlabel('x', fontsize=11)
    ax1.set_ylabel('y', fontsize=11)
    ax1.set_title('Funkcja oryginalna i wielomiany interpolacyjne')
    ax1.legend(loc='best', fontsize=9)
    ax1.grid(True, alpha=0.3)

    # Wykres 2: Błędy interpolacji
    ax2 = axes[0, 1]
    ax2.semilogy(df['x'], df['error_equi'], 'r-', linewidth=1.5, label='Błąd - węzły równoodległe')
    ax2.semilogy(df['x'], df['error_cheb'], 'b-', linewidth=1.5, label='Błąd - węzły Czebyszewa')
    ax2.set_xlabel('x', fontsize=11)
    ax2.set_ylabel('|f(x) - P(x)|', fontsize=11)
    ax2.set_title('Błędy interpolacji (skala logarytmiczna)')
    ax2.legend(loc='best', fontsize=9)
    ax2.grid(True, alpha=0.3)

    # Wykres 3: Zbliżenie na krańce - węzły równoodległe
    ax3 = axes[1, 0]
    mask = (df['x'] >= 0.7) | (df['x'] <= -0.7)
    df_edge = df[mask]
    ax3.plot(df_edge['x'], df_edge['f(x)'], 'k-', linewidth=2, label='f(x)')
    ax3.plot(df_edge['x'], df_edge['P_equidistant(x)'], 'r--', linewidth=1.5, label='P(x) - równoodległe')
    ax3.plot(nodes['x_equi'], nodes['y_equi'], 'ro', markersize=6)
    ax3.set_xlabel('x', fontsize=11)
    ax3.set_ylabel('y', fontsize=11)
    ax3.set_title('Zbliżenie na krańce - węzły równoodległe (oscylacje!)')
    ax3.legend(loc='best', fontsize=9)
    ax3.grid(True, alpha=0.3)

    # Wykres 4: Zbliżenie na krańce - węzły Czebyszewa
    ax4 = axes[1, 1]
    ax4.plot(df_edge['x'], df_edge['f(x)'], 'k-', linewidth=2, label='f(x)')
    ax4.plot(df_edge['x'], df_edge['P_chebyshev(x)'], 'b--', linewidth=1.5, label='P(x) - Czebyszew')
    ax4.plot(nodes['x_cheb'], nodes['y_cheb'], 'bs', markersize=6)
    ax4.set_xlabel('x', fontsize=11)
    ax4.set_ylabel('y', fontsize=11)
    ax4.set_title('Zbliżenie na krańce - węzły Czebyszewa (stabilne)')
    ax4.legend(loc='best', fontsize=9)
    ax4.grid(True, alpha=0.3)

    plt.tight_layout()

    # Zapis do pliku
    output_file = 'runge_phenomenon.png'
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"Wykres zapisany do pliku: {output_file}")

    # Wyświetlenie
    plt.show()

def print_statistics():
    """Wyświetla statystyki błędów"""
    df = pd.read_csv('runge_results.csv')

    print("\n=== Statystyki błędów ===")
    print("\nWęzły równoodległe:")
    print(f"  Maksymalny błąd: {df['error_equi'].max():.6e}")
    print(f"  Średni błąd:     {df['error_equi'].mean():.6e}")
    print(f"  Błąd RMS:        {np.sqrt((df['error_equi']**2).mean()):.6e}")

    print("\nWęzły Czebyszewa:")
    print(f"  Maksymalny błąd: {df['error_cheb'].max():.6e}")
    print(f"  Średni błąd:     {df['error_cheb'].mean():.6e}")
    print(f"  Błąd RMS:        {np.sqrt((df['error_cheb']**2).mean()):.6e}")

    print(f"\nPoprawa (stosunek max. błędów): {df['error_equi'].max() / df['error_cheb'].max():.2f}x")

if __name__ == "__main__":
    print("Wizualizacja zjawiska Rungego")
    print("=" * 50)
    plot_runge_phenomenon()
    print_statistics()
