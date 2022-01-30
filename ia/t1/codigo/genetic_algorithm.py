import abc
from itertools import permutations
from os import pathconf
from typing import NewType
from tsp import TSP
import random
import copy
random.seed(42)

mutationOp = 0.5
parentSelectionOp = 1
crossOverOp = 0
nextGenSelectionOp = 0


class Individual():
    def __init__(self, permutation, fitness):
        self.permutation = permutation
        self.fitness = fitness

    def __lt__(self, other):
        return self.fitness < other.fitness

    def __le__(self, other):
        return self.fitness <= other.fitness

    def __gt__(self, other):
        return self.fitness > other.fitness

    def __ge__(self, other):
        return self.fitness >= other.fitness


def random_population(problem, pop_size):
    population = []
    for _ in range(pop_size):
        permutation = problem.random_path()
        fitness = problem.evaluate(permutation)
        population.append(Individual(permutation, fitness))
    return population

'''
  _  _                    _ _        
 | \| |___ _ _ _ __  __ _| (_)______ 
 | .` / _ \ '_| '  \/ _` | | |_ / -_)
 |_|\_\___/_| |_|_|_\__,_|_|_/__\___|
                                     
'''
def normaliza_fitness(problem,population):
    # normalizes fitness to be a number between 0 and 1
    # higher fitness = cheaper path

    # invert fitness, so paths with smaller path cost have higher fitness
    # print(population)

    for individual in population:
        individual.fitness = problem.evaluate(individual.permutation)

    for individual in population:
        individual.fitness = 1.0/individual.fitness

    #normalizes fitness
    soma = 0.0
    for individual in population:
        soma += individual.fitness
    soma2 = 0.0
    for individual in population:
        individual.fitness = individual.fitness/soma
        soma2 += individual.fitness
    # print("somas:", soma, soma2)


'''
  ___                  _     ___      _        _   _          
 | _ \__ _ _ _ ___ _ _| |_  / __| ___| |___ __| |_(_)___ _ _  
 |  _/ _` | '_/ -_) ' \  _| \__ \/ -_) / -_) _|  _| / _ \ ' \ 
 |_| \__,_|_| \___|_||_\__| |___/\___|_\___\__|\__|_\___/_||_|
                                                                                           
'''

def poportionalIndividualSelection (problem, population):
    cumulativeProb = 0.0
    p = random.random()
    for individual in population:
        cumulativeProb += individual.fitness
        if (p <= cumulativeProb):
            return individual

def tournamentParentSelection(problem, population, randomIndividual = 5):
    randomIndividualsArray = []
    for _ in (0, randomIndividual):
        randomIndividualsArray.append(random.choice(population))
    while(len(randomIndividualsArray)>1):
        sakai = random.choice(randomIndividualsArray)
        ryuzo = random.choice(randomIndividualsArray)
        if (ryuzo.fitness >= sakai.fitness):
            randomIndividualsArray.remove(sakai)
        else:
            randomIndividualsArray.remove(ryuzo)
    return randomIndividualsArray[0]
        
    

    

def parentSelection(problem, population):
    if parentSelectionOp == 0:
        return (poportionalIndividualSelection(problem, population))
    elif parentSelectionOp == 1:
        return tournamentParentSelection(problem, population, int(len(population[0].permutation)/10))
'''
  __  __      _        _   _          
 |  \/  |_  _| |_ __ _| |_(_)___ _ _  
 | |\/| | || |  _/ _` |  _| / _ \ ' \ 
 |_|  |_|\_,_|\__\__,_|\__|_\___/_||_|
                                      
'''


def mutate(permutation, mutationRate):
    val = random.random()
    # elements in the permutation are randomly swaped 
    #probability of being swaped is based on mutation rate, which is a number between 0 and 1
    # for i in range(0, len(permutation)):
    while(val <= mutationRate):
        ixa = random.choice(permutation)
        ixb = random.choice(permutation)
        tmpElem = permutation[ixa]
        permutation[ixa] = permutation[ixb]
        permutation[ixb] = tmpElem
        val = random.random()
    return permutation

