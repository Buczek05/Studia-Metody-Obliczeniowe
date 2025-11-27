#!/usr/bin/gnuplot

set terminal pngcairo enhanced font 'Arial,12' size 1200,900
set output 'convergence_analysis.png'

set multiplot layout 2,3 title "Analiza zbieżności przybliżeń różnicowych - f(x) = cos(x)"

# ========== DOUBLE - PUNKT ŚRODKOWY ==========
set title "Double: Punkt środkowy (x = π/4)"
set xlabel "log_{10}(h)"
set ylabel "log_{10}(błąd)"
set grid
set key left top

plot 'convergence_double_middle.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 title "Forward 2pt (O(h))", \
     'convergence_double_middle.dat' u 1:3 w lp pt 9 ps 0.8 lw 2 title "Backward 2pt (O(h))", \
     'convergence_double_middle.dat' u 1:4 w lp pt 5 ps 0.8 lw 2 title "Central 3pt (O(h^2))", \
     'convergence_double_middle.dat' u 1:5 w lp pt 13 ps 0.8 lw 2 title "Central 5pt (O(h^4))", \
     x with lines dt 2 lc rgb "red" title "slope = 1", \
     2*x with lines dt 2 lc rgb "blue" title "slope = 2", \
     4*x with lines dt 2 lc rgb "green" title "slope = 4"

# ========== DOUBLE - BRZEG POCZĄTKOWY ==========
set title "Double: Brzeg początkowy (x = 0)"
plot 'convergence_double_start.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 title "Forward 2pt (O(h))", \
     'convergence_double_start.dat' u 1:3 w lp pt 5 ps 0.8 lw 2 title "Central 3pt (O(h^2))", \
     'convergence_double_start.dat' u 1:4 w lp pt 11 ps 0.8 lw 2 title "Forward 3pt (O(h^2))", \
     x with lines dt 2 lc rgb "red" title "slope = 1", \
     2*x with lines dt 2 lc rgb "blue" title "slope = 2"

# ========== DOUBLE - BRZEG KOŃCOWY ==========
set title "Double: Brzeg końcowy (x = π/2)"
plot 'convergence_double_end.dat' u 1:2 w lp pt 9 ps 0.8 lw 2 title "Backward 2pt (O(h))", \
     'convergence_double_end.dat' u 1:3 w lp pt 5 ps 0.8 lw 2 title "Central 3pt (O(h^2))", \
     'convergence_double_end.dat' u 1:4 w lp pt 11 ps 0.8 lw 2 title "Backward 3pt (O(h^2))", \
     x with lines dt 2 lc rgb "red" title "slope = 1", \
     2*x with lines dt 2 lc rgb "blue" title "slope = 2"

# ========== LONG DOUBLE - PUNKT ŚRODKOWY ==========
set title "Long Double: Punkt środkowy (x = π/4)"
plot 'convergence_long_double_middle.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 title "Forward 2pt (O(h))", \
     'convergence_long_double_middle.dat' u 1:3 w lp pt 9 ps 0.8 lw 2 title "Backward 2pt (O(h))", \
     'convergence_long_double_middle.dat' u 1:4 w lp pt 5 ps 0.8 lw 2 title "Central 3pt (O(h^2))", \
     'convergence_long_double_middle.dat' u 1:5 w lp pt 13 ps 0.8 lw 2 title "Central 5pt (O(h^4))", \
     x with lines dt 2 lc rgb "red" title "slope = 1", \
     2*x with lines dt 2 lc rgb "blue" title "slope = 2", \
     4*x with lines dt 2 lc rgb "green" title "slope = 4"

# ========== LONG DOUBLE - BRZEG POCZĄTKOWY ==========
set title "Long Double: Brzeg początkowy (x = 0)"
plot 'convergence_long_double_start.dat' u 1:2 w lp pt 7 ps 0.8 lw 2 title "Forward 2pt (O(h))", \
     'convergence_long_double_start.dat' u 1:3 w lp pt 5 ps 0.8 lw 2 title "Central 3pt (O(h^2))", \
     'convergence_long_double_start.dat' u 1:4 w lp pt 11 ps 0.8 lw 2 title "Forward 3pt (O(h^2))", \
     x with lines dt 2 lc rgb "red" title "slope = 1", \
     2*x with lines dt 2 lc rgb "blue" title "slope = 2"

# ========== LONG DOUBLE - BRZEG KOŃCOWY ==========
set title "Long Double: Brzeg końcowy (x = π/2)"
plot 'convergence_long_double_end.dat' u 1:2 w lp pt 9 ps 0.8 lw 2 title "Backward 2pt (O(h))", \
     'convergence_long_double_end.dat' u 1:3 w lp pt 5 ps 0.8 lw 2 title "Central 3pt (O(h^2))", \
     'convergence_long_double_end.dat' u 1:4 w lp pt 11 ps 0.8 lw 2 title "Backward 3pt (O(h^2))", \
     x with lines dt 2 lc rgb "red" title "slope = 1", \
     2*x with lines dt 2 lc rgb "blue" title "slope = 2"

unset multiplot

# ========== PORÓWNANIE DOUBLE VS LONG DOUBLE ==========
set output 'comparison_double_vs_long_double.png'
set title "Porównanie: Double vs Long Double\n(Central 5pt w punkcie środkowym)"
set xlabel "log_{10}(h)"
set ylabel "log_{10}(błąd)"
set grid
set key left top

plot 'convergence_double_middle.dat' u 1:5 w lp pt 7 ps 1 lw 2 lc rgb "blue" title "Double", \
     'convergence_long_double_middle.dat' u 1:5 w lp pt 9 ps 1 lw 2 lc rgb "red" title "Long Double", \
     4*x with lines dt 2 lc rgb "green" title "slope = 4 (teoretyczny)"

print "Wykresy zapisane:"
print "  - convergence_analysis.png"
print "  - comparison_double_vs_long_double.png"
