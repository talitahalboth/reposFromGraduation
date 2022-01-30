echo "Problema 1"
printf "        "; 
printf "1k     ";
printf "2k     ";
printf "4k     ";
printf "8k     ";
printf "16k    ";
printf "32k    ";
printf "64k    ";
echo ;
printf "frag    "
grep din_dmm f*_{1,2,4,8,16,32,64}k*A1*B16*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "jpeg_enc"
grep din_dmm j*_{1,2,4,8,16,32,64}k*A1*B16*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "rtr     "
grep din_dmm r*_{1,2,4,8,16,32,64}k*A1*B16*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "zip_dec "
grep din_dmm zip_dec*_{1,2,4,8,16,32,64}k*A1*B16*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "zip_enc "
grep din_dmm zip_enc*_{1,2,4,8,16,32,64}k*A1*B16*WwAn | awk '{printf $6" " }' ; 
echo ;
echo;
echo "Problema 2";
printf "frag "; 
printf "2k     ";
printf "4k     ";
printf "8k     ";
echo ;
printf "1    ";
grep din_dmm f*_[2-8]k*A1*B64*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "2    ";
grep din_dmm f*_[2-8]k*A2*B64*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "4    ";
grep din_dmm f*_[2-8]k*A4*B64*WwAn | awk '{printf $6" " }' ; 
echo ;
echo;
printf "rtr  "; 
printf "2k     ";
printf "4k     ";
printf "8k     ";
echo ;
printf "1    ";
grep din_dmm r*_[2-8]k*A1*B64*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "2    ";
grep din_dmm r*_[2-8]k*A2*B64*WwAn | awk '{printf $6" " }' ; 
echo ;
printf "4    ";
grep din_dmm r*_[2-8]k*A4*B64*WwAn | awk '{printf $6" " }' ; 
echo ;
echo;
#a partir daqui comecei a usar variáveis porque acho mais fácil
echo "Problema 3";
prog=1;
while [ $prog -le 5 ]
do
  case $prog in
    1)  
      path="fra"
      printf "frag     ";
      ;;
    2)  
      path="jpe"
      printf "jpeg_enc "
      ;;
    3)  
      path="rtr"
      printf "rtr      "
      ;;
    4)  
      path="zip_dec" 
      printf "zip_dec  "
      ;;
    5)  
      path="zip_enc"
      printf "zip_enc  "
      ;;
    *)
  esac
  printf "16     ";
  echo ;
  i=1;
  while [ $i -le 8 ]; do
    printf $i;
    printf " WwAn   ";
    grep din_dmm $path*_16k*A$i*B4*WwAn | awk '{printf $6" " }' ; 
    echo ;
    printf $i;
    printf " WcAw   ";
    grep din_dmm $path*_16k*A$i*B4*WcAw | awk '{printf $6" " }' ; 
    echo ;  
    i=$((i*2))
  done
  prog=$((prog+1))
  echo;
done
echo
echo
echo "Problema 4";

prog=1;
while [ $prog -le 5 ]
do
	case $prog in
		1)	
			path="fra"
			printf "frag     ";
			;;
		2)	
			path="jpe"
			printf "jpeg_enc "
			;;
		3)	
			path="rtr"
			printf "rtr      "
			;;
		4)	
			path="zip_dec" 
			printf "zip_dec  "
			;;
		5)	
			path="zip_enc"
			printf "zip_enc  "
			;;
		*)
	esac
	printf "16     ";
	printf "32     ";
	printf "64     ";
	echo ;

	i=2
	j=16
	while [ $i -le 8 ]
	do
		j=16
		printf $i"k       "
		while [ $j -le 64 ]
		do
			
			
			grep din_dmm $path*_$i"k"*A4*B$j*WwAn | awk '{printf $6" " }' ; 
			
			j=$((j*2))
		done
		echo;
		i=$((i*2))
	done
	prog=$((prog+1))
done