'''
   ___                                
  / __|_ _ ___ ______ _____ _____ _ _ 
 | (__| '_/ _ (_-<_-</ _ \ V / -_) '_|
  \___|_| \___/__/__/\___/\_/\___|_|  
                                      
'''


def onePointCrossover(parentA, parentB, problem):
    used = []
    newPermutation = []
    for _ in range(0, len(parentA.permutation)):
        used.append(0)
        newPermutation.append(None)
    for i in range(0, int(len(parentA.permutation)/2)):
        index = int(parentA.permutation[i])
        used[index]=1
        newPermutation [i] = index
    nextIndex = int(len(parentA.permutation)/2)
    for elem in parentB.permutation:
        if (used[int(elem)] == 0):
            newPermutation[nextIndex] = int(elem)
            used[int(elem)] = 1
            nextIndex += 1
    child = Individual(newPermutation, problem.evaluate(newPermutation) )
    return child

def chooseRandomParentCus(parentPerm):
    i = random.randint(0, len(parentPerm)-1)
    j = random.randint(i+1, len(parentPerm))
    return i,j

def selectCitiesNotCopied(parent, used):
    lista = []
    for i in range(len(parent.permutation)):
        if (not used[parent.permutation[i]]):
            lista.append(parent.permutation[i])
    return lista

def pmx(parentA, parentB, problem):
    permSize = len(parentA.permutation)
    indexOf = [[None]*permSize, [None]*permSize]
    for i in range(permSize):
        indexOf[0][parentA.permutation[i]]=i
        indexOf[1][parentB.permutation[i]]=i

    child1 = [None]*permSize
    child2 = [None]*permSize
    i,j = chooseRandomParentCus(parentA.permutation)
    pai = [parentA, parentB]
    filho = [child1, child2]
    lista = [[],[]]
    used = [[None]*permSize, [None]*permSize]
    for ix in range(i,j):
        child1[ix] = parentB.permutation[ix]
        used[0][child1[ix]] = 1
        child2[ix] = parentA.permutation[ix]
        used[1][child2[ix]] = 1
    for v in range(2):
        lista[v] = selectCitiesNotCopied(pai[(v+1)%2], used[v])
        for c in lista[v]:
            aux = c
            while (i <= indexOf[v][c] < j):
                c = filho[v][indexOf[v][c]]
            filho[v][indexOf[v][c]] = aux
    filho[0] = Individual(filho[0], problem.evaluate(filho[0]))
    filho[1] = Individual(filho[1], problem.evaluate(filho[1]))
    return filho

class Edge:
    def __init__(self, v1, v2, p, w):
        self.v1 = v1
        self.v2 = v2
        self.p = p
        self.w = w
        self.lock = 0
        self.used = 0

    def swapVertexes(self):
        tmp = self.v1 
        self.v1 = self.v2
        self.v2 = tmp
    def chooseRandomVertex(self):
        ori = random.randint(0,1)
        if (ori == 0):
            self.swapVertexes()
            return self.v2
        return self.v2


