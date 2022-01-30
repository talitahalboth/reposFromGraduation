# -*- coding: utf-8 -*-
"""
Programa que implementa um cliente sobre TCP e se comunica usando mensagens criptografadas
As mensagens são criptografadas usando DES
A chave do DES é gerada usando o algoritmo Diffie-Hellman

Autoras: Stephanie Briere Americo e Talita Halboth Cunha Fernandes
Disciplina: Redes II
Data da última atualização: 02/08/2021
"""

import sys
import socket

from log import *
from utils import *

# Recebe p, g e x
def RetrievePublicKey(s):
    separator = '-'
    # recebe mensagem do servidor, 1024 bytes por vez
    Log("esperando p", source=RetrievePublicKey.__name__)
    msgp = s.recv(1024)
    decodedp = msgp.decode()
    Log("Mensagem recebida: " + decodedp, source=RetrievePublicKey.__name__)
    # faz checagens para lidar com casos em que 2 ou mais mensagens são combinadas em 1 só
    splitp = decodedp.split(separator)
    splitp = list(filter(None, splitp))
    p = splitp[0]
    Log("p recebido, " + str(p), source=RetrievePublicKey.__name__)
    if len(splitp) > 1:
        g = splitp[1]
        Log("g recebido, " + str(g), source=RetrievePublicKey.__name__)
        if len(splitp) > 2:
            x = splitp[2]
            Log("x recebido, " + str(x), source=RetrievePublicKey.__name__)
        else:
            Log("esperando x", source=RetrievePublicKey.__name__)
            msgx = s.recv(1024)
            decodedx = msgx.decode()
            Log("Mensagem recebida: " + decodedx, source=RetrievePublicKey.__name__)
            splitx = decodedx.split(separator)
            splitx = list(filter(None, splitx))
            x = splitx[0]
            Log("x recebido, " + str(x), source=RetrievePublicKey.__name__)
    else:
        Log("esperando g", source=RetrievePublicKey.__name__)
        msgg = s.recv(1024)
        decodedg = msgg.decode()
        Log("Mensagem recebida: " + decodedg, source=RetrievePublicKey.__name__)
        splitg = decodedg.split(separator)
        splitg = list(filter(None, splitg))
        g = splitg[0]
        Log("g recebido, " + str(g), source=RetrievePublicKey.__name__)
        if len(splitg) > 1:
            x = splitg[1]
            Log("x recebido, " + str(x), source=RetrievePublicKey.__name__)
        else:
            Log("esperando x", source=RetrievePublicKey.__name__)
            msgx = s.recv(1024)
            decodedx = msgx.decode()
            Log("Mensagem recebida: " + decodedx, source=RetrievePublicKey.__name__)
            splitx = decodedx.split(separator)
            splitx = list(filter(None, splitx))
            x = splitx[0]
            Log("x recebido, " + str(x), source=RetrievePublicKey.__name__)
    return p, g, x

# Continua aguardando mensagens indefinidamente
def KeepConnectionOpen(connection, key):
    while(1):
        SendEncryptedMessage(connection, key)
        ReceiveEncryptedMessage(connection, key)

def main(args):
    if len(args) < 3:
        Log("Modo de uso: python cliente.py <host> <port>", logType=LogType.ERROR, source=main.__name__)
        return 0
    host = args[1]
    port = args[2]
    Log("Iniciando cliente", source=main.__name__)

    # Cria um socket usando TCP / IP
    s = socket.socket(socket.AF_INET,
                      socket.SOCK_STREAM)

    # Conecta ao servidor
    Log("Conectando com servidor", source=main.__name__)
    s.connect((host, int(port)))
    Log("Conectado", source=main.__name__)

    p, g, x = RetrievePublicKey(s)
    p = int(p)
    g = int(g)
    x = int(x)
    b = int(GenerateSecretInteger())

    # y = (g ^ b) mod p 
    y = int(pow(g, b, p))

    # x ^ b mod p
    secretKey = int(pow(x, b, p))

    s.send(str.encode((str(y))))
    Log("y enviado, " + str(y), source=main.__name__)

    Log("Chave secreta calculada: " + str(secretKey), logType=LogType.SUCCESS, source=main.__name__)

    key = PadKey(str(secretKey))
    KeepConnectionOpen(s, key)

    # Desconecta o cliente
    s.close()
    return 0


if __name__ == '__main__':
    initMessage = "Inicio da Execução: programa que implementa um servidor sobre TCP\n"
    initMessage += "Stephanie Briere Americo e Talita Halboth Cunha Fernandes\n"
    initMessage += "Disciplina de Redes II"
    Log("=============================================================================", printInfo=False)
    Log(initMessage, printInfo=False)
    Log("=============================================================================", printInfo=False)
    sys.exit(main(sys.argv))
