g[0]=L3
g[1]=L2CACHE
g[2]=FLOPS_DP
size=3
tam=32
CAM=sba16-thcf16
CORE=0

for (( i = 0; i < 7; i++ )); do
    tam2=$((tam+1))
    for (( j = 0; j <= 2; j++ )); do
        cd $CAM
        sudo likwid-perfctr -c $CORE -g ${g[$j]} ./invmat -r $tam -i 10 -o saida > likwid/{g[$j]}-$tam
        cd ..
        cd $CAM\0 
        sudo likwid-perfctr -c $CORE -g ${g[$j]} ./invmat -r $tam -i 10 -o saida > likwid/${g[$j]}-$tam
        cd ..
    done
    tam=$((tam*2))
    if [[ $tam == 1024 ]]; then
    tam=1000
    fi
    
done
tam=32
for (( i = 0; i < 4; i++ )); do
    tam2=$((tam+1))
    for (( j = 0; j <= 2; j++ )); do
        cd $CAM
        sudo likwid-perfctr -c $CORE -g ${g[$j]} ./invmat -r $tam2 -i 10 -o saida > likwid/${g[$j]}-$tam2
        cd ..
        cd $CAM\0
        sudo likwid-perfctr -c $CORE -g ${g[$j]} ./invmat -r $tam2 -i 10 -o saida > likwid/${g[$j]}-$tam2
        cd ..
    done
    tam=$((tam*2))
    if [[ $tam==1024 ]]; then
        tam=1000
    fi

done