class Graph:
    def __init__(self, v, problem):
        self.v = v
        self.e = []
        self.w = problem.distance_matrix
        self.aAdjList = [None]*v
        self.bAdjList = [None]*v
        self.remaining = 0
        for i in range(v):
            self.aAdjList[i]=([])
            self.bAdjList[i]=([])
        self.adjlist = [self.aAdjList, self.bAdjList]

    def insertEdge(self, v1, v2, p):
        self.remaining+=1
        self.e.append(Edge(v1,v2,p, self.w[v1][v2]))
        self.adjlist[p][v1].append([v2,len(self.e)-1])
        self.adjlist[p][v2].append([v1, len(self.e)-1])

    def removeEdge(self, v1, v2, p):
        index = -1
        pos = -1
        # print(v1,v2,p)
        # print(len(self.adjlist[p][v1]))
        if(self.adjlist[p][v1][0][0] == v2):
            index = self.adjlist[p][v1][0][1]
            pos=0
        if(self.adjlist[p][v1][1][0] == v2):
            index = self.adjlist[p][v1][1][1]
            pos=1
        if (index == -1):
            print("ERROR")
        else:
            self.e[index].used = 1

    def chooseRandomEdgeA(self, p):
        ix = random.randint(0, self.v-1)
        ix*=2
        ix+=p
        while(self.e[ix].used == 1):
            ix = random.randint(0, self.v-1)
            ix*=2
            ix+=p
        self.e[ix].lock = 1
        return self.e[ix]
    def chooseRandomEdgeVertex(self, p, v):
        pos = random.randint(0,1)
        index = self.adjlist[p][v][pos][1]
        # if its locker (already use this abcycle) or was used
        # change the sibling we take
        if (self.e[index].lock or self.e[index].used):
            if (pos == 1):
                pos = 0
            else:
                pos = 1
        
        index = self.adjlist[p][v][pos][1]
        v1 = v
        v2 =  self.adjlist[p][v][pos][0]

        self.e[index].v1 = v1
        self.e[index].v2 = v2
        self.e[index].lock = 1
        edge = self.e[index]
        return edge

    def removeEdges(self, allEdges, index):
        for edge in allEdges:
            edge.lock = 0
        count = 0
        for i in range(index, len(allEdges)):
            # print (i)
            count+=1
            self.remaining-=1
            allEdges[i].used = 1

def isABCycle(path, R):
    if (len(path) == 0):
        return 0

    tmp = [0,0,0]
    visited = [tmp]*R.v
    paths = [[],[]]
    parity = 0
    count = 0
    for element in path:
        print("-----------------")
        print(element)
        print(visited[element])
        if (visited[element][0] == 1 and visited[element][1] == parity):
            return 1, visited[element][2]
        visited[element]=[1,parity,count]
        count+=1
        if (parity == 0):
            parity = 1
        else:
            parity = 0
    return 0, 0

def ABCycles(R,problem):
    abCyclesArray = []
    # repeats until R has no more edges
    while(R.remaining>0):
        abCycleVertexes = []
        abCycle = []


        parent = 0
        # choose random edge
        edge = R.chooseRandomEdgeA(parent)
        # choose random vertex as origin
        vertex = edge.chooseRandomVertex()
        abCycle.append(edge)
        abCycleVertexes.append(edge.v1)
        abCycleVertexes.append(edge.v2)
        if (parent == 1):
            parent = 0
        else:
            parent = 1
        isCycle,i = isABCycle(abCycleVertexes, R)
        while (not isCycle):
            # choose edge from vertex to another v in parente p
            newEdge = R.chooseRandomEdgeVertex(parent, vertex)
            abCycle.append(newEdge)
            if (newEdge != 0):
                abCycleVertexes.append(newEdge.v2)
                vertex = newEdge.v2
            if (parent == 1):
                parent = 0
            else:
                parent = 1
            isCycle,i= isABCycle(abCycleVertexes, R)
        abCyclesArray.append(abCycle[i:])
        R.removeEdges(abCycle, i)
    return abCyclesArray

def generateESet(array):
    d = []
    for element in array:
        p = random.random()
        if (p < 0.5):
            d.append(element)
    return d

class DSU:
    def __init__(self, size, edges):
        self.size = size
        self.p = []
        self.edges = []
        for i in range(size):
            self.p.append(i)
            self.edges.append([edges[i][0],edges[i][0]])
    def findSet(self, i):
        # print(i, len(self.p), self.size)
        if (self.p[i] == i):
            return i
        self.p[i] = self.findSet(self.p[i])
        return self.p[i]
    def isSameSet(self, i, j):
        return self.findSet(i) == self.findSet(j)
    def unionSet(self, i, j, edge):
        if (not self.isSameSet(i,j)):
            originalSet = self.findSet(i)
            self.p[self.findSet(i)] = self.findSet(j)
            # self.size-=1
            for edge in self.edges[originalSet]:
                self.edges[self.findSet(i)].append(edge)

