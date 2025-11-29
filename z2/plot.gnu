set terminal pngcairo size 1600,1000 enhanced font "Helvetica,12"
set output "wynik.png"

set xlabel "log10(x)"
set ylabel "log10(|blad wzgledny|)"
set grid
set key left top

set style line 1 lc rgb "#0072BD" lw 2
set style line 2 lc rgb "#D95319" lw 2

plot \
    "bledy_basic.dat"    using 1:2 with lines ls 1 title "naiwny", \
    "bledy_improved.dat" using 1:2 with lines ls 2 title "poprawiony"

unset output
