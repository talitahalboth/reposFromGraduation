from matplotlib.pyplot import tight_layout


results = []
with open('sorted2') as openfileobject:
    for line in openfileobject:
        obj = line[1:-2].split(',')
        obj[0] = float(obj[0])
        obj[1] = obj[1][2:-1]
        obj[2] = obj[2][2:-1]
        results.append(obj)
        # print(line[1:-2])

    print("\\hline")
    titulo = "Acurácia & Activation & Solver\\\\"

    print("\t", titulo)
    print("\\hline")
    for result in results:
        print ("\t",result[0],"&",result[1],"&",result[2],"\\\\",)
    print("\\hline")
    
results.sort()

results.reverse()

results2 = []
with open('sorted') as openfileobject:
    for line in openfileobject:
        obj = line[1:-2].split(',')
        obj[0] = float(obj[0])
        for i in range(1, len(obj)):
            obj[i] = int(obj[i])
        pass
        results2.append(obj)
    print("\\hline")
    titulo = "Acurácia & 1a camada & 2a camada & 3 camada & 4a camada\\\\"

    print("\t", titulo)
    print("\\hline")
    for result in results2[-5:]:
        print ("\t",result[0],"&",result[1],"&",result[2],"&",result[3],"&",result[4],"\\\\",)
    print("\\hline")
        # for i in range(0,len(result)):
        #     print(result[i])
        #     pass