def splitTours(tourArray):
    dsu = DSU(len(tourArray), tourArray)
    for edge in tourArray:
        dsu.unionSet(edge[0], edge[1], edge)
        # print(edge)
        pass
    pass
    position = [None]*len(tourArray)
    cont = 0
    for i in range(dsu.size):
        if (position[dsu.findSet(i)] == None):
            position[dsu.findSet(i)] = cont
            cont+=1
    ret = []
    for i in range(cont):
        ret.append([])
    for edge in tourArray:
        ret[position[dsu.findSet(edge[0])]].append(edge)
    return ret

def cut( e1, e2, problem):
    c1 = problem.distance_matrix[e1[0]][e1[1]]
    c2 = problem.distance_matrix[e2[0]][e2[1]]
    return c1+c2
    
def link(e1,e2,problem):

    c1 = problem.distance_matrix[e1[0]][e2[0]]
    c2 = problem.distance_matrix[e1[1]][e2[1]]
    
    c3 = problem.distance_matrix[e1[0]][e2[1]]
    c4 = problem.distance_matrix[e1[1]][e2[0]]

    return min((c1+c2), (c3+c4))

def exchangeLinks(e1, e2, problem):
    a = e1[0]
    b = e1[1]
    c = e2[0]
    d = e2[1]
    if ((a == c and b == d) or (a==d and b==c)):
        return (e1,e2)

    c1 = problem.distance_matrix[a][c]
    c2 = problem.distance_matrix[b][d]
    
    c3 = problem.distance_matrix[a][d]
    c4 = problem.distance_matrix[b][c]

    if (c1+c2 < c3 + c4):
        e1 = [a,c]
        e2 = [b,d]
    else:
        e1 = [a,d]
        e2 = [b,c]
    return (e1,e2)

def localSearchEax(ciclos, problem):
    k = len(ciclos)
    s = k
    u = []
    for i in range(k):
        u.append(ciclos[i])
    u = sorted( u, key=len )
    print("-------------")
    print("original")
    for elem in u:
        print (elem)
    print("-------------")
    while(s>1):
        iStar = 0
        minLen = 1000
        for i in range(s):
            if (len(u[i])<minLen and len(u[i]) > 0):
                minLen = len(u[i])
                iStar = i
        menor = 10000
        minq = 0
        minr = [0,0]
        edge = 0
        edgeb = 0
        # print(u[iStar][0])
        for i0 in range(len(u[iStar])):
            egde = u[iStar][i0]
            for i in range(s):
                if (i != iStar):
                    for i2 in range(len(u[i])):
                        if (len(u[i])> 0):
                            # u[i][i2] = u[i][i2]
                            corte = cut(u[iStar][i0], u[i][i2], problem)
                            linka = link(u[iStar][i0], u[i][i2], problem)
                            if ((linka - corte) < menor):
                                menor = (linka - corte)
                                minq = i0
                                minr = [i, i2]

        jStar = minr[0]
        print ("j* :",jStar)
        print(u[jStar])
        print (minq, minr)
        print("all tours:", len(u))
        for elem in u:
            print(len(elem))
            if (len(elem) > 15):
                print("-----------------------------------")
                print(elem)
                print("-----------------------------------")
        print("antes: ",u[iStar][minq], u[minr[0]][minr[1]])
        newA, newB = exchangeLinks(u[iStar][minq], u[minr[0]][minr[1]])
        u[iStar].pop(minq)
        u[jStar].pop(minr[1])
        for elem in u[jStar]:
            u[iStar].append(elem)

        u[iStar].append(newA)
        u[iStar].append(newB)
        u[jStar] = u[s-1]

        s-=1
    return u[0]

