import sys
import numpy

_trash=chr (255)
def encrypt_rf(key_s, message_s):
    keySize=len(key_s)
    v=[]
    i=0
    #sort key by its letters
    #this order will be used to order which columns to write on the output
    v=numpy.argsort(key_s)
    
    #completes the output with \b to complete the output
    while (len(message_s)%keySize != 0):
        message_s.append(_trash)
    messSize=len(message_s)

    m=[]
    for i in range(keySize):
        for j in range(messSize/keySize):
            m.append((message_s[j*(keySize)+v[i]] ))

    return m
            
def decrypt_rf(key_s, message_s):
    keySize=len(key_s)

    v=[]
    aux=[]
    i=0
    v=numpy.argsort(key_s)
    aux=numpy.argsort(v)

    messSize=len(message_s)
    m=[]
    x=0

    for i in range(messSize/keySize):
        for j in range(keySize):
            m.append((message_s[aux[j]*(messSize/keySize)+i] ))
    x=len(m)-1
    while (x>=len(m)-keySize):
        if x < len(m) and m[x]==_trash:
            del m[x]
        x=x-1
    return list(m)

