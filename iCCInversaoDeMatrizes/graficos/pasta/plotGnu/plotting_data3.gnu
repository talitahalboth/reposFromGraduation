#!/usr/bin/gnuplot
#
# Plotting the data of file plotting_data1.dat
#
# AUTHOR: Hagen Wierstorf


# wxt
#set terminal wxt size 600,600 enhanced font 'Verdana,10' persist
# png
set terminal pngcairo size 600,600 enhanced font 'Verdana,10'
set output 'plotting_data1.png'
# svg
#set terminal svg size 350,262 fname 'Verdana, Helvetica, Arial, sans-serif' \
#fsize '10'
#set output 'plotting_data1.svg'

# color definitions
set border linewidth 1.5
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5 # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 7 ps 1.5   # --- red
set style line 3 lc rgb '#86aa25' lt 1 lw 2 pt 7 ps 1.5   # --- red
set style line 4 lc rgb '#dc166d' lt 1 lw 2 pt 7 ps 1.5   # --- red



set title 'Teste de tempo'
set logscale y

plot 'xyTempo.dat' title 'Original op1' with linespoints ls 1, \
     ''                   index 1 title 'Original op2' with linespoints ls 2, \
     ''                   index 2 title 'Otimizado op1' with linespoints ls 3, \
     ''                   index 3 title 'Otimizado op2' with linespoints ls 4