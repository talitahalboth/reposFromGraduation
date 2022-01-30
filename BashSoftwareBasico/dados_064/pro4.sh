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