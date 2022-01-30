from queue import PriorityQueue
from tsp import TSP


class Node():
    def __init__(self, state, path_cost, heuristic_cost, city, parent_node):
        self.state = state
        self.path_cost = path_cost
        self.heuristic_cost = heuristic_cost
        self.node_cost = path_cost + heuristic_cost
        self.city = city
        self.parent_node = parent_node

    def __lt__(self, other):
        return self.node_cost < other.node_cost

    def __le__(self, other):
        return self.node_cost <= other.node_cost

    def __gt__(self, other):
        return self.node_cost > other.node_cost

    def __ge__(self, other):
        return self.node_cost >= other.node_cost


def backtrack_path( current, problem):
    path = []
    while current.parent_node != -1:
        path.append(current.city)
        current = current.parent_node
    path.append(0)
    return (path)

def a_star(problem):
    nodesQ = PriorityQueue()
    startState = problem.get_start_state()
    first = Node(startState, 0, problem.get_heuristic(startState), 0, -1 )
    nodesQ.put(first)
    
    while not nodesQ.empty():
        current = nodesQ.get()
        if problem.is_goal_state(current.state):
            return backtrack_path(current, problem)

        neighbours = problem.get_next_states(current.state)
        for neighbour in neighbours:
            tentativePath = current.path_cost + neighbour[2]
            h = problem.get_heuristic(neighbour[0])
            newNode = Node(neighbour[0], tentativePath, h, neighbour[1], current)
            if (problem.is_goal_state(newNode.state)):
                return backtrack_path(newNode, problem)
            nodesQ.put(newNode)                
    return (0)



if __name__ == "__main__":
    problem = TSP('instances/berlin10.tsp')
    path = a_star(problem)
    print(path, problem.evaluate(path))
