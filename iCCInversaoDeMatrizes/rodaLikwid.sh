g[0]=L2
g[1]=L3
g[2]=L2CACHE
g[3]=L3CACHE
g[4]=FLOPS_AVX
size=4
tam=32
CAM=sba16-thcf16
CORE=2

for (( i = 0; i < 7; i++ )); do
    tam2=$((tam+1))
    for (( j = 0; j <= $size; j++ )); do
        cd $CAM
        echo
        echo "Estou em:"
        pwd
        echo "rodando o grupo" ${g[$j]} "com o tamanho " $tam
        echo "Rodar aqui levou:"
        time (likwid-perfctr -f -C $CORE -g ${g[$j]} -m ./invmat -r $tam -i 10 -o saida${g[$j]}-$tam > likwid/${g[$j]}-$tam)
        cd ..
        cd $CAM\0 
        echo
        echo "Estou em:"
        pwd
        echo "rodando o grupo" ${g[$j]} "com o tamanho " $tam
        echo "Rodar aqui levou:"
        time (likwid-perfctr -f -C $CORE -g ${g[$j]} -m ./invmat -r $tam -i 10 -o saida${g[$j]}-$tam > likwid/${g[$j]}-$tam)
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
    for (( j = 0; j <= $size; j++ )); do
        cd $CAM
        echo
        echo "Estou em:"
        pwd
        echo "rodando o grupo" ${g[$j]} "com o tamanho " $tam
        echo "Rodar aqui levou:"
        time (likwid-perfctr -f -C $CORE -g ${g[$j]} -m ./invmat -r $tam2 -i 10 -o saida${g[$j]}-$tam > likwid/${g[$j]}-$tam2)
        cd ..
        cd $CAM\0
        echo
        echo "Estou em:"
        pwd
        echo "rodando o grupo" ${g[$j]} "com o tamanho " $tam
        echo "Rodar aqui levou:"
        time (likwid-perfctr -f -C $CORE -g ${g[$j]} -m ./invmat -r $tam2 -i 10 -o saida${g[$j]}-$tam > likwid/${g[$j]}-$tam2)
        cd ..
    done
    tam=$((tam*2))

done
