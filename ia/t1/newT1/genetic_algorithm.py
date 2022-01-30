import abc

import numpy as np
from tsp import TSP
import random
random.seed(42)

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

def normalizeFitness(problem, population):
    # normalizes fitness so that they sum to 1.0. Smaller paths -> higher fitness

    fitnessArray = []
    for i in range(len(population)):
        # invert the fitness, so a longer path becomes a smaller fitness
        fitnessArray.append(1/problem.evaluate(population[i].permutation))
        population[i].fitness = 1/problem.evaluate(population[i].permutation)
    soma2 = 0.0
    for individual in population:
        soma2+=individual.fitness
    res = 0.0

    for i in range(len(population)):
        fitnessArray[i] = fitnessArray[i]/soma2
        population[i].fitness = fitnessArray[i]
        res += population[i].fitness


'''
  ___                  _     ___      _        _   _          
 | _ \__ _ _ _ ___ _ _| |_  / __| ___| |___ __| |_(_)___ _ _  
 |  _/ _` | '_/ -_) ' \  _| \__ \/ -_) / -_) _|  _| / _ \ ' \ 
 |_| \__,_|_| \___|_||_\__| |___/\___|_\___\__|\__|_\___/_||_|
                                                                                           
'''

def tournamentSelection(problem, population, randomIndividual = 5):
    randomIndividualsArray = []
    # choses random individuals and makes them get into tournaments to chose the best
    for _ in (0, randomIndividual):
        randomIndividualsArray.append(random.choice(population))
    last = None
    while(len(randomIndividualsArray)>1):
        # choses two individuals and remove from the competitors the one that loses
        sakai = random.choice(randomIndividualsArray)
        ryuzo = random.choice(randomIndividualsArray)
        if (ryuzo.fitness >= sakai.fitness):
            randomIndividualsArray.remove(sakai)
            last = ryuzo
        else:
            randomIndividualsArray.remove(ryuzo)
            last = sakai
    return last


def parentSelection(problem, population):
    return tournamentSelection(problem, population, min(int(len(population[0].permutation)/10), 1))

'''
   ___                                
  / __|_ _ ___ ______ _____ _____ _ _ 
 | (__| '_/ _ (_-<_-</ _ \ V / -_) '_|
  \___|_| \___/__/__/\___/\_/\___|_|  
                                      
'''


# check if a path forms  an AB cycle
def isABcycle(path, size):
    pathVertices = []
    A = 0
    B = 1

    pathVertices.append(path[0][0])
    for i in range(len(path)):
        pathVertices.append(path[i][1])
    # stores the time at which an edge was visited and its from parent A.
    # 0 if edge wasn't visited
    visitedByA = []

    for i in range(size):
        visitedByA.append(0)
    current = A
    count = 0
    for edge in pathVertices:
        if (visitedByA[edge] != 0 and current == A):
            # returns 1 and position at which the cycle starts
            return (1,visitedByA[edge]-1)
        if (current == A):
            visitedByA[edge] = count+1
            current = B
        else:
            current = A
        count+=1
    

    return 0, 0

# generates AB Cycles
def generateABcycle(Ea,Eb,problem, size):
    
    # Set of AB Cycles generated
    abcycles = []
    # helper variable to store beginning of cycle
    i = 0
    # Adjency list of A
    adjListA = []
    # Adjency list of B
    adjListB = []
    edgesInA=0
    edgesInB=0
    for _ in range(size):
        adjListA.append([])
        adjListB.append([])
    for edge in Ea:
        u = edge[0]
        v = edge[1]
        # add edges v -> u and u -> v to adjency list
        adjListA[u].append(v)
        adjListA[v].append(u)
        edgesInA+=1
    for edge in Eb:
        u = edge[0]
        v = edge[1]
        # add edges v -> u and u -> v to adjency list
        adjListB[u].append(v)
        adjListB[v].append(u)
        edgesInB+=1
    A = 0
    B = 1
    while (edgesInA > 0):
        
        # select vertex U the belongs to the vertices V s.t. number of edges incident to vertex  included in A != 0 randomly.
        vi = random.randint(0, size-1)
        while(len(adjListA[vi]) == 0):
            vi = random.randint(0, size-1)
        # current path
        path = []
        parent = A
        # choose randomly one of the other vertices that vi connects to
        vj = random.choice(adjListA[vi])
        # remove vertices from adj list
        adjListA[vi].remove(vj)
        adjListA[vj].remove(vi)
        edgesInA-=1

        # stores vertices u,v of an edge
        edgeA = []
        edgeA.append(vi)
        edgeA.append(vj)
        # add edge to path
        path.append(edgeA)
        # controls last vertex visited in path
        prev = vj
        isCycle = 0
        while ((not isCycle )):
            if (parent == A):
                edgeB = []
                edgeB.append(prev)
                v = adjListB[prev][0]
                if (len(adjListB[prev]) == 2):
                    v = random.choice(adjListB[prev])
                adjListB[prev].remove(v)
                adjListB[v].remove(prev)
                edgeB.append(v)
                path.append(edgeB)
                prev = v
                parent = B
            else:
                edgeA = []
                edgeA.append(prev)
                v = adjListA[prev][0]
                if (len(adjListA[prev]) == 2):
                    v = random.choice(adjListA[prev])
                edgeA.append(v)
                adjListA[prev].remove(v)
                adjListA[v].remove(prev)
                parent = A
                path.append(edgeA)
                prev = v
                edgesInA-=1


            isCycle, i = isABcycle(path, size)
        # put back in adj lists vertices that werent used in cycle
        if (i > 0):
            for index in range(0,i):
                v = path[index][0]
                u = path[index][1]
                if (index%2==0):
                    adjListA[v].append(u)
                    adjListA[u].append(v)
                    edgesInA+=1
                else:
                    adjListB[v].append(u)
                    adjListB[u].append(v)
        # get vertices that form cycle from the path
        cycle = []
        for i in range(i, len(path)):
            cycle.append(path[i])
        abcycles.append(cycle)
    return abcycles


