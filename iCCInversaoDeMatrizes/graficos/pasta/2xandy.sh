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

#cat L2\ bandwidth | egrep "32 Oti" -A4 | sed -n '3p' #op2


#Cada teste deve ser reportado sob a forma de um gráfico de linhas, 
    #com linhas em cores distintas para os resultados de cada versão (v1 e v2);
#No eixo das abcissas os gráficos representam o tamanho da matriz (N).  
    #Cada teste deve ser executado para os seguintes tamanhos de matriz:  N={32, 33, 64, 65, 128, 129, 256, 257, 512, 1000, 2000};
#O número de iterações em todos os testes, para todos tamanhos de matrizes, deve ser -i 10;
#As matrizes devem ser geradas aleatoreamente com a função definida no primeiro trabalho;
#Cada teste deve apresentar em linhas distintas os valores para o cálculo de cada operações (op1 e op2).
    #Assim, os gráficos terão sempre 4 linhas, duas para a v1 e duas para a v2;
#Cada gráfico deve ser explicado e você deve demonstrar que consegue entender o que está reportado nele;
#Os gráficos devem ser apresentados com o eixo das ordenadas em escala logarítmica.

#!/bin/bash
rm xy*
i=0
total=0
for (( l = 0; l < 11; l++ )); do
    input=${info[$l]}
    echo $input
    for (( j = 0; j < 4; j++ )); do
        i=0;
        k=0;
        total=0;

        while IFS= read -r var
        do
            if [[ $i == 0 ]]; then
                foo[$total]=$(echo -ne $var  | cut -d " " -f1 | tr -d ' ')
                #echo ${foo[$total]}
            fi

            #Não otimizado, op1
            if [[ $i == 1 ]]; then
                a1[$total]=$(echo -ne $var  | cut -d " " -f1 | tr -d ' ')
            fi

            #Não otimizado, op2
            if [[ $i == 2 ]]; then
                a2[$total]=$(echo -ne $var  | cut -d " " -f1 | tr -d ' ')
            fi

            #Otimizado, op1
            if [[ $i == 4 ]]; then
                a3[$total]=$(echo -ne $var  | cut -d " " -f1 | tr -d ' ')
            fi

            #otimizado, op2
            if [[ $i == 5 ]]; then
                a4[$total]=$(echo -ne $var  | cut -d " " -f1 | tr -d ' ')
            fi
            k=$((k+1))
            i=$((i+1))
            i=$((i%6))
            if [[ $i == 0 ]]; then
                total=$((total+1))
            fi
        done < "$input"
    done
    for (( i = 0; i < $total; i++ )); do
        echo -ne ${foo[$i]} ${a1[$i]}  ${a2[$i]}  ${a3[$i]}  ${a4[$i]}" " >> "xy$input.dat"
        #echo vetor ${foo[@]}
        echo >> "xy$input.dat"
        
    done
done

