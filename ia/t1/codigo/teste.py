from queue import PriorityQueue

q = PriorityQueue()
q.put(10)
q.put(1)
q.put(5)
while not q.empty():
	print (q.get())

