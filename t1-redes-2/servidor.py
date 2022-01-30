# -*- coding: utf-8 -*-
"""
Programa que implementa um servidor sobre TCP e se comunica usando mensagens criptografadas
As mensagens são criptografadas usando DES
A chave do DES é gerada usando o algoritmo Diffie-Hellman

Autoras: Stephanie Briere Americo e Talita Halboth Cunha Fernandes
Disciplina: Redes II
Data da última atualização: 02/08/2021
"""

import random
import sys
import socket

from log import *
from utils import *

# Inicia o socket
def InitSocket(port):
    s = socket.socket(socket.AF_INET,
                      socket.SOCK_STREAM)
    s.bind(('', port))
    s.listen()
    return s

# Checa se um numero n e primo
def isPrime(n):
    if n <= 1:
        return False
    if n <= 3:
        return 1
    if n % 2 == 0 or n % 3 == 0:
        return False

    i = 3
    while i * i <= n:
        if n % i == 0:
            return False
        i = i + 2

    return True

# Encontra os fatores primos de um numero
def findPrimeFactors(n):
    # usa set pra evitar fatores repetidos
    primeFactors = set()
    while n % 2 == 0:
        primeFactors.add(2)
        n = int(n / 2)
    i = 3
    while i * i <= n:
        while n % i == 0:
            primeFactors.add(i)
            n = int(n / i)
        i = i + 2
    if n > 2:
        primeFactors.add(n)
    return primeFactors

# Encontra a menor raiz primitiva de n
def findSmallestPrimitive(n):
    if not isPrime(n):
        Log("Numero n não é primo, abortando", LogType.ERROR, source=findSmallestPrimitive.__name__)
        exit(1)

    phi = n - 1

    s = findPrimeFactors(phi)

    for r in range(2, phi + 1):
        flag = False
        for ix in s:
            if power(r, phi // ix, n) == 1:
                flag = True
                break
        if not flag:
            return r
    return -1

# Encontra o n-esimo numero primo
def findNthPrime(n):
    primesFound = 0
    nthPrime = -1
    i = 1
    while primesFound < n:
        if i == 1 or i == 0:
            i += 1
            continue
        flag = 1

        for j in range(2, int(i / 2) + 1):
            if i % j == 0:
                flag = 0
                break
        if flag == 1:
            primesFound += 1
            nthPrime = i
        i += 1
    return nthPrime

# Gera p e g
def GeneratePubKey():
    n = random.randint(1, 2048)
    # acha o enésimo número primo
    p = findNthPrime(n)
    # acha menor raiz primitiva
    g = findSmallestPrimitive(p)
    return p, g

# Continua aguardando mensagens indefinidamente
def KeepConnectionOpen(connection, key):
    while(True):
        ReceiveEncryptedMessage(connection, key)
        SendEncryptedMessage(connection, key)

def main(args):
    if len(args) < 2:
        Log("Modo de uso: python servidor.py <port>", logType=LogType.ERROR, source=main.__name__)
        return 0
    
    useWrongKey = False
    if len(args) == 3:
        if args[2] == "-wk":
            useWrongKey = True

    port = args[1]
    Log("Iniciando servidor", source=main.__name__)
    socketConnection = InitSocket(int(port))
    Log("Servidor inicializado", source=main.__name__)
    # p e g são públicos
    # p primo, g raiz primitiva de p
    p, g = GeneratePubKey()

    # aguarda ate receber conexao
    connection, address = socketConnection.accept()
    Log("Conexão com " + str(address) + " iniciada", source=main.__name__)

    a = GenerateSecretInteger()

    # x = (g ^ a) mod p 
    x = int(pow(g, a, p))
    # usa separador pra enviar as mensages pro cliente
    separator = '-'
    connection.send(str.encode(str(p) + separator))
    Log("p enviado, " + str(p), source=main.__name__)
    connection.send(str.encode(str(g) + separator))
    Log("g enviado, " + str(g), source=main.__name__)
    connection.send(str.encode(str(x) + separator))
    Log("x enviado, " + str(x), source=main.__name__)

    Log("esperando y", source=main.__name__)
    msgy = connection.recv(1024)

    y = int(msgy.decode())
    Log("y recebido, " + str(y), source=main.__name__)

    # y ^ a mod p
    secretKey = int(pow(y, a, p))
    Log("Chave secreta calculada: " + str(secretKey), logType=LogType.SUCCESS, source=main.__name__)

    # se parametro -wr (wrong key) for utilizado, corrompe a chave
    if useWrongKey:
        secretKey = secretKey*10
        Log("Corrompendo a chave propositalmente: " + str(secretKey), logType=LogType.SUCCESS, source=main.__name__)

    # chave precisa ter 8 bytes
    key = PadKey(str(secretKey))
    KeepConnectionOpen(connection, key)


if __name__ == '__main__':
    initMessage = "Inicio da Execução: programa que implementa um servidor sobre TCP\n"
    initMessage += "Stephanie Briere Americo e Talita Halboth Cunha Fernandes\n"
    initMessage += "Disciplina de Redes II"
    Log("=============================================================================", printInfo=False)
    Log(initMessage, printInfo=False)
    Log("=============================================================================", printInfo=False)
    sys.exit(main(sys.argv))
