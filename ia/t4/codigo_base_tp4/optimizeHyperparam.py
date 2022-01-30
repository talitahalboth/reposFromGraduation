import os
import random
import statistics
from pyeasyga import pyeasyga
import subprocess

# setup seed data
# epsilon, gamma, alpha
seed_data = [0.5, 0.8, 0.5]

# initialise the GA
ga = pyeasyga.GeneticAlgorithm(seed_data,
                               population_size=100,
                               generations=100,
                               crossover_probability=0.8,
                               mutation_probability=0.2,
                               elitism=True,
                               maximise_fitness=True)


# define and set function to create a candidate solution representation
def create_individual(data):
    individual = []
    for _ in range(3):
        individual.append(random.random())
    # print(individual)
    return individual


ga.create_individual = create_individual


# define and set the GA's crossover operation
def crossover(parent_1, parent_2):
    child_1 = []
    child_2 = []
    ini = random.randint(0, 3)
    for i in range(0, ini):
        child_1.append(parent_1[i])
        child_2.append(parent_2[i])

    for i in range(ini, 3):
        child_1.append(parent_2[i])
        child_2.append(parent_1[i])
    # print("children:")
    # print(child_1, child_2)
    return child_1, child_2


ga.crossover_function = crossover


# define and set the GA's mutation operation
def mutate(individual):
    mutate_index1 = random.randrange(len(individual))
    individual[mutate_index1] = random.random()


ga.mutate_function = mutate


# define and set the GA's selection operation
def tournament_selection(population):
    print(population)
    parents = random.choices(population, k=5)
    parents = sorted(parents, key=lambda agent: agent.fitness, reverse=True)
    return parents[0]


ga.selection_function = tournament_selection


# define a fitness function
def fitness(individual, data):
    if os.path.exists("tmp"):
        os.remove("tmp")
    command = "python frozen_lake.py -e " + str(individual[0]) + " -g " + str(individual[1]) + " -a" + str(
        individual[2]) + " -s"
    with open('tmp', "a") as outfile:
        procs = [subprocess.Popen(command, shell=False, stdout=outfile) for i in range(10)]
        for p in procs:
            p.wait()
    f = open('tmp', 'r')
    lines = f.readlines()
    treinamento = []
    validacao = []
    par = False
    for line in lines:
        rate = line.split(' ')[-1]
        splitRate = rate.split('/')
        rate = int(splitRate[0]) / (1.0 * int(splitRate[1][:-1]))
        if not par:
            treinamento.append(rate)
        else:
            validacao.append(rate)
        par = not par
    # print("fitness")
    # print(statistics.mean(validacao))
    return statistics.mean(validacao)


ga.fitness_function = fitness  # set the GA's fitness function
ga.run()  # run the GA

# # print the GA's best solution (valid only if there are no collisions)
print(ga.best_individual())
f = open("best.txt", "w")
f.write((ga.best_individual()))
f.write(ga)
