def getSize(fileobject):
    fileobject.seek(0,2) # move the cursor to the end of the file
    size = fileobject.tell()
    return size

def geraSaida (data):
    with open("waveHeader.bin","r+b") as header:
        bytes = bytearray(header.read())

    #data = open("saida", "rb")    
    #size = getSize(data)
    #with open("saida", "r+b") as data:
    #    encrypted = bytearray(data.read())

    size = len(data)

    sz=size+36 #size eh o tam. do arquivo criptografado
    #tentei fazer um "for" e deu ruim, fica faltando pedaco
    sz1=chr(sz%256)
    sz=sz/256
    sz2=chr(sz%256)
    sz=sz/256
    sz3=chr(sz%256)
    sz=sz/256
    sz4=chr(sz%256)

    file=open("saida.wav", "w+b")

    file.write("RIFF")
    file.write(sz1)
    file.write(sz2)
    file.write(sz3)
    file.write(sz4)
    file.write("WAVE")
    file.write(bytes)
    file.write("data")

    out=''.join(data)
    file.write(out)

    file.close
    header.close
    