def eax(a, b, problem):
    R = Graph(len(a.permutation), problem)

    A = Graph(len(a.permutation), problem)
    B = Graph(len(a.permutation), problem)
    child = Graph(len(a.permutation), problem)

    for i in range (R.v):
        i2 = (i+1) % R.v
        # edges in position even are from a, in position odd are from b
        R.insertEdge(a.permutation[i], a.permutation[i2], 0)
        R.insertEdge(b.permutation[i], b.permutation[i2], 1)
        
        A.insertEdge(a.permutation[i], a.permutation[i2], 0)
        child.insertEdge(a.permutation[i], a.permutation[i2], 0)
        B.insertEdge(a.permutation[i], a.permutation[i2], 0)
    abCyclesArray = ABCycles(R, problem)

    eSet = generateESet(abCyclesArray)
    removed = 0
    added = 0
    print("subtours ____________________ini")
    for subtour in eSet:
        par = 0
        for edge in subtour:
            print(edge.v1, '->',edge.v2)
            par = edge.p
            if (par == 0):
                removed+=1
                child.removeEdge(edge.v1, edge.v2, edge.p)
                par = 1
            else:
                added+=1
                child.insertEdge(edge.v1, edge.v2, edge.p)
                par = 0
    print("subtours ____________________end")
    finalEdgesArray = []
    print("removed: ",removed,"added: ", added)
    for edge in child.e:
        if (not edge.used):
            finalEdgesArray.append([edge.v1, edge.v2])
    allTours = splitTours(finalEdgesArray)
    # print(len(allTours))
    childEdges = localSearchEax(allTours, problem)
    # permutationArray = [None]*len(a.permutation)
    permutationArray = []
    for i in range(len(a.permutation)):
        permutationArray.append([])
    for edge in childEdges:
        v1 = edge[0]
        v2 = edge[1]
        permutationArray[v1].append(v2)
        permutationArray[v2].append(v1) 
    permutation = []
    nxt = 0
    cur = -1
    while(len(permutation) < len(a.permutation)):
        permutation.append(nxt)
        tmp = nxt
        if (permutationArray[nxt][0] != cur):
            nxt = permutationArray[nxt][0]
            cur = tmp
        else:
            nxt = permutationArray[nxt][1]
            cur = tmp


    # print(permutation)
    child = Individual(permutation, problem.evaluate(permutation)) 
    return child
    




def crossover(parentA, parentB, problem):
    
    if crossOverOp == 0:
        eax(parentA,parentB, problem)
        # print(parentA)
        # print(parentB)
        return pmx(parentA, parentB, problem)

    elif crossOverOp == 1:
        kids = [[],[]]
        kids[0] = onePointCrossover(parentA, parentB, problem)
        kids[1] = onePointCrossover(parentA, parentB, problem)
        return kids
    elif crossOverOp == 2:
        kids = [[],[]]
        kids[0] = eax(parentA,parentB, problem)
        # kids[1] = eax(parentA,parentB, problem)
        kids[1] = kids[0]
        # kids[1] = eax(parentA,parentB, problem)
        return kids


'''
  _  _         _      ___            ___      _        _   _          
 | \| |_____ _| |_   / __|___ _ _   / __| ___| |___ __| |_(_)___ _ _  
 | .` / -_) \ /  _| | (_ / -_) ' \  \__ \/ -_) / -_) _|  _| / _ \ ' \ 
 |_|\_\___/_\_\\__|  \___\___|_||_| |___/\___|_\___\__|\__|_\___/_||_|
                                                                      
'''

def selectionBaseOnAptitude(problem, populationA, populationB, populationSize):
    # rate parent and children population based on fitness, 
    populationTmp = []
    for individual in populationA:
        individual.fitness = problem.evaluate(individual.permutation)
        populationTmp.append(individual)
    for individual in populationB:
        individual.fitness = problem.evaluate(individual.permutation)
        populationTmp.append(individual)
    populationTmp.sort()
    newPopulation = []
    for i in range (0, populationSize):
        newPopulation.append(populationTmp[i])
    normaliza_fitness(problem,newPopulation)
    return newPopulation
    
