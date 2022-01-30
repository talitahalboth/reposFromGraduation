info[0]="xyL2 data volume"
info[1]="xyL2 bandwidth"
info[2]="xyL3 data volume"
info[3]="xyL3 bandwidth"
info[4]="xyL2 request rate"
info[5]="xyL2 miss ratio"
info[6]="xyL3 request rate"
info[7]="xyL3 miss ratio"
info[8]="xyPacked DP"
info[9]="xyPacked SP"
info[10]="xyTempo"

title[0]="Volume de Dados L2 [Gb]"
title[1]="Banda de Memória L2 [Mb/s]"
title[2]="Volume de Dados L3 [Gb]"
title[3]="Banda de Memória L3 [Mb/s]"
title[4]="Taxa de Requisição L2"
title[5]="Cache miss L2"
title[6]="Taxa de Requisição L3"
title[7]="Cache miss L3"
title[8]="Operações Aritméticas Double Point / s"
title[9]="Operações Aritméticas Single Point / s"
title[10]="Teste de Tempo"

rm plotting*
for (( i = 0; i <= 10; i++ )); do
    echo "plotting_${info[$i]}.gnu"
    echo "#!/usr/bin/gnuplot

set terminal pngcairo size 600,600 enhanced font 'Courier,15'
set grid

set style line 1 lc rgb '#343d3a' lt 1 lw 3 pt 5 ps 1 # --- red
set style line 2 lc rgb '#fd2e58' lt 1 lw 3 pt 9 ps 1   # --- yellow
set style line 3 lc rgb '#efa93a' lt 1 lw 3 pt 5 ps 1   # --- blue
set style line 4 lc rgb '#5fd0d4' lt 1 lw 3 pt 9 ps 1   # --- green


" >> "plotting_${info[$i]}.gnu"
chmod +x "plotting_${info[$i]}.gnu"
    echo "set title '"${title[$i]}"'" >> "plotting_${info[$i]}.gnu"
    echo "set logscale y
set logscale x 2" >> "plotting_${info[$i]}.gnu"
    saida=$(echo ${info[$i]} | sed -e 's/ /_/g')
    echo "set output '"$saida".png' " >> "plotting_${info[$i]}.gnu"
echo "plot '"${info[$i]}".dat' index 0 title 'Original op1' with linespoints ls 1, \\
     ''                   index 1 title 'Original op2' with linespoints ls 2, \\
     ''                   index 2 title 'Otimizado op1' with linespoints ls 3, \\
     ''                   index 3 title 'Otimizado op2' with linespoints ls 4
     " >> "plotting_${info[$i]}.gnu"
chmod +x "plotting_${info[$i]}.gnu"
done
plotting_xy*