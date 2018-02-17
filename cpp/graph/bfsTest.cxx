/**
 * @file bfs.cxx    Contains the Breadth-First Search implementation
 * @brief 
 *   Implementation of Breadth First Search algorithm over a graph.
 *
 * @author George Heineman
 * @date 6/15/08
 * @modified Andriy Zatserklyaniy
 * @date 11/9/16
 */

//#include "bfs.h"
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
void bfsSearch (Graph const &graph, int s, int maxdepth,    /* in */
	        std::vector<int> &dist, std::vector<int> &pred)       /* out */
{
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

        if (maxdepth < 0 || dist[u]+1 <= maxdepth) {
            // Explore neighbors of u to expand the search horizon
            for (VertexList::const_iterator ci = graph.begin(u); ci != graph.end(u); ++ci) {
                int v = ci->first;
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

        // process vertex here
        cout<< "\tbfsSearch: done with vertex " << u <<endl;
    }
}

int main(int argc, char *argv[])
{
    int maxdepth = -1;
    if (argc > 1) maxdepth = atoi(argv[1]);
    cout<< "maxdepth = " << maxdepth <<endl;
    
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

    bfsSearch(graph, s, maxdepth, dist, pred);

    for (unsigned ivertex=0; ivertex<graph.numVertices(); ++ivertex) {
        cout<< "dist[" << ivertex << "] = " << dist[ivertex] << "\t   pred[" << ivertex << "] = " << pred[ivertex] << (ivertex == s? " <-- s = 4": "") <<endl;
    }
}
/*
graph-book$ clang++ -Wall bfsTest.cxx Graph.cxx
graph-book$ ./a.out 4
maxdepth = 4
graph.numVertices() = 8
	bfsSearch: done with vertex 4
	bfsSearch: done with vertex 5
	bfsSearch: done with vertex 1
	bfsSearch: done with vertex 6
	bfsSearch: done with vertex 2
	bfsSearch: done with vertex 0
	bfsSearch: done with vertex 7
	bfsSearch: done with vertex 3
dist[0] = 2	   pred[0] = 2
dist[1] = 1	   pred[1] = 1
dist[2] = 2	   pred[2] = 2
dist[3] = 3	   pred[3] = 3
dist[4] = 0	   pred[4] = 0 <-- s = 4
dist[5] = 1	   pred[5] = 1
dist[6] = 2	   pred[6] = 2
dist[7] = 3	   pred[7] = 3
graph-book$ ./a.out 3
maxdepth = 3
graph.numVertices() = 8
	bfsSearch: done with vertex 4
	bfsSearch: done with vertex 5
	bfsSearch: done with vertex 1
	bfsSearch: done with vertex 6
	bfsSearch: done with vertex 2
	bfsSearch: done with vertex 0
	bfsSearch: done with vertex 7
	bfsSearch: done with vertex 3
dist[0] = 2	   pred[0] = 2
dist[1] = 1	   pred[1] = 1
dist[2] = 2	   pred[2] = 2
dist[3] = 3	   pred[3] = 3
dist[4] = 0	   pred[4] = 0 <-- s = 4
dist[5] = 1	   pred[5] = 1
dist[6] = 2	   pred[6] = 2
dist[7] = 3	   pred[7] = 3
graph-book$ ./a.out 2
maxdepth = 2
graph.numVertices() = 8
	bfsSearch: done with vertex 4
	bfsSearch: done with vertex 5
	bfsSearch: done with vertex 1
	bfsSearch: done with vertex 6
	bfsSearch: done with vertex 2
	bfsSearch: done with vertex 0
dist[0] = 2	   pred[0] = 2
dist[1] = 1	   pred[1] = 1
dist[2] = 2	   pred[2] = 2
dist[3] = 2147483647	   pred[3] = 2147483647
dist[4] = 0	   pred[4] = 0 <-- s = 4
dist[5] = 1	   pred[5] = 1
dist[6] = 2	   pred[6] = 2
dist[7] = 2147483647	   pred[7] = 2147483647
graph-book$ ./a.out 1
maxdepth = 1
graph.numVertices() = 8
	bfsSearch: done with vertex 4
	bfsSearch: done with vertex 5
	bfsSearch: done with vertex 1
dist[0] = 2147483647	   pred[0] = 2147483647
dist[1] = 1	   pred[1] = 1
dist[2] = 2147483647	   pred[2] = 2147483647
dist[3] = 2147483647	   pred[3] = 2147483647
dist[4] = 0	   pred[4] = 0 <-- s = 4
dist[5] = 1	   pred[5] = 1
dist[6] = 2147483647	   pred[6] = 2147483647
dist[7] = 2147483647	   pred[7] = 2147483647
graph-book$ ./a.out 0
maxdepth = 0
graph.numVertices() = 8
	bfsSearch: done with vertex 4
dist[0] = 2147483647	   pred[0] = 2147483647
dist[1] = 2147483647	   pred[1] = 2147483647
dist[2] = 2147483647	   pred[2] = 2147483647
dist[3] = 2147483647	   pred[3] = 2147483647
dist[4] = 0	   pred[4] = 0 <-- s = 4
dist[5] = 2147483647	   pred[5] = 2147483647
dist[6] = 2147483647	   pred[6] = 2147483647
dist[7] = 2147483647	   pred[7] = 2147483647
graph-book$ ./a.out -1
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
dist[0] = 2	   pred[0] = 2
dist[1] = 1	   pred[1] = 1
dist[2] = 2	   pred[2] = 2
dist[3] = 3	   pred[3] = 3
dist[4] = 0	   pred[4] = 0 <-- s = 4
dist[5] = 1	   pred[5] = 1
dist[6] = 2	   pred[6] = 2
dist[7] = 3	   pred[7] = 3
graph-book$ 
*/