def uniformSelection(problem, populationA, populationB, populationSize):
    newPopulation  = []
    tmpPopulation = []
    # print("-------------------")
    for individual in populationA:
        # print(individual.permutation)
        newInd = copy.deepcopy(individual)
        newInd.fitness = problem.evaluate(individual.permutation)
        tmpPopulation.append(newInd)
        
    for individual in populationB:
        # print(individual.permutation)
        newInd = copy.deepcopy(individual)
        newInd.fitness = problem.evaluate(individual.permutation)
        tmpPopulation.append(newInd)
    # print("-------------------")

    normaliza_fitness(problem,tmpPopulation)
    for _ in range(0, populationSize):
        newIndividual = poportionalIndividualSelection(problem, tmpPopulation)
        # print(newIndividual)
        newPopulation.append(newIndividual)
    # print("-------------------")
    return newPopulation



def nextGenSelection(problem, populationA, populationB, populationSize):
    if (nextGenSelectionOp == 0):
        return selectionBaseOnAptitude(problem, populationA, populationB, populationSize)
    elif (nextGenSelectionOp == 1):
        return populationB[0:populationSize]
    elif (nextGenSelectionOp == 2):
        return uniformSelection(problem, populationA, populationB, populationSize)


'''
  _  _               ___                       _   _           
 | \| |_____ __ __  / __|___ _ _  ___ _ _ __ _| |_(_)___ _ __  
 | .` / -_) V  V / | (_ / -_) ' \/ -_) '_/ _` |  _| / _ \ '  \ 
 |_|\_\___|\_/\_/   \___\___|_||_\___|_| \__,_|\__|_\___/_|_|_|
                                                               
'''

def new_generation(problem, population):

    children = []
    for _ in range(0, len(population)):
        parentA = parentSelection(problem, population)
        parentB = parentSelection(problem, population)
        # crossover function generates 2 kids
        [newIndividual,newIndividual1] = crossover(parentA, parentB, problem)
        # print(newIndividual1.permutation)
        newIndividual.permutation = mutate(newIndividual.permutation, mutationOp)
        children.append(newIndividual)
        newIndividual1.permutation = mutate(newIndividual1.permutation, mutationOp)
        children.append(newIndividual1)

    newGen = nextGenSelection(problem, population, children, len(population))
    # print(len(newGen))
    return newGen

def genetic_algorithm(problem, pop_size=50, max_gen=2000, mutationOper=0.5, parentSelectionOper=1, crossOverOper=0, nextGenSelectionOper=0):

    global mutationOp 
    global parentSelectionOp 
    global crossOverOp 
    global nextGenSelectionOp 

    mutationOp=mutationOper
    parentSelectionOp=parentSelectionOper
    crossOverOp=crossOverOper
    nextGenSelectionOp=nextGenSelectionOper
    population = random_population(problem, pop_size)
    print(mutationOp, parentSelectionOp, crossOverOp, nextGenSelectionOp)
    fitness_history = []
    best_permutation = None
    #SUA IMPLEMENTACAO AQUI

    # starts by normalizing the fitness of the population, so its a probability between [0,1]
    normaliza_fitness(problem,population)

    bestFitness = problem.evaluate(population[0].permutation) 
    best_permutation = population[0].permutation
    fitness_history.append(bestFitness)
    # finds the best fitness of the initial population
    for individual in population:
        if (problem.evaluate(individual.permutation) <= bestFitness):
            bestFitness = problem.evaluate(individual.permutation)
            best_permutation = individual.permutation
            


    generations = 1
    while (generations < max_gen):
        generations+=1
        newGen = new_generation(problem, population)
        normaliza_fitness(problem,newGen)
        population = newGen
        for individual in population:
            if (problem.evaluate(individual.permutation) <= bestFitness):
                bestFitness = problem.evaluate(individual.permutation)
                best_permutation = individual.permutation
        
        fitness_history.append(bestFitness)

    return best_permutation, fitness_history


if __name__ == "__main__":
    problem = TSP('instances/berlin15.tsp')
    # crossOverOp = 2
    best_solution, fitness_history = genetic_algorithm(problem, 50, 20)
    print(best_solution, problem.evaluate(best_solution))