# select cycles with probability 0.5
def selectRandomCycles(abCycles):
    D = []
    for element in abCycles:
        p = random.random()
        if (p < 0.5):
            D.append(element)
    # return at least one cycle randomly
    if (len(D) == 0):
        D.append(random.choice(abCycles))
    return D

def generateIntermediateSolution(D, C):
    A = 0
    B = 1
    for subTour in D:
        current = A
        for edge in subTour:
            reveseEdge = [edge[1],edge[0]]
            # remove from the child each edge that comes from parent A
            if (current == A and (edge in C)):
                C.remove(edge)
            elif (current == A and (reveseEdge in C)):
                C.remove(reveseEdge)
            # add to child each edge that comes from parent B
            elif (current == B):
                C.append(edge)

            if (current == A):
                current = B
            else:
                current = A
    return C

# Disjoint-Set Union
# data structure that stores a collection of disjoint (non-overlapping) sets
class DSU:
    def __init__(self, size, edges):
        self.size = size
        self.p = []
        for i in range(size):
            self.p.append(i)

    # finds set that i belongs to
    def findSet(self, i):
        if (self.p[i] == i):
            return i
        self.p[i] = self.findSet(self.p[i])
        return self.p[i]

    # check if two elements belong to same set
    def isSameSet(self, i, j):
        return self.findSet(i) == self.findSet(j)
    
    # merge two sets
    def unionSet(self, i, j, edge):
        if (not self.isSameSet(i,j)):
            self.p[self.findSet(i)] = self.findSet(j)
            

# splits tours
def splitTours(tourArray):
    dsu = DSU(len(tourArray), tourArray)
    for edge in tourArray:
        # if there is and edge u -> v, merge sets of edge u and edge v
        dsu.unionSet(edge[0], edge[1], edge)

    # array of position to store each of the final sets
    position = [None]*len(tourArray)
    cont = 0
    for i in range(dsu.size):
        if (position[dsu.findSet(i)] == None):
            position[dsu.findSet(i)] = cont
            cont+=1
    # array with final edges of cycles
    ret = []
    for i in range(cont):
        ret.append([])
    for edge in tourArray:
        ret[position[dsu.findSet(edge[0])]].append(edge)
    return ret

def cut( e1, e2, problem):
    # price of cutting edge
    c1 = problem.distance_matrix[e1[0]][e1[1]]
    c2 = problem.distance_matrix[e2[0]][e2[1]]
    return c1+c2
    
def link(e1,e2,problem):
    # price of linking two 4 vetices (from 2 edges)
    c1 = problem.distance_matrix[e1[0]][e2[0]]
    c2 = problem.distance_matrix[e1[1]][e2[1]]
    
    c3 = problem.distance_matrix[e1[0]][e2[1]]
    c4 = problem.distance_matrix[e1[1]][e2[0]]

    return min((c1+c2), (c3+c4))

# exchanges links between 2 edges as to minimize cost
def exchangeLinks(e1, e2, problem):
    a = e1[0]
    b = e1[1]
    c = e2[0]
    d = e2[1]

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

# modifies set of subtours as to unite all in a single tour
def modification(problem, U, size):
    k = len(U)
    s = k
    while(s > 1):
        iStar = 0
        minLen = len(U[0])
        for i in range(s):
            if (len(U[i]) < minLen and len(U) > 0):
                iStar = i
                minLen = len(U[i])
        menor = -1
        jStar = 0
        ix = 0
        jx = 0
        for j in range(s):
            if (j != iStar):
                for i0 in range(len(U[iStar])):
                    for i1 in range(len(U[j])):
                        corte = cut(U[iStar][i0], U[j][i1], problem)
                        linka = link(U[iStar][i0], U[j][i1], problem)
                        res = linka - corte
                        if (menor == -1):
                            menor = res
                            ix = i0
                            jStar = j
                            jx = i1
                        if (res < menor):
                            menor = res
                            ix = i0
                            jStar = j
                            jx = i1
                        pass
        edgea = U[iStar][ix]
        edgeb = U[jStar][jx]
        U[iStar].remove(edgea)
        U[jStar].remove(edgeb)
        for edge in U[jStar]:
            U[iStar].append(edge)
    
        newA, newB = exchangeLinks(edgea, edgeb, problem)
        U[iStar].append(newA)
        U[iStar].append(newB)
        U[jStar] = U[s-1]
        s-=1
    adjList = []
    for i in range(size):
        adjList.append([])
    for u in U[0]:
        v = u[0]
        w = u[1]
        adjList[v].append(w)
        adjList[w].append(v)
    return U[0]


