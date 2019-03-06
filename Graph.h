#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <deque>
#include <iostream>
#include <functional>
using namespace std;

template<typename T>
struct Edge {
    T source;
    T dest;
    double cost;
    Edge() {}
    Edge(T source, T dest, double cost) : source(source), dest(dest), cost(cost) {}
    virtual ~Edge() {}
};

template<typename T>
struct UndirectedEdge : public Edge<T> {
    bool operator==(const UndirectedEdge<T>& rhs) const;
    /* friend ostream& operator<< <T> (ostream& out, const UndirectedEdge<T>& edge); */
    UndirectedEdge() {}
    UndirectedEdge(T source, T dest, double cost) : Edge<T>(source, dest, cost) {}
};

template<typename T>
bool UndirectedEdge<T>::operator==(const UndirectedEdge<T>& rhs) const
{
    return (this->source == rhs.source || this->source == rhs.dest) &&
        (this->dest == rhs.source || this->dest == rhs.dest) &&
        this->cost == rhs.cost;
}

namespace std {
    template<typename T> struct hash<UndirectedEdge<T> > {
        size_t operator()(const UndirectedEdge<T>& edge) const
        {
            return (((hash<T>()(edge.source) ^ hash<T>()(edge.dest)) << 1 ^ hash<double>()(edge.cost)) << 1) >> 1;
        }
    };
}

template<typename T>
ostream& operator<<(ostream& out, const UndirectedEdge<T>& edge)
{
    out << edge.source << " <-> " << edge.dest;
    return out;
}

template<typename T>
class Graph
{
    protected:
        unordered_set<T> verts;
        unordered_map<T, vector<Edge<T> > > adjList;
    public:
        Graph();
        virtual ~Graph();
        int numVertices() const;
        virtual int numEdges() const = 0;
        bool addVertex(const T& x);
        T delVertex(const T& x);
        virtual bool addEdge(const T& u, const T& v, double cost) = 0;
        unordered_set<T> getVerts() const;
        vector<Edge<T> > getEdges(T v) const;
        static bool isConnected(const Graph<T>& g);
};

template<typename T>
T Graph<T>::delVertex(const T& x)
{
    T answer = *(verts.find(x));
    adjList.erase(x);
    verts.erase(x);
    return answer;
}

template<typename T>
Graph<T>::Graph()
{
}

template<typename T>
Graph<T>::~Graph()
{
}

template<typename T>
int Graph<T>::numVertices() const
{
    return verts.size();
}

template<typename T>
bool Graph<T>::addVertex(const T& x)
{
    bool inserted = verts.insert(x).second;
    if(inserted) adjList[x];
    return inserted;
}

template<typename T>
unordered_set<T> Graph<T>::getVerts() const
{
    return verts;
}

template<typename T>
vector<Edge<T> > Graph<T>::getEdges(T v) const
{
    return adjList.at(v);
}

template<typename T>
bool Graph<T>::isConnected(const Graph<T>& g)
{
    unordered_set<T> verts = g.getVerts();
    auto v = verts.begin();

    deque<T> unvisited;
    unordered_set<T> visited;

    T root = *v;

    unvisited.push_back(root);

    while(!unvisited.empty()) {
        T cur_node = unvisited.front();
        unvisited.pop_front();
        visited.insert(cur_node);
        vector<Edge<T> > adjs = g.getEdges(cur_node);
        for(Edge<T> e : adjs) {
            T neighbor = e.dest;
            if(visited.find(neighbor) == visited.end()) {
                unvisited.push_back(neighbor);
            }
        }
    }
    if(visited.size() == verts.size()) return true;
    return false;
}

template<typename T> class UndirectedGraph;
template<typename T> ostream& operator<<(ostream& out, const UndirectedGraph<T>& graph);

template<typename T>
class UndirectedGraph : public Graph<T>
{
    private:
        unordered_set<UndirectedEdge<T> > edges;
    public:
        UndirectedGraph();
        int numEdges() const;
        bool addEdge(const T& u, const T& v, double cost);
        unordered_set<UndirectedEdge<T> > allEdges() const;

        friend ostream& operator<< <T> (ostream& out, const UndirectedGraph<T>& graph);
};

template<typename T>
UndirectedGraph<T>::UndirectedGraph()
{
}

template<typename T>
int UndirectedGraph<T>::numEdges() const
{
    return edges.size();
}

template<typename T>
bool UndirectedGraph<T>::addEdge(const T& u, const T& v, double cost)
{
    UndirectedEdge<T> edge(u, v, cost);
    if(edges.find(edge) != edges.end()) return false;
    if(Graph<T>::verts.find(u) == Graph<T>::verts.end() || Graph<T>::verts.find(v) == Graph<T>::verts.end()) return false;
    Graph<T>::adjList[u].push_back(UndirectedEdge<T>(u, v, cost));
    Graph<T>::adjList[v].push_back(UndirectedEdge<T>(v, u, cost));
    edges.insert(edge);
    return true;
}

template<typename T>
unordered_set<UndirectedEdge<T> > UndirectedGraph<T>::allEdges() const
{
    return edges;
}

template<typename T>
ostream& operator<<(ostream& out, const UndirectedGraph<T>& graph)
{
    out << "G = ({";
    for(auto it = graph.verts.begin(); it != graph.verts.end(); it++) {
        if(it != graph.verts.begin()) out << ", ";
        out << *it;
    }
    out << "}, {";
    for(auto it = graph.edges.begin(); it != graph.edges.end(); it++) {
        if(it != graph.edges.begin()) out << ", ";
        out << "{";
        out << it->source << ", " << it->dest << "(" << it->cost << ")";
        out << "}";
    }
    out << "})";
    return out;
}

#endif
