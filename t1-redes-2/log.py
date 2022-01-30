# -*- coding: utf-8 -*-
"""
Programa que implementa um servidor sobre TCP e se comunica usando mensagens criptografadas
As mensagens são criptografadas usando DES
A chave do DES é gerada usando o algoritmo Diffie-Hellman

Autoras: Stephanie Briere Americo e Talita Halboth Cunha Fernandes
Disciplina: Redes II
Data da última atualização: 03/08/2021
"""

from enum import Enum

class LogType(Enum):
    INFO = 0
    ERROR = 1
    SUCCESS = 2
    WARNING = 3

class LogColour:
    INFO = '\033[95m'
    SUCCESS = '\033[92m'
    FAIL = '\033[91m'
    WARNING = '\033[93m'
    ENDC = '\033[0m'

def Log(message, logType=LogType.INFO, source=None, printInfo=True):
    if printInfo:
        print("----------------------")
        if logType == LogType.INFO:
            print(f"{LogColour.INFO}Log type: Info{LogColour.ENDC}")
            print("Source:", source)
            print("Mensagem:", message)
        elif logType == LogType.SUCCESS:
            print(f"{LogColour.SUCCESS}Log type: Success{LogColour.ENDC}")
            print("Source:", source)
            print("Mensagem:", message)
        elif logType == LogType.ERROR:
            print(f"{LogColour.FAIL}Log type: Error{LogColour.ENDC}")
            print("Source:", source)
            print("Mensagem:", message)
        elif logType == LogType.WARNING:
            print(f"{LogColour.WARNING}Log type: Warning{LogColour.ENDC}")
            print("Source:", source)
            print("Mensagem:", message)
        print("----------------------")
    else:
        print(message)