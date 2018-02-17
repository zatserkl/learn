/**
 * @file Graph.h   Defines the Graph concept
 * @brief 
 *   A Graph=(V,E) and is a central data structure for numerous algorithms.
 *   Each edge (u,v) has a weight; if no edge weights are assigned then the
 *   default value of '1' is used.
 * 
 * @author George Heineman
 * @date 6/15/08
 * @modified Andriy Zatserklyaniy
 * @date 11/10/16
 */

#ifndef _Graph_h_
#define _Graph_h_

#include <limits>
#include <list>
#include <vector>

// For vertex u, store information about (v,w) where edge (u,v)
// has the designated edge weight w. The first value is the id
// for the vertex v while the second value is the weight w.
typedef std::pair<int,int> IdWeight;

// Adjacency list for a vertex
typedef std::list<IdWeight> VertexList;

/** Types of vertes colorings used by the DepthFirst and BreadthFirst searches. */
enum vertexColor { White, Gray, Black };

/** Types of computed edge types during DepthFirstSearch. */
enum edgeType { Tree, Backward, Forward, Cross };

/**
 * Graph superclass to define common interface for Graph objects and
 * provide ability to load up from a file.
 *
 * @author George Heineman
 * @date 6/15/08
 * @modified Andriy Zatserklyaniy
 * @date 11/10/16
 */
class Graph {
protected:
    std::vector<VertexList> vertices_;      // each vertex has list.
    bool directed_;                         // is graph directed?
public:
    /** Create empty undirected graph. */
    Graph () : directed_(false) {}

    /** Create graph with n vertices. */
    Graph (int n, bool d=false) : directed_(d) {
        vertices_.resize(n);
    }

    const int numVertices() const { return vertices_.size(); }
    bool directed() const { return directed_; }
    const VertexList& getVertex(int u) const {return vertices_.at(u);}
    void addWeight(int u, int v, int increment=1) {
        // TODO: the weight may contain the nunber of transaction
        VertexList list = vertices_.at(u);
        for (VertexList::iterator it=vertices_[u].begin(); it!=vertices_[u].end(); ++it) {
            if (it->first == v) {
                it->second += increment;
                return;
            }
        }
    }
    bool isEdge (int u, int v) const {
        // returns true if edge between vertices u and v exists
        for (VertexList::const_iterator it = vertices_[u].begin(); it != vertices_[u].end(); ++it) {
            if (it->first == v) {
                return true;
            }
        }
        return false;
    }
    bool isEdge (int u, int v, int &w) const {
        for (VertexList::const_iterator it = vertices_[u].begin(); it != vertices_[u].end(); ++it) {
            if (it->first == v) {
                w = it->second;
                return true;
            }
        }
        return false;
    }

    VertexList::const_iterator begin(int u) const {
        return vertices_[u].begin();
    }

    VertexList::const_iterator end(int u) const {
        return vertices_[u].end();
    } 

    void addEdge (int u, int v, int w=1) {
        if (u > numVertices() || v > numVertices()) {
            throw "Graph::addEdge given vertex larger than graph size";
        }

        std::pair<int,int> edge(v,w);
        vertices_[u].push_front(edge);

        // undirected have both.
        if (!directed_) {
            std::pair<int, int> edgeR (u,w);
            vertices_[v].push_front(edgeR);
        }
    }
    bool removeEdge (int u, int v) {
        bool found = false;
        for (VertexList::const_iterator it=vertices_[u].begin(); it!=vertices_[u].end(); ++it) {
            if (it->first == v) {
	        vertices_[u].remove(*it);
	        found = true;
	        break;
            }
        }

        if (!found) return false;

        if (!directed_) {
            for (VertexList::const_iterator it=vertices_[v].begin(); it!=vertices_[v].end(); ++it) {
	        if (it->first == u) {
	            vertices_[v].remove(*it);
	            break;
	        }
            }
        }

        return true;
    }
};

#endif  // _Graph_h_
