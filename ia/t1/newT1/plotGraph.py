
import matplotlib.pyplot as plt
from math import log
from math import trunc
from functools import cmp_to_key


plt.style.use('ggplot')
class Result():
    def __init__(self, average, time, parameters):
        self.averageArray = []
        self.instanceName = []
        self.diffArray = []
        self.average = average
        self.avgDiff = 0
        self.timeArray = []
        self.time = time
        self.parameters = parameters

    def averageFit(self):
        sum=0
        count=0
        for value in self.averageArray:
            sum+=value
            count+=1
        self.average = sum/count
        
    def averageDiff(self):
        sum=0
        count=0
        for value in self.diffArray:
            sum+=value
            count+=1
        self.avgDiff = sum/count

    def averageTime(self):
        sum=0.0
        count=0
        for value in self.timeArray:
            sum+=value
            count+=1
        self.time = sum/count

    def addInstanceName (self, name):
        self.instanceName.append(name)

    def addAverage(self, value, time):
        value = float (value)
        self.averageArray.append(value)
        self.averageFit()
        # self.timeArray.append(time)
        # self.averageTime()
    def addTime(self, time):
        self.timeArray.append(time)
        self.averageTime()

    def insertDiff(self, value):
        self.diffArray.append(value)

    def __lt__(self, other):
        return self.avgDiff < other.avgDiff

    def __le__(self, other):
        return self.avgDiff <= other.avgDiff

    def __gt__(self, other):
        return self.avgDiff > other.avgDiff

    def __ge__(self, other):
        return self.avgDiff >= other.avgDiff



results = []

instances = ['berlin10.tsp', 'berlin15.tsp', 'berlin16.tsp']
instances += ['dj38.tsp', 'berlin52.tsp', 'eli51.tsp']
    

def plot_evolution(results):
    cont = 0
    plt.rcParams.update({'font.size': 10})
    # for i in reversed(range(5,len(results))):
    #     x = instances
    #     y = results[i].diffArray
    #     plt.plot(x, y, label = str(results[i].parameters)+", "+str((results[i].avgDiff)),  linewidth=1, alpha=0.4)
    #     if (cont%2 == 0):
    #         plt.text(x[-1], y[-1], str(results[i].parameters))
    #     else:
    #         plt.text(x[-1], y[-1], str(results[i].parameters))
    #     cont += 1
    props = dict(boxstyle='round', facecolor='white', alpha=1)

    text = "Parent Selection:\n0 - Proportional Selection\n1 - Tournament Selection\n\n"
    text+="Crossover\n0 - Copy First Half\n1 - PMX\n2 - EAX\n\n"
    text+= "Next Gen Selection\n0 - Aptitude Based\n1 - First N\n2 - Proportional Selection"
    # plt.text(0.5,100, text)
    # plt.text(0.5,250, text, fontsize=14,verticalalignment='top', bbox=props)
    # for i in range(len(results)-10, len(results)):
    #     x = instances
    #     y = results[i].diffArray
    #     plt.plot(x, y, color='brown', linewidth=.5, alpha=0.4)
    width = 1
    colors = ["red", "orange", "yellow","green","blue"]
    for i in (range(1)):
        x = instances
        # alpha = 7/(i/2)
        y = results[i].diffArray
        plt.plot(x,y,  label = str(results[i].parameters)+", "+str((results[i].time)), color=colors[i], linewidth=width, alpha=0.7)
        for j in range(len(x)):
            plt.text(x[j], y[j], str(trunc(y[j]*1000)/1000))
        # y = results[i].timeArray
        # plt.plot(x,y,  label = str(results[i].parameters)+", "+str((results[i].avgDiff)), color=colors[i], linewidth=width, alpha=0.7)
        # if (width%2 == 0):
        #     plt.text(x[-1], y[-1], str(results[i].parameters))
        # else:
        #     plt.text(x[-1], y[-1], str(results[i].parameters))
        # plt.text(0.08, 0.2, 'sin')
        width +=1
    # plt.xticks(rotation=90, ha='right')

    plt.xlabel('Instância')
    plt.ylabel('Diferença de Custo em % para ótimo')
    # plt.ylabel('Diferença de Custo em % para ótimo')

    # plt.yscale('log')
    plt.title('Comparação entre Instâncias')
    # plt.suptitle('Parametros: Parent Selection, Crossover, Next Gen Selection')
    # plt.legend()
    plt.show()


optimalCost = [4889, 4967,5027 ,6656,7542,426]


with open('tmp') as openfileobject:
    count = 0
    parameters = []
    costs = []
    times = []
    diferences = []
    time = 0
    for line in openfileobject:
        if (count %6 == 0):
            _ = 0
        elif (count%6 == 1):
            line = line[1:-2]
            lista = line.split(',')
            for elem in lista:
                elem = float(elem)
            costs =  list(map(float, lista))
        elif (count%6 == 2):
            time = float(line)
        elif (count%6 == 3):
            line = line[1:-2]
            lista = line.split(',')
            for elem in lista:
                elem = float(elem)
            times =  list(map(float, lista))
        elif (count%6 == 4):
            line = line[1:-2]
            lista = line.split(',')
            lista = lista [0]
            parameters = lista
        else:
            results.append(Result(0,0,parameters))
            
            for cost in costs:
                   results[-1].addAverage(cost, 1)
            for time in times:
                   results[-1].addTime(time)
            line = line[1:-2]
            lista = line.split(',')
            for elem in lista:
                elem = float(elem)
                results[-1].insertDiff(float(elem))
            results[-1].averageDiff()
            # results[-1].addTime(time)
        count+=1    

instance = 5
# parameters
def compareByInstance(item1, item2):
    if item1.averageArray[instance] < item2.averageArray[instance]:
        return -1
    elif item1.averageArray[instance] > item2.averageArray[instance]:
        return 1
    else:
        return 0
param = 2
def compareByParameters(item1, item2):
    if item1.parameters[param] < item2.parameters[param]:
        return -1
    elif item1.parameters[param] > item2.parameters[param]:
        return 1
    else:
        return 0


def compareByTime(item1, item2):
    if item1.time < item2.time:
        return -1
    elif item1.time > item2.time:
        return 1
    else:
        return 0
results.sort()
# results = sorted(results, key=cmp_to_key(compareByTime))
param = 2 
mult = 3
# print ("par cros nxt")
# resultsByParam = [None]*mult
# for i in range(mult):
#     resultsByParam[i] = []
# for res in results:
#     index = int(res.parameters[param])
#     resultsByParam[index].append(res)

# averages = [None]*mult

# for resArray in resultsByParam:
#     soma = 0
#     count = 0
#     for val in resArray:
#         print(val.parameters)
#         soma+=val.avgDiff
#         count+=1
#     print(soma/count)


# results.sort(key=compareByInstance)

for result in results:
    print("-------------------")
    print("param     ", result.parameters)
    print("dif       ",result.avgDiff)
    print("dif array ",result.diffArray)
    print("average   ",result.average)
    print("avg array ",result.averageArray)
    print("time      ",result.time)
    print("time      ",result.timeArray)
    print("-------------------")
plot_evolution(results)