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

