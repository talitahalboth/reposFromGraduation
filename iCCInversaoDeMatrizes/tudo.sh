g[0]=L2
g[1]=L3
g[2]=L2CACHE
g[3]=L3CACHE
g[4]=FLOPS_AVX
size=4
CAM=sba16-thcf16
CORE=2
info[0]="L2 data volume"
info[1]="L2 bandwidth"
info[2]="L3 data volume"
info[3]="L3 bandwidth"
info[4]="L2 request rate"
info[5]="L2 miss ratio"
info[6]="L3 request rate"
info[7]="L3 miss ratio"
info[8]="Packed DP"
info[9]="Packed SP"
GRAPH=graficos/
mkdir -p $GRAPH 
cd $GRAPH
rm *
cd ..

for (( j = 0; j <= $size; j++ )); do
    tam=32
    for (( i = 0; i < 7; i++ )); do
        tam2=$((tam+1))
        j1=$((j*2))
        j2=$((j1+1))


        cd $CAM\0 
        echo $tam Original >> ../$GRAPH/"${info[$j1]}"
        cat likwid/${g[$j]}-$tam | grep "${info[$j1]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j1]}"
        cd ..
        cd $CAM
        echo $tam Otimizado >> ../$GRAPH/"${info[$j1]}"
        cat likwid/${g[$j]}-$tam | grep "${info[$j1]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j1]}"
        cd ..

        cd $CAM\0 
        echo $tam Original >> ../$GRAPH/"${info[$j2]}"
        cat likwid/${g[$j]}-$tam | grep "${info[$j2]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j2]}"
        cd ..
        cd $CAM
        echo $tam Otimizado >> ../$GRAPH/"${info[$j2]}"
        cat likwid/${g[$j]}-$tam | grep "${info[$j2]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j2]}"
        cd ..

        if [[ $tam -le 257 ]]; then

            cd $CAM\0 
            echo $tam2 Original >> ../$GRAPH/"${info[$j1]}"
            cat likwid/${g[$j]}-$tam2 | grep "${info[$j1]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j1]}"
            cd ..
            cd $CAM
            echo $tam2 Otimizado >> ../$GRAPH/"${info[$j1]}"
            cat likwid/${g[$j]}-$tam2 | grep "${info[$j1]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j1]}"
            cd ..

            cd $CAM\0 
            echo $tam2 Original >> ../$GRAPH/"${info[$j2]}"
            cat likwid/${g[$j]}-$tam2 | grep "${info[$j2]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j2]}"
            cd ..
            cd $CAM
            echo $tam2 Otimizado >> ../$GRAPH/"${info[$j2]}"
            cat likwid/${g[$j]}-$tam2 | grep "${info[$j2]}" | cut -d'|' -f3 | tr -d ' ' >> ../$GRAPH/"${info[$j2]}"
            cd ..

        fi

        tam=$((tam*2))
        if [[ $tam == 1024 ]]; then
            tam=1000   
        fi
    done
    
done


tempo[0]="Tempo iter"
tempo[1]="residuo"
for (( j = 0; j <= 0; j++ )); do
    tam=32
    for (( i = 0; i < 7; i++ )); do
        tam2=$((tam+1))


        cd $CAM\0 
        echo $tam Original >> ../$GRAPH/"Tempo"
        cat saida${g[$j]}-$tam | grep "${tempo[0]}" | cut -d':' -f2 | tr -d ' ' >> ../$GRAPH/"Tempo"    
        cat saida${g[$j]}-$tam | grep "${tempo[1]}" | cut -d':' -f2 | tr -d ' '  >> ../$GRAPH/"Tempo"
        cd ..
        cd $CAM
        echo $tam Otimizado >> ../$GRAPH/"Tempo"
        cat saida${g[$j]}-$tam | grep "${tempo[0]}" | cut -d':' -f2 | tr -d ' ' >> ../$GRAPH/"Tempo"    
        cat saida${g[$j]}-$tam | grep "${tempo[1]}" | cut -d':' -f2 | tr -d ' '  >> ../$GRAPH/"Tempo"
        cd ..

        if [[ $tam -le 257 ]]; then

            cd $CAM\0 
            echo $tam2 Original >> ../$GRAPH/"Tempo"
            cat saida${g[$j]}-$tam | grep "${tempo[0]}" | cut -d':' -f2 | tr -d ' ' >> ../$GRAPH/"Tempo"    
            cat saida${g[$j]}-$tam2 | grep "${tempo[1]}"| cut -d':' -f2 | tr -d ' '  >> ../$GRAPH/"Tempo"
            cd ..
            cd $CAM
            echo $tam2 Otimizado >> ../$GRAPH/"Tempo"
            cat saida${g[$j]}-$tam | grep "${tempo[0]}" | cut -d':' -f2 | tr -d ' ' >> ../$GRAPH/"Tempo"    
            cat saida${g[$j]}-$tam2 | grep "${tempo[1]}"| cut -d':' -f2 | tr -d ' '  >> ../$GRAPH/"Tempo"
            cd ..

        fi

        tam=$((tam*2))
        if [[ $tam == 1024 ]]; then
            tam=1000   
        fi
    done
done


cd $GRAPH








info[0]="L2 data volume"
info[1]="L2 bandwidth"
info[2]="L3 data volume"
info[3]="L3 bandwidth"
info[4]="L2 request rate"
info[5]="L2 miss ratio"
info[6]="L3 request rate"
info[7]="L3 miss ratio"
info[8]="Packed DP"
info[9]="Packed SP"
info[10]="Tempo"

rm xy*
i=0
for (( l = 0; l < 11; l++ )); do
    input=${info[$l]}
    echo $input
    for (( j = 0; j < 4; j++ )); do
        i=0;
        k=0;

        while IFS= read -r var
        do
            if [[ $k == 0 ]]; then
                echo >> "xy$input.dat"
                echo >> "xy$input.dat"
                
            fi


            if [[ $i == 0 ]]; then
                foo=$(echo -ne $var  | cut -d " " -f1 )
            fi

            #Não otimizado, op1
            if [[ $j == 0 ]]; then
                if [[ $i == 1 ]]; then
                    var=$(echo -ne $var  | cut -d " " -f1 )
                    echo $foo $var" " >> "xy$input.dat"
                fi
            fi 

            #Não otimizado, op2
            if [[ $j == 1 ]]; then
                if [[ $i == 2 ]]; then
                    var=$(echo -ne $var  | cut -d " " -f1 )
                    echo $foo $var" " >> "xy$input.dat"
                fi
            fi 

            #Otimizado, op1
            if [[ $j == 2 ]]; then
                if [[ $i == 4 ]]; then
                    var=$(echo -ne $var  | cut -d " " -f1 )
                    echo $foo $var" " >> "xy$input.dat"
                fi
            fi

            #otimizado, op2
            if [[ $j == 3 ]]; then
                if [[ $i == 5 ]]; then
                    var=$(echo -ne $var  | cut -d " " -f1 )
                    echo $foo $var" " >> "xy$input.dat"
                fi
            fi  
            k=$((k+1))
            i=$((i+1))
            i=$((i%6))
        done < "$input"
    done
done

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