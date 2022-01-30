
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