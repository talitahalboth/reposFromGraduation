#!/usr/bin/gnuplot
reset
set terminal png

set xdata time
set timefmt "%d/%m/%Y %H:%M:%S"
set format x "%H:%M"
set xlabel "time"

set ylabel "total actives"
set yrange [0:31]

set title "M7YC Performance per time"
set key reverse Left outside
set grid

set style data linespoints

plot 'xyL2 bandwidth.dat' using 1:2 title "slot 1", \
'' using 1:3 title "slot 2", \
'' using 1:4 title "slot 3", \
#