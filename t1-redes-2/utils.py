# -*- coding: utf-8 -*-
"""
Programa que implementa um servidor sobre TCP e se comunica usando mensagens criptografadas
As mensagens são criptografadas usando DES
A chave do DES é gerada usando o algoritmo Diffie-Hellman

Autoras: Stephanie Briere Americo e Talita Halboth Cunha Fernandes
Disciplina: Redes II
Data da última atualização: 03/08/2021
"""

import random
import hashlib
from Crypto.Cipher import DES
from Crypto.Util.Padding import pad, unpad

from log import *

# Calcula x ^ y mod p de forma iterativa
def power(x, y, p):
    # inicializa resultado
    res = 1

    # atualiza x se for maior ou igual a p
    x = x % p

    while y > 0:

        # Se y é ímpar, multiplica x pelo resultado
        if y & 1:
            res = (res * x) % p

        # y é par
        y = y >> 1  # y = y/2
        x = (x * x) % p

    return res

# Gera o inteiro para a e b no calculo de x e y
def GenerateSecretInteger():
    a = random.randint(1, 2048)
    return a

# DES precisa de uma chave de 8 bytes
def PadKey(key):
    size = len(key)
    lenDiff = 8 - size
    key += "-" * lenDiff
    key = str.encode(key)
    return key

def PadMsg(msg):
    size = len(msg)
    lenDiff = (int(size/8) + 1)*8 - size
    msg += "\0" * lenDiff
    return msg

# Verifica checksum MD5
def CheckHeader(decryptedMessage):
    md5Msg = decryptedMessage[:16]
    msg = decryptedMessage[16:]
    novoMd5 = hashlib.md5(msg).digest()

    if md5Msg == novoMd5:
        Log("Checksum MD5 confere!", logType=LogType.SUCCESS, source=CheckHeader.__name__)
        return True

    Log("Checksum MD5 não confere!", logType=LogType.ERROR, source=CheckHeader.__name__)
    return False

# Adiciona checksum MD5 ao header da mensagem
def AddHeader(plainText):
    msg = hashlib.md5(plainText).digest() + plainText
    return msg

# Remove checksum MD5 do header da mensagem
def RemoveHeader(decryptedMessage):
    msg = decryptedMessage[16:]
    return msg

# Manda mensagem criptografada
def SendEncryptedMessage(s, key):
    print("Digite a mensagem a ser enviada:")
    msg = input()
    Log("Mensagem digitada pelo usuario:\n" + msg, source=SendEncryptedMessage.__name__)
    # DES so funciona com mensagens multiplas de 8
    text1 = PadMsg(msg)
    text1 = str.encode(text1)
    # Adiciona checksum
    text1 = AddHeader(text1)
    Log("Mensagem descriptografada binaria:\n" + str(text1), source=SendEncryptedMessage.__name__)

    des = DES.new(key, DES.MODE_ECB)
    encrypted_text = des.encrypt(text1)
    Log("Mensagem criptografada:\n" + str(encrypted_text), source=SendEncryptedMessage.__name__)
    s.send(encrypted_text)
    Log("Mensagem enviada", source=SendEncryptedMessage.__name__)

# Recebe mensagem criptografada
def ReceiveEncryptedMessage(connection, key):
    Log("Esperando mensagem", source=ReceiveEncryptedMessage.__name__)

    des = DES.new(key, DES.MODE_ECB)
    encryptedMsg = connection.recv(1024)
    while (not encryptedMsg):
        encryptedMsg = connection.recv(1024)

    Log("Mensagem recebida: " + str(encryptedMsg), source=ReceiveEncryptedMessage.__name__)

    msgDec = des.decrypt(encryptedMsg)
    Log("Mensagem descriptografada binaria:\n" + str(msgDec), source=ReceiveEncryptedMessage.__name__)

    if (CheckHeader(msgDec)):
        Log("Mensagem descriptografada com sucesso", logType=LogType.SUCCESS, source=ReceiveEncryptedMessage.__name__)
        decryptedMsg = RemoveHeader(msgDec).decode()
        Log("Mensagem descriptografada:\n" + decryptedMsg, logType=LogType.SUCCESS, source=ReceiveEncryptedMessage.__name__)
    else:
        Log("Erro ao descriptografar a mensagem", logType=LogType.ERROR,source=ReceiveEncryptedMessage.__name__)