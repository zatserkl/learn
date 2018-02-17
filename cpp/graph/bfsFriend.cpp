/**
 * @file bfsFriend.cpp
 * @brief 
 *   Implementation of Breadth First Search algorithm over a graph.
 *
 * @author George Heineman
 * @date 6/15/08
 * @modified Andriy Zatserklyaniy
 * @date 11/10/16
 */

#include "Graph.h"
#include <queue>
#include <iostream>
#include <cstdarg>
#include <vector>
#include <limits>

using std::cout;    using std::endl;

/**
 * Perform breadth-first search on graph from vertex s, and compute BFS
 * distance and pred vertex for all vertices in the graph.
 */
int bfsSearch (Graph const &graph, int s, int maxdepth, int id_search, std::vector<int> &dist, std::vector<int> &pred)
{
    int id_search_distance = -1;    // return value: distance to vertex id_search

    // initialize dist and pred to mark vertices as unvisited. Begin at s
    // and mark as Gray since we haven't yet visited its neighbors.
    const int n = graph.numVertices();
    pred.assign(n, -1);
    dist.assign(n, std::numeric_limits<int>::max());
    std::vector<vertexColor> color (n, White);

    dist[s] = 0;
    color[s] = Gray;

    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();

        if (maxdepth < 0 || dist[u] < maxdepth)
        {
            // Explore neighbors of u to expand the search horizon
            for (VertexList::const_iterator it = graph.begin(u); it != graph.end(u); ++it) {
                int v = it->first;
                if (color[v] == White) {
	            dist[v] = dist[u]+1;
	            pred[v] = u;
	            color[v] = Gray;
	            q.push(v);
                }
            }
        }

        q.pop();
        color[u] = Black;

        cout<< "\tbfsSearch: done with vertex " << u << " at the distance " << dist[u] <<endl;
        //
        // process vertex here
        //
        if (u == id_search) {
            id_search_distance = dist[u];
            cout<< "--- found friend id_search = " << id_search << " at the distance " << dist[u] <<endl;
            // return id_search_distance;
        }
    }

    return id_search_distance;
}

int main(int argc, char *argv[])
{
    int maxdepth = -1;
    if (argc > 1) maxdepth = atoi(argv[1]);
    cout<< "maxdepth = " << maxdepth <<endl;

    int id_search = -1;
    if (argc > 2) id_search = atoi(argv[2]);
    cout<< "id_search = " << id_search <<endl;
    
    Graph graph(8,false);

    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 4, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 6, 1);
    graph.addEdge(6, 7, 1);

    cout<< "graph.numVertices() = " << graph.numVertices() <<endl;

    // use as a start vertex s = 4
    int s = 4;

    std::vector<int> dist(graph.numVertices());
    std::vector<int> pred(graph.numVertices());

    int id_search_distance = bfsSearch(graph, s, maxdepth, id_search, dist, pred);

    for (unsigned ivertex=0; ivertex<graph.numVertices(); ++ivertex) {
        cout<< "dist[" << ivertex << "] = " << dist[ivertex] << "\t   pred[" << ivertex << "] = " << pred[ivertex] << (ivertex == s? " <-- s = 4": "") <<endl;
    }

    if (id_search_distance >= 0) cout<< "-- found a friend " << id_search << " at the distance " << id_search_distance <<endl;
    else cout<< "-- no tructed friend found withing depth " << maxdepth <<endl;

    return 0;
}

/*
graph-book$ clang++ -Wall bfsTest.cxx 
graph-book$ ./a.out 

maxdepth = -1
graph.numVertices() = 8
	bfsSearch: done with vertex 4
	bfsSearch: done with vertex 5
	bfsSearch: done with vertex 1
	bfsSearch: done with vertex 6
	bfsSearch: done with vertex 2
	bfsSearch: done with vertex 0
	bfsSearch: done with vertex 7
	bfsSearch: done with vertex 3
dist[0] = 2	   pred[0] = 1
dist[1] = 1	   pred[1] = 4
dist[2] = 2	   pred[2] = 1
dist[3] = 3	   pred[3] = 2
dist[4] = 0	   pred[4] = -1 <-- s = 4
dist[5] = 1	   pred[5] = 4
dist[6] = 2	   pred[6] = 5
dist[7] = 3	   pred[7] = 6
graph-book$ 
graph-book$ 
graph-book$ clang++ -Wall bfsFriend.cpp 

graph-book$ ./a.out 4
maxdepth = 4
id_search = -1
graph.numVertices() = 8
	bfsSearch: done with vertex 4 at the distance 0
	bfsSearch: done with vertex 5 at the distance 1
	bfsSearch: done with vertex 1 at the distance 1
	bfsSearch: done with vertex 6 at the distance 2
	bfsSearch: done with vertex 2 at the distance 2
	bfsSearch: done with vertex 0 at the distance 2
	bfsSearch: done with vertex 7 at the distance 3
	bfsSearch: done with vertex 3 at the distance 3
dist[0] = 2	   pred[0] = 1
dist[1] = 1	   pred[1] = 4
dist[2] = 2	   pred[2] = 1
dist[3] = 3	   pred[3] = 2
dist[4] = 0	   pred[4] = -1 <-- s = 4
dist[5] = 1	   pred[5] = 4
dist[6] = 2	   pred[6] = 5
dist[7] = 3	   pred[7] = 6
-- no tructed friend found withing depth 4

graph-book$ ./a.out 3
maxdepth = 3
id_search = -1
graph.numVertices() = 8
	bfsSearch: done with vertex 4 at the distance 0
	bfsSearch: done with vertex 5 at the distance 1
	bfsSearch: done with vertex 1 at the distance 1
	bfsSearch: done with vertex 6 at the distance 2
	bfsSearch: done with vertex 2 at the distance 2
	bfsSearch: done with vertex 0 at the distance 2
	bfsSearch: done with vertex 7 at the distance 3
	bfsSearch: done with vertex 3 at the distance 3
dist[0] = 2	   pred[0] = 1
dist[1] = 1	   pred[1] = 4
dist[2] = 2	   pred[2] = 1
dist[3] = 3	   pred[3] = 2
dist[4] = 0	   pred[4] = -1 <-- s = 4
dist[5] = 1	   pred[5] = 4
dist[6] = 2	   pred[6] = 5
dist[7] = 3	   pred[7] = 6
-- no tructed friend found withing depth 3

graph-book$ ./a.out 2
maxdepth = 2
id_search = -1
graph.numVertices() = 8
	bfsSearch: done with vertex 4 at the distance 0
	bfsSearch: done with vertex 5 at the distance 1
	bfsSearch: done with vertex 1 at the distance 1
	bfsSearch: done with vertex 6 at the distance 2
	bfsSearch: done with vertex 2 at the distance 2
	bfsSearch: done with vertex 0 at the distance 2
dist[0] = 2	   pred[0] = 1
dist[1] = 1	   pred[1] = 4
dist[2] = 2	   pred[2] = 1
dist[3] = 2147483647	   pred[3] = -1
dist[4] = 0	   pred[4] = -1 <-- s = 4
dist[5] = 1	   pred[5] = 4
dist[6] = 2	   pred[6] = 5
dist[7] = 2147483647	   pred[7] = -1
-- no tructed friend found withing depth 2

graph-book$ ./a.out 1
maxdepth = 1
id_search = -1
graph.numVertices() = 8
	bfsSearch: done with vertex 4 at the distance 0
	bfsSearch: done with vertex 5 at the distance 1
	bfsSearch: done with vertex 1 at the distance 1
dist[0] = 2147483647	   pred[0] = -1
dist[1] = 1	   pred[1] = 4
dist[2] = 2147483647	   pred[2] = -1
dist[3] = 2147483647	   pred[3] = -1
dist[4] = 0	   pred[4] = -1 <-- s = 4
dist[5] = 1	   pred[5] = 4
dist[6] = 2147483647	   pred[6] = -1
dist[7] = 2147483647	   pred[7] = -1
-- no tructed friend found withing depth 1

graph-book$ ./a.out -1
maxdepth = -1
id_search = -1
graph.numVertices() = 8
	bfsSearch: done with vertex 4 at the distance 0
	bfsSearch: done with vertex 5 at the distance 1
	bfsSearch: done with vertex 1 at the distance 1
	bfsSearch: done with vertex 6 at the distance 2
	bfsSearch: done with vertex 2 at the distance 2
	bfsSearch: done with vertex 0 at the distance 2
	bfsSearch: done with vertex 7 at the distance 3
	bfsSearch: done with vertex 3 at the distance 3
dist[0] = 2	   pred[0] = 1
dist[1] = 1	   pred[1] = 4
dist[2] = 2	   pred[2] = 1
dist[3] = 3	   pred[3] = 2
dist[4] = 0	   pred[4] = -1 <-- s = 4
dist[5] = 1	   pred[5] = 4
dist[6] = 2	   pred[6] = 5
dist[7] = 3	   pred[7] = 6
-- no tructed friend found withing depth -1
*/
