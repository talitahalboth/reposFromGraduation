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