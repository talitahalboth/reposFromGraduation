import sys
from rail_fence import decrypt_rf
from playfair import decrypt_pf
from vigenere_autokey import decrypt_va
key_rf=raw_input()
key_pf=raw_input()
key_va=raw_input()

#essa e a parte que le o arquivo
i=0
k=""
with open("saida.wav", 'rb') as file:
    for byte in iter(lambda: file.read(1), b''):
        i=i+1
        if i>=41:
            k=k+(byte)

file.close
arq=k

decrypted_va=decrypt_va(key_va, arq)

decrypted_rf=decrypt_rf(list(key_rf), decrypted_va)

decrypted_pf=decrypt_pf(key_pf,decrypted_rf)

sys.stdout.write(decrypted_pf)









