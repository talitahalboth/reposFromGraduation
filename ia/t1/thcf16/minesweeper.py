import random
import sys
from os import system, name 
from time import sleep 


def atacaVizinhos(x, y, pontos, att, h, w):
    if pontos[x][y] == 0:
        if (y > 0):
            if (att[x][y - 1] == 0):
                att[x][y - 1] = 1
                atacaVizinhos(x, y - 1, pontos, att, h, w)
        if (y < h - 1):
            if (att[x][y + 1] == 0):
                att[x][y + 1] = 1
                atacaVizinhos(x, y + 1, pontos, att, h, w)
        if (x > 0):
            if (att[x - 1][y] == 0):
                att[x - 1][y] = 1
                atacaVizinhos(x - 1, y, pontos, att, h, w)
            if (y > 0):
                if (att[x - 1][y - 1] == 0):
                    att[x - 1][y - 1] = 1
                    atacaVizinhos(x - 1, y - 1, pontos, att, h, w)
            if (y < h - 1):
                if (att[x - 1][y + 1] == 0):
                    att[x - 1][y + 1] = 1
                    atacaVizinhos(x - 1, y + 1, pontos, att, h, w)
        if (x < w - 1):
            if (att[x + 1][y] == 0):
                att[x + 1][y] = 1
                atacaVizinhos(x + 1, y, pontos, att, h, w)
            if (y > 0):
                if (att[x + 1][y - 1] == 0):
                    att[x + 1][y - 1] = 1
                    atacaVizinhos(x + 1, y - 1, pontos, att, h, w)
            if (y < h - 1):
                if (att[x + 1][y + 1] == 0):
                    att[x + 1][y + 1] = 1
                    atacaVizinhos(x + 1, y + 1, pontos, att, h, w)


# inicializa
bomb = 5
w, h = 6, 6
print ("How to Play: \nChoose the mode \n0 - attack \n1 - place flag")
print("THen, choose the coordinates x and y (from 0 to "+str(h)+")")
print ("x y ->\n|\nv")
bombas = [[0 for x in range(w)] for y in range(h)]
pontos = [[0 for x in range(w)] for y in range(h)]
att = [[0 for x in range(w)] for y in range(h)]

# cria bombas
for x in range(0, w):
    for y in range(0, h):
        bombas[x][y] = 0
count = 0
while (count != bomb):
    x = random.randrange(w)
    y = random.randrange(h)
    if (bombas[x][y] == 0):
        bombas[x][y] = 1
        count = count + 1

# calcula pontos
for x in range(0, w):
    for y in range(0, h):
        if (bombas[x][y] == 1):
            if (y > 0):
                pontos[x][y - 1] = pontos[x][y - 1] + 1
            if (y < h - 1):
                pontos[x][y + 1] = pontos[x][y + 1] + 1
            if (x > 0):
                pontos[x - 1][y] = pontos[x - 1][y] + 1
                if (y > 0):
                    pontos[x - 1][y - 1] = pontos[x - 1][y - 1] + 1
                if (y < h - 1):
                    pontos[x - 1][y + 1] = pontos[x - 1][y + 1] + 1
            if (x < w - 1):
                pontos[x + 1][y] = pontos[x + 1][y] + 1
                if (y > 0):
                    pontos[x + 1][y - 1] = pontos[x + 1][y - 1] + 1
                if (y < h - 1):
                    pontos[x + 1][y + 1] = pontos[x + 1][y + 1] + 1


# roda jogo
vivo = 1
while (vivo == 1):
    system('cls')
    for x in range(0, w):
        for y in range(0, h):
            if (att[x][y] == 1):
                sys.stdout.write(str(pontos[x][y]))
            elif (att[x][y] == 2):
                sys.stdout.write('F')
            else:
                sys.stdout.write(u"\u25A1")
            sys.stdout.write(' ')
        sys.stdout.write('\n')
    mode = int(input('mode '))
    x = int(input('x '))
    y = int(input('y '))
    if (mode == 0 and att[x][y] != 2):
        att[x][y] = 1
        if (pontos[x][y] == 0):
            atacaVizinhos(x, y, pontos, att, h, w)
        if (bombas[x][y] == 1):
            vivo = 0
        else:
            count = 0
            for x in range(0, w):
                for y in range(0, h):
                    if (att[x][y] == 1):
                        count = count + 1
            if (count == w * h - bomb):
                vivo = 2
    elif (mode == 1):
        if (att[x][y] == 2):
            att[x][y] = 0
        elif(att[x][y] == 0):
            att[x][y] = 2

system('cls')
for x in range(0, w):
    for y in range(0, h):
        if (bombas[x][y] == 1):
            if (att[x][y] == 1):
                sys.stdout.write(u"\u203B")
            else:
                sys.stdout.write(u"\u2585")
        else:
            sys.stdout.write(str(pontos[x][y]))
        sys.stdout.write(' ')
    sys.stdout.write('\n')
sys.stdout.write('\n')
if (vivo == 0):
    print ("GAME OVER")
else:
    print ("YOU WON")





