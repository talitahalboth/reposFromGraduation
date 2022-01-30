import random
import itertools


class MSTGraph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def __str__(self):
        return str(self.graph)

    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])

    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def apply_union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def compute_mst(self):
        result = []
        i, e, cost = 0, 0, 0
        self.graph = sorted(self.graph, key=lambda item: item[2])
        parent = []
        rank = []
        for node in range(self.V):
            parent.append(node)
            rank.append(0)
        while e < self.V - 1:
            u, v, w = self.graph[i]
            i += 1
            x = self.find(parent, u)
            y = self.find(parent, v)
            if x != y:
                e += 1
                result.append([u, v, w])
                cost += w
                self.apply_union(parent, rank, x, y)
        return cost


class TSP():
    def __init__(self, instance_file):
        self.__read_file(instance_file)

    def __read_file(self, instance_file):
        
        coords = {}
        self.coords = []
        with open(instance_file) as file:
            lines = [line.rstrip() for line in file if line]
            for line in lines:
                if 'DIMENSION' in line:
                    self.size = int(line.split(':')[-1].strip())
                elif 'NAME' in line:
                    self.instance = line.split(':')[-1].strip()
                elif line[0].isdigit():
                    city, coord_x, coord_y = [x.strip() for x in line.split()]
                    city, coord_x, coord_y = int(city), float(coord_x), float(coord_y)
                    # use 0...n-1 representation instead of 1...n
                    coords[city-1] = (coord_x, coord_y)
                    self.coords.append([coord_x, coord_y])

        self.distance_matrix = [[0] * self.size for _ in range(self.size)]
        
        for i, j in itertools.combinations(range(self.size), 2):
            dist = self.__euclidean_dist(coords, i, j)
            dist = round(dist)
            self.distance_matrix[i][j] = dist
            self.distance_matrix[j][i] = dist

    def __euclidean_dist(self, coords, i, j):
        return ((coords[i][0] - coords[j][0]) ** 2 + (coords[i][1] - coords[j][1]) ** 2) ** .5

    def __str__(self):
        return 'TSP_' + self.instance

    def evaluate(self, solution):
        fitness = self.distance_matrix[solution[-1]][solution[0]]
        for i in range(len(solution)-1):
            fitness += self.distance_matrix[solution[i]][solution[i+1]]
        return fitness

    def get_start_state(self):
        return 0,

    def is_goal_state(self, state):
        return len(state) == self.size

    def __get_unvisited(self, state):
        if len(state) == self.size:
            #next action is to return to the initial city
            return {state[0]}
        return set(range(self.size)) - set(state)

    def get_next_states(self, state):
        unvisited = self.__get_unvisited(state)
        successors = []
        for city in unvisited:
            cost = self.distance_matrix[state[-1]][city]
            next_state = (state[0],) + tuple(random.sample(state[1:], len(state)-1)) + (city,)
            successors.append((next_state, city, cost))
        return successors

    def random_path(self):
        path = list(range(self.size))
        random.shuffle(path)
        return path

    def __get_city_idx(self, city, idx_dict):
        if city in idx_dict:
            return idx_dict[city]
        new_idx = len(idx_dict)
        idx_dict[city] = new_idx
        return new_idx

    def __nearest_unvisited_dist(self, city, unvisited):
        unvisited_dists = [self.distance_matrix[city][i] for i in unvisited]
        return min(unvisited_dists)

    def get_heuristic(self, state):
        unvisited = self.__get_unvisited(state)
        if len(unvisited) == 0:
            return 0
        dist_to_current = self.__nearest_unvisited_dist(state[-1], unvisited)
        dist_to_start = self.__nearest_unvisited_dist(state[0], unvisited)
        if len(unvisited) == 1:
            return dist_to_start + dist_to_current
        aux_graph = MSTGraph(len(unvisited))
        idx_dict = {}
        for city_a, city_b in itertools.combinations(unvisited, 2):
            u = self.__get_city_idx(city_a, idx_dict)
            v = self.__get_city_idx(city_b, idx_dict)
            aux_graph.add_edge(u, v, self.distance_matrix[city_a][city_b])
        mst_dist = aux_graph.compute_mst()
        return dist_to_current + dist_to_start + mst_dist
