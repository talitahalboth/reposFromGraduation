for (( i = 0; i < 10; i++ )); do
	echo >> temp/tempo;echo "Otimizado:" >> temp/tempo;cd sba16-thcf16; (time invmat -r 2000 -i 10 -o ../temp/saida1) 2>> ../temp/tempo; cd ..
	echo >> temp/tempo;echo "Não Otimizado:" >> temp/tempo;cd sba16-thcf162; (time invmat -r 2000 -i 10 -o ../temp/saida2) 2>> ../temp/tempo; cd ..
done