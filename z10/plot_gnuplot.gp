#!/usr/bin/env gnuplot
# Skrypt gnuplot do wizualizacji wyników
# Alternatywa dla skryptu Python

# Ustawienia ogólne
set terminal pngcairo enhanced font 'Arial,12' size 1200,800
set grid
set key left top
set xlabel 't'
set ylabel 'y(t)'

# ============================================================================
# Wykres 1: Metoda Eulera bezpośrednia - przypadki stabilności
# ============================================================================

set output 'wykres_1_euler_explicit_gnuplot.png'
set title 'Metoda Eulera bezpośrednia - analiza stabilności'

set multiplot layout 1,3

# Przypadek stabilny
set title 'a) Stabilny (dt = 0.005)'
plot 'analytical.csv' using 1:2 with lines lw 2 title 'Analityczne', \
     'euler_explicit_stable.csv' using 1:2 with points pt 7 ps 0.5 title 'Numeryczne'

# Przypadek graniczny
set title 'b) Graniczny (dt = 0.02)'
plot 'analytical.csv' using 1:2 with lines lw 2 title 'Analityczne', \
     'euler_explicit_marginal.csv' using 1:2 with points pt 7 ps 0.5 title 'Numeryczne'

# Przypadek niestabilny
set title 'c) Niestabilny (dt = 0.05)'
set autoscale y
plot 'analytical.csv' using 1:2 with lines lw 2 title 'Analityczne', \
     'euler_explicit_unstable.csv' using 1:2 with points pt 7 ps 0.5 title 'Numeryczne'

unset multiplot

# ============================================================================
# Wykres 2: Metoda Eulera pośrednia
# ============================================================================

set output 'wykres_2_euler_implicit_gnuplot.png'
set title 'Metoda Eulera pośrednia (implicit)'
set autoscale y

plot 'analytical.csv' using 1:2 with lines lw 2 lc rgb 'blue' title 'Analityczne', \
     'euler_implicit.csv' using 1:2 with points pt 6 ps 1 lc rgb 'red' title 'Numeryczne (dt=0.01)'

# ============================================================================
# Wykres 3: Metoda trapezów
# ============================================================================

set output 'wykres_3_trapezoidal_gnuplot.png'
set title 'Metoda trapezów'

plot 'analytical.csv' using 1:2 with lines lw 2 lc rgb 'blue' title 'Analityczne', \
     'trapezoidal.csv' using 1:2 with points pt 8 ps 1 lc rgb 'green' title 'Numeryczne (dt=0.01)'

# ============================================================================
# Wykres 4: Analiza zbieżności (log-log)
# ============================================================================

set output 'wykres_4_convergence_gnuplot.png'
set title 'Analiza zbieżności: log_{10}(błąd) vs log_{10}(Δt)'
set logscale xy
set xlabel 'Krok czasowy Δt'
set ylabel 'Maksymalny błąd bezwzględny'
set format x "10^{%T}"
set format y "10^{%T}"
set key left top

# Funkcje referencyjne
slope1(x) = 1e-2 * x      # Rząd 1
slope2(x) = 1e0 * x**2    # Rząd 2

plot 'convergence_analysis.csv' using 1:3 with linespoints lw 2 pt 4 title 'Euler pośrednia', \
     'convergence_analysis.csv' using 1:4 with linespoints lw 2 pt 8 title 'Trapezów', \
     slope1(x) with lines dt 2 lw 1.5 lc rgb 'black' title 'Rząd 1 (nachylenie = 1)', \
     slope2(x) with lines dt 3 lw 1.5 lc rgb 'black' title 'Rząd 2 (nachylenie = 2)'

# ============================================================================
# Wykres 5: Porównanie błędów w funkcji czasu
# ============================================================================

set output 'wykres_5_error_comparison_gnuplot.png'
set title 'Porównanie błędów metod numerycznych'
unset logscale x
set logscale y
set xlabel 't'
set ylabel 'Błąd bezwzględny |y_{num} - y_{anal}|'
set format y "10^{%T}"
set autoscale x

plot 'euler_explicit_stable.csv' using 1:4 with lines lw 2 title 'Euler bezpośrednia (dt=0.005)', \
     'euler_implicit.csv' using 1:4 with lines lw 2 title 'Euler pośrednia (dt=0.01)', \
     'trapezoidal.csv' using 1:4 with lines lw 2 title 'Trapezów (dt=0.01)'

print "Wykresy zostały wygenerowane:"
print "  - wykres_1_euler_explicit_gnuplot.png"
print "  - wykres_2_euler_implicit_gnuplot.png"
print "  - wykres_3_trapezoidal_gnuplot.png"
print "  - wykres_4_convergence_gnuplot.png"
print "  - wykres_5_error_comparison_gnuplot.png"
