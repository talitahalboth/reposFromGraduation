import sys
from rail_fence import encrypt_rf
from rail_fence import decrypt_rf
from playfair import encrypt_pf
from playfair import decrypt_pf
from vigenere_autokey import encrypt_va
from vigenere_autokey import decrypt_va
from gera_audio import geraSaida

key_rf=raw_input()
#m=raw_input()
key_pf=raw_input()
key_va=raw_input()

entrada=open("entrada", "rb")
m=entrada.read()

encrypted_pf=encrypt_pf(list(key_pf), list(m))


encrypted_rf=encrypt_rf(list(key_rf), list(encrypted_pf))

encrypted_va=encrypt_va(key_va, encrypted_rf)

geraSaida(encrypted_va)