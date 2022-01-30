# from codigo.genetic_algorithm import crossover
from itertools import repeat
from numpy.lib.function_base import append
from tsp import TSP
from a_star import a_star
from genetic_algorithm import genetic_algorithm
import time
import matplotlib.pyplot as plt
from math import log
import statistics 

plt.style.use('ggplot')
pop = 50
gen = 2000
class Result():
    def __init__(self, average, time, parameters):
        self.averageArray = []
        self.instanceName = []
        self.diffArray = []
        self.average = average
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
        self.averageArray.append(value)
        self.averageFit()
        self.timeArray.append(time)
        self.averageTime()

    def insertDiff(self, value):
        self.diffArray.append(value)

    def __lt__(self, other):
        return self.average < other.average

    def __le__(self, other):
        return self.average <= other.average

    def __gt__(self, other):
        return self.average > other.average

    def __ge__(self, other):
        return self.average >= other.average
results = []

def plot_evolution(results):

    plt.figure()
    cont = 0
    # for i in range(len(results)):
    #     x = results[i].instanceName 
    #     y = results[i].diffArray
    #     plt.plot(x, y, color='grey', linewidth=.5, alpha=0.4)
    #     cont += 1
    
    # for i in range(len(results)-10, len(results)):
    #     x = results[i].instanceName 
    #     y = results[i].diffArray
    #     plt.plot(x, y, color='brown', linewidth=.5, alpha=0.4)
    #     cont += 1
    colors = ["red", "orange", "yellow","green","blue"]
    for i in reversed(range(5)):
        x = results[i].instanceName 
        y = results[i].diffArray
        width = 4/(i+1)
        # alpha = 7/(i/2)
        plt.plot(x,y,  label = str(results[i].parameters), color=colors[i], linewidth=1, alpha=0.7)

    plt.xlabel('Instancia')
    plt.ylabel('Diferença de Custo')
    plt.yscale('log')
    plt.title('Comparacao Algo Genetico, pop = '+str(pop)+', gerações = ' + str(gen))
    plt.legend()
    # plt.show()

    outfile = 'pop = ' + str(pop)+', gerações = ' + str(gen) + '.pdf'
    plt.savefig(outfile, dpi=300, bbox_inches='tight')


def ga_tests(mutationOp, parentSelectionOp, crossOverOp, nextGenSelectionOp):
    # instances = ['instances/berlin10.tsp', 'instances/berlin15.tsp']
    instances = ['instances/berlin10.tsp', 'instances/berlin15.tsp', 'instances/berlin16.tsp']
    instances += ['instances/dj38.tsp', 'instances/berlin52.tsp', 'instances/eli51.tsp']
    print('Executando Algoritmo Genético...')
    results.append(Result(0, 0, [mutationOp,parentSelectionOp,crossOverOp,nextGenSelectionOp]))
    print(results[-1].parameters)
    for instance in instances:
        problem = TSP(instance)
        historiy_list = []
        mean_time = 0
        mean_cost = 0
        results[-1].addInstanceName(instance)
        print(problem)
        repeat = 10
        costs = []
        for i in range(repeat):
            start_time = time.time()
            path, history = genetic_algorithm(problem, mutationRate=mutationOp)
            mean_time += time.time() - start_time
            cost = problem.evaluate(path)
            mean_cost += cost
            costs.append(cost)
            print('Custo do caminho:', cost)
            historiy_list.append(history)
        mean_history = [sum(x) for x in zip(*historiy_list)]
        print('Custo medio:', mean_cost/repeat)
        print('Desvio padrao:', statistics.stdev(costs))
        print('Tempo medio:', str(mean_time/repeat), 'segundos')
        results[-1].addAverage(mean_cost/repeat, mean_time/repeat)

# a_star_tests()
pop = 50
gen = 2000
mutations = [0.0, 0.01, 0.1, 0.2, 0.5]
# for mutation in mutations:
ga_tests(0.01,1,2,0)
    # 0: proportional selection
    # 1: tournament selection
    # for parentSelection in range(2):
    #     # cut in half, permutation order
    #     for crossover in range(3):
    #         # 0: elitism selection
    #         # 1: simple selection
    #         # 2: proportional selection (uniform)
    #         for nextGen in range(3):

results.sort()  
optimalCost = [4889, 4967,5027 ,6656,7542,426]
for result in results:
    print (result.average)
    print(result.averageArray)
    print(result.time)
    print(result.timeArray)
    print(result.parameters)
    for i in range(len(result.averageArray)):
        value = result.averageArray[i]
        optimal = optimalCost[i]
        dif = value - optimal
        result.insertDiff((dif/optimal)*100)
    print(result.diffArray)
        
        

# plot_evolution(results)
