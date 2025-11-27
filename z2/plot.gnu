#!/usr/bin/gnuplot

# Skrypt gnuplot do wizualizacji błędów obliczeniowych
# f(x) = x^3 / (6 * (sinh(x) - x))

set terminal pngcairo enhanced size 1200,800 font 'Arial,12'
set output 'error_analysis.png'

set title "Analiza błędów względnych obliczania f(x) = x^3/(6[sinh(x)-x])"
set xlabel "log_{10}(x)"
set ylabel "log_{10}(błąd względny)"
set grid
set key left top

# Linia reprezentująca błąd maszynowy (precyzja double ~10^-16)
set arrow from -10,-16 to 3,-16 nohead lw 2 lc rgb "gray" dt 2

# Legenda dla linii błędu maszynowego
set label "Błąd maszynowy (≈10^{-16})" at -8,-15.5 textcolor rgb "gray"

plot 'results_naive.txt' using 2:6 with lines lw 2 lc rgb "red" title "Metoda naiwna (sinh)", \
     'results_taylor.txt' using 2:6 with lines lw 2 lc rgb "blue" title "Szereg Taylora", \
     'results_hybrid.txt' using 2:6 with lines lw 2 lc rgb "green" title "Metoda hybrydowa"

# Drugi wykres - porównanie wartości obliczonych
set output 'function_values.png'
set title "Wartości funkcji f(x) = x^3/(6[sinh(x)-x])"
set xlabel "log_{10}(x)"
set ylabel "f(x)"
set key right top
unset label
unset arrow

plot 'results_naive.txt' using 2:3 with lines lw 2 lc rgb "red" title "Metoda naiwna", \
     'results_taylor.txt' using 2:3 with lines lw 2 lc rgb "blue" title "Szereg Taylora", \
     'results_hybrid.txt' using 2:3 with lines lw 2 lc rgb "green" title "Metoda hybrydowa", \
     'results_naive.txt' using 2:4 with points pt 7 ps 0.5 lc rgb "black" title "Wartości dokładne"

# Trzeci wykres - zoom na małe x (gdzie występuje problem)
set output 'error_analysis_zoom.png'
set title "Zoom: błędy względne dla małych x"
set xlabel "log_{10}(x)"
set ylabel "log_{10}(błąd względny)"
set xrange [-10:0]
set yrange [-18:0]
set key left top

set arrow from -10,-16 to 0,-16 nohead lw 2 lc rgb "gray" dt 2
set label "Błąd maszynowy (≈10^{-16})" at -9,-15.5 textcolor rgb "gray"

plot 'results_naive.txt' using 2:6 with lines lw 2 lc rgb "red" title "Metoda naiwna (sinh)", \
     'results_taylor.txt' using 2:6 with lines lw 2 lc rgb "blue" title "Szereg Taylora", \
     'results_hybrid.txt' using 2:6 with lines lw 2 lc rgb "green" title "Metoda hybrydowa"

print "Wykresy zapisane:"
print "  - error_analysis.png (pełny zakres)"
print "  - error_analysis_zoom.png (zoom na małe x)"
print "  - function_values.png (wartości funkcji)"
