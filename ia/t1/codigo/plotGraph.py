
import matplotlib.pyplot as plt
from math import log
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

instances = ['instances/berlin10.tsp', 'instances/berlin15.tsp', 'instances/berlin16.tsp']
instances += ['instances/dj38.tsp', 'instances/berlin52.tsp', 'instances/eli51.tsp']
    

def plot_evolution(results):
    cont = 0
    for i in range(10):
        x = instances
        y = results[i].diffArray
        plt.plot(x, y, color='grey', linewidth=.5, alpha=0.4)
        cont += 1

    
    for i in range(len(results)-10, len(results)):
        x = instances
        y = results[i].diffArray
        plt.plot(x, y, color='brown', linewidth=.5, alpha=0.4)

    colors = ["red", "orange", "yellow","green","blue"]
    for i in reversed(range(5)):
        x = instances
        y = results[i].diffArray
        width = 4/(i+1)
        # alpha = 7/(i/2)
        plt.plot(x,y,  label = str(results[i].parameters), color=colors[i], linewidth=1, alpha=0.7)

    plt.xlabel('Instancia')
    plt.ylabel('Diferença de Custo')
    # plt.yscale('log')
    plt.title('Teste')
    plt.legend()
    plt.show()


optimalCost = [4889, 4967,5027 ,6656,7542,426]


with open('res') as openfileobject:
    count = 0
    parameters = []
    costs = []
    diferences = []
    for line in openfileobject:
        if (count %5 == 0):
            _ = 0
        elif (count%5 == 1):
            line = line[1:-2]
            lista = line.split(',')
            for elem in lista:
                elem = float(elem)
            costs =  list(map(float, lista))
        elif (count%5 == 2):
            _ = 0
        elif (count%5 == 3):
            line = line[1:-2]
            lista = line.split(',')
            parameters = list(map(float, lista))
        else:
            results.append(Result(0,0,parameters))
            
            for cost in costs:
                   results[-1].addAverage(cost, 1)
            line = line[1:-2]
            lista = line.split(',')
            for elem in lista:
                elem = float(elem)
                results[-1].insertDiff(float(elem))
            results[-1].averageDiff()
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
param = 3
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
# results.sort()
results = sorted(results, key=cmp_to_key(compareByTime))
resultsByParam = [None]*3
for i in range(3):
    resultsByParam[i] = []
for res in results:
    index = int(res.parameters[param])
    resultsByParam[index].append(res)

averages = [None]*3

for resArray in resultsByParam:
    soma = 0
    count = 0
    for val in resArray:
        soma+=val.average
        count+=1
    # print(soma/count)


# results.sort(key=compareByInstance)

for result in results:
    print("-------------------")
    print(result.parameters)
    print(result.avgDiff)
    print(result.diffArray)
    print (result.average)
    print(result.averageArray)
    print("-------------------")
plot_evolution(results)