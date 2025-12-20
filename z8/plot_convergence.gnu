#!/usr/bin/gnuplot

set terminal pngcairo enhanced font 'Arial,12' size 1400,1000
set output 'convergence_analysis.png'

set multiplot layout 2,3 title "Analiza zbieznosci przyblizen roznicowych - f(x) = cos(x)" font ',14'

set xlabel "log_{10}(h)"
set ylabel "log_{10}(blad)"
set grid
set key left top font ',9'
set xrange [-16:0]

# ========== DOUBLE - POCZATEK (x = 0) ==========
# Kolumny: log10(h), progresywna
set title "Double: x = 0 (poczatek)\nProgresywna"
set yrange [-22:2]

plot 'bledy_double_start.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 lc rgb "red" title "Progresywna O(h)", \
     x with lines dt 2 lc rgb "gray" title "nachylenie = 1"

# ========== DOUBLE - SRODEK (x = pi/4) ==========
# Kolumny: log10(h), progresywna, wsteczna, centralna, centr.II rz.
set title "Double: x = pi/4 (srodek)\nWszystkie metody"
set yrange [-16:16]

plot 'bledy_double_middle.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 lc rgb "red" title "Progresywna O(h)", \
     'bledy_double_middle.dat' u 1:3 w lp pt 9 ps 0.8 lw 2 lc rgb "blue" title "Wsteczna O(h)", \
     'bledy_double_middle.dat' u 1:4 w lp pt 5 ps 0.8 lw 2 lc rgb "green" title "Centralna O(h^2)", \
     'bledy_double_middle.dat' u 1:5 w lp pt 13 ps 0.8 lw 2 lc rgb "purple" title "Centr. II rz. O(h^2)", \
     x with lines dt 2 lc rgb "gray" title "nachylenie = 1", \
     2*x with lines dt 3 lc rgb "gray" title "nachylenie = 2"

# ========== DOUBLE - KONIEC (x = pi/2) ==========
# Kolumny: log10(h), wsteczna
set title "Double: x = pi/2 (koniec)\nWsteczna"
set yrange [-16:16]

plot 'bledy_double_end.dat' u 1:2 w lp pt 9 ps 0.8 lw 2 lc rgb "blue" title "Wsteczna O(h)", \
     x with lines dt 2 lc rgb "gray" title "nachylenie = 1"

# ========== LONG DOUBLE - POCZATEK (x = 0) ==========
set title "Long Double: x = 0 (poczatek)\nProgresywna"
set yrange [-22:2]

plot 'bledy_long_double_start.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 lc rgb "red" title "Progresywna O(h)", \
     x with lines dt 2 lc rgb "gray" title "nachylenie = 1"

# ========== LONG DOUBLE - SRODEK (x = pi/4) ==========
set title "Long Double: x = pi/4 (srodek)\nWszystkie metody"
set yrange [-24:10]

plot 'bledy_long_double_middle.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 lc rgb "red" title "Progresywna O(h)", \
     'bledy_long_double_middle.dat' u 1:3 w lp pt 9 ps 0.8 lw 2 lc rgb "blue" title "Wsteczna O(h)", \
     'bledy_long_double_middle.dat' u 1:4 w lp pt 5 ps 0.8 lw 2 lc rgb "green" title "Centralna O(h^2)", \
     'bledy_long_double_middle.dat' u 1:5 w lp pt 13 ps 0.8 lw 2 lc rgb "purple" title "Centr. II rz. O(h^2)", \
     x with lines dt 2 lc rgb "gray" title "nachylenie = 1", \
     2*x with lines dt 3 lc rgb "gray" title "nachylenie = 2"

# ========== LONG DOUBLE - KONIEC (x = pi/2) ==========
set title "Long Double: x = pi/2 (koniec)\nWsteczna"
set yrange [-24:10]

plot 'bledy_long_double_end.dat' u 1:2 w lp pt 9 ps 0.8 lw 2 lc rgb "blue" title "Wsteczna O(h)", \
     x with lines dt 2 lc rgb "gray" title "nachylenie = 1"

unset multiplot

# ========== POROWNANIE DOUBLE VS LONG DOUBLE ==========
set output 'comparison_double_vs_long_double.png'
set terminal pngcairo enhanced font 'Arial,14' size 900,700
set title "Porownanie: Double vs Long Double\n(Punkt srodkowy x = pi/4, metoda centralna)"
set xlabel "log_{10}(h)"
set ylabel "log_{10}(blad)"
set grid
set key left top
set xrange [-16:0]
set yrange [-22:2]

plot 'bledy_double_middle.dat' u 1:4 w lp pt 7 ps 1 lw 2 lc rgb "blue" title "Double - Centralna", \
     'bledy_long_double_middle.dat' u 1:4 w lp pt 9 ps 1 lw 2 lc rgb "red" title "Long Double - Centralna", \
     2*x with lines dt 2 lc rgb "green" lw 2 title "nachylenie = 2 (teoretyczny)"

print "Wykresy zapisane:"
print "  - convergence_analysis.png"
print "  - comparison_double_vs_long_double.png"