def eax (a,b,problem):
    Ea = []
    Eb = []
    C = []
    size = len(a.permutation)
    for i in range (size):
        i2 = (i+1) % size
        Ea.append([a.permutation[i], a.permutation[i2]])
        Eb.append([b.permutation[i], b.permutation[i2]])
        # child starts as copy of parent A
        C.append([a.permutation[i], a.permutation[i2]])
    
    abCycles = generateABcycle(Ea,Eb,problem, size)

    D = selectRandomCycles(abCycles)

    intermediateSolution = generateIntermediateSolution(D, C)
    subtours = splitTours(intermediateSolution)
    childEdges = modification(problem, subtours, size)
    permutationArray = []
    for i in range(len(a.permutation)):
        permutationArray.append([])
    for edge in childEdges:
        v1 = edge[0]
        v2 = edge[1]
        permutationArray[v1].append(v2)
        permutationArray[v2].append(v1) 
    permutation = []
    # generate permutation from edges list
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
    child = Individual(permutation, problem.evaluate(permutation)) 
    return child

    
def crossover(a,b,problem):
    children = [[],[]]
    # generates 2 children with the same parent and returns them
    children[0] = eax(a,b,problem)
    children[1] = eax(a,b,problem)
    return children

'''
  __  __      _        _   _          
 |  \/  |_  _| |_ __ _| |_(_)___ _ _  
 | |\/| | || |  _/ _` |  _| / _ \ ' \ 
 |_|  |_|\_,_|\__\__,_|\__|_\___/_||_|
                                      
'''


def mutate(permutation, mutationRate = 0.01):
    val = random.random()
    # elements in the permutation are randomly swaped 
    #probability of being swaped is based on mutation rate, which is a number between 0 and 1
    while(val <= mutationRate):
        ixa = random.choice(permutation)
        ixb = random.choice(permutation)
        tmpElem = permutation[ixa]
        permutation[ixa] = permutation[ixb]
        permutation[ixb] = tmpElem
        val = random.random()
    return permutation

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
    normalizeFitness(problem,newPopulation)
    return newPopulation


def nextGenSelection(problem, populationA, populationB, populationSize):
    return selectionBaseOnAptitude(problem, populationA, populationB, populationSize)



def new_generation(problem, population):
    children = []
    for _ in range(len(population)):
        parentA = parentSelection(problem, population)
        parentB = parentSelection(problem, population)
        
        [newIndividual,newIndividual1] = crossover(parentA, parentB, problem)
        
        mutate(newIndividual.permutation)
        mutate(newIndividual1.permutation)

        children.append(newIndividual)
        children.append(newIndividual1)

    nextGen = nextGenSelection(problem, population, children, len(population))
    return nextGen
    pass


def genetic_algorithm(problem, pop_size=50, max_gen=2000):

    population = random_population(problem, pop_size)
    fitness_history = []
    best_permutation = None
    #SUA IMPLEMENTACAO AQUI

    normalizeFitness(problem, population)

    bestFitness = problem.evaluate(population[0].permutation) 
    best_permutation = population[0].permutation
    fitness_history.append(bestFitness)
    lastBestGen = 1
    
    # finds the best fitness of the initial population
    for individual in population:
        if (problem.evaluate(individual.permutation) <= bestFitness):
            bestFitness = problem.evaluate(individual.permutation)
            best_permutation = individual.permutation
    generations = 1
    # utils.drawTour(problem, best_permutation,bestFitness,1)
    bestGens = []
    bestGens.append(0)
    while (generations < max_gen) and (generations) < lastBestGen*5:
        newGen = new_generation(problem, population)
        normalizeFitness(problem,newGen)
        population = newGen
        lastBest = bestFitness
        bestThis = problem.evaluate(population[0].permutation)
        for individual in population:
            curr = problem.evaluate(individual.permutation)
            if (curr <= bestThis):
                bestThis = curr
            if (curr <= bestFitness):
                bestFitness = curr
                best_permutation = individual.permutation

        if (bestFitness != lastBest):
            # utils.drawTour(problem, best_permutation,bestFitness,generations)
            lastBestGen = generations

            bestGens.append(generations)
        generations+=1

        
        fitness_history.append(bestThis)
    return best_permutation, fitness_history


if __name__ == "__main__":
    problem = TSP('instances/eli51.tsp')
    best_solution, fitness_history = genetic_algorithm(problem, 50, 2000)
    print(best_solution, problem.evaluate(best_solution))

