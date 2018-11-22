from __future__ import print_function
from collections import deque


class Graph:
    def __init__(self):
        self.vertices = []

    def __repr__(self):
        return self.vertices

    def __str__(self):
        return str(self.vertices)

    def addVertex(self, vertex):
        self.vertices.append(vertex)    # vertex is just a list

    def show(self):
        for i, vertex in enumerate(self.vertices):
            print(i, vertex)

    #
    # Depth First Search
    #
    def depthFirstSearch(self, s):
        """
        Depth First Search: search path from the target vertex s.
        The Depth First Search can locate a path more quickly,
        but it may not be the shortest path.
        Recursive algorithm.

        Returns a list of predecessors on the path to the target vertex s.
        """
        self.pred = [-1]*len(self.vertices)
        self.color = [0]*len(self.vertices)  # 0 is white
        self.dfsVisit(s)                     # call recursive function dfsVisit
        return self.pred

    def dfsVisit(self, u):
        """ Main part of the Depth First search
        """
        self.color[u] = 1                       # 1 is gray
        for neighbor in self.vertices[u]:
            if self.color[neighbor] == 0:
                self.pred[neighbor] = u
                self.dfsVisit(neighbor)
        self.color[u] = 2                       # 2 is black

    #
    # Breadth First Search
    #

    def breadthFirstSearch(self, s):
        """
        Breadth First Search: search layer-by-layer from the target vertex s.
        Garanteed to find the shortest path from the target vertex s.
        Non-recursive algorithm.
        Needs storage for queue.

        Returns a list of predecessors and a list of distances to the vertex s.
        """
        dist = [-1]*len(self.vertices)
        color = [0]*len(self.vertices)     # 0 is white
        pred = [-1]*len(self.vertices)

        color[s] = 1                       # 1 is gray
        dist[s] = 0

        queue = deque()
        queue.appendleft(s)     # use appendleft and pop (pop from the right)

        #                         head
        #            +-----+-----+-----+
        # enqueue -> |  3  |  2  |  1  | -> dequeue
        #            +-----+-----+-----+
        #                         front

        while len(queue) > 0:
            u = queue.pop()  # extract head of the queue (front in C++), element queue[-1]
            for neighbor in self.vertices[u]:
                if color[neighbor] == 0:
                    dist[neighbor] = dist[u] + 1
                    pred[neighbor] = u
                    color[neighbor] = 1    # gray
                    queue.appendleft(neighbor)  # add from the left
            color[u] = 2                   # mark black: done with this vertex
        return pred, dist


############################
# General purpose function #
############################

def path(pred, vertex):
    v = vertex
    print(v, end='')
    while pred[v] >= 0:
        v = pred[v]
        print('-->', v, end='')
    print()


#
# main
#
if __name__ == '__main__':

    #       1-------2----6
    #       |       |
    #       |   5   |    8
    #       |   |   |    |
    #       0---4---3    7
    #       s

    graph = Graph()

    graph.addVertex([4, 1])         # 0: will be vertex s
    graph.addVertex([0, 2])         # 1
    graph.addVertex([1, 3, 6])      # 2
    graph.addVertex([2, 4])         # 3
    graph.addVertex([0, 5, 3])      # 4
    graph.addVertex([4])            # 5
    graph.addVertex([2])            # 6
    graph.addVertex([8])            # 7
    graph.addVertex([7])            # 8

    print(graph)
    graph.show()

    s = 0                           # get path to this vertex

    #
    # Depth First Search
    #

    print('\nDepth First Search')

    pred = graph.depthFirstSearch(s)

    print('pred:', pred)
    for i, iv in enumerate(pred):
        print(i, iv)

    # print('\npath for vertex 5 to vertex 0\n')
    # path(pred, 5)

    print('\npath to vertex 0 (if any)\n')

    for v in range(len(pred)):
        path(pred, v)

    #
    # Breadth First Search
    #

    print('\nBreadth First Search')

    pred, dist = graph.breadthFirstSearch(s)

    print('pred =', pred)
    print('dist =', dist)

    print('\npath to vertex 0 (if any)\n')

    for v in range(len(pred)):
        path(pred, v)